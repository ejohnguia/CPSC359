// Include files
#include "uart.h"
#include "gpio.h"
#include "irq.h"
#include "sysreg.h"

// Function prototypes
// Pin 17 to output
void init_GPIO17_to_output();
void set_GPIO17();
void clear_GPIO17();

// Pin 27 to output
void init_GPIO27_to_output();
void set_GPIO27();
void clear_GPIO27();

// Pin 22 to output
void init_GPIO22_to_output();
void set_GPIO22();
void clear_GPIO22();

// Pin 23 to input with falling edge
void init_GPIO23_to_fallingEdgeInterrupt();
// Pin 24 to input with rising edge
void init_GPIO24_to_risingEdgeInterrupt();

void light_next(int time, int gPIN);
void busyLoop(int time);

// Declare a global shared variable
unsigned int state;

//Main Function
void main()
{
    int LED[] = {17, 27, 22};
    state = 0;

    // Set up the UART serial port
    uart_init();

    // Set up GPIO pin #24 to input and so that it triggers
    // an interrupt when a rising edge is detected
    init_GPIO24_to_risingEdgeInterrupt();

    // Set up GPIO pin #23 to input and so that it triggers
    // an interrupt when a falling edge is detected
    init_GPIO23_to_fallingEdgeInterrupt();

    //Set up the GPIO pin 17 to output
    init_GPIO17_to_output();

    //Set up the GPIO pin 27 to output
    init_GPIO27_to_output();

    //Set up the GPIO pin 22 to output
    init_GPIO22_to_output();

    // Enable IRQ Exceptions
    enableIRQ();

    // Loop forever, waiting for interrupts to change the shared value.
    while (1) {
        if (state == 1){
            int speed = 0x000FFFFF;
            light_next(speed, LED[2]);
            light_next(speed, LED[1]);
            light_next(speed, LED[0]);
        }
        else{                 
            int speed = 0x001FFFFF;
            light_next(speed, LED[0]);
            light_next(speed, LED[1]);
            light_next(speed, LED[2]);
        }
    }
}

// Turns on the pin setting it to a 1.
// Run busyloop with given time. Then resets the pin.
void light_next(int time, int gPIN)
{
  register unsigned int r;

  r = (0x1 << gPIN);
  *GPSET0 = r;

  busyLoop(time);

  *GPCLR0 = r;
}

// Loop without operations for a certain time.
void busyLoop(int time)
{
  while(time--){
    asm volatile("nop");
  }
}

//Set GPIO pin 17 as an output
void init_GPIO17_to_output()
{
    register unsigned int r;


    // Get the current contents of the GPIO Function Select Register 1
    r = *GPFSEL1;

    // Clear bits 21 - 23. This is the field FSEL17, which maps to GPIO pin 17.
    // We clear the bits by ANDing with a 000 bit pattern in the field.
    r &= ~(0x7 << 21);

    // Set the field FSEL17 to 001, which sets pin 17 to an output pin.
    // We do so by ORing the bit pattern 001 into the field.
    r |= (0x1 << 21);

    // Write the modified bit pattern back to the
    // GPIO Function Select Register 2
    *GPFSEL1 = r;

    // Disable the pull-up/pull-down control line for GPIO pin 17. We follow the
    // procedure outlined on page 101 of the BCM2837 ARM Peripherals manual. The
    // internal pull-up and pull-down resistor isn't needed for an output pin.

    // Disable pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
    *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
    busyLoop(150);

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 17 to
    // clock in the control signal for GPIO pin 17. Note that all other pins
    // will retain their previous state.
    *GPPUDCLK0 = (0x1 << 17);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
    busyLoop(150);

    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
    *GPPUDCLK0 = 0;
}

//Function set GPIO output pin 17 to a 1 (High) level
void set_GPIO17()
{
    register unsigned int r;

    // Put a 1 into the SET17 field of the GPIO Pin Output Set Register 0
    r = (0x1 << 17);
    *GPSET0 = r;
}

//Function clear GPIO pin 17 to a 0 (low) level
void clear_GPIO17()
{
    register unsigned int r;

    // Put a 1 into the CLR17 field of the GPIO Pin Output Clear Register 0
    r = (0x1 << 17);
    *GPCLR0 = r;
}

//Function set the GPIO pin 27 to an output pin
void init_GPIO27_to_output()
{
    register unsigned int r;

    // Get the current contents of the GPIO Function Select Register 3
    r = *GPFSEL2;

    // Clear bits 21 - 23. This is the field FSEL27, which maps to GPIO pin 27.
    // We clear the bits by ANDing with a 000 bit pattern in the field.
    r &= ~(0x7 << 21);

    // Set the field FSEL23 to 001, which sets pin 27 to an output pin.
    // We do so by ORing the bit pattern 001 into the field.
    r |= (0x1 << 21);

    // Write the modified bit pattern back to the
    // GPIO Function Select Register 2
    *GPFSEL2 = r;

    // Disable the pull-up/pull-down control line for GPIO pin 27. We follow the
    // procedure outlined on page 101 of the BCM2837 ARM Peripherals manual. The
    // internal pull-up and pull-down resistor isn't needed for an output pin.

    // Disable pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
    *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
    busyLoop(150);

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 27 to
    // clock in the control signal for GPIO pin 27. Note that all other pins
    // will retain their previous state.
    *GPPUDCLK0 = (0x1 << 27);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
    busyLoop(150);

    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
    *GPPUDCLK0 = 0;
}

//Function to set GPIO output pin 27 to 1 (high) level 
void set_GPIO27()
{
    register unsigned int r;

    // Put a 1 into the SET27 field of the GPIO Pin Output Set Register 0
    r = (0x1 << 27);
    *GPSET0 = r;
}

//Function to clear GPIO output pin 27 to 0 (low) level
void clear_GPIO27()
{
    register unsigned int r;

    // Put a 1 into the CLR27 field of the GPIO Pin Output Clear Register 0
    r = (0x1 << 27);
    *GPCLR0 = r;
}

//Function to set GPIO pin 22 to an output pin
void init_GPIO22_to_output()
{
    register unsigned int r;


    // Get the current contents of the GPIO Function Select Register 2
    r = *GPFSEL2;

    // Clear bits 6 - 8. This is the field FSEL22, which maps to GPIO pin 22.
    // We clear the bits by ANDing with a 000 bit pattern in the field.
    r &= ~(0x7 << 6);

    // Set the field FSEL23 to 001, which sets pin 22 to an output pin.
    // We do so by ORing the bit pattern 001 into the field.
    r |= (0x1 << 6);

    // Write the modified bit pattern back to the
    // GPIO Function Select Register 2
    *GPFSEL2 = r;

    // Disable the pull-up/pull-down control line for GPIO pin 2. We follow the
    // procedure outlined on page 101 of the BCM2837 ARM Peripherals manual. The
    // internal pull-up and pull-down resistor isn't needed for an output pin.

    // Disable pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
    *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
    busyLoop(150);

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 2 to
    // clock in the control signal for GPIO pin 22. Note that all other pins
    // will retain their previous state.
    *GPPUDCLK0 = (0x1 << 22);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
    busyLoop(150);

    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
    *GPPUDCLK0 = 0;
}

//Function to set GPIO pin 22 to a 1 (high) level
void set_GPIO22()
{
    register unsigned int r;

    // Put a 1 into the SET22 field of the GPIO Pin Output Set Register 0
    r = (0x1 << 22);
    *GPSET0 = r;
}

//Function to clear GPIO pin 22 to a 0 (low) level
void clear_GPIO22()
{
    register unsigned int r;

    // Put a 1 into the CLR22 field of the GPIO Pin Output Clear Register 0
    r = (0x1 << 22);
    *GPCLR0 = r;
}

//Function to sets GPIO pin 23 to an input pin
void init_GPIO23_to_fallingEdgeInterrupt()
{
    register unsigned int r;

    // Get the current contents of the GPIO Function Select Register 1
    r = *GPFSEL2;

    // Clear bits 9 - 12. This is the field FSEL17, which maps to GPIO pin 23.
    // We clear the bits by ANDing with a 000 bit pattern in the field. This
    // sets the pin to be an input pin
    r &= ~(0x7 << 9);

    // Write the modified bit pattern back to the
    // GPIO Function Select Register 1
    *GPFSEL2 = r;

    // Disable the pull-up/pull-down control line for GPIO pin 23. We follow the
    // procedure outlined on page 101 of the BCM2837 ARM Peripherals manual. We
    // will pull down the pin using an external resistor connected to ground.

    // Disable internal pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
    *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
    busyLoop(150);

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 23 to
    // clock in the control signal for GPIO pin 18. Note that all other pins
    // will retain their previous state.
    *GPPUDCLK0 = (0x1 << 23);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
    busyLoop(150);

    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
    *GPPUDCLK0 = 0;

    // Set pin 18 to so that it generates an interrupt on a rising edge.
    // We do so by setting bit 18 in the GPIO Rising Edge Detect Enable
    // Register 0 to a 1 value (p. 97 in the Broadcom manual).
    *GPFEN0 = (0x1 << 23);

    // Enable the GPIO IRQS for ALL the GPIO pins by setting IRQ 52
    // GPIO_int[3] in the Interrupt Enable Register 2 to a 1 value.
    // See p. 117 in the Broadcom Peripherals Manual.
    *IRQ_ENABLE_IRQS_2 = (0x1 << 20);
}

//This function sets GPIO pin 24 to an input pin
void init_GPIO24_to_risingEdgeInterrupt()
{
    register unsigned int r;

    // Get the current contents of the GPIO Function Select Register 2
    r = *GPFSEL2;

    // Clear bits 12 - 14. This is the field FSEL24, which maps to GPIO pin 24.
    // We clear the bits by ANDing with a 000 bit pattern in the field. This
    // sets the pin to be an input pin
    r &= ~(0x7 << 12);

    // Write the modified bit pattern back to the
    // GPIO Function Select Register 2
    *GPFSEL2 = r;

    // Disable the pull-up/pull-down control line for GPIO pin 24. We follow the
    // procedure outlined on page 101 of the BCM2837 ARM Peripherals manual. We
    // will pull down the pin using an external resistor connected to ground.

    // Disable internal pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
    *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
    busyLoop(150);

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 24 to
    // clock in the control signal for GPIO pin 24. Note that all other pins
    // will retain their previous state.
    *GPPUDCLK0 = (0x1 << 24);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
    busyLoop(150);
    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
    *GPPUDCLK0 = 0;

    // Set pin 24 to so that it generates an interrupt on a rising edge.
    // We do so by setting bit 24 in the GPIO Rising Edge Detect Enable
    // Register 0 to a 1 value (p. 97 in the Broadcom manual).
    *GPREN0 = (0x1 << 24);

    // Enable the GPIO IRQS for ALL the GPIO pins by setting IRQ 52
    // GPIO_int[3] in the Interrupt Enable Register 2 to a 1 value.
    // See p. 117 in the Broadcom Peripherals Manual.
    *IRQ_ENABLE_IRQS_2 = (0x1 << 20);
}