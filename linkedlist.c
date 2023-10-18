#include "shell.h"

list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);

/**
 * add_alias_end - Adds a node to the end of a alias_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */

alias_t *add_alias_end(alias_t **head, char *name, char *value) {
    alias_t *new_alias_node = malloc(sizeof(alias_t));
    alias_t *last_node;

    if (!new_alias_node)
        return (NULL);

    new_alias_node->next = NULL;
    new_alias_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
    if (!new_alias_node->name) {
        free(new_alias_node);
        return (NULL);
    }
    new_alias_node->value = value;
    _strcpy(new_alias_node->name, name);

    if (*head) {
        last_node = *head;
        while (last_node->next != NULL)
            last_node = last_node->next;
        last_node->next = new_alias_node;
    } else {
        *head = new_alias_node;
    }

    return (new_alias_node);
}
/**
 * add_node_end - Adds a node to the end of a list_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_t *add_node_end(list_t **head, char *dir) {
    list_t *new_list_node = malloc(sizeof(list_t));
    list_t *last_node;

    if (!new_list_node)
        return (NULL);

    new_list_node->dir = dir;
    new_list_node->next = NULL;

    if (*head) {
        last_node = *head;
        while (last_node->next != NULL)
            last_node = last_node->next;
        last_node->next = new_list_node;
    } else {
        *head = new_list_node;
    }

    return (new_list_node);
}

/**
 * free_alias_list - Frees a alias_t linked list.
 * @head: THe head of the alias_t list.
 */
void free_alias_list(alias_t *head) {
    alias_t *next_node;

    while (head) {
        next_node = head->next;
        free(head->name);
        free(head->value);
        free(head);
        head = next_node;
    }
}
/**
 * free_list - Frees a list_t linked list.
 * @head: The head of the list_t list.
 */
void free_list(list_t *head) {
    list_t *next_node;

    while (head) {
        next_node = head->next;
        free(head->dir);
        free(head);
        head = next_node;
    }
}
