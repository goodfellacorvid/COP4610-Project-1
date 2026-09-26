#include "extern_exec.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// This function takes in a pathname for a command, the list of arguments, and then executes it
bool external_command_exec(const char * pathname, tokenlist *tokens, redirect *redir)
{
    pid_t pid = fork();
    int fd; // Declaration for later use
    int outfd;
    if (redir->out_file)
    {
        // copied from "output-redirection.c"
        // duplicate stdout descriptor to index 3 in file descriptor table (saves stdout reference to the open file table)
        outfd = dup(STDOUT_FILENO);
        // close stdout; STDOUT_FILENO is an alias for 1
        close(STDOUT_FILENO);
        // creates a fd at index 1 in the file descriptor table; anything printed to stdout will be redirected to redir->out_file
        fd = open(redir->out_file,O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    }

    if (pid == 0)
    { //Process is child, execute command
        // to test redirection: only works when tokens like > and < are excluded from tokenlist->items. need to remove.
        // char *x[2];
		// x[0]="ls";
		// x[1]=NULL;
        // execv(pathname, x);
        execv(pathname, tokenlist->items);
        perror("Error");
        exit(1);
    }
    else
    { // Process is parent, wait on child
        waitpid(pid, NULL, 0); // Parent will wait on child- the status of child is stored by NULL (can replace with ptr later)
    }
    if (redir->out_file)
    {
        // replace the reference to text.txt in the open file table at index 1 with the original reference to stdout in the parent process
        dup2(outfd, STDOUT_FILENO);
        // we can close extra reference to stdout
        close(outfd);
    }
    return true;
}