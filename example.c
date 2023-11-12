#include <stdio.h>

/**
 *print_hello- Prints "Hello, world!"
 * main - Entry point of the program
 *int num - Stores the value 10 
 * main - Entry point of the program
 *Return: Always 0 (Success)
 * **/


void print_hello();

int main() {
    
    int num = 10;
    
    
    print_hello();
    
    
    printf("The value of num is: %d\n", num);
    
    return 0;
}


void print_hello() {
    printf("Hello, world!\n");
}
