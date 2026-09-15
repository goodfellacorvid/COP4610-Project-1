#include <string.h>
#include <stdbool.h>
#include "lexer.h"


bool is_env_var(const char *temp);
tokenlist* expand_env_variables(tokenlist * tokens);