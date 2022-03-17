#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
  STD_ERR = 2,
  STACK_SIZE = 1000
};

char stack[STACK_SIZE];
size_t stack_free_position = 0;

void stack_push (char item) {
  if (stack_free_position < STACK_SIZE)
    stack[stack_free_position++] = item;
  else {
    dprintf(STD_ERR, "Error: stack is full!\n");
    exit(1);
  }
}

char stack_pop (void) {
  if (stack_free_position > 0)
    return stack[--stack_free_position];
  else
    return 0;
}

bool valid_braces (const char *braces) {
  stack_free_position = 0; /* clear stack */

  for ( ; *braces; ++braces) {
    switch (*braces) {
    case '(':
    case '{':
    case '[':
      stack_push(*braces);
      break;

    case ')':
      if (stack_pop() != '(')
        return false;
      break;

    case '}':
      if (stack_pop() != '{')
        return false;
      break;

    case ']':
      if (stack_pop() != '[')
        return false;
      break;

    default:
      dprintf(STD_ERR, "Error: unknown character '%c'!\n", *braces);
      exit(1);
    }
  }

  return (stack_free_position == 0) ? (true) : (false);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    dprintf(STD_ERR, "Error: wrong number of the argument! Expected 2 but %d was given!\n", argc);
    exit(1);
  }

  printf("%s\n", valid_braces(argv[1]) ? "True" : "False");
  return 0;
}
