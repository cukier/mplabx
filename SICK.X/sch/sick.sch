EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:w_relay
LIBS:sick-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Encoder SICK"
Date "2017-03-20"
Rev "0"
Comp "Krebsfer Industrial LTDA"
Comment1 "Engenheiro Eletrico"
Comment2 "Mauricio Cukier"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LM7805CT U2
U 1 1 5894BAA8
P 2350 1050
F 0 "U2" H 2150 1250 50  0000 C CNN
F 1 "LM7805CT" H 2350 1250 50  0000 L CNN
F 2 "TO-220" H 2350 1150 50  0000 C CIN
F 3 "" H 2350 1050 50  0000 C CNN
	1    2350 1050
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P1
U 1 1 5894BC09
P 700 1050
F 0 "P1" H 700 1200 50  0000 C CNN
F 1 "PWR" V 800 1050 50  0000 C CNN
F 2 "" H 700 1050 50  0000 C CNN
F 3 "" H 700 1050 50  0000 C CNN
	1    700  1050
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 5894BC4E
P 1000 1200
F 0 "#PWR3" H 1000 1200 30  0001 C CNN
F 1 "GND" H 1000 1130 30  0001 C CNN
F 2 "" H 1000 1200 60  0000 C CNN
F 3 "" H 1000 1200 60  0000 C CNN
	1    1000 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 1200 1000 1100
Wire Wire Line
	1000 1100 900  1100
$Comp
L D_Small D1
U 1 1 5894BD8D
P 1200 1000
F 0 "D1" H 1150 1080 50  0000 L CNN
F 1 "1n4007" H 1050 920 50  0000 L CNN
F 2 "" V 1200 1000 50  0000 C CNN
F 3 "" V 1200 1000 50  0000 C CNN
	1    1200 1000
	-1   0    0    1   
$EndComp
Wire Wire Line
	1100 1000 900  1000
Wire Wire Line
	1300 1000 1950 1000
$Comp
L CP C3
U 1 1 5894BEA1
P 1450 1250
F 0 "C3" H 1475 1350 50  0000 L CNN
F 1 "470uF" H 1475 1150 50  0000 L CNN
F 2 "" H 1488 1100 50  0000 C CNN
F 3 "" H 1450 1250 50  0000 C CNN
	1    1450 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1100 1450 1000
Connection ~ 1450 1000
$Comp
L GND #PWR5
U 1 1 5894BF19
P 1450 1450
F 0 "#PWR5" H 1450 1450 30  0001 C CNN
F 1 "GND" H 1450 1380 30  0001 C CNN
F 2 "" H 1450 1450 60  0000 C CNN
F 3 "" H 1450 1450 60  0000 C CNN
	1    1450 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1450 1450 1400
$Comp
L C C4
U 1 1 5894BFD4
P 1750 1250
F 0 "C4" H 1775 1350 50  0000 L CNN
F 1 "100nF" H 1775 1150 50  0000 L CNN
F 2 "" H 1788 1100 50  0000 C CNN
F 3 "" H 1750 1250 50  0000 C CNN
	1    1750 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR7
U 1 1 5894C00E
P 1750 1450
F 0 "#PWR7" H 1750 1450 30  0001 C CNN
F 1 "GND" H 1750 1380 30  0001 C CNN
F 2 "" H 1750 1450 60  0000 C CNN
F 3 "" H 1750 1450 60  0000 C CNN
	1    1750 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1450 1750 1400
$Comp
L GND #PWR9
U 1 1 5894C226
P 2350 1400
F 0 "#PWR9" H 2350 1400 30  0001 C CNN
F 1 "GND" H 2350 1330 30  0001 C CNN
F 2 "" H 2350 1400 60  0000 C CNN
F 3 "" H 2350 1400 60  0000 C CNN
	1    2350 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 1400 2350 1300
$Comp
L CP C7
U 1 1 5894C50E
P 2900 1250
F 0 "C7" H 2925 1350 50  0000 L CNN
F 1 "470uF" H 2925 1150 50  0000 L CNN
F 2 "" H 2938 1100 50  0000 C CNN
F 3 "" H 2900 1250 50  0000 C CNN
	1    2900 1250
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 5894C5A2
P 3200 1250
F 0 "C8" H 3225 1350 50  0000 L CNN
F 1 "100nF" H 3225 1150 50  0000 L CNN
F 2 "" H 3238 1100 50  0000 C CNN
F 3 "" H 3200 1250 50  0000 C CNN
	1    3200 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR12
U 1 1 5894C5F7
P 2900 1450
F 0 "#PWR12" H 2900 1450 30  0001 C CNN
F 1 "GND" H 2900 1380 30  0001 C CNN
F 2 "" H 2900 1450 60  0000 C CNN
F 3 "" H 2900 1450 60  0000 C CNN
	1    2900 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 1450 2900 1400
$Comp
L GND #PWR15
U 1 1 5894C633
P 3200 1450
F 0 "#PWR15" H 3200 1450 30  0001 C CNN
F 1 "GND" H 3200 1380 30  0001 C CNN
F 2 "" H 3200 1450 60  0000 C CNN
F 3 "" H 3200 1450 60  0000 C CNN
	1    3200 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 1450 3200 1400
Wire Wire Line
	3200 950  3200 1100
Wire Wire Line
	2750 1000 3200 1000
Connection ~ 2900 1000
$Comp
L +5V #PWR14
U 1 1 5894C723
P 3200 950
F 0 "#PWR14" H 3200 1040 20  0001 C CNN
F 1 "+5V" H 3200 1040 30  0000 C CNN
F 2 "" H 3200 950 60  0000 C CNN
F 3 "" H 3200 950 60  0000 C CNN
	1    3200 950 
	1    0    0    -1  
$EndComp
Connection ~ 3200 1000
$Comp
L CONN_01X05 P3
U 1 1 5894E84D
P 5100 1100
F 0 "P3" H 5100 1400 50  0000 C CNN
F 1 "ISCP" V 5200 1100 50  0000 C CNN
F 2 "" H 5100 1100 50  0000 C CNN
F 3 "" H 5100 1100 50  0000 C CNN
	1    5100 1100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5300 1000 5750 1000
Wire Wire Line
	5300 1100 5900 1100
Text Label 5750 900  0    60   ~ 0
MCLR
NoConn ~ 5750 1000
$Comp
L GND #PWR24
U 1 1 5894EF0E
P 5900 1200
F 0 "#PWR24" H 5900 1200 30  0001 C CNN
F 1 "GND" H 5900 1130 30  0001 C CNN
F 2 "" H 5900 1200 60  0000 C CNN
F 3 "" H 5900 1200 60  0000 C CNN
	1    5900 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 1100 5900 1200
Text Label 6250 1900 0    60   ~ 0
PGC
Text Label 6250 1550 0    60   ~ 0
PGD
$Comp
L CONN_01X04 P2
U 1 1 58951663
P 3750 1050
F 0 "P2" H 3750 1300 50  0000 C CNN
F 1 "ENCODER" V 3850 1050 50  0000 C CNN
F 2 "" H 3750 1050 50  0000 C CNN
F 3 "" H 3750 1050 50  0000 C CNN
	1    3750 1050
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR21
U 1 1 589516DA
P 4600 950
F 0 "#PWR21" H 4600 950 30  0001 C CNN
F 1 "GND" H 4600 880 30  0001 C CNN
F 2 "" H 4600 950 60  0000 C CNN
F 3 "" H 4600 950 60  0000 C CNN
	1    4600 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 950  4600 900 
Wire Wire Line
	4600 900  3950 900 
$Comp
L LM7805CT U5
U 1 1 58951982
P 7850 1300
F 0 "U5" H 7650 1500 50  0000 C CNN
F 1 "LM7805CT" H 7850 1500 50  0000 L CNN
F 2 "TO-220" H 7850 1400 50  0000 C CIN
F 3 "" H 7850 1300 50  0000 C CNN
	1    7850 1300
	1    0    0    -1  
$EndComp
Text Label 1500 1000 0    60   ~ 0
PWR_LINE
Text Label 6600 1250 0    60   ~ 0
PWR_LINE
$Comp
L +5VD #PWR36
U 1 1 58952900
P 8400 1200
F 0 "#PWR36" H 8400 1150 20  0001 C CNN
F 1 "+5VD" H 8400 1300 30  0000 C CNN
F 2 "" H 8400 1200 60  0000 C CNN
F 3 "" H 8400 1200 60  0000 C CNN
	1    8400 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1000 4500 1000
Wire Wire Line
	3950 1100 4500 1100
Wire Wire Line
	3950 1200 4650 1200
$Comp
L Q_NPN_BCE Q3
U 1 1 589536F7
P 7500 3000
F 0 "Q3" H 7800 3050 50  0000 R CNN
F 1 "2n2222" H 8000 2950 50  0000 R CNN
F 2 "" H 7700 3100 50  0000 C CNN
F 3 "" H 7500 3000 50  0000 C CNN
	1    7500 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR30
U 1 1 58953896
P 7600 3300
F 0 "#PWR30" H 7600 3300 30  0001 C CNN
F 1 "GND" H 7600 3230 30  0001 C CNN
F 2 "" H 7600 3300 60  0000 C CNN
F 3 "" H 7600 3300 60  0000 C CNN
	1    7600 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 3300 7600 3200
$Comp
L R R8
U 1 1 58953B71
P 7000 3000
F 0 "R8" V 7080 3000 50  0000 C CNN
F 1 "10k" V 7000 3000 50  0000 C CNN
F 2 "" V 6930 3000 50  0000 C CNN
F 3 "" H 7000 3000 50  0000 C CNN
	1    7000 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	7300 3000 7150 3000
Wire Wire Line
	6850 3000 6500 3000
$Comp
L R R10
U 1 1 58954004
P 7600 2450
F 0 "R10" V 7680 2450 50  0000 C CNN
F 1 "10k" V 7600 2450 50  0000 C CNN
F 2 "" V 7530 2450 50  0000 C CNN
F 3 "" H 7600 2450 50  0000 C CNN
	1    7600 2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	7600 2600 7600 2800
Wire Wire Line
	7600 2200 7600 2300
Wire Wire Line
	7600 2700 8100 2700
Connection ~ 7600 2700
Text Label 7800 2700 0    60   ~ 0
FC
Text Label 6650 3000 0    60   ~ 0
TX
$Comp
L SP3485CP U4
U 1 1 589552C3
P 7600 4550
F 0 "U4" H 7300 4900 50  0000 L CNN
F 1 "SP3485CP" H 7700 4900 50  0000 L CNN
F 2 "DIP-8" H 7600 4550 50  0000 C CIN
F 3 "" H 7600 4550 50  0000 C CNN
	1    7600 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 4650 7200 4650
Wire Wire Line
	7150 4450 7150 4650
Wire Wire Line
	7150 4450 7200 4450
Wire Wire Line
	7150 4550 6900 4550
Connection ~ 7150 4550
$Comp
L R R6
U 1 1 58955DAA
P 6900 4350
F 0 "R6" V 6980 4350 50  0000 C CNN
F 1 "1k" V 6900 4350 50  0000 C CNN
F 2 "" V 6830 4350 50  0000 C CNN
F 3 "" H 6900 4350 50  0000 C CNN
	1    6900 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	7050 4350 7200 4350
$Comp
L R R7
U 1 1 589561A3
P 6900 4750
F 0 "R7" V 6980 4750 50  0000 C CNN
F 1 "1k" V 6900 4750 50  0000 C CNN
F 2 "" V 6830 4750 50  0000 C CNN
F 3 "" H 6900 4750 50  0000 C CNN
	1    6900 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	7050 4750 7200 4750
Wire Wire Line
	6750 4350 6450 4350
Wire Wire Line
	6750 4750 6450 4750
Text Label 6550 4750 0    60   ~ 0
TX
Text Label 6550 4350 0    60   ~ 0
RX
Text Label 6950 4550 0    60   ~ 0
FC
$Comp
L GND #PWR32
U 1 1 58957DF3
P 7600 5100
F 0 "#PWR32" H 7600 5100 30  0001 C CNN
F 1 "GND" H 7600 5030 30  0001 C CNN
F 2 "" H 7600 5100 60  0000 C CNN
F 3 "" H 7600 5100 60  0000 C CNN
	1    7600 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 5100 7600 4950
Wire Wire Line
	7600 3950 7600 4150
$Comp
L C C13
U 1 1 589587C6
P 7950 3800
F 0 "C13" H 7975 3900 50  0000 L CNN
F 1 "100nF" H 7975 3700 50  0000 L CNN
F 2 "" H 7988 3650 50  0000 C CNN
F 3 "" H 7950 3800 50  0000 C CNN
	1    7950 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR35
U 1 1 58958B2C
P 7950 4000
F 0 "#PWR35" H 7950 4000 30  0001 C CNN
F 1 "GND" H 7950 3930 30  0001 C CNN
F 2 "" H 7950 4000 60  0000 C CNN
F 3 "" H 7950 4000 60  0000 C CNN
	1    7950 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 4000 7950 3950
Wire Wire Line
	7950 3600 7950 3650
Wire Wire Line
	8000 4450 8350 4450
Wire Wire Line
	8000 4650 8350 4650
Text Label 8100 4450 0    60   ~ 0
A
Text Label 8100 4650 0    60   ~ 0
B
Text Label 4050 1100 0    60   ~ 0
A
Text Label 4050 1200 0    60   ~ 0
B
Text Label 4050 1000 0    60   ~ 0
VERMELHO
Text Label 4050 900  0    60   ~ 0
AZUL
Text Label 4250 1100 0    60   ~ 0
LILAS
Text Label 4250 1200 0    60   ~ 0
AMARELO
$Comp
L MAX232 U6
U 1 1 5895D0EF
P 9700 1750
F 0 "U6" H 9250 2600 50  0000 L CNN
F 1 "MAX232" H 9900 2600 50  0000 L CNN
F 2 "" H 9700 1750 50  0000 C CNN
F 3 "" H 9700 1750 50  0000 C CNN
	1    9700 1750
	1    0    0    -1  
$EndComp
$Comp
L CP C14
U 1 1 5895DA37
P 8900 1250
F 0 "C14" H 8925 1350 50  0000 L CNN
F 1 "10uF" H 8925 1150 50  0000 L CNN
F 2 "" H 8938 1100 50  0000 C CNN
F 3 "" H 8900 1250 50  0000 C CNN
	1    8900 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 1450 8900 1450
Wire Wire Line
	8900 1450 8900 1400
Wire Wire Line
	9100 1050 8900 1050
Wire Wire Line
	8900 1050 8900 1100
$Comp
L CP C15
U 1 1 5895E65F
P 8900 1750
F 0 "C15" H 8925 1850 50  0000 L CNN
F 1 "10uF" H 8925 1650 50  0000 L CNN
F 2 "" H 8938 1600 50  0000 C CNN
F 3 "" H 8900 1750 50  0000 C CNN
	1    8900 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 1550 8900 1550
Wire Wire Line
	8900 1550 8900 1600
Wire Wire Line
	9100 1950 8900 1950
Wire Wire Line
	8900 1950 8900 1900
$Comp
L CP C16
U 1 1 5895E7DE
P 10700 1650
F 0 "C16" H 10725 1750 50  0000 L CNN
F 1 "10uF" H 10725 1550 50  0000 L CNN
F 2 "" H 10738 1500 50  0000 C CNN
F 3 "" H 10700 1650 50  0000 C CNN
	1    10700 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10700 1500 10700 1450
Wire Wire Line
	10700 1450 10300 1450
$Comp
L CP C17
U 1 1 5895EB75
P 10700 2150
F 0 "C17" H 10725 2250 50  0000 L CNN
F 1 "10uF" H 10725 2050 50  0000 L CNN
F 2 "" H 10738 2000 50  0000 C CNN
F 3 "" H 10700 2150 50  0000 C CNN
	1    10700 2150
	-1   0    0    1   
$EndComp
Wire Wire Line
	10700 2000 10700 1950
Wire Wire Line
	10700 1950 10300 1950
$Comp
L GND #PWR45
U 1 1 5895EE59
P 10700 2400
F 0 "#PWR45" H 10700 2400 30  0001 C CNN
F 1 "GND" H 10700 2330 30  0001 C CNN
F 2 "" H 10700 2400 60  0000 C CNN
F 3 "" H 10700 2400 60  0000 C CNN
	1    10700 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10700 2400 10700 2300
$Comp
L GND #PWR44
U 1 1 5895F446
P 10700 1850
F 0 "#PWR44" H 10700 1850 30  0001 C CNN
F 1 "GND" H 10700 1780 30  0001 C CNN
F 2 "" H 10700 1850 60  0000 C CNN
F 3 "" H 10700 1850 60  0000 C CNN
	1    10700 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10700 1850 10700 1800
$Comp
L +5V #PWR42
U 1 1 5895FE70
P 10400 900
F 0 "#PWR42" H 10400 990 20  0001 C CNN
F 1 "+5V" H 10400 990 30  0000 C CNN
F 2 "" H 10400 900 60  0000 C CNN
F 3 "" H 10400 900 60  0000 C CNN
	1    10400 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 900  10400 1050
$Comp
L C C18
U 1 1 58960B45
P 10850 1250
F 0 "C18" H 10875 1350 50  0000 L CNN
F 1 "100nF" H 10875 1150 50  0000 L CNN
F 2 "" H 10888 1100 50  0000 C CNN
F 3 "" H 10850 1250 50  0000 C CNN
	1    10850 1250
	1    0    0    -1  
$EndComp
Connection ~ 10400 1050
$Comp
L GND #PWR46
U 1 1 58960F3A
P 10850 1450
F 0 "#PWR46" H 10850 1450 30  0001 C CNN
F 1 "GND" H 10850 1380 30  0001 C CNN
F 2 "" H 10850 1450 60  0000 C CNN
F 3 "" H 10850 1450 60  0000 C CNN
	1    10850 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	10850 1450 10850 1400
Wire Wire Line
	10300 1050 10850 1050
Wire Wire Line
	10850 1050 10850 1100
$Comp
L DB9 J1
U 1 1 58962A0F
P 10650 3650
F 0 "J1" H 10650 4200 50  0000 C CNN
F 1 "DB9" H 10650 3100 50  0000 C CNN
F 2 "" H 10650 3650 50  0000 C CNN
F 3 "" H 10650 3650 50  0000 C CNN
	1    10650 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR39
U 1 1 58962C3D
P 10000 3400
F 0 "#PWR39" H 10000 3400 30  0001 C CNN
F 1 "GND" H 10000 3330 30  0001 C CNN
F 2 "" H 10000 3400 60  0000 C CNN
F 3 "" H 10000 3400 60  0000 C CNN
	1    10000 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 3400 10000 3250
Wire Wire Line
	10000 3250 10200 3250
Wire Wire Line
	10200 3850 9800 3850
NoConn ~ 10200 3350
NoConn ~ 10200 3450
NoConn ~ 10200 3550
NoConn ~ 10200 3750
NoConn ~ 10200 3950
NoConn ~ 10200 4050
Text Label 9900 3850 0    60   ~ 0
PC_RX
Wire Wire Line
	10500 2250 10500 2600
Wire Wire Line
	10500 2600 10850 2600
Text Label 10500 2600 0    60   ~ 0
PC_RX
Wire Wire Line
	10500 2250 10300 2250
$Comp
L D_Small D2
U 1 1 58969D74
P 7200 1250
F 0 "D2" H 7150 1330 50  0000 L CNN
F 1 "1n4007" H 7050 1170 50  0000 L CNN
F 2 "" V 7200 1250 50  0000 C CNN
F 3 "" V 7200 1250 50  0000 C CNN
	1    7200 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	7850 1650 7850 1550
Wire Wire Line
	7300 1250 7450 1250
Wire Wire Line
	7100 1250 6550 1250
Wire Wire Line
	8400 1250 8400 1200
Wire Wire Line
	8250 1250 8400 1250
$Comp
L RELAY_9001 RLY1
U 1 1 58950710
P 9950 4900
F 0 "RLY1" H 9950 5100 60  0000 C CNN
F 1 "RELAY_9001" H 9950 4700 60  0000 C CNN
F 2 "" H 9950 4850 60  0000 C CNN
F 3 "" H 9950 4850 60  0000 C CNN
	1    9950 4900
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR40
U 1 1 58951181
P 10050 4600
F 0 "#PWR40" H 10050 4690 20  0001 C CNN
F 1 "+5V" H 10050 4690 30  0000 C CNN
F 2 "" H 10050 4600 60  0000 C CNN
F 3 "" H 10050 4600 60  0000 C CNN
	1    10050 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 4600 10050 4700
Wire Wire Line
	9800 5500 9950 5500
Text Label 9300 5500 0    60   ~ 0
EN
$Comp
L +5VD #PWR38
U 1 1 58957D00
P 9850 4600
F 0 "#PWR38" H 9850 4550 20  0001 C CNN
F 1 "+5VD" H 9850 4700 30  0000 C CNN
F 2 "" H 9850 4600 60  0000 C CNN
F 3 "" H 9850 4600 60  0000 C CNN
	1    9850 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 4600 9850 4700
Wire Wire Line
	9850 5100 9850 5200
Wire Wire Line
	9850 5200 9250 5200
Text Label 9350 5200 0    60   ~ 0
VERMELHO
Wire Wire Line
	9800 3650 10200 3650
Text Label 9900 3650 0    60   ~ 0
PC_TX
Wire Wire Line
	10300 2350 10450 2350
Wire Wire Line
	10450 2350 10450 2700
Wire Wire Line
	10450 2700 10850 2700
Text Label 10500 2700 0    60   ~ 0
PC_TX
NoConn ~ 10300 2450
NoConn ~ 9100 2350
NoConn ~ 9100 2150
$Comp
L JUMPER JP1
U 1 1 58C9D091
P 5900 1550
F 0 "JP1" H 5900 1700 50  0000 C CNN
F 1 "JUMPER" H 5900 1470 50  0000 C CNN
F 2 "" H 5900 1550 50  0000 C CNN
F 3 "" H 5900 1550 50  0000 C CNN
	1    5900 1550
	1    0    0    -1  
$EndComp
$Comp
L JUMPER JP2
U 1 1 58C9D318
P 5900 1900
F 0 "JP2" H 5900 2050 50  0000 C CNN
F 1 "JUMPER" H 5900 1820 50  0000 C CNN
F 2 "" H 5900 1900 50  0000 C CNN
F 3 "" H 5900 1900 50  0000 C CNN
	1    5900 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 1550 6550 1550
Wire Wire Line
	6200 1900 6550 1900
Wire Wire Line
	5600 1550 5500 1550
Wire Wire Line
	5500 1550 5500 1200
Wire Wire Line
	5500 1200 5300 1200
Wire Wire Line
	5600 1900 5450 1900
Wire Wire Line
	5450 1900 5450 1300
Wire Wire Line
	5450 1300 5300 1300
$Comp
L R R2
U 1 1 58CA21C0
P 5500 900
F 0 "R2" V 5400 900 50  0000 C CNN
F 1 "100" V 5500 900 50  0000 C CNN
F 2 "" V 5430 900 50  0000 C CNN
F 3 "" H 5500 900 50  0000 C CNN
	1    5500 900 
	0    1    1    0   
$EndComp
Wire Wire Line
	5350 900  5300 900 
Wire Wire Line
	5650 900  6000 900 
$Comp
L PIC24FJ1024GB610 U3
U 1 1 58D01880
P 3400 4950
F 0 "U3" H 3400 4700 60  0000 C CNN
F 1 "PIC24FJ1024GB610" H 3400 4500 60  0000 C CNN
F 2 "" H 3600 4950 60  0000 C CNN
F 3 "" H 3600 4950 60  0000 C CNN
	1    3400 4950
	1    0    0    -1  
$EndComp
$Comp
L D_Small D3
U 1 1 58D07EDE
P 7850 800
F 0 "D3" H 7800 880 50  0000 L CNN
F 1 "1n4007" H 7700 720 50  0000 L CNN
F 2 "" V 7850 800 50  0000 C CNN
F 3 "" V 7850 800 50  0000 C CNN
	1    7850 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 1250 8300 800 
Wire Wire Line
	8300 800  7950 800 
Connection ~ 8300 1250
Wire Wire Line
	7750 800  7400 800 
Wire Wire Line
	7400 800  7400 1250
Connection ~ 7400 1250
$Comp
L GND #PWR33
U 1 1 58D08485
P 7850 1650
F 0 "#PWR33" H 7850 1650 30  0001 C CNN
F 1 "GND" H 7850 1580 30  0001 C CNN
F 2 "" H 7850 1650 60  0000 C CNN
F 3 "" H 7850 1650 60  0000 C CNN
	1    7850 1650
	1    0    0    -1  
$EndComp
$Comp
L LD1117S33CTR U1
U 1 1 58D0D657
P 1600 1900
F 0 "U1" H 1600 2150 50  0000 C CNN
F 1 "LD1117S33CTR" H 1600 2100 50  0000 C CNN
F 2 "SOT-223" H 1600 2000 50  0000 C CNN
F 3 "" H 1600 1900 50  0000 C CNN
	1    1600 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 58D0E085
P 1600 2250
F 0 "#PWR6" H 1600 2250 30  0001 C CNN
F 1 "GND" H 1600 2180 30  0001 C CNN
F 2 "" H 1600 2250 60  0000 C CNN
F 3 "" H 1600 2250 60  0000 C CNN
	1    1600 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2250 1600 2150
$Comp
L +5V #PWR1
U 1 1 58D0F001
P 700 1750
F 0 "#PWR1" H 700 1840 20  0001 C CNN
F 1 "+5V" H 700 1840 30  0000 C CNN
F 2 "" H 700 1750 60  0000 C CNN
F 3 "" H 700 1750 60  0000 C CNN
	1    700  1750
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 58D0FCF0
P 700 2150
F 0 "C1" H 725 2250 50  0000 L CNN
F 1 "470uF" H 725 2050 50  0000 L CNN
F 2 "" H 738 2000 50  0000 C CNN
F 3 "" H 700 2150 50  0000 C CNN
	1    700  2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 58D0FCF6
P 700 2350
F 0 "#PWR2" H 700 2350 30  0001 C CNN
F 1 "GND" H 700 2280 30  0001 C CNN
F 2 "" H 700 2350 60  0000 C CNN
F 3 "" H 700 2350 60  0000 C CNN
	1    700  2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  2350 700  2300
$Comp
L C C2
U 1 1 58D0FCFD
P 1000 2150
F 0 "C2" H 1025 2250 50  0000 L CNN
F 1 "100nF" H 1025 2050 50  0000 L CNN
F 2 "" H 1038 2000 50  0000 C CNN
F 3 "" H 1000 2150 50  0000 C CNN
	1    1000 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR4
U 1 1 58D0FD03
P 1000 2350
F 0 "#PWR4" H 1000 2350 30  0001 C CNN
F 1 "GND" H 1000 2280 30  0001 C CNN
F 2 "" H 1000 2350 60  0000 C CNN
F 3 "" H 1000 2350 60  0000 C CNN
	1    1000 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 2350 1000 2300
Wire Wire Line
	700  1750 700  2000
Wire Wire Line
	700  1850 1200 1850
Wire Wire Line
	1000 2000 1000 1850
Connection ~ 1000 1850
Connection ~ 700  1850
$Comp
L CP C5
U 1 1 58D10AA8
P 2200 2050
F 0 "C5" H 2225 2150 50  0000 L CNN
F 1 "470uF" H 2225 1950 50  0000 L CNN
F 2 "" H 2238 1900 50  0000 C CNN
F 3 "" H 2200 2050 50  0000 C CNN
	1    2200 2050
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 58D10AAE
P 2500 2050
F 0 "C6" H 2525 2150 50  0000 L CNN
F 1 "100nF" H 2525 1950 50  0000 L CNN
F 2 "" H 2538 1900 50  0000 C CNN
F 3 "" H 2500 2050 50  0000 C CNN
	1    2500 2050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 58D10AB4
P 2200 2250
F 0 "#PWR8" H 2200 2250 30  0001 C CNN
F 1 "GND" H 2200 2180 30  0001 C CNN
F 2 "" H 2200 2250 60  0000 C CNN
F 3 "" H 2200 2250 60  0000 C CNN
	1    2200 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2250 2200 2200
$Comp
L GND #PWR11
U 1 1 58D10ABB
P 2500 2250
F 0 "#PWR11" H 2500 2250 30  0001 C CNN
F 1 "GND" H 2500 2180 30  0001 C CNN
F 2 "" H 2500 2250 60  0000 C CNN
F 3 "" H 2500 2250 60  0000 C CNN
	1    2500 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2250 2500 2200
Wire Wire Line
	2000 1850 2500 1850
Wire Wire Line
	2500 1800 2500 1900
Wire Wire Line
	2200 1900 2200 1850
Connection ~ 2200 1850
$Comp
L +3.3V #PWR10
U 1 1 58D10D32
P 2500 1800
F 0 "#PWR10" H 2500 1760 30  0001 C CNN
F 1 "+3.3V" H 2500 1910 30  0000 C CNN
F 2 "" H 2500 1800 60  0000 C CNN
F 3 "" H 2500 1800 60  0000 C CNN
	1    2500 1800
	1    0    0    -1  
$EndComp
Connection ~ 2500 1850
Wire Wire Line
	1750 1100 1750 1000
Connection ~ 1750 1000
Wire Wire Line
	2900 1100 2900 1000
Wire Wire Line
	3450 3050 3450 3200
Wire Wire Line
	3350 3050 3350 3200
Wire Wire Line
	3250 3200 3250 3050
Connection ~ 3350 3050
Wire Wire Line
	3150 2900 3150 3200
Connection ~ 3250 3050
$Comp
L CP C9
U 1 1 58D156A7
P 3800 3000
F 0 "C9" H 3825 3100 50  0000 L CNN
F 1 "10uF 16V" H 3825 2900 50  0000 L CNN
F 2 "" H 3838 2850 50  0000 C CNN
F 3 "" H 3800 3000 50  0000 C CNN
	1    3800 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR17
U 1 1 58D1582C
P 3800 3250
F 0 "#PWR17" H 3800 3250 30  0001 C CNN
F 1 "GND" H 3800 3180 30  0001 C CNN
F 2 "" H 3800 3250 60  0000 C CNN
F 3 "" H 3800 3250 60  0000 C CNN
	1    3800 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 3250 3800 3150
Wire Wire Line
	3600 2750 3600 3200
Wire Wire Line
	3600 2750 3800 2750
Wire Wire Line
	3800 2750 3800 2850
$Comp
L +3.3V #PWR13
U 1 1 58D16427
P 3150 2900
F 0 "#PWR13" H 3150 2860 30  0001 C CNN
F 1 "+3.3V" H 3150 3010 30  0000 C CNN
F 2 "" H 3150 2900 60  0000 C CNN
F 3 "" H 3150 2900 60  0000 C CNN
	1    3150 2900
	1    0    0    -1  
$EndComp
Connection ~ 3150 3050
Wire Wire Line
	3150 3050 3450 3050
$Comp
L GND #PWR16
U 1 1 58D18891
P 3550 7050
F 0 "#PWR16" H 3550 7050 30  0001 C CNN
F 1 "GND" H 3550 6980 30  0001 C CNN
F 2 "" H 3550 7050 60  0000 C CNN
F 3 "" H 3550 7050 60  0000 C CNN
	1    3550 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 6800 3550 7050
Wire Wire Line
	3450 6900 3450 6800
Wire Wire Line
	3250 6900 3550 6900
Connection ~ 3550 6900
Wire Wire Line
	3350 6800 3350 6900
Connection ~ 3450 6900
Wire Wire Line
	3250 6800 3250 6900
Connection ~ 3350 6900
$Comp
L +3.3V #PWR29
U 1 1 58D1B856
P 7600 2200
F 0 "#PWR29" H 7600 2160 30  0001 C CNN
F 1 "+3.3V" H 7600 2310 30  0000 C CNN
F 2 "" H 7600 2200 60  0000 C CNN
F 3 "" H 7600 2200 60  0000 C CNN
	1    7600 2200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR34
U 1 1 58D1D347
P 7950 3600
F 0 "#PWR34" H 7950 3560 30  0001 C CNN
F 1 "+3.3V" H 7950 3710 30  0000 C CNN
F 2 "" H 7950 3600 60  0000 C CNN
F 3 "" H 7950 3600 60  0000 C CNN
	1    7950 3600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR31
U 1 1 58D1D6AA
P 7600 3950
F 0 "#PWR31" H 7600 3910 30  0001 C CNN
F 1 "+3.3V" H 7600 4060 30  0000 C CNN
F 2 "" H 7600 3950 60  0000 C CNN
F 3 "" H 7600 3950 60  0000 C CNN
	1    7600 3950
	1    0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 58D215A7
P 10400 4900
F 0 "R13" V 10480 4900 50  0000 C CNN
F 1 "10k" V 10400 4900 50  0000 C CNN
F 2 "" V 10330 4900 50  0000 C CNN
F 3 "" H 10400 4900 50  0000 C CNN
	1    10400 4900
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR43
U 1 1 58D21F2D
P 10400 4650
F 0 "#PWR43" H 10400 4740 20  0001 C CNN
F 1 "+5V" H 10400 4740 30  0000 C CNN
F 2 "" H 10400 4650 60  0000 C CNN
F 3 "" H 10400 4650 60  0000 C CNN
	1    10400 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 4650 10400 4750
$Comp
L Q_NPN_BCE Q4
U 1 1 58D228C3
P 10150 5500
F 0 "Q4" H 10450 5550 50  0000 R CNN
F 1 "bc337" H 10650 5450 50  0000 R CNN
F 2 "" H 10350 5600 50  0000 C CNN
F 3 "" H 10150 5500 50  0000 C CNN
	1    10150 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 5100 10050 5200
Wire Wire Line
	10050 5200 10400 5200
Wire Wire Line
	10400 5200 10400 5050
Wire Wire Line
	10250 5300 10250 5200
Connection ~ 10250 5200
$Comp
L GND #PWR41
U 1 1 58D23360
P 10250 5850
F 0 "#PWR41" H 10250 5850 30  0001 C CNN
F 1 "GND" H 10250 5780 30  0001 C CNN
F 2 "" H 10250 5850 60  0000 C CNN
F 3 "" H 10250 5850 60  0000 C CNN
	1    10250 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 5850 10250 5700
$Comp
L R R12
U 1 1 58D26124
P 9650 5500
F 0 "R12" V 9730 5500 50  0000 C CNN
F 1 "1k" V 9650 5500 50  0000 C CNN
F 2 "" V 9580 5500 50  0000 C CNN
F 3 "" H 9650 5500 50  0000 C CNN
	1    9650 5500
	0    1    1    0   
$EndComp
Wire Wire Line
	9500 5500 9100 5500
Wire Wire Line
	5400 4850 5700 4850
Wire Wire Line
	5400 4750 5700 4750
Text Label 5550 4850 0    60   ~ 0
TX
Text Label 5550 4750 0    60   ~ 0
RX
Wire Wire Line
	5400 3850 5700 3850
Text Label 5550 3850 0    60   ~ 0
EN
Wire Wire Line
	1300 4850 1000 4850
Wire Wire Line
	1300 4950 1000 4950
Text Label 1000 4950 0    60   ~ 0
PGD
Text Label 1000 4850 0    60   ~ 0
PGC
Wire Wire Line
	5400 5350 5750 5350
Wire Wire Line
	5400 5250 5750 5250
$Comp
L BS170 Q2
U 1 1 58D35836
P 7150 5850
F 0 "Q2" H 7350 5925 50  0000 L CNN
F 1 "BS170" H 7350 5850 50  0000 L CNN
F 2 "TO-92" H 7350 5775 50  0000 L CIN
F 3 "" H 7150 5850 50  0000 L CNN
	1    7150 5850
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 58D37D09
P 6800 5700
F 0 "R5" V 6880 5700 50  0000 C CNN
F 1 "10k" V 6800 5700 50  0000 C CNN
F 2 "" V 6730 5700 50  0000 C CNN
F 3 "" H 6800 5700 50  0000 C CNN
	1    6800 5700
	-1   0    0    1   
$EndComp
$Comp
L R R9
U 1 1 58D380ED
P 7500 5700
F 0 "R9" V 7580 5700 50  0000 C CNN
F 1 "10k" V 7500 5700 50  0000 C CNN
F 2 "" V 7430 5700 50  0000 C CNN
F 3 "" H 7500 5700 50  0000 C CNN
	1    7500 5700
	-1   0    0    1   
$EndComp
Wire Wire Line
	7350 5950 7950 5950
Wire Wire Line
	7500 5950 7500 5850
Wire Wire Line
	6400 5950 6950 5950
Wire Wire Line
	6800 5950 6800 5850
$Comp
L +3.3V #PWR27
U 1 1 58D38FC1
P 6800 5400
F 0 "#PWR27" H 6800 5360 30  0001 C CNN
F 1 "+3.3V" H 6800 5510 30  0000 C CNN
F 2 "" H 6800 5400 60  0000 C CNN
F 3 "" H 6800 5400 60  0000 C CNN
	1    6800 5400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR28
U 1 1 58D39D74
P 7500 5400
F 0 "#PWR28" H 7500 5490 20  0001 C CNN
F 1 "+5V" H 7500 5490 30  0000 C CNN
F 2 "" H 7500 5400 60  0000 C CNN
F 3 "" H 7500 5400 60  0000 C CNN
	1    7500 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 5650 7100 5450
Connection ~ 6800 5950
Connection ~ 7500 5950
Wire Wire Line
	7500 5400 7500 5550
Wire Wire Line
	6800 5400 6800 5550
Wire Wire Line
	7100 5450 6800 5450
Connection ~ 6800 5450
Text Label 5450 5350 0    60   ~ 0
TX_DBG
Text Label 5450 5250 0    60   ~ 0
RX_DBG
$Comp
L BS170 Q1
U 1 1 58D3CC4B
P 6100 7350
F 0 "Q1" H 6300 7425 50  0000 L CNN
F 1 "BS170" H 6300 7350 50  0000 L CNN
F 2 "TO-92" H 6300 7275 50  0000 L CIN
F 3 "" H 6100 7350 50  0000 L CNN
	1    6100 7350
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 58D3CC51
P 5750 7200
F 0 "R3" V 5830 7200 50  0000 C CNN
F 1 "10k" V 5750 7200 50  0000 C CNN
F 2 "" V 5680 7200 50  0000 C CNN
F 3 "" H 5750 7200 50  0000 C CNN
	1    5750 7200
	-1   0    0    1   
$EndComp
$Comp
L R R4
U 1 1 58D3CC57
P 6450 7200
F 0 "R4" V 6530 7200 50  0000 C CNN
F 1 "10k" V 6450 7200 50  0000 C CNN
F 2 "" V 6380 7200 50  0000 C CNN
F 3 "" H 6450 7200 50  0000 C CNN
	1    6450 7200
	-1   0    0    1   
$EndComp
Wire Wire Line
	6300 7450 6900 7450
Wire Wire Line
	6450 7450 6450 7350
Wire Wire Line
	5350 7450 5900 7450
Wire Wire Line
	5750 7450 5750 7350
$Comp
L +3.3V #PWR23
U 1 1 58D3CC63
P 5750 6900
F 0 "#PWR23" H 5750 6860 30  0001 C CNN
F 1 "+3.3V" H 5750 7010 30  0000 C CNN
F 2 "" H 5750 6900 60  0000 C CNN
F 3 "" H 5750 6900 60  0000 C CNN
	1    5750 6900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR26
U 1 1 58D3CC69
P 6450 6900
F 0 "#PWR26" H 6450 6990 20  0001 C CNN
F 1 "+5V" H 6450 6990 30  0000 C CNN
F 2 "" H 6450 6900 60  0000 C CNN
F 3 "" H 6450 6900 60  0000 C CNN
	1    6450 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 7150 6050 6950
Connection ~ 5750 7450
Connection ~ 6450 7450
Wire Wire Line
	6450 6900 6450 7050
Wire Wire Line
	5750 6900 5750 7050
Wire Wire Line
	6050 6950 5750 6950
Connection ~ 5750 6950
Text Label 7650 5950 0    60   ~ 0
TX_PC_5
Text Label 6550 7450 0    60   ~ 0
RX_PC_5
Wire Wire Line
	8650 2250 9100 2250
Wire Wire Line
	9100 2450 8650 2450
Text Label 8650 2450 0    60   ~ 0
RX_PC_5
Text Label 6400 5950 0    60   ~ 0
TX_DBG
Text Label 5350 7450 0    60   ~ 0
RX_DBG
Text Label 8650 2250 0    60   ~ 0
TX_PC_5
NoConn ~ 5400 6550
NoConn ~ 5400 6450
NoConn ~ 5400 6350
NoConn ~ 5400 6250
NoConn ~ 5400 6150
NoConn ~ 5400 5650
NoConn ~ 5400 5550
NoConn ~ 5400 5450
NoConn ~ 5400 5150
NoConn ~ 5400 5050
NoConn ~ 5400 4950
NoConn ~ 5400 4650
NoConn ~ 5400 4550
NoConn ~ 5400 4450
NoConn ~ 5400 4350
NoConn ~ 5400 4050
NoConn ~ 5400 3950
NoConn ~ 5400 3750
NoConn ~ 5400 3650
NoConn ~ 5400 3550
NoConn ~ 5400 3450
NoConn ~ 1300 3450
NoConn ~ 1300 3550
NoConn ~ 1300 3650
NoConn ~ 1300 3750
NoConn ~ 1300 3850
NoConn ~ 1300 3950
Text Label 1000 4050 0    60   ~ 0
MCLR
Wire Wire Line
	1000 4050 1300 4050
NoConn ~ 1300 4150
NoConn ~ 1300 4450
NoConn ~ 1300 4550
NoConn ~ 1300 4650
NoConn ~ 1300 4750
NoConn ~ 1300 5050
NoConn ~ 1300 5150
NoConn ~ 1300 5450
NoConn ~ 1300 5550
NoConn ~ 1300 5650
NoConn ~ 1300 5750
NoConn ~ 1300 6050
NoConn ~ 1300 6150
NoConn ~ 1300 6250
NoConn ~ 1300 6350
NoConn ~ 1300 6450
NoConn ~ 1300 6550
$Comp
L SW_PUSH SW1
U 1 1 58D4B821
P 4550 2700
F 0 "SW1" H 4700 2810 50  0000 C CNN
F 1 "SW_PUSH" H 4550 2620 50  0000 C CNN
F 2 "" H 4550 2700 50  0000 C CNN
F 3 "" H 4550 2700 50  0000 C CNN
	1    4550 2700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR20
U 1 1 58D4BE8C
P 4550 3150
F 0 "#PWR20" H 4550 3150 30  0001 C CNN
F 1 "GND" H 4550 3080 30  0001 C CNN
F 2 "" H 4550 3150 60  0000 C CNN
F 3 "" H 4550 3150 60  0000 C CNN
	1    4550 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3150 4550 3000
$Comp
L R R1
U 1 1 58D4D07A
P 4550 2100
F 0 "R1" V 4450 2100 50  0000 C CNN
F 1 "10k" V 4550 2100 50  0000 C CNN
F 2 "" V 4480 2100 50  0000 C CNN
F 3 "" H 4550 2100 50  0000 C CNN
	1    4550 2100
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR19
U 1 1 58D4D79A
P 4550 1850
F 0 "#PWR19" H 4550 1810 30  0001 C CNN
F 1 "+3.3V" H 4550 1960 30  0000 C CNN
F 2 "" H 4550 1850 60  0000 C CNN
F 3 "" H 4550 1850 60  0000 C CNN
	1    4550 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 1950 4550 1850
Wire Wire Line
	4550 2250 4550 2400
Wire Wire Line
	4150 2350 5050 2350
Connection ~ 4550 2350
Text Label 4750 2350 0    60   ~ 0
MCLR
$Comp
L C C10
U 1 1 58D4FAD3
P 4150 2600
F 0 "C10" H 4175 2700 50  0000 L CNN
F 1 "100nF" H 4175 2500 50  0000 L CNN
F 2 "" H 4188 2450 50  0000 C CNN
F 3 "" H 4150 2600 50  0000 C CNN
	1    4150 2600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR18
U 1 1 58D4FD5B
P 4150 2800
F 0 "#PWR18" H 4150 2800 30  0001 C CNN
F 1 "GND" H 4150 2730 30  0001 C CNN
F 2 "" H 4150 2800 60  0000 C CNN
F 3 "" H 4150 2800 60  0000 C CNN
	1    4150 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2800 4150 2750
Wire Wire Line
	4150 2450 4150 2350
$Comp
L Crystal Y1
U 1 1 58D51F32
P 5850 2600
F 0 "Y1" H 5850 2750 50  0000 C CNN
F 1 "16MHz" H 5850 2450 50  0000 C CNN
F 2 "" H 5850 2600 50  0000 C CNN
F 3 "" H 5850 2600 50  0000 C CNN
	1    5850 2600
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 58D52F73
P 5500 2900
F 0 "C11" H 5525 3000 50  0000 L CNN
F 1 "22pF" H 5525 2800 50  0000 L CNN
F 2 "" H 5538 2750 50  0000 C CNN
F 3 "" H 5500 2900 50  0000 C CNN
	1    5500 2900
	1    0    0    -1  
$EndComp
$Comp
L C C12
U 1 1 58D53041
P 6200 2900
F 0 "C12" H 6225 3000 50  0000 L CNN
F 1 "22pF" H 6225 2800 50  0000 L CNN
F 2 "" H 6238 2750 50  0000 C CNN
F 3 "" H 6200 2900 50  0000 C CNN
	1    6200 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2350 6200 2750
Wire Wire Line
	6200 2600 6000 2600
$Comp
L GND #PWR22
U 1 1 58D53242
P 5500 3200
F 0 "#PWR22" H 5500 3200 30  0001 C CNN
F 1 "GND" H 5500 3130 30  0001 C CNN
F 2 "" H 5500 3200 60  0000 C CNN
F 3 "" H 5500 3200 60  0000 C CNN
	1    5500 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3200 5500 3050
$Comp
L GND #PWR25
U 1 1 58D533FA
P 6200 3200
F 0 "#PWR25" H 6200 3200 30  0001 C CNN
F 1 "GND" H 6200 3130 30  0001 C CNN
F 2 "" H 6200 3200 60  0000 C CNN
F 3 "" H 6200 3200 60  0000 C CNN
	1    6200 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3200 6200 3050
Wire Wire Line
	5500 2250 5500 2750
Wire Wire Line
	5500 2600 5700 2600
Wire Wire Line
	5500 2250 6150 2250
Connection ~ 5500 2600
Wire Wire Line
	6200 2350 5650 2350
Connection ~ 6200 2600
Wire Wire Line
	5400 5850 5650 5850
Wire Wire Line
	5400 5950 5650 5950
Text Label 5650 5850 2    60   ~ 0
OSC0
Text Label 5650 5950 2    60   ~ 0
OSC1
Text Label 5950 2350 2    60   ~ 0
OSC0
Text Label 5950 2250 2    60   ~ 0
OSC1
$Comp
L LED D4
U 1 1 58D03404
P 9050 5200
F 0 "D4" H 9050 5300 50  0000 C CNN
F 1 "LED" H 9050 5100 50  0000 C CNN
F 2 "" H 9050 5200 50  0000 C CNN
F 3 "" H 9050 5200 50  0000 C CNN
	1    9050 5200
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 58D034D8
P 8700 5400
F 0 "R11" V 8780 5400 50  0000 C CNN
F 1 "1k" V 8700 5400 50  0000 C CNN
F 2 "" V 8630 5400 50  0000 C CNN
F 3 "" H 8700 5400 50  0000 C CNN
	1    8700 5400
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR37
U 1 1 58D035D0
P 8700 5650
F 0 "#PWR37" H 8700 5650 30  0001 C CNN
F 1 "GND" H 8700 5580 30  0001 C CNN
F 2 "" H 8700 5650 60  0000 C CNN
F 3 "" H 8700 5650 60  0000 C CNN
	1    8700 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 5650 8700 5550
Wire Wire Line
	8700 5250 8700 5200
Wire Wire Line
	8700 5200 8850 5200
$EndSCHEMATC
