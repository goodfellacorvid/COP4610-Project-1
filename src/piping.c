#include "piping.h"
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

    // TODO: Implement pipe(), fork(), dup2(), and execv() logic here

    // Free the split command tokens
    for (int i = 0; i < num_cmds; i++) {
        free_tokens(commands[i]);
    }
}