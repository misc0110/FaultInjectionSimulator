#include <stdio.h>

volatile int is_admin = 0;

int main() {
    if(!is_admin) {
        puts("Nope, you are not admin\n");
        return 1;
    } else {
        if(is_admin) {
            puts("Would be too easy ;)\n");
            return 1;
        }
        puts("Success!\n");
        return 0;
    }

}
