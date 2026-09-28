#pragma once

#include "lexer.h"

// Returns the number of pipes (0, 1, or 2) found in the input
int count_pipes(tokenlist *tokens);

// Handles splitting the tokens and executing the piped commands
void execute_pipeline(tokenlist *tokens, int is_background, char *input);

