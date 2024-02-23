#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigquit_handler(int sig) {
    printf("SIGQUIT received, preparing to exit and potentially generate a core dump...\n");
    // Optionally perform cleanup here

    // Re-raise the signal with the default handler to ensure core dump generation
    signal(SIGQUIT, SIG_DFL);
    raise(SIGQUIT);
}

int main() {
    struct sigaction sa;

    sa.sa_handler = sigquit_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; // You might set SA_RESETHAND to restore the default action after the first use

    sigaction(SIGQUIT, &sa, NULL);

    printf("Process %d running... Press Ctrl-\\ to test SIGQUIT handling.\n", getpid());

    // Infinite loop to keep the process alive until SIGQUIT is received
    while (1) {
        pause(); // Wait for signals
    }

    return 0; // This line is never reached
}