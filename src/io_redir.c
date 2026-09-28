#include "io_redir.h"

redirect *get_redirection(tokenlist *tokens)
{
    redirect *redir = (redirect *)malloc(sizeof(redirect*));
    redir->in_file = NULL;
    redir->out_file = NULL;
    // Tokenlist in redir to ensure redirection tokens aren't passed to execv as input
    redir->tokens = new_tokenlist();

    for (int i = 0; i < tokens->size; i++)
    {
        if (strcmp(tokens->items[i], ">") == 0 || strcmp(tokens->items[i], "<") == 0)
        {
            if (i+1 >= tokens->size)
            {
                fprintf(stderr, "Expected a filename after %s", tokens->items[i]);
                return NULL;
            }
            if (strcmp(tokens->items[i], ">") == 0)
            { // Token is for outfile
                char * out_file = (char *)malloc(strlen(tokens->items[i+1]) + 1);
                strcpy(out_file, tokens->items[i+1]);
                redir->out_file = out_file;
                out_file = NULL;
            }
            if (strcmp(tokens->items[i], "<") == 0)
            { // Token is for infile
                if (access(tokens->items[i+1], R_OK) == 0)
                { // Token is readable, okay to add
                    char * in_file = (char *)malloc(strlen(tokens->items[i+1]) + 1);
                    strcpy(in_file, tokens->items[i+1]);
                    redir->in_file = in_file;
                    in_file = NULL;
                }
                else
                {
                    fprintf(stderr, "File %s is not readable.", tokens->items[i+1]);
                    return NULL;
                }
            }
        }
        else
        { //Append to tokenlist without IO redirection tokens (so it can be passed to execv without issue)
            if (i-1 >= 0)
            { // Make sure not indexing out of bounds if i == 0
                if (strcmp(tokens->items[i-1], ">") != 0 && strcmp(tokens->items[i-1], "<") != 0)
                { // Token is not an input or output filename, append it to tokenlist
                    add_token(redir->tokens, tokens->items[i]);
                }
            }
            else if (i == 0)
            { // Can access first element with no issues, add command
                add_token(redir->tokens, tokens->items[i]);
            }
        }
    }
    return redir;
}