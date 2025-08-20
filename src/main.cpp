#include <stdio.h>
#include <sstream>
#include <iostream>
#include <orbis/libkernel.h>

#include "util.h"

int main(void)
{
    int sleepSeconds = 2;
    
    // No buffering
    setvbuf(stdout, NULL, _IONBF, 0);

		Notify("Hello Homebrew");

    sceKernelUsleep(2 * 1000000);

    for (;;) {}
}