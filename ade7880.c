 #include "ade7880.h"
 
unsigned char ADE_Read8(unsigned int reg){
    unsigned char b0;
    char r1,r0;
     r0=(unsigned char)(reg & 0xFF);
     r1=(unsigned char)(reg >> 8);
     ADE_SpiMode(1);
     GPIOA_ODRbits.ODR15=0;
     Delay_us(10);
     
     SPI_Write(0x01);
      SPI_Write(r1);
     SPI_Write(r0);
     b0=SPI_Read(0x00);
     
     GPIOA_ODRbits.ODR15=1; 
     Delay_us(10);
     return b0;
}

unsigned int ADE_Read16(unsigned int reg){
    
    unsigned char b1,b0;
    char r1,r0;
    
    r0=(unsigned char)(reg & 0xFF);
     r1=(unsigned char)(reg >> 8);
    ADE_SpiMode(1);
     
    GPIOA_ODRbits.ODR15=0;
    Delay_us(10);

    SPI_Write(0x01);
     SPI_Write(r1);
     SPI_Write(r0);
    b1=SPI_Read(0x00);
    b0=SPI_Read(0x00);
   
    GPIOA_ODRbits.ODR15=1; 
    Delay_us(10);
    
    return (unsigned int)b1<<8 | (unsigned int)b0;
}

unsigned long ADE_Read24(unsigned int reg){
    unsigned char b2,b1,b0;
    char r1,r0;
    
    r0=(unsigned char)(reg & 0xFF);
    r1=(unsigned char)(reg >> 8);
     
     ADE_SpiMode(1);
     
    GPIOA_ODRbits.ODR15=0;
    Delay_us(10);
    
    SPI_Write(0x01);
     SPI_Write(r1);
     SPI_Write(r0);
    b2=SPI_Read(0x00);
    b1=SPI_Read(0x00);
    b0=SPI_Read(0x00);
    
    GPIOA_ODRbits.ODR15=1; 
    Delay_us(10);
    return (unsigned long)b2<<16 | (unsigned long)b1<<8 | (unsigned long)b0;
}

unsigned long ADE_Read32(unsigned int reg){

    unsigned char b3,b2,b1,b0;
    char r1,r0;
    
    r0=(unsigned char)(reg & 0xFF);
    r1=(unsigned char)(reg >> 8);
    
    ADE_SpiMode(1);
     
    GPIOA_ODRbits.ODR15=0;
    Delay_us(10);
    
    SPI_Write(0x01);
     SPI_Write(r1);
     SPI_Write(r0);
    b3=SPI_Read(0x00);
    b2=SPI_Read(0x00);
    b1=SPI_Read(0x00);
    b0=SPI_Read(0x00);
    
    GPIOA_ODRbits.ODR15=1; 
    Delay_us(10);
    
    return (unsigned long)b3<<24 | (unsigned long)b2<<16 | (unsigned long)b1<<8 | (unsigned long)b0;
}

void ADE_Write8(unsigned int reg ,unsigned char dat){

     char r1,r0;
     
     r0=(unsigned char)(reg & 0xFF);
     r1=(unsigned char)(reg >> 8);
     
     ADE_SpiMode(0);
     
     GPIOA_ODRbits.ODR15=0;
     Delay_us(10);
     
     SPI_Write(0x00);
      SPI_Write(r1);
     SPI_Write(r0);
     SPI_Write(dat);
     
     GPIOA_ODRbits.ODR15=1; 
     Delay_us(10);
}

void ADE_Write16(unsigned int reg, unsigned int dat){
     
     char b0,b1;
     char r1,r0;
     
     b0=(unsigned char)(dat & 0xFF);
     b1=(unsigned char)(dat >> 8);
     
     r0=(unsigned char)(reg & 0xFF);
     r1=(unsigned char)(reg >> 8);
     
     ADE_SpiMode(0);
     GPIOA_ODRbits.ODR15=0;
     Delay_us(10);
     
     SPI_Write(0x00);
      SPI_Write(r1);
     SPI_Write(r0);
     SPI_Write(b1);
     SPI_Write(b0);
     
     GPIOA_ODRbits.ODR15=1; 
     Delay_us(10);

}

 void ADE_Write24(unsigned int reg, unsigned long dat){
 
     char b0,b1,b2;
     char r1,r0;
     
     b0=(unsigned char)(dat & 0xFF);
     b1=(unsigned char)(dat >> 8);
     b2=(unsigned char)(dat >> 16);
     
     r0=(unsigned char)(reg & 0xFF);
     r1=(unsigned char)(reg >> 8);
   
     ADE_SpiMode(0);
     GPIOA_ODRbits.ODR15=0;
     Delay_us(10);
     
     SPI_Write(0x00);
     r0=(unsigned char)(reg & 0xFF);
     r1=(unsigned char)(reg >> 8);
     SPI_Write(b2);
     SPI_Write(b1);
     SPI_Write(b0);
     
     GPIOA_ODRbits.ODR15=1; 
     Delay_us(10);
 }
 
 void ADE_Write32(unsigned int reg, unsigned long dat){
      char b0,b1,b2,b3;
      char r1,r0;
      
     b0=(unsigned char)(dat & 0xFF);
     b1=(unsigned char)(dat >> 8);
     b2=(unsigned char)(dat >> 16);
     b3=(unsigned char)(dat >> 24);
     
     r0=(unsigned char)(reg & 0xFF);
     r1=(unsigned char)(reg >> 8);
     
     ADE_SpiMode(0);
     
     GPIOA_ODRbits.ODR15=0;
     Delay_us(10);
     
     SPI_Write(0x00);
     SPI_Write(r1);
     SPI_Write(r0);
     SPI_Write(b3);
     SPI_Write(b2);
     SPI_Write(b1);
     SPI_Write(b0);
     
     GPIOA_ODRbits.ODR15=1; 
     Delay_us(10);
 
 }  
 
 void ADE_Init(){
     
     //start dsp
     ADE_Write8(RUNREG,0x01);
     //Write protection
     ADE_Write8(0xE7FE,0xAD);
     ADE_Write8(0xE7E2,0x14);
     ADE_Write8(0xE7FE,0xAD);
     ADE_Write8(0xE7E2,0x04);
 
 } 
 
 void ADE_SpiEnable(){
   char d=0;
   //toggle cs 3 times by writing 0x0 to a reserved reg address
   for(d=0;d<3;d++)ADE_Write8(0xEBFF,0x00);
   
   //lock spi
   ADE_Write8(CONFIG2,0x00);   
}

 unsigned long getVRMS(char phase){
 
 if(phase==0)return ADE_Read32(AVRMS);
 else if (phase==1)return ADE_Read32(BVRMS);
 else return ADE_Read32(CVRMS);
 
 }
 unsigned long getIRMS(char phase){
 
 if(phase==0)return ADE_Read32(AIRMS);
 else if (phase==1)return ADE_Read32(BIRMS);
 else return ADE_Read32(CIRMS);
 
 }
 
 unsigned long getWatt(char phase){
 
 if(phase==0)return ADE_Read32(AWATT);
 else if (phase==1)return ADE_Read32(BWATT);
 else return ADE_Read32(CWATT);
 
 }
 unsigned long getVA(char phase){
 
 if(phase==0)return ADE_Read32(AVA);
 else if (phase==1)return ADE_Read32(BVA);
 else return ADE_Read32(CVA);
 
 }
 
 unsigned int getPhaseShift(char phase){
 
 if(phase==0)return ADE_Read16(ANGLE0);
 else if (phase==1)return ADE_Read16(ANGLE1);
 else return ADE_Read16(ANGLE2);
 
 }
 void ADE_SpiMode(char n){
 //Write shift on first clock edge
 if(n==0){
  SPI1_Init_Advanced(_SPI_FPCLK_DIV32, _SPI_MASTER | _SPI_8_BIT |_SPI_CLK_IDLE_HIGH |
    _SPI_FIRST_CLK_EDGE_TRANSITION | _SPI_MSB_FIRST | _SPI_SS_ENABLE | _SPI_SSM_DISABLE |
    _SPI_SSI_0, &_GPIO_MODULE_SPI1_PB345);
 }
 //Read shift on 2nd clock edge
 else {
 
   SPI1_Init_Advanced(_SPI_FPCLK_DIV32, _SPI_MASTER | _SPI_8_BIT |_SPI_CLK_IDLE_HIGH |
    _SPI_SECOND_CLK_EDGE_TRANSITION | _SPI_MSB_FIRST | _SPI_SS_ENABLE | _SPI_SSM_DISABLE |
    _SPI_SSI_0, &_GPIO_MODULE_SPI1_PB345);
 }
 
 }