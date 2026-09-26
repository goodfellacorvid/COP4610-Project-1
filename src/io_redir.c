#include "io_redir.h"


// Function notes: 9/26/2026
//
// This function takes in a list of tokens and extracts any potential redirects with input and output.
// Right now it doesn't return any values and only extracts the names of the input/output files.
// The readability from the input file should be verified before it's passed to command execution as input.
// Program should also create output files with r/w permissions (maybe with open() to get file descriptor)
// Should also use dup()/dup2() for redirection
bool get_redirection(const tokenlist * tokens)
{
    char * out_file = NULL;
    char * in_file = NULL;
    for (int i = 0; i < tokens->size; i++)
    {
        if (strcmp(tokens->items[i], ">") == 0 || strcmp(tokens->items[i], "<") == 0)
        { // Redirect input to output
            if (i+1 >= tokens->size)
            { // Last item in tokenlist without a given filename
                printf("Error, expected a filename after %s\n", tokens->items[i]);
                return false;
            }
            // printf() statements only to confirm input/output files
            if (strcmp(tokens->items[i], ">") == 0)
            {
                char * out_file = (char *)malloc(strlen(tokens->items[i+1]) + 1); // Allocate memory for output
                strcpy(out_file, tokens->items[i+1]);
                printf("Desired output file: %s\n", out_file);
            }
            if (strcmp(tokens->items[i], "<") == 0)
            {
                char * in_file = (char *)malloc(strlen(tokens->items[i+1]) + 1); // Allocate for input
                strcpy(in_file, tokens->items[i+1]);
                printf("Desired input file: %s\n", in_file);
            }
        }
    }
    return true;
}