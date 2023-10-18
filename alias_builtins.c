#include "shell.h"

void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_alias - A built-in command that manages aliases by printing all aliases, specific aliases, or setting a new alias.
 * @args: An array of arguments.
 * @front: A dual pointer indicating the starting point of args.
 *
 * Return: -1 denotes an error occurrence, while 0 represents the absence of errors.
 */

int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *current_alias = aliases;
	int index, result = 0;
	char *value;

	if (!args[0])
	{
		while (current_alias)
		{
			print_alias(current_alias);
			current_alias = current_alias->next;
		}
		return result;
	}

	for (index = 0; args[index]; index++)
	{
		current_alias = aliases;
		value = _strchr(args[index], '=');
		if (!value)
		{
			while (current_alias)
			{
				if (_strcmp(args[index], current_alias->name) == 0)
				{
					print_alias(current_alias);
					break;
				}
				current_alias = current_alias->next;
			}
			if (!current_alias)
				result = create_error(args + index, 1);
		}
		else
			set_alias(args[index], value);
	}

	return result;
}

/**
 * print_alias - Formats and prints the alias name='value'.
 * @alias: Reference to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}

/**
 * set_alias - Either updates an existing alias named 'name' with a new value 'value', or creates a new alias with 'name' and 'value'.
 * @var_name: Name of the alias.
 * @value: Value of the alias. First char is a '='.
 */
void set_alias(char *var_name, char *value) {
    alias_t *temp_alias = aliases;
    int new_len, new_j, new_k;
    char *new_val;

    *value = '\0';
    value++;
    new_len = _strlen(value) - _strspn(value, "'\"");
    new_val = malloc(sizeof(char) * (new_len + 1));
    if (!new_val)
        return;
    for (new_j = 0, new_k = 0; value[new_j]; new_j++) {
        if (value[new_j] != '\'' && value[new_j] != '"')
            new_val[new_k++] = value[new_j];
    }
    new_val[new_k] = '\0';
    while (temp_alias) {
        if (_strcmp(var_name, temp_alias->name) == 0) {
            free(temp_alias->value);
            temp_alias->value = new_val;
            break;
        }
        temp_alias = temp_alias->next;
    }
    if (!temp_alias)
        add_alias_end(&aliases, var_name, new_val);
}

/**
 * replace_aliases - iterates through the arguments and replaces any matching aliases with their corresponding values.
 * @args: 2D reference to the arguments.
 *
 * Return: 2D reference to the arguments.
 */

char **replace_aliases(char **args) {
    alias_t *temp_alias;
    int index;
    char *new_value;

    if (_strcmp(args[0], "alias") == 0)
        return args;

    for (index = 0; args[index]; index++) {
        temp_alias = aliases;
        while (temp_alias) {
            if (_strcmp(args[index], temp_alias->name) == 0) {
                new_value = malloc(sizeof(char) * (_strlen(temp_alias->value) + 1));
                if (!new_value) {
                    free_args(args, args);
                    return NULL;
                }
                _strcpy(new_value, temp_alias->value);
                free(args[index]);
                args[index] = new_value;
                index--;
                break;
            }
            temp_alias = temp_alias->next;
        }
    }

    return args;
}
