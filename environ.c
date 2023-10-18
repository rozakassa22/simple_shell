#include "shell.h"

char **_getenv(const char *var);
char **_copyenv(void);
void free_env(void);

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a double pointer to the new copy.
 */

char **_copyenv(void) {
    char **new_environ;
    size_t new_size;
    int new_index;

    for (new_size = 0; environ[new_size]; new_size++)
        ;

    new_environ = malloc(sizeof(char *) * (new_size + 1));
    if (!new_environ)
        return (NULL);

    for (new_index = 0; environ[new_index]; new_index++) {
        new_environ[new_index] = malloc(_strlen(environ[new_index]) + 1);

        if (!new_environ[new_index]) {
            for (new_index--; new_index >= 0; new_index--)
                free(new_environ[new_index]);
            free(new_environ);
            return (NULL);
        }
        _strcpy(new_environ[new_index], environ[new_index]);
    }
    new_environ[new_index] = NULL;

    return (new_environ);
}

/**
 * free_env - Frees the the environment copy.
 */
void _free_env(void) {
    int new_index;

    for (new_index = 0; environ[new_index]; new_index++)
        free(environ[new_index]);
    free(environ);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */

char **_getenv(const char *var) {
    int new_index, length;

    length = _strlen(var);
    for (new_index = 0; environ[new_index]; new_index++) {
        if (_strncmp(var, environ[new_index], length) == 0)
            return (&environ[new_index]);
    }

    return (NULL);
}
