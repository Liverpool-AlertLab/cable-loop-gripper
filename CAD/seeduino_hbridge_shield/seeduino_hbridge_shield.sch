EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Seeeduino_XIAO:SeeeduinoXIAO U1
U 1 1 608B027A
P 7450 2650
F 0 "U1" H 7425 1711 50  0000 C CNN
F 1 "SeeeduinoXIAO" H 7425 1620 50  0000 C CNN
F 2 "Seeeduino XIAO KICAD:Seeeduino XIAO-MOUDLE14P-2.54-21X17.8MM" H 7100 2850 50  0001 C CNN
F 3 "" H 7100 2850 50  0001 C CNN
	1    7450 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2500 3950 2500
Wire Wire Line
	8250 3100 8400 3100
Wire Wire Line
	8250 2350 8400 2350
$Comp
L SN754410:SN754410 IC1
U 1 1 608BEB59
P 7350 5450
F 0 "IC1" H 7400 6531 50  0000 C CNN
F 1 "SN754410" H 7400 6440 50  0000 C CNN
F 2 "DIP16" H 7350 5450 50  0000 L BNN
F 3 "" H 7350 5450 50  0001 L BNN
	1    7350 5450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male SerialConnector1
U 1 1 608BAEAB
P 3750 2500
F 0 "SerialConnector1" H 3858 2681 50  0000 C CNN
F 1 "Conn_01x02_Male" H 3858 2590 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3858 2589 50  0001 C CNN
F 3 "~" H 3750 2500 50  0001 C CNN
	1    3750 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2600 3950 2600
$Comp
L Connector:Conn_01x02_Male PowerConnector1
U 1 1 608C0014
P 3750 2900
F 0 "PowerConnector1" H 3858 3081 50  0000 C CNN
F 1 "Conn_01x02_Male" H 3858 2990 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3750 2900 50  0001 C CNN
F 3 "~" H 3750 2900 50  0001 C CNN
	1    3750 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3000 4200 3000
Wire Wire Line
	3950 2900 4200 2900
Text GLabel 4200 2900 2    50   Input ~ 0
6V
Text GLabel 4200 3000 2    50   Input ~ 0
GND
Wire Wire Line
	8250 2200 8400 2200
Text GLabel 8400 2200 2    50   Input ~ 0
5V
Text GLabel 8400 2350 2    50   Input ~ 0
GND
NoConn ~ 7200 4750
Wire Wire Line
	7350 4550 7350 4150
Wire Wire Line
	7350 4150 7850 4150
Wire Wire Line
	7450 4550 7450 4250
Wire Wire Line
	7450 4250 7850 4250
Text GLabel 7850 4150 2    50   Input ~ 0
5V
Text GLabel 7850 4250 2    50   Input ~ 0
6V
Wire Wire Line
	7150 5950 7150 6150
Wire Wire Line
	7150 6150 7250 6150
Wire Wire Line
	7450 6150 7450 5950
Wire Wire Line
	7350 5950 7350 6150
Connection ~ 7350 6150
Wire Wire Line
	7350 6150 7450 6150
Wire Wire Line
	7250 5950 7250 6150
Connection ~ 7250 6150
Wire Wire Line
	7250 6150 7350 6150
Wire Wire Line
	7450 6150 8400 6150
Connection ~ 7450 6150
Text GLabel 8800 6150 2    50   Input ~ 0
GND
$Comp
L Connector:Conn_01x06_Male MotorConnector1
U 1 1 608C841D
P 3750 3600
F 0 "MotorConnector1" H 3858 3981 50  0000 C CNN
F 1 "Conn_01x06_Male" H 3858 3890 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 3750 3600 50  0001 C CNN
F 3 "~" H 3750 3600 50  0001 C CNN
	1    3750 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3600 4200 3600
Wire Wire Line
	3950 3900 4200 3900
Text GLabel 4200 3600 2    50   Input ~ 0
GND
Text GLabel 4200 3900 2    50   Input ~ 0
5V
$Comp
L Connector:Conn_01x04_Male SingletactConnector1
U 1 1 608CCD40
P 3750 4350
F 0 "SingletactConnector1" H 3858 4631 50  0000 C CNN
F 1 "Conn_01x04_Male" H 3858 4540 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 3750 4350 50  0001 C CNN
F 3 "~" H 3750 4350 50  0001 C CNN
	1    3750 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 4250 4200 4250
Text GLabel 4200 4250 2    50   Input ~ 0
5V
Wire Wire Line
	6500 2950 6600 2950
Wire Wire Line
	6600 2800 6500 2800
Wire Wire Line
	6600 2650 6500 2650
Wire Wire Line
	6600 2500 6500 2500
Text GLabel 6500 2500 0    50   Input ~ 0
EncoderA
Text GLabel 6500 2650 0    50   Input ~ 0
EncoderB
Wire Wire Line
	3950 3700 4200 3700
Wire Wire Line
	3950 3800 4200 3800
Text GLabel 4200 3700 2    50   Input ~ 0
EncoderA
Text GLabel 4200 3800 2    50   Input ~ 0
EncoderB
Wire Wire Line
	6500 5550 6750 5550
Wire Wire Line
	6500 5450 6750 5450
$Comp
L Device:R Rsck1
U 1 1 60918B91
P 4150 4800
F 0 "Rsck1" H 4220 4846 50  0000 L CNN
F 1 "4.7k" H 4220 4755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 4080 4800 50  0001 C CNN
F 3 "~" H 4150 4800 50  0001 C CNN
	1    4150 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R 4.7k1
U 1 1 6091A335
P 4000 4800
F 0 "4.7k1" H 4070 4846 50  0000 L CNN
F 1 "Rsck" H 4070 4755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3930 4800 50  0001 C CNN
F 3 "~" H 4000 4800 50  0001 C CNN
	1    4000 4800
	1    0    0    -1  
$EndComp
Text GLabel 3900 5150 0    50   Input ~ 0
3.3v
Text GLabel 8400 2500 2    50   Input ~ 0
3.3v
Wire Wire Line
	8250 2500 8400 2500
Wire Wire Line
	3900 5150 4000 5150
Wire Wire Line
	4150 5150 4150 4950
Wire Wire Line
	4000 5150 4000 4950
Connection ~ 4000 5150
Wire Wire Line
	4000 5150 4150 5150
Wire Wire Line
	4000 4650 4000 4550
Text GLabel 6500 5550 0    50   Input ~ 0
MotorB
Text GLabel 6500 5450 0    50   Input ~ 0
MotorA
Wire Wire Line
	4200 3500 3950 3500
Wire Wire Line
	4200 3400 3950 3400
Text GLabel 4200 3500 2    50   Input ~ 0
MotorB
Text GLabel 4200 3400 2    50   Input ~ 0
MotorA
Wire Wire Line
	4200 4350 3950 4350
Text GLabel 4200 4350 2    50   Input ~ 0
GND
Wire Wire Line
	3950 4450 4150 4450
Wire Wire Line
	3950 4550 4000 4550
Connection ~ 4000 4550
Wire Wire Line
	4000 4550 4200 4550
Wire Wire Line
	4150 4650 4150 4450
Connection ~ 4150 4450
Wire Wire Line
	4150 4450 4200 4450
Text GLabel 4200 4550 2    50   Input ~ 0
SDA
Text GLabel 4200 4450 2    50   Input ~ 0
SCL
Wire Wire Line
	8050 5050 8400 5050
Wire Wire Line
	8400 5050 8400 6150
Connection ~ 8400 6150
Wire Wire Line
	8400 6150 8800 6150
Text GLabel 6500 2800 0    50   Input ~ 0
SDA
Text GLabel 6500 2950 0    50   Input ~ 0
SCL
Text GLabel 6500 3100 0    50   Input ~ 0
TX
Text GLabel 8400 3100 2    50   Input ~ 0
RX
Wire Wire Line
	6600 3100 6500 3100
Wire Wire Line
	7350 3500 7350 3800
Wire Wire Line
	7350 3800 8350 3800
Text GLabel 8350 3800 2    50   Input ~ 0
6V
Text GLabel 8400 2800 2    50   Input ~ 0
MotorAcontrol
Text GLabel 8400 2950 2    50   Input ~ 0
MotorBcontrol
Text GLabel 8400 2650 2    50   Input ~ 0
PWM
Wire Wire Line
	8250 2650 8400 2650
Wire Wire Line
	8250 2800 8400 2800
Wire Wire Line
	8250 2950 8400 2950
Text GLabel 6500 5050 0    50   Input ~ 0
PWM
Wire Wire Line
	6500 5250 6750 5250
Wire Wire Line
	6500 5150 6750 5150
Wire Wire Line
	6750 5050 6500 5050
Text GLabel 8300 3650 2    50   Input ~ 0
GND
Wire Wire Line
	7550 3500 7550 3650
Wire Wire Line
	7550 3650 8300 3650
Text GLabel 4250 2500 2    50   Input ~ 0
TX
Text GLabel 4250 2600 2    50   Input ~ 0
RX
Text GLabel 6500 5250 0    50   Input ~ 0
MotorBcontrol
Text GLabel 6500 5150 0    50   Input ~ 0
MotorAcontrol
$EndSCHEMATC
