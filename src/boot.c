#include "fe-kernel.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

volatile int fe_status = 0;

void fe_signal_handler(int signal)
{
    fe_status = signal;
}

void fe_panic()
{
    printf("BOOT: Killing Files Engine...\n");
    raise(SIGINT);
    printf("BOOT: Files Engine kernel panic with status: %d\n", fe_status);
    exit(-1);
}

int main()
{
    signal(SIGINT, fe_signal_handler);
    //int status = fe_main();
    //printf("BOOT: fe_main() killed with status (%d)\n", status);
    fe_main();

    return 0;
}
