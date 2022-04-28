//for testing the shell

#include <stdio.h>
#include <unistd.h>
int main () {
    int x = 0;
        for (;;) {
         printf ("%d\n", x++);
         sleep(3);
        }
}
