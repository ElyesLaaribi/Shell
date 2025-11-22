#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cmd_available 3

//  builtins array
const char *builtin_cmd[cmd_available] = {"echo", "type", "exit"};

// functions declaration
void prompt();
void read_input(char *buffer, int size);
int is_builtin(const char *cmd);
void handle_exit(const char *input);
void handle_echo(const char *input);
void handle_type(const char *input);
void process_command(const char *input);

void prompt()
{
  printf("$ ");
}

void read_input(char *buffer, int size)
{
  fgets(buffer, size, stdin);
  buffer[strcspn(buffer, "\n")] = '\0';
}

int is_builtin(const char *cmd)
{
  for (int i = 0; i < cmd_available; i++)
  {
    if (strcmp(cmd, builtin_cmd[i]) == 0)
    {
      return 1;
    }
  }
  return 0;
}

void handle_exit(const char *input)
{
  if (strcmp(input, "exit 0") == 0 || strcmp(input, "exit 1") == 0)
  {
    exit(0);
  }
}

void handle_echo(const char *input)
{
  if (strncmp(input, "echo ", 5) == 0)
  {
    printf("%s\n", input + 5);
  }
  else if (strcmp(input, "echo") == 0)
  {
    printf("\n");
  }
}

void handle_type(const char *input)
{
  if (strncmp(input, "type ", 5) != 0)
    return;

  const char *cmd = input + 5;
  if (is_builtin(cmd))
  {
    printf("%s is a shell builtin\n", cmd);
  }
  else
  {
    printf("%s: not found\n", cmd);
  }
}

void process_command(const char *input)
{
  handle_exit(input);

  if (strncmp(input, "echo", 4) == 0)
  {
    handle_echo(input);
    return;
  }

  if (strncmp(input, "type", 4) == 0)
  {
    handle_type(input);
    return;
  }

  printf("%s: command not found\n", input);
}

int main(int argc, char *argv[])
{
  // Flush after every printf
  setbuf(stdout, NULL);

  // Read users input
  int max_size = 1024;
  char input[max_size];

  prompt();

  while (1)
  {
    read_input(input, sizeof(input));
    process_command(input);
    prompt();
  }

  return 0;
}
