#include "path_search.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>


// This function takes in a command (like cd or ls) and searches dirs in the $PATH variable for the bin/executable
// If it is found, the pathname of the bin/executable is returned
char *search_for_path(const char *command)
{
    // Retrieve $PATH
    const char *path = getenv("PATH");

    // Operate on a deep copy of path to ensure it isn't modified
    char *path_deep_copy = (char*)malloc(strlen(path) + 1);
    strcpy(path_deep_copy, path);

    // Access each directory in $PATH
    char* pathnames = strtok(path_deep_copy, ":");

    while (pathnames != NULL) {
        char *dir = (char *)malloc(strlen(pathnames) + 1 + strlen(command) + 1); 
        
        strcpy(dir, pathnames);
        strcat(dir, "/");
        strcat(dir, command);

        // If executable for command exists in $PATH, free memory and return
        if (access(dir, X_OK) == 0) 
        {
            free(path_deep_copy);
            return dir;
        }
        
        free(dir);
        pathnames = strtok(NULL, ":");
    }
    // Executable command not found in $PATH
    free(path_deep_copy);
    return NULL;
}