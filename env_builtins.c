#include "shell.h"
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_env(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */

int shellby_env(char **args, char __attribute__((__unused__)) **front) {
    int new_index;
    char new_line = '\n';

    if (!environ)
        return (-1);

    for (new_index = 0; environ[new_index]; new_index++) {
        write(STDOUT_FILENO, environ[new_index], _strlen(environ[new_index]));
        write(STDOUT_FILENO, &new_line, 1);
    }

    (void)args;
    return (0);
}

/**
 * shellby_setenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */

int shellby_setenv(char **args, char __attribute__((__unused__)) **front) {
    char **new_env_var = NULL, **new_environ, *new_value;
    size_t new_size;
    int new_index;

    if (!args[0] || !args[1])
        return (create_error(args, -1));

    new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
    if (!new_value)
        return (create_error(args, -1));
    _strcpy(new_value, args[0]);
    _strcat(new_value, "=");
    _strcat(new_value, args[1]);

    new_env_var = _getenv(args[0]);
    if (new_env_var) {
        free(*new_env_var);
        *new_env_var = new_value;
        return (0);
    }
    for (new_size = 0; environ[new_size]; new_size++)
        ;

    new_environ = malloc(sizeof(char *) * (new_size + 2));
    if (!new_environ) {
        free(new_value);
        return (create_error(args, -1));
    }

    for (new_index = 0; environ[new_index]; new_index++)
        new_environ[new_index] = environ[new_index];

    free(environ);
    environ = new_environ;
    environ[new_index] = new_value;
    environ[new_index + 1] = NULL;

    return (0);
}

/**
 * shellby_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */

int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front) {
    char **new_env_var, **new_environ;
    size_t new_size;
    int new_index, new_index2;

    if (!args[0])
        return (create_error(args, -1));
    new_env_var = _getenv(args[0]);
    if (!new_env_var)
        return (0);

    for (new_size = 0; environ[new_size]; new_size++)
        ;

    new_environ = malloc(sizeof(char *) * new_size);
    if (!new_environ)
        return (create_error(args, -1));

    for (new_index = 0, new_index2 = 0; environ[new_index]; new_index++) {
        if (*new_env_var == environ[new_index]) {
            free(*new_env_var);
            continue;
        }
        new_environ[new_index2] = environ[new_index];
        new_index2++;
    }
    free(environ);
    environ = new_environ;
    environ[new_size - 1] = NULL;

    return (0);
}
