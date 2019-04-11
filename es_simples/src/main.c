#include <stdbool.h>
#include <stdint.h>
#include "inc/tm4c1294ncpdt.h" // CMSIS-Core
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h" // driverlib
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#define AMOSTRAUMSEG 1090472 // 631711 * 1,7262
#define AMOSTRAUMMILI 1198 // 632 * 1,99

void main(void){
  uint32_t ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                              SYSCTL_OSC_MAIN |
                                              SYSCTL_USE_PLL |
                                              SYSCTL_CFG_VCO_480),
                                              24000000); // PLL em 24MHz
   //iartheworld
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION); 
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)); // Aguarda final da habilita��o
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM); 
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)); // Aguarda final da habilita��o
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); 
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilita��o
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ); 
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)); // Aguarda final da habilita��o
  
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0); 
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3); 
  GPIOPinTypeGPIOInput(GPIO_PORTM_BASE, GPIO_PIN_3); 
  GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1); 
  GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 , 0); 
  while(1)
  {
    int contagem = 0;
    int i;
    int leituraAnterior = GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_3);
    int leitura = GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1);
    int x = leitura;
    if(x == leitura) {
      x = leitura;
    }
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 , GPIO_PIN_3); 
    for(i = 0; i < AMOSTRAUMMILI; i++)
    {
      int a = GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_3);
      if (a != leituraAnterior && a == GPIO_PIN_3)
      {
        contagem++;
      }
      leituraAnterior = a;
    }
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 , 0); 
  }
}