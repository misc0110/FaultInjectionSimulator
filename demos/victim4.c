#include <stdio.h>
#include <faultconfig.h>

int main() {
    int i;
    for(i = 0; i < 10000; i++) {
        asm volatile("nop");
    }
    if(i >= 100 && i <= 300) {
        printf("Well done!\n");
        return 0;
    } else {
        printf("Nope: %d\n", i);
    }
    return 1;
}

FAULT_CONFIG("TIMEOUT=5");
FAULT_CONFIG("NOLOGFAULT");
FAULT_CONFIG("NOCODEFAULT");
FAULT_CONFIG_ENTRY(main);
