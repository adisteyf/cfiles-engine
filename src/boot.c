#include "fe-kernel.h"
#include <stdbool.h>
#include "fe-commands.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

volatile int fe_status = 0;
fe_rd rd;

void
fe_signal_handler (int signal) {
    fe_status = signal;
}

void
fe_panic (void)
{
    printf("BOOT: Killing Files Engine...\n");
    raise(SIGINT);
    printf("BOOT: Files Engine kernel panic with status: %d\n", fe_status);
    exit(-1);
}

void
vars_init (void)
{
	/* rd tier */
	rd.wireframe     = false;
	rd.wireframe_len = 5;
}

int
main (void)
{
    printf("BOOT: Booting Files Engine...\n");
    signal(SIGINT, fe_signal_handler);
		printf("BOOT: Setting up variables...\n");
		vars_init();
    printf("BOOT: Starting fe_main()...\n");
    fe_main();

    return 0;
}
