#include "piping.h"
#include "path_search.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int count_pipes(tokenlist *tokens) {
    int count = 0;
    for (int i = 0; i < tokens->size; i++) {
        if (strcmp(tokens->items[i], "|") == 0) {
            count++;
        }
    }
    return count;
}

void execute_pipeline(tokenlist *tokens) {
    int num_pipes = count_pipes(tokens);
    int num_cmds = num_pipes + 1;
    
    // Array to hold the separate tokenlists for each command
    tokenlist *commands[3]; // Max 2 pipes means max 3 commands
    for (int i = 0; i < num_cmds; i++) {
        commands[i] = new_tokenlist();
    }

    int cmd_index = 0;
    for (int i = 0; i < tokens->size; i++) {
        if (strcmp(tokens->items[i], "|") == 0) {
            cmd_index++; // Move to the next command bucket
        } else {
            add_token(commands[cmd_index], tokens->items[i]);
        }
    }

    // --- DEBUG: Verify parsing worked ---
    for (int i = 0; i < num_cmds; i++) {
        printf("Command %d: ", i);
        for (int j = 0; j < commands[i]->size; j++) {
            printf("[%s] ", commands[i]->items[j]);
        }
        printf("\n");
    }
    // ------------------------------------

    // TODO: implement pipe(), fork(), dup2(), and execv() logic - (in progress)
    int pipes[2][2]; // Supports up to 2 pipes
    pid_t pids[3];   // Supports up to 3 chained commands

    for (int i = 0; i < num_cmds; i++) {
        // 1. creating a pipe for this command (except for the very last command)
        if (i < num_pipes) {
            if (pipe(pipes[i]) < 0) {
                perror("Pipe creation failed");
                return;
            }
        }

        // 2. forking the process
        pids[i] = fork();
        
        if (pids[i] < 0) {
            perror("Fork failed");
            return;
        }

        if (pids[i] == 0) { 
            // --- CHILD PROCESS ---
            
            // if not the first command, grab input from the previous pipe's read end
            if (i > 0) {
                dup2(pipes[i-1][0], STDIN_FILENO);
            }
            // if not the last command, push output to the current pipe's write end
            if (i < num_pipes) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            // closing all pipe file descriptors in the child before executing (important!)
            for (int j = 0; j <= i && j < num_pipes; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // resolving path and execute
            char *path = search_for_path(commands[i]->items[0]);
            if (path == NULL) {
                printf("Command not found: %s\n", commands[i]->items[0]);
                exit(1);
            }
            
            execv(path, commands[i]->items);
            perror("Execution failed"); // if execv fails
            exit(1);
            
        } else {
            // --- PARENT PROCESS ---
            
            // parent closes the read end of the previous pipe (passed to child)
            if (i > 0) {
                close(pipes[i-1][0]);
            }
            // parent closes the write end of the current pipe (prevents the pipeline from hanging)
            if (i < num_pipes) {
                close(pipes[i][1]);
            }
        }
    }

    // 3. parent waits for all children in the pipeline to finish before returning to shell prompt
    for (int i = 0; i < num_cmds; i++) {
        waitpid(pids[i], NULL, 0);
    }

    // freeing the split command tokens
    for (int i = 0; i < num_cmds; i++) {
        free_tokens(commands[i]);
    }
}