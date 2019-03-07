#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
char os[] = "Windows";
#else
char os[] = "OSX";
#endif

#include<editline/readline.h>


int main(int argc, char** argv) {
  char version[100] = "Lispy Verison 0.1 ";
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