#include <stdio.h>
#include <faultconfig.h>

volatile int is_admin = 0;

int main() {
    if(!is_admin) {
        puts("Nope, you are not admin\n");
        return 1;
    } else {
        puts("Success!\n");
        return 0;
    }

}

FAULT_CONFIG("NOHAVOC");
FAULT_CONFIG("NOSKIP");
