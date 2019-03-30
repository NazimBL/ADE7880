#define RUNREG 0xE228

//Phase rms voltage and current
#define AIRMS 0x43C0
#define AVRMS 0x43C1
#define BIRMS 0x43C2
#define BVRMS 0x43C3
#define CIRMS 0x43C4
#define CVRMS 0x43C5
#define NIRMS 0x43C6

//Peak register
#define IPEAK 0xE500
#define VPEAK 0xE501

//interrupt status regs
#define STATUS0 0xE502
#define STATUS1 0xE503

//interrupt enable regs
#define MASK0 0xE50A 
#define MASK1 0xE50B

//Instantaneous value of Phase currents
#define IAWV 0xE50C
#define IBWV 0xE50D
#define ICWV 0xE50E
#define INWV 0xE50F

//Instantaneous value of Phase voltages
#define VAWV 0xE510
#define VBWV 0xE511
#define VCWV 0xE512

//Instantaneous value of active power
#define AWATT 0xE513
#define BWATT 0xE514
#define CWATT 0xE515

//Instantaneous value of active power
#define AVA 0xE519
#define BVA 0xE51A
#define CVA 0xE51B

#define CHECKSUM 0xE51F

#define CONFIG 0xE618
#define CONFIG2 0xEC01
#define CONFIG3 0xEA00
#define MMODE 0xE700
//callibration regs
//0x03 default for threashold
#define WTHR 0xEA02
#define VARTHR 0xEA03
#define VATHR 0xEA04
//def 0x38000
#define VLEVEL 0x439F
//0x01FF 
#define COMPMODE 0xE60E
//configuration reg
#define CFMODE 0xE610
//denumerator
#define CF1DEN 0xE611
#define CF2DEN 0xE612
#define CF2DEN 0xE613

//gain  callib
#define GainRegister 0xE60F
//Current and voltage
#define AIGAIN 0x4380
#define AVGAIN 0x4381
#define BIGAIN 0x4382
#define BVGAIN 0x4383
#define CIGAIN 0x4384
#define CVGAIN 0x4385
#define NIGAIN 0x4386

//power gain , active power offset
#define APGAIN 0x4389
#define AWATTOS 0x438A
#define BPGAIN 0x438B
#define BWATTOS 0x438C
#define CPGAIN 0x438D
#define CWATTOS 0x438E

 //phase callib
#define APHCAL 0xE614
#define BPHCAL 0xE615
#define CPHCAL 0xE616

//active energy offset
#define AFWATTOS 0x43A2
#define BFWATTOS 0x43A3
#define CFWATTOS 0x43A4

//Reactive Energy Offset Calibration
#define AFVAROS 0x43A5
#define BFVAROS 0x43A6
#define CFVAROS 0x43A7

//RMS Offset
#define AIRMSOS 0x438F
#define AVRMSOS 0x4390
#define BIRMSOS 0x4391
#define BVRMSOS 0x4392
#define CIRMSOS 0x4393
#define CVRMSOS 0x4394
#define NIRMSOS 0x4395

//phase angles
#define ANGLE0 0xE601
#define ANGLE1 0xE602
#define ANGLE2 0xE603
 

 unsigned char ADE_Read8(unsigned int reg);
 unsigned int ADE_Read16(unsigned int reg);
 unsigned long ADE_Read24(unsigned int reg);
 unsigned long ADE_Read32(unsigned int reg);
 
 void ADE_Write8(unsigned int reg, unsigned char dat);
 void ADE_Write16(unsigned int reg, unsigned int dat);
 void ADE_Write24(unsigned int reg, unsigned long dat);
 void ADE_Write32(unsigned int reg, unsigned long dat);
 
 void ADE_Init();
 void ADE_SpiEnable();
 void ADE_SpiMode(char mode);
 unsigned long getVRMS(char phase);
 unsigned long getIRMS(char phase); 
 
 unsigned long getWatt(char phase);
 unsigned long getVA(char phase);
 unsigned int getPhaseShift(char phase);  