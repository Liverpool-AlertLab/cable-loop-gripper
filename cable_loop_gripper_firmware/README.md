# cable_loop_gripper_firmware

Firmware running on the SEEEDUINO xiao inside the cable loop gripper

Follow the steps in this guide (https://wiki.seeedstudio.com/Seeeduino-XIAO/) to get the SEEEDUINO microcontroller working with the arduino IDE.

The following libraries are required to compile the code:

FlashStorage https://github.com/cmaglie/FlashStorage
AutoPID      https://github.com/r-downing/AutoPID

this code is compatible with the ros package cable_loop_gripper available here https://github.com/itsameWolf/cable_loop_gripper

## G codes

List of all the codes supported by the gripper

### S

Set which control loop to use. <br />
Takes: 

- 0 : Force.
- 1 : Loop size.

### P

Set the target size of the loop. <br />
Takes: Float input.

### F

Set the target gripping force. <br />
Takes: Float from 0.0 to 10.0.

### R

Reset the control system. <br />
Takes:
- 0 : Reset control system state.
- 1 : Reset the control loop parameters.

### T

Access the control system parameters. <br />
Takes: 
- 0 : Return the current values for Kp, Ki, Kd for both loop size and force loops.
- 1 : Modify the loop size Kp, Ki, Kd. <br />
  takes:
  - P : Kp Float. 
  - I : Ki Float.
  - D : Kd Float.
  - K : motor deadzone Float.
- 2 : Modify the force Kp, Ki, Kd. <br />
  takes:
  - P : Kp Float.
  - I : Ki Float.
  - D : Kd Float
  
### O 

Set Loop curent size. <br />
Takes: Float
