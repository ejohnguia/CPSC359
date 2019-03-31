// This file contains C functions to handle particular kinds of exceptions.
// Only a function to handle IRQ exceptions is currently implemented.

// Header files
#include "uart.h"
#include "gpio.h"
#include "irq.h"
#include "sysreg.h"

// Reference to the global shared value
extern unsigned int state;

//Function determine the particular kind of pending interrupt.
//Interrupt is cleared, and set to a different value.
void IRQ_handler()
{

    // Handle GPIO interrupts in general
    if (*IRQ_PENDING_2 == (0x1 << 20)) {
        if(*GPEDS0 == (0x1 << 23)){
          *GPEDS0 = (0x1 << 23);
          state = 0;
        }
        if(*GPEDS0 == (0x1 << 24)){
          *GPEDS0 = (0x1 << 24);
          state = 1;
        }
    }

    // Return to the IRQ exception handler stub
    return;
}
