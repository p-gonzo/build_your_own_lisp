#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpc.h"

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

int number_of_nodes(mpc_ast_t* t) {
  printf("%s %s\n ", t->tag, t->contents);
  if (t->children_num == 0) { return 1; }
  if (t->children_num >= 1) {
    int total = 1;
    for (int i = 0; i < t->children_num; i++) {
      total = total + number_of_nodes(t->children[i]);
    }
    return total;
  }
  return 0;
}


int main(int argc, char** argv) {

  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
  "                                                         \
  number        :  /-?[0-9]+(\\.[0-9]*)?/ ;                             \
  operator      :  '+' | '-' | '*' | '/' | '%' ;            \
  expr          :  <number> | '(' <operator> <expr>+ ')';   \
  lispy         : /^/ <operator> <expr>+ /$/ ;              \
  ",
  Number, Operator, Expr, Lispy);
  
  char version[50] = "Lispy Verison 1.0 on ";
  strcat(version, os);
  puts(version);
  puts("Press Ctrl+c to Exit\n");
  
  while (1) {
    char* input = readline("lispy> ");
    add_history(input);
    /* Attempt to parse the user input */
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      /* On success, print AST */
      // mpc_ast_print(r.output);
      printf("The total number of nodes was: %i\n", number_of_nodes(r.output));
      
      mpc_ast_delete(r.output);
    } else {
      /* Otherwise, print the error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
    free(input);
  }

  mpc_cleanup(4, Number, Operator, Expr, Lispy);
  return 0;
};