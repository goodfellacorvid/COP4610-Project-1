#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "lexer.h"

bool external_command_exec(const char * pathname, tokenlist * tokens);