#include "bg_processing.h"
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

// Parallel static arrays to hold job data invisibly
static pid_t bg_pids[10];
static char bg_cmds[10][256];

void init_bg_jobs() {
    for (int i = 0; i < 10; i++) {
        bg_pids[i] = 0; // 0 indicates the slot is available
        bg_cmds[i][0] = '\0';
    }
}

void add_bg_job(pid_t pid, const char *cmd) {
    for (int i = 0; i < 10; i++) {
        if (bg_pids[i] == 0) { // Find the first empty slot
            bg_pids[i] = pid;
            strncpy(bg_cmds[i], cmd, 255);
            bg_cmds[i][255] = '\0'; // Guarantee null-termination
            
            // The job number is strictly the index + 1
            printf("[%d] %d\n", i + 1, pid);
            return;
        }
    }
    printf("Background job limit reached.\n");
}

void check_bg_jobs() {
    for (int i = 0; i < 10; i++) {
        if (bg_pids[i] != 0) { // Only check active slots
            // WNOHANG checks if it finished without pausing the shell
            pid_t result = waitpid(bg_pids[i], NULL, WNOHANG);
            
            if (result > 0) {
                printf("[%d] + done %s\n", i + 1, bg_cmds[i]);
                bg_pids[i] = 0; // Reset to 0 to free the slot
            }
        }
    }
}