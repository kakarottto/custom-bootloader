#pragma once

double sqrt(double n)
{
	double result;
	asm (
		"fldl %1;"	//Load the double argument into the FPU stack
		"fsqrt;"	//Perform the square root operation
		"fstpl %0;"	//Store the result from the FPU stack into the result variable
		: "=m" (result)	//Output: store result into 'result' variable
		: "m" (n)		//Input: pass 'n' as the argument
		: "st"			//Clobbered register: the FPU stack register 'st'
	);
	return result;
}
