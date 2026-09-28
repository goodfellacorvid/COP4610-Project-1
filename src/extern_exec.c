#include "extern_exec.h"
#include "bg_processing.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

// This function takes in a pathname for a command, the list of arguments, and then executes it
bool external_command_exec(const char * pathname, tokenlist *tokens, redirect * redirection, int is_background, char *input)
{
    pid_t pid = fork();

    // For IO redirection
    int fd; // Declaration for later use
    int outfd;
    if (redirection->out_file)
    { // Output should be redirected to specified file. Overwrite it, or create if it doesn't already exist
        if (remove(redirection->out_file) == 0)
        {
            //Successfully deleted file for replacement, continue
        }
        outfd = dup(STDOUT_FILENO);
        close(STDOUT_FILENO);
        // File is readable and writeable
        fd = open(redirection->out_file,O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    }
    if (pid == 0)
    { //Process is child, execute command
        execv(pathname, redirection->tokens->items);
        perror("Error");
        exit(1);
    }
    else
    { // Process is parent, wait on child OR send to background
        if (!is_background) {
            waitpid(pid, NULL, 0); 
        }
    }
    if (redirection->out_file)
    {
        dup2(outfd, STDOUT_FILENO);
        close(outfd);
    }
    if (is_background) {
        add_bg_job(pid, input);
    }
    return true;
}