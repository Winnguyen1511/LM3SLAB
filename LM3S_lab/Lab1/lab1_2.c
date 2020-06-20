#include <stdint.h>
#include <stdbool.h>
#include "inc/lm3s8962.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
void configClocks(void);
void configIO(void);
int main()
{
  configClocks();
  configIO();
  while(1)
  {
    while(!(GPIO_PORTF_DATA_R & 0x02))
    {
      GPIO_PORTF_DATA_R ^= 0x01;
      SysCtlDelay(3000000);
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
  SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;
  GPIO_PORTF_DIR_R |= 0x01;
  GPIO_PORTF_DEN_R |= 0x01 + 0x02;
  GPIO_PORTF_PUR_R |= 0x02;
}