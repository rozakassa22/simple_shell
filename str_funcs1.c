#include "shell.h"

char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);

/**
 * _strlen - Returns the length of a string.
 * @s: A pointer to the characters string.
 *
 * Return: The length of the character string.
 */
int _strlen(const char *s)
{
	int lengthh = 0;

	if (!s)
		return (lengthh);
	for (lengthh = 0; s[lengthh]; lengthh++)
		;
	return (lengthh);
}

/**
 * _strcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t index;

	for (index = 0; src[index] != '\0'; index++)
		dest[index] = src[index];
	dest[index] = '\0';
	return (dest);
}

/**
 * _strcat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTempp;

	destTemp = dest;
	srcTempp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTempp != '\0')
		*destTemp++ = *srcTempp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t index;

	for (index = 0; index < n && src[index] != '\0'; index++)
		dest[dest_len + index] = src[index];
	dest[dest_len + index] = '\0';

	return (dest);
}
