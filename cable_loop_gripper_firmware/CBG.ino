#include <FlashStorage.h>
#include <AutoPID.h>
#include <Wire.h>

#define EncoderA    3
#define EncoderB    2
#define MotorA      10
#define MotorB      9
#define PWMMotor    8

#define BAUD        115200
#define MaxBuff     64

#define COM         Serial1
#define MAX_R       40
#define MIN_R       8

enum controlApproach {
  FORCE    = 0,
  RADIUS   = 1
};

typedef struct {
  bool valid;
  double radiusKp;
  double radiusKi;
  double radiusKd;
  double forceKp;
  double forceKi;
  double forceKd;
  double deadzone;
} ControlParameters;

/////////////////////////Global Variables////////////////////////

ControlParameters parameters;

double pollingRatio = 100;
double T0;
double T1;

double radius;
double targetRadius;

double force;
double targetForce;

bool radiusSetpointFlag;
bool forceSetpointFlag;

double control;
int motorSpeed;

char buff[MaxBuff];
int Ibuff = 0;

int controlState = RADIUS;
bool debugState = false;

double ticks;

short address = 0x04;

////////////////////////Method Definitions////////////////////////

void initMotor();
void motorDrive();

void processCommand();

void debugPrint();
void ROSprint();

int parseInteger(char code, float val);
float parseFloating(char code, float val);

short readSensor();

void Arising_ISR();
void Afalling_ISR();
void Brising_ISR();
void Bfalling_ISR();

////////////////////////Object Instantiations////////////////////////

FlashStorage(my_flash_store, ControlParameters);

AutoPID radiusControl(&radius, &targetRadius, &control, -1, 1, 1, 0, 0);
AutoPID forceControl(&force,  &targetForce, &control, -1, 1, 1, 0, 0);

////////////////////////Setup////////////////////////

void setup()
{
  COM.begin(BAUD);

  Wire.begin();

  parameters = my_flash_store.read();

  if (!parameters.valid) {
    resetParameters();
  }

  radiusControl.setGains(parameters.radiusKp, parameters.radiusKi, parameters.radiusKd);
  radiusControl.setOutputRange(-255 + parameters.deadzone, 255 - parameters.deadzone);

  forceControl.setGains(parameters.forceKp, parameters.forceKi, parameters.forceKd);
  forceControl.setOutputRange(-255 + parameters.deadzone, 255 - parameters.deadzone);

  radiusControl.setTimeStep(pollingRatio);

  forceControl.setTimeStep(pollingRatio);

  initMotor();

  radius = 8;
  ticks = (radius / 20) * (12 * 291 / 1.5);

  force = (double) readSensor();

  targetRadius = 8;
  targetForce = 0;

  radiusSetpointFlag = 0;
  forceSetpointFlag = 0;

  void Arising_ISR();
  void Afalling_ISR();
  void Brising_ISR();
  void Bfalling_ISR();

  attachInterrupt(digitalPinToInterrupt(EncoderA), Arising_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderA), Afalling_ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(EncoderB), Brising_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderB), Bfalling_ISR, FALLING);

  T0 = millis();
}

////////////////////////Main Loop////////////////////////

void loop()
{
  if (COM.available())
  {
    char c = COM.read();

    if (Ibuff < MaxBuff)
    {
      buff[Ibuff++] = c;
    }
    // if we got a return character (\n) the message is done.
    if (c == '\n')
    {
      //COM.print(F("\r\n")); // optional: send back a return for debugging

      // strings must end with a \0.
      buff[Ibuff] = 0;
      processCommand(); // do something with the command
      Ibuff = 0;
    }
  }

  T1 = millis();
  if (T1 - T0 >= pollingRatio)
  {
    radius = ticks * 20 / (12 * 291 / 1.5);

    if (radius > MAX_R + 1)
    {
      controlState = RADIUS;
      targetRadius = MAX_R;
    } else if (radius < MIN_R - 1)
    {
      controlState = RADIUS;
      targetRadius = MIN_R;
    }

    force = map((double)readSensor(), 260, 767, 0, 100);

    switch (controlState)
    {
      case RADIUS:
        motorSpeed = control;
        break;
      case FORCE:
        motorSpeed = -control;
        break;
    }

    motorDrive();

    if (debugState)
    {
      debugPrint();
    } else {
      ROSprint();
    }
    T0 = T1;
  }
  if (controlState == RADIUS)
  {
    radiusControl.run();
    if (radiusControl.atSetPoint(1))
    {
      radiusSetpointFlag = 1;
    } else {
      radiusSetpointFlag = 0;
    }
    forceControl.stop();

  }
  else if (controlState == FORCE)
  {
    forceControl.run();
    radiusControl.stop();
    if (forceControl.atSetPoint(2))
    {
      forceSetpointFlag = 1;
    } else {
      forceSetpointFlag = 0;
    }
    //COM.println(control);
  }

}

////////////////////////Methods////////////////////////

void initMotor()
{
  pinMode(MotorA, OUTPUT);
  pinMode(MotorB, OUTPUT);
  pinMode(PWMMotor, OUTPUT);

  digitalWrite(MotorA, LOW);
  digitalWrite(MotorB, LOW);
  analogWrite(PWMMotor, 0);
}

void motorDrive()
{
  if (motorSpeed < -1 || motorSpeed == -1)
  {
    digitalWrite(MotorA, LOW);
    digitalWrite(MotorB, HIGH);
    analogWrite(PWMMotor, (motorSpeed * -1) + parameters.deadzone);
  }
  else if (motorSpeed > 1 || motorSpeed == 1)
  {
    digitalWrite(MotorA, HIGH);
    digitalWrite(MotorB, LOW);
    analogWrite(PWMMotor, motorSpeed + parameters.deadzone);
  }
  else
  {
    digitalWrite(MotorA, LOW);
    digitalWrite(MotorB, LOW);
    analogWrite(PWMMotor, 0);
  }
}

void debugPrint()
{
  COM.print("postion: ");
  COM.print(radius);
  COM.print("\t target displacment: ");
  COM.print(targetRadius);
  COM.print("\t force: ");
  COM.print(force);
  COM.print("\t target force: ");
  COM.print(targetForce);
  COM.print("\t control: ");
  COM.println(control);
  COM.print("\t speed: ");
  COM.println(motorSpeed);
}

void ROSprint()
{
  COM.print(radius);
  COM.print(" - ");
  COM.print(targetRadius);
  COM.print(" - ");
  COM.print(force);
  COM.print(" - ");
  COM.print(targetForce);
  COM.print(" - ");
  COM.print(control);
  COM.print(" - ");
  COM.print(radiusSetpointFlag);
  COM.print(" - ");
  COM.println(forceSetpointFlag);
}
void processCommand()
{
  int cmdI = parseInteger('S', -1);
  switch (cmdI)
  {
    case 0:
      controlState = FORCE;
      //COM.println("Switched to force control");
      break;
    case 1:
      controlState = RADIUS;
      //COM.println("Switched to Position control");
      break;
    default: break;
  }

  // look for commands that start with 'M'
  float cmdF = parseFloating('P', -1);
  if (cmdF != -1)
  {
    targetRadius = (double) cmdF;
    if (targetRadius > MAX_R)
    {
      targetRadius = MAX_R;
    }
    //COM.println(targetRadius);
  }
  cmdF = parseFloating('F', -1);
  if (cmdF != -1)
  {
    targetForce = (double) cmdF;
    //COM.println(targetForce);
  }
  cmdI = parseInteger('D', -1);
  switch (cmdI)
  {
    case 0:
      debugState = false;
      COM.println("Debugging mode is switched off");
      break;
    case 1:
      debugState = true;
      COM.println("Debugging mode is switched on");
      break;
    default: break;
  }
  cmdI = parseInteger('R', -1);
  switch (cmdI)
  {
    case 0:
      COM.println("Reset control system");
      resetPID();
      break;
    case 1:
      COM.println("Reset control system parameters");
      resetPID();
      resetParameters();
      break;
  }
  cmdI = parseInteger('T', -1);
  switch (cmdI)
  {
    case 0:
      my_flash_store.write(parameters);
      COM.println("Position control");
      COM.print("Kp: ");
      COM.println(parameters.radiusKp);
      COM.print("Ki: ");
      COM.println(parameters.radiusKi);
      COM.print("Kd: ");
      COM.println(parameters.radiusKd);
      COM.println("Force control");
      COM.print("Kp: ");
      COM.println(parameters.forceKp);
      COM.print("Ki: ");
      COM.println(parameters.forceKi);
      COM.print("Kd: ");
      COM.println(parameters.forceKd);
      break;
    case 1:
      {
        float p = parseFloating('P', -1);
        if (p != -1)
        {
          parameters.radiusKp = p;
        }
        float i = parseFloating('I', -1);
        if (i != -1)
        {
          parameters.radiusKi = i;
        }
        float d = parseFloating('D', -1);
        if (d != -1)
        {
          parameters.radiusKd = d;
        }
        int k = parseFloating('K', -1);
        if (k != -1)
        {
          parameters.deadzone = k;
          radiusControl.setOutputRange(-255 + parameters.deadzone, 255 - parameters.deadzone);
          forceControl.setOutputRange(-255 + parameters.deadzone, 255 - parameters.deadzone);
        }
        radiusControl.setGains(parameters.radiusKp, parameters.radiusKi, parameters.radiusKd);
      }
      radiusControl.reset();
      COM.print("Kp: ");
      COM.println(parameters.radiusKp);
      COM.print("Ki: ");
      COM.println(parameters.radiusKi);
      COM.print("Kd: ");
      COM.println(parameters.radiusKd);
      break;
    case 2:
      {
        float p = parseFloating

                  ('P', -1);
        if (p != -1)
        {
          parameters.forceKp = p;
        }
        float i = parseFloating('I', -1);
        if (i != -1)
        {
          parameters.forceKi = i;
        }
        float d = parseFloating('D', -1);
        if (d != -1)
        {
          parameters.forceKd = d;
        }
        forceControl.setGains(parameters.radiusKp, parameters.radiusKi, parameters.radiusKd);
      }
      forceControl.reset();
      COM.print("Kp: ");
      COM.println(parameters.forceKp);
      COM.print("Ki: ");
      COM.println(parameters.forceKi);
      COM.print("Kd: ");
      COM.println(parameters.forceKd);
      break;
  }
  cmdF = parseFloating('O', -1);
  if (cmdF != -1)
  {
    resetPID();
    ticks = (cmdF / 20) * (12 * 291 / 1.5);
    targetRadius = cmdF;
  }
}


int parseInteger(char code, float val)
{
  char *ptr = buff; // start at the beginning of buffer
  while ((long)ptr > 1 && (*ptr) && (long)ptr < (long)buff + Ibuff)
  { // walk to the end
    if (*ptr == code)
    { // if you find code on your walk,
      return atoi(ptr + 1); // convert the digits that follow into a int and return it
    }
    ptr = strchr(ptr, ' ') + 1; // take a step from here to the letter after the next space
  }
  return val;  // end reached, nothing found, return default val.
}

float parseFloating(char code, float val)
{
  char *ptr = buff; // start at the beginning of buffer
  while ((long)ptr > 1 && (*ptr) && (long)ptr < (long)buff + Ibuff)
  { // walk to the end
    if (*ptr == code)
    { // if you find code on your walk,
      return atof(ptr + 1); // convert the digits that follow into a float and return it
    }
    ptr = strchr(ptr, ' ') + 1; // take a step from here to the letter after the next space
  }
  return val;  // end reached, nothing found, return default val.
}

short readSensor()
{
  byte i2cPacketLength = 6;//i2c packet length. Just need 6 bytes from each slave
  byte outgoingI2CBuffer[3];//outgoing array buffer
  byte incomingI2CBuffer[6];//incoming array buffer

  outgoingI2CBuffer[0] = 0x01;//I2c read command
  outgoingI2CBuffer[1] = 128;//Slave data offset
  outgoingI2CBuffer[2] = i2cPacketLength;//require 6 bytes

  Wire.beginTransmission(address); // transmit to device
  Wire.write(outgoingI2CBuffer, 3);// send out command
  byte error = Wire.endTransmission(); // stop transmitting and check slave status
  if (error != 0) return -1; //if slave not exists or has error, return -1
  Wire.requestFrom(address, i2cPacketLength);//require 6 bytes from slave

  byte incomeCount = 0;
  while (incomeCount < i2cPacketLength)    // slave may send less than requested
  {
    if (Wire.available())
    {
      incomingI2CBuffer[incomeCount] = Wire.read(); // receive a byte as character
      incomeCount++;
    }
    else
    {
      delayMicroseconds(10); //Wait 10us
    }
  }

  short rawData = (incomingI2CBuffer[4] << 8) + incomingI2CBuffer[5]; //get the raw data

  return rawData;
}

void resetParameters()
{
  parameters.valid = true;
  parameters.radiusKp = 1.0;
  parameters.radiusKi = 0.0;
  parameters.radiusKd = 0.0;
  parameters.forceKp = 2.2;
  parameters.forceKi = 1.5;
  parameters.forceKd = 0.0;
  parameters.deadzone = 70;
  my_flash_store.write(parameters);
}

void resetPID()
{
  //radius = 0;
  targetRadius = 8;
  targetForce = 0;
  radiusControl.reset();
  forceControl.reset();
}
////////////////////////Interrupt Service Routines////////////////////////

void Arising_ISR()
{
  if (digitalRead(EncoderB))
  {
    ticks++;
  } else {
    ticks--;
  }
}

void Afalling_ISR()
{
  if (digitalRead(EncoderB))
  {
    ticks--;
  } else {
    ticks++;
  }
}

void Brising_ISR()
{
  if (digitalRead(EncoderA))
  {
    ticks--;
  } else {
    ticks++;
  }
}

void Bfalling_ISR()
{
  if (digitalRead(EncoderA))
  {
    ticks++;
  } else {
    ticks--;
  }
}
