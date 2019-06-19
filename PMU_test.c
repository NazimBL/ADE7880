
 #include "ade7880.h"
 char take='b',buff='a',take1,buff1;
 char val1[8],val2[4];
 void ReadVI();
 void SpiSetup();
 char v=0;
 char txt[17];
 char txt3[7];
 unsigned long checksum=0;
 unsigned int angle=0;
 unsigned int status=0;
 
void main() {

    GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_13);
    SpiSetup();
    UART1_Init_Advanced(19200, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT, &_GPIO_MODULE_USART1_PB67); 
    Delay_ms(400);
    ADE_Init();
    ADE_SpiEnable();
     
    while(1){
         
     checksum=ADE_Read32(CHECKSUM);      
     LongLongUnsignedToHex(checksum, txt);
     UART1_Write_Text("checksum: ");
     UART1_Write_Text(txt);
     UART1_Write('\n');
     UART1_Write('\r');
     
     checksum=getIRMS(0);
     LongLongUnsignedToHex(checksum, txt);
     UART1_Write_Text("current: ");
     UART1_Write_Text(txt);
     UART1_Write('\n');
     UART1_Write('\r');
      checksum=getVRMS(0);
     LongLongUnsignedToHex(checksum, txt);
     UART1_Write_Text("voltage: ");
     UART1_Write_Text(txt);
     UART1_Write('\n');
     UART1_Write('\r');
     checksum=getWatt(0);        
     LongLongUnsignedToHex(checksum, txt);
     UART1_Write_Text("active power: ");
     UART1_Write_Text(txt);
     UART1_Write('\n');
     UART1_Write('\r');
     checksum=getVA(0);      
     LongLongUnsignedToHex(checksum, txt);
     UART1_Write_Text("apparent power: ");
     UART1_Write_Text(txt);
     UART1_Write('\n');
     UART1_Write('\r');
     angle=getPhaseShift(0);
     IntToStr(angle, txt3);
     UART1_Write_Text("phase: ");
     UART1_Write_Text(txt3);
     UART1_Write('\n');
     UART1_Write('\r');
      Delay_ms(1000); 
     }
}

void SpiSetup(){
   
    GPIO_Digital_Output(&GPIOB_BASE, _GPIO_PINMASK_3| _GPIO_PINMASK_5);
    GPIO_Digital_Input(&GPIOB_BASE, _GPIO_PINMASK_4);
    GPIO_Digital_Output(&GPIOA_BASE, _GPIO_PINMASK_15);// Set CS# pin as Output
    GPIOA_ODRbits.ODR15=1; 
    AFIOEN_bit = 1;
    SWJ_CFG1_bit = 1; 
    SPI1_Init_Advanced(_SPI_FPCLK_DIV32, _SPI_MASTER | _SPI_8_BIT |_SPI_CLK_IDLE_HIGH |
    _SPI_FIRST_CLK_EDGE_TRANSITION | _SPI_MSB_FIRST | _SPI_SS_ENABLE | _SPI_SSM_DISABLE |
    _SPI_SSI_0, &_GPIO_MODULE_SPI1_PB345);
    AFIO_MAPR.SPI1_REMAP=1;

}

/*
void checksum(){
     
     checksum=ADE_Read32(CHECKSUM);      
     if(checksum==0xAFFA63B9) GPIOC_ODRbits.ODR13=0;
     else GPIOC_ODRbits.ODR13=1;
     
     LongLongUnsignedToHex(checksum, txt);
     UART1_Write_Text("Checksum: ");
     UART1_Write_Text(txt);
     UART1_Write('\n');
     UART1_Write('\r');
}

void readPhase(){

 angle=getPhaseShift(0);
     IntToStr(angle, txt3);
     UART1_Write_Text("phase: ");
     UART1_Write_Text(txt3);
     UART1_Write('\n');
     UART1_Write('\r');
}

*/
