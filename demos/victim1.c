#include <stdio.h>
#include <faultconfig.h>

int main() {

    asm volatile("1: jmp 1b\n");
    puts("Success!\n");
}

FAULT_CONFIG("NOZERO");
FAULT_CONFIG("NOHAVOC");
FAULT_CONFIG("MAXSKIP=2");
FAULT_CONFIG("MINSKIP=0");
FAULT_CONFIG("TIMEOUT=3");
FAULT_CONFIG("FAILEVERY=2");
