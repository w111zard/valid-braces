#include <stdio.h>
#include <stdbool.h>

enum {
  STACK_SIZE = 1000
};

char stack[STACK_SIZE];
size_t stack_free_position = 0;

void stack_push (char item) {
  if (stack_free_position < STACK_SIZE)
    stack[stack_free_position++] = item;
  else
    printf("Error: stack is full!!!\n");
}

char stack_pop (void) {
  if (stack_free_position > 0)
    return stack[--stack_free_position];
  else
    printf("Error: stack is empty!!!\n");
}

void stack_print() {
  printf("### STACK ###\n");
  printf("pos = %ld\n", stack_free_position);
  for (int i = 0; i < stack_free_position; ++i)
    printf("#%3d = %c\n", i, stack[i]);
  printf("\n");
}

bool valid_braces (const char *braces) {
  for ( ; *(braces + 1); ++braces) {
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
      if (stack_pop() != ']')
        return false;
      break;
    }
  }

  if (stack_free_position == 1)
    return true;
  else
    return false;
}

int main() {
  char *braces = "(){}";
  bool result = valid_braces(braces);
  printf("%d\n", result);
  return 0;
}
