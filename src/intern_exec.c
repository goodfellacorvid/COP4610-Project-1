//Need this line to compile, because the Makefile uses -std=c99
#define _POSIX_C_SOURCE 200809L

#include "intern_exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define HISTORY_SIZE 3
#define MAX_COMMAND_LEN 200

//Holds the most recent valid command lines
static char history[HISTORY_SIZE][MAX_COMMAND_LEN + 1];
static int history_count = 0;

//Checks if the input is an internal command
bool is_builtin(const char *command)
{
	return strcmp(command, "exit") == 0 || strcmp(command, "cd") == 0 ||
	       strcmp(command, "jobs") == 0;
}

//Records the last 3 valid commands, and overrides the previous ones if more than 3 commands are called
void record_valid_command(const char *command_line)
{
	int slot = history_count % HISTORY_SIZE;
	strncpy(history[slot], command_line, MAX_COMMAND_LEN);
	history[slot][MAX_COMMAND_LEN] = '\0';
	history_count++;
}

//Prints the last three valid commands, oldest first, or fewer if needed
static void print_history(void)
{
	if (history_count == 0) {
		printf("No valid commands.\n");
		return;
	}

	if (history_count < HISTORY_SIZE) {
		int last = (history_count - 1) % HISTORY_SIZE;
		printf("Last valid command:\n[1]: %s\n", history[last]);
		return;
	}

	printf("Last (%d) valid commands:\n", HISTORY_SIZE);
	for (int i = 0; i < HISTORY_SIZE; i++) {
		int slot = (history_count - HISTORY_SIZE + i) % HISTORY_SIZE;
		printf("[%d]: %s\n", i + 1, history[slot]);
	}
}

//Waits for any remaining child processes to finish, then prints history
static bool builtin_exit(void)
{
	while (wait(NULL) > 0)
		;

	print_history();
	return false;
}

//Changes directory to the argument, or $HOME if none, and updates $PWD
static bool builtin_cd(tokenlist *tokens)
{
	if (tokens->size > 2) {
		fprintf(stderr, "cd: too many arguments\n");
		return false;
	}

	const char *target = (tokens->size == 1) ? getenv("HOME") : tokens->items[1];
	if (target == NULL) {
		fprintf(stderr, "cd: HOME not set\n");
		return false;
	}

	struct stat info;
	if (stat(target, &info) != 0) {
		fprintf(stderr, "cd: %s: No such file or directory\n", target);
		return false;
	}
	if (!S_ISDIR(info.st_mode)) {
		fprintf(stderr, "cd: %s: Not a directory\n", target);
		return false;
	}
	if (chdir(target) != 0) {
		perror("cd");
		return false;
	}

	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		setenv("PWD", cwd, 1);
	return true;
}

//Lists active background jobs (connects to Part 8s job table later)
static bool builtin_jobs(void)
{
	printf("No active background processes.\n");
	return true;
}

bool run_builtin(tokenlist *tokens)
{
	const char *command = tokens->items[0];

	if (strcmp(command, "exit") == 0)
		return builtin_exit();
	if (strcmp(command, "cd") == 0)
		return builtin_cd(tokens);
	return builtin_jobs();
}