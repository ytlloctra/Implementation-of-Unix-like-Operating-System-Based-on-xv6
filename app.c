#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    printf(1, "Hello World\n");
    int a;
    a = fork();
    a = fork();
    while(1) {
        a++;
    } 
    exit();
}