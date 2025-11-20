#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  // Flush after every printf
  setbuf(stdout, NULL);

  printf("$ ");

  // Read users input
  int max_size = 1024;
  char input[max_size];

  while (fgets(input, max_size, stdin) != NULL)
  {
    // check if input is given
    input[strcspn(input, "\n")] = '\0';
    if (strcmp(input, "exit 0") == 0 || strcmp(input, "exit 1") == 0)
      exit(0);

    printf("%s: command not found\n", input);
    printf("$ ");
  }

  return 0;
}
