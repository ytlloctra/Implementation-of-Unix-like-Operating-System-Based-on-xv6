#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char * argv[]) {
    int pid;
    printf(1, "This is a demo for prio-schedule!\n");
    pid = getpid();
    chpri(pid, 19);

    int i = 0;

    pid = fork();

    if (pid == 0) {
        chpri(getpid(), 5);
        i = 1;
        while (i <= 20000) {
            if (i == 1000 || i == 10000) printf(1, "p2 is running\n");
            i++;
        }
        printf(1, "p2 sleeping\n");
        sleep(100);
        i = 1;
        while (i <= 2000) {
            if (i == 1000 || i == 10000) printf(1, "p2 is running again\n");
            i++;
        }
        printf(1, "p2 finished\n");
    } else {
        i = 1;
        while (i < 2000) {
            if (i == 1000 || i == 10000) printf(1, "p1 is running\n");
            i++;
        }
    }

    exit();
}
