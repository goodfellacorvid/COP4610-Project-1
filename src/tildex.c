#include "tildex.h"
#include <stdlib.h>
#include <string.h>


//Checks if the first or second character of the token being checked
static bool needs_tilde_expansion(const char *token)
{
	return token[0] == '~' && (token[1] == '\0' || token[1] == '/');
}


//Goes through all the tokens and sees if any of them need a tilde expansion. 
//If yes, replaces the ~ shortcut with the full length address path. (~/test1 becomes /home/user/test1)
tokenlist *expand_tilde(tokenlist *tokens)
{
	const char *home = getenv("HOME");

	if (home == NULL)
		return tokens;

	for (size_t i = 0; i < tokens->size; i++) {
		char *token = tokens->items[i];
		if (!needs_tilde_expansion(token))
			continue;

		const char *rest = token + 1;
		char *expanded = malloc(strlen(home) + strlen(rest) + 1);
		if (expanded == NULL)
			continue;

		strcpy(expanded, home);
		strcat(expanded, rest);

		free(token);
		tokens->items[i] = expanded;
	}
	return tokens;
}