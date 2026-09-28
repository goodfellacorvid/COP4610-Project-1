#include "lexer.h"
#include "env_var.h"
#include "tildex.h"
#include "path_search.h"
#include "extern_exec.h"
#include "intern_exec.h"
#include "io_redir.h"
#include "piping.h"
#include "bg_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	//Get environment variables for prompt
	char *user = getenv("USER");
	char *machine = getenv("MACHINE");

	init_bg_jobs(); // initializing parallel arrays for background processing

	while (1) {
		check_bg_jobs(); //checking for finished processs

		printf("%s@%s:%s> ", user, machine, getenv("PWD"));

		/* input contains the whole command
		 * tokens contains substrings from input split by spaces
		 */

		char *input = get_input();
		//printf("whole input: %s\n", input);

		tokenlist *tokens = get_tokens(input);

		//preventing empty input crashes (segfault occured while testing background processing)
		if(tokens->size == 0){
			free(input);
			free_tokens(tokens);
			continue; // skips the execution and loops back to print a new prompt
		}

		tokens = expand_tilde(tokens);
		tokens = expand_env_variables(tokens); // Expand environment variables

		// detecting and removing '&' flag
		int is_background = 0;
		if (tokens->size > 0 && strcmp(tokens->items[tokens->size - 1], "&") == 0) {
			is_background = 1;
			free(tokens->items[tokens->size - 1]);
			tokens->items[tokens->size - 1] = NULL;
			tokens->size--;
		}

		char *pathname = search_for_path(tokens->items[0]); // Get pathname of command to execute

		for (int i = 0; i < tokens->size; i++) {
			printf("token %d: (%s)\n", i, tokens->items[i]);
		}
		
		redirect * redir = get_redirection(tokens);

		// Some test code to make sure redir has valid values, ignore this
		// if (redir)
		// {
		// 	printf("Desired redirection:\n");
		// 	printf("Tokenlist: \n");
		// 	for (int j = 0; j < redir->tokens->size; j++)
		// 	{
		// 		printf("%s ", redir->tokens->items[j]);
		// 	}
		// 	printf("\n");
		// 	if (redir->in_file)
		// 	{
		// 		printf("Desired input: %s\n", redir->in_file);
		// 	}
		// 	if (redir->out_file)
		// 	{
		// 		printf("Desired output: %s\n", redir->out_file);
		// 	}
		// }

		//intercepting piped commands before the shell tries to run them as normal
		//checking with if statement at the beginning
		if(count_pipes(tokens) > 0){
			execute_pipeline(tokens, is_background, input);
			record_valid_command(input);
		}else if (is_builtin(tokens->items[0]))
		{
			if (run_builtin(tokens))
				record_valid_command(input);
			if (strcmp(tokens->items[0], "exit") == 0)
			{
				free(input);
				free_tokens(tokens);
				break;
			}
		}
		else if (!redir) printf("Invalid redirection.\n");
		else if (pathname) 
		{
			external_command_exec(pathname, tokens, redir, is_background, input);
			record_valid_command(input);
			free(pathname);
		}
		else printf("Command not recognized.\n"); // Do nothing if command DNE
		

		free(input);
		free_tokens(tokens);
	}

	return 0;
}

char *get_input(void) {
	char *buffer = NULL;
	int bufsize = 0;
	char line[5];
	while (fgets(line, 5, stdin) != NULL)
	{
		int addby = 0;
		char *newln = strchr(line, '\n');
		if (newln != NULL)
			addby = newln - line;
		else
			addby = 5 - 1;
		buffer = (char *)realloc(buffer, bufsize + addby);
		memcpy(&buffer[bufsize], line, addby);
		bufsize += addby;
		if (newln != NULL)
			break;
	}
	buffer = (char *)realloc(buffer, bufsize + 1);
	buffer[bufsize] = 0;
	return buffer;
}

tokenlist *new_tokenlist(void) {
	tokenlist *tokens = (tokenlist *)malloc(sizeof(tokenlist));
	tokens->size = 0;
	tokens->items = (char **)malloc(sizeof(char *));
	tokens->items[0] = NULL; /* make NULL terminated */
	return tokens;
}

void add_token(tokenlist *tokens, char *item) {
	int i = tokens->size;

	tokens->items = (char **)realloc(tokens->items, (i + 2) * sizeof(char *));
	tokens->items[i] = (char *)malloc(strlen(item) + 1);
	tokens->items[i + 1] = NULL;
	strcpy(tokens->items[i], item);

	tokens->size += 1;
}

tokenlist *get_tokens(char *input) {
	char *buf = (char *)malloc(strlen(input) + 1);
	strcpy(buf, input);
	tokenlist *tokens = new_tokenlist();
	char *tok = strtok(buf, " ");
	while (tok != NULL)
	{
		add_token(tokens, tok);
		tok = strtok(NULL, " ");
	}
	free(buf);
	return tokens;
}

void free_tokens(tokenlist *tokens) {
	for (int i = 0; i < tokens->size; i++)
		free(tokens->items[i]);
	free(tokens->items);
	free(tokens);
}
