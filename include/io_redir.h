#include "lexer.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

redirect * get_redirection(tokenlist * tokens);