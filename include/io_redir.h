#include "lexer.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

redirect * get_redirection(const tokenlist * tokens);