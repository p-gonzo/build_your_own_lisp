#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
char os[] = "Windows";

static char buffer[2048];

/*Fake readline function*/
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc((strlen(buffer) + 1));
  strcpy(cpy, buffer);
  cpy[strlen(cpy) -1] = '\0';
  return cpy;
}

#else
char os[] = "OSX";
#include<editline/readline.h>
#endif




int main(int argc, char** argv) {
  
  char version[50] = "Lispy Verison 1.0 on ";
  strcat(version, os);
  puts(version);
  puts("Press Ctrl+c to Exit\n");
  
  while (1) {
    char* input = readline("lispy> ");
    add_history(input);
    printf("No you're a %s\n", input);
    free(input);
  }

  return 0;
};