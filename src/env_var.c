#include "env_var.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


//This function is called to see if something is a valid environment variable
bool is_env_var(const char *temp)
{
    if (temp[0] == '$')
        return getenv(temp + 1); //Returns true if env var exists
    return false;
}

//This function takes in a pointer to a tokenlist object and parses for env vars
//If an env var is found at a token, free its memory and reallocate it for the env var value
tokenlist *expand_env_variables(tokenlist *tokens)
{
    //Parse all tokens
    for (int i = 0; i < tokens->size; i++)
    {
        if (tokens->items[i][0] == '$')
        {
            if (is_env_var(tokens->items[i])) 
            { //If env var exists, re-allocate memory for its value
                const char *env_var = getenv(&tokens->items[i][1]);
                free(tokens->items[i]);
                tokens->items[i] = (char*)malloc(strlen(env_var) + 1);
                strcpy(tokens->items[i], env_var);
            }
            else
            { //If it doesn't exist, replace with empty string to flag as invalid
                free(tokens->items[i]);
                tokens->items[i] = (char*)malloc(1);
                tokens->items[i][0] = '\0';
            }
        }
    }
    return tokens;
}