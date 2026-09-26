#pragma once

#include <stdbool.h>
#include "lexer.h"

// Returns true if the command name is exit, cd, or jobs
bool is_builtin(const char *command);

// Runs the built-in named by tokens->items[0].
// Returns true if it succeeded (counts as a valid command).
// exit returns false so it is not saved to the history.
bool run_builtin(tokenlist *tokens);

// Saves a command line to the history shown by exit
void record_valid_command(const char *command_line);