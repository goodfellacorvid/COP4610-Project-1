#include "env_var.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_env_var(const char *temp)
{
    if (temp[0] == '$')
    {
        char *env = getenv(temp + 1);
        if (env)
        {
            printf("Environment variable found: %s\n", env);
            return true;
        }
    }
    return false;
}