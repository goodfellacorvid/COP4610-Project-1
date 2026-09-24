#include "extern_exec.h"

// This function takes in a pathname for a command, the list of arguments, and then executes it
bool external_command_exec(const char * pathname, tokenlist *tokens)
{
    pid_t pid = fork();

    if (pid == 0)
    { //Process is child, execute command
        execv(pathname, tokens->items);
        perror("Error");
        exit(1);
    }
    else
    { // Process is parent, wait on child
        waitpid(pid, NULL, 0); // Parent will wait on child- the status of child is stored by NULL (can replace with ptr later)
    }
    return true;
}