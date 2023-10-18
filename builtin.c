#include "shell.h"

int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);
int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);

/**
 * get_builtin - Checks if a command matches any built-in function in the shellby program.
 * @command: The command to match.
 *
 * Return: A function reference to the corresponding builtin.
 */

int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "setenv", shellby_setenv },
		{ "unsetenv", shellby_unsetenv },
		{ "cd", shellby_cd },
		{ "alias", shellby_alias },
		{ "help", shellby_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * shellby_exit - This code snippet handles the normal termination of the shellby shell process.
 * @args: An array of arguments containing the exit value.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */

int shellby_exit(char **args, char **front) {
    int new_i, new_len_of_int = 10;
    unsigned int new_num = 0, new_max = 1 << (sizeof(int) * 8 - 1);

    if (args[0]) {
        if (args[0][0] == '+') {
            new_i = 1;
            new_len_of_int++;
        }
        for (; args[0][new_i]; new_i++) {
            if (new_i <= new_len_of_int && args[0][new_i] >= '0' && args[0][new_i] <= '9')
                new_num = (new_num * 10) + (args[0][new_i] - '0');
            else
                return (create_error(--args, 2));
        }
    }
    else {
        return (-3);
    }
    if (new_num > new_max - 1)
        return (create_error(--args, 2));
    args -= 1;
    free_args(args, front);
    free_env();
    free_alias_list(aliases);
    exit(new_num);
}

/**
 * shellby_cd - Changes the current directory of the shellby process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */

int shellby_cd(char **args, char __attribute__((__unused__)) **front) {
    char **new_dir_info, *new_line = "\n";
    char *oldpwd = NULL, *pwd = NULL;
    struct stat new_dir;

    oldpwd = getcwd(oldpwd, 0);
    if (!oldpwd)
        return (-1);

    if (args[0]) {
        if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0) {
            if ((args[0][1] == '-' && args[0][2] == '\0') ||
                    args[0][1] == '\0') {
                if (_getenv("OLDPWD") != NULL)
                    (chdir(*_getenv("OLDPWD") + 7));
            }
            else {
                free(oldpwd);
                return (create_error(args, 2));
            }
        }
        else {
            if (stat(args[0], &new_dir) == 0 && S_ISDIR(new_dir.st_mode)
                    && ((new_dir.st_mode & S_IXUSR) != 0))
                chdir(args[0]);
            else {
                free(oldpwd);
                return (create_error(args, 2));
            }
        }
    }
    else {
        if (_getenv("HOME") != NULL)
            chdir(*(_getenv("HOME")) + 5);
    }

    pwd = getcwd(pwd, 0);
    if (!pwd)
        return (-1);

    new_dir_info = malloc(sizeof(char *) * 2);
    if (!new_dir_info)
        return (-1);

    new_dir_info[0] = "OLDPWD";
    new_dir_info[1] = oldpwd;
    if (shellby_setenv(new_dir_info, new_dir_info) == -1)
        return (-1);

    new_dir_info[0] = "PWD";
    new_dir_info[1] = pwd;
    if (shellby_setenv(new_dir_info, new_dir_info) == -1)
        return (-1);
    if (args[0] && args[0][0] == '-' && args[0][1] != '-') {
        write(STDOUT_FILENO, pwd, _strlen(pwd));
        write(STDOUT_FILENO, new_line, 1);
    }
    free(oldpwd);
    free(pwd);
    free(new_dir_info);
    return (0);
}

/**
 * shellby_help - displays information regarding the built-in commands in the shellby program.
 * @args: An array of arguments.
 * @front: A reference to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
