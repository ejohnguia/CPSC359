// This file provides functions to query and set various system registers.
// It is written in assembly code, since the system registers must be written
// to or read from using the msr and mrs instructions.


		.text
		.balign 4

//Clear individual DAIF flags
		.global enableIRQ
enableIRQ:	msr	DAIFClr, 0b0010
		ret


//Set individual DAIF flags
		.global disableIRQ
disableIRQ:	msr	DAIFSet, 0b0010
		ret
