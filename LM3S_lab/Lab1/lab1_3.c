#include "inc/lm3s8962.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
/* STANDARD BITS
************************************************************/

#define BIT0                   (0x0001)
#define BIT1                   (0x0002)
#define BIT2                   (0x0004)
#define BIT3                   (0x0008)
#define BIT4                   (0x0010)
#define BIT5                   (0x0020)
#define BIT6                   (0x0040)
#define BIT7                   (0x0080)
#define BIT8                   (0x0100)
#define BIT9                   (0x0200)
#define BITA                   (0x0400)
#define BITB                   (0x0800)
#define BITC                   (0x1000)
#define BITD                   (0x2000)
#define BITE                   (0x4000)
#define BITF                   (0x8000)
#define POOL_PRIORITY           BIT0+BIT3+BIT4
#define LEFT_PRIORITY           BIT1+BIT2+BIT4
#define RIGHT_PRIORITY          BIT0+BIT2+BIT5
void configClocks(void);
void configIO(void);
int main()
{
  configClocks();
  configIO();
  while(1)
  {
    if(!(GPIO_PORTF_DATA_R & BIT1))//if pool has car
    {
      GPIO_PORTA_DATA_R = POOL_PRIORITY;
    }else
    if(!(GPIO_PORTF_DATA_R & BIT2))//if right has car but pool not have car
    {
      GPIO_PORTA_DATA_R = RIGHT_PRIORITY;
    }else
    if(!(GPIO_PORTF_DATA_R & BIT0))// if left has car but others dont have cars
    {
      GPIO_PORTA_DATA_R = LEFT_PRIORITY;
    }    
  }
  return 0;
}
void configClocks(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}
void configIO(void)
{
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF + SYSCTL_RCGC2_GPIOG;
    //GPIO_PORTF_DIR_R |= BIT0 + BIT1 +BIT2;
    GPIO_PORTF_DEN_R |= BIT0 + BIT1 +BIT2;
    GPIO_PORTF_PUR_R |= BIT0 + BIT1 +BIT2;
    
    GPIO_PORTA_DEN_R |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 +BIT5;
    GPIO_PORTA_DIR_R |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 +BIT5;
    
}