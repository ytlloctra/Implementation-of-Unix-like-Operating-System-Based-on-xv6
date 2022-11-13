#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int pid = fork();
    int i, n;
    for (i = 0; i < 10000; i++) {
        n = sh_var_read();
        sh_var_write(n + 1);
    }
    printf(1, "sum = %d\n", sh_var_read());
    if (pid > 0) wait();
    exit();
    return 0;
}