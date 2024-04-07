#include "shell.h"
#define MAX_LINE 80 /* The maximum length command */

int main(int argc, char **argv) {
  if (argc == 2 && equal(argv[1], "--interactive")) {
    return interactiveShell();
  } else {
    return runTests();
  }
}

// interactive shell to process commands
int interactiveShell() {
  bool should_run = true;
  char *line = calloc(1, MAXLINE);
  char *args[MAX_LINE/2 + 1]; /* command line arguments */
  while (should_run) {
    printf(PROMPT);
    fflush(stdout);
    int n = fetchline(&line);
    printf("read: %s (length = %d)\n", line, n);
    // ^D results in n == -1
    tokenize(&line, &args);

    parse_args();

    if (n == -1 || equal(line, "exit")) {
      should_run = false;
      continue;
    }
    if (equal(line, "")) {
      continue;
    }
    processLine(line);
  }
  free(line);
  return 0;
}

void processLine(char *line) { printf("processing line: %s\n", line); }

int runTests() {
  printf("*** Running basic tests ***\n");
  char lines[7][MAXLINE] = {
      "ls",      "ls -al", "ls & whoami ;", "ls > junk.txt", "cat < junk.txt",
      "ls | wc", "ascii"};
  for (int i = 0; i < 7; i++) {
    printf("* %d. Testing %s *\n", i + 1, lines[i]);
    processLine(lines[i]);
  }

  return 0;
}

// return true if C-strings are equal
bool equal(char *a, char *b) { return (strcmp(a, b) == 0); }

// read a line from console
// return length of line read or -1 if failed to read
// removes the \n on the line read
int fetchline(char **line) {
  size_t len = 0;
  size_t n = getline(line, &len, stdin);
  if (n > 0) {
    (*line)[n - 1] = '\0';
  }
  return n;
}

void tokenize(char **line, char **args) {
  char *pch;

  pch = strtok(line, " ");
  int num = 0;
  while (pch != NULL) {
    printf("Token %d: %s\n", num, pch);
    args[num] = pch;
    ++num;
    pch = strtok(NULL, " ");
  }
}

void parse_args(char **args) {
  char cmd[] = "";
  for (int i = 0; i < len(args); ++i) {
    // might need to start at index 1
    if (args[i] !=  '|' && args[i] !=  ';' && args[i] !=  '&' && i == len(args) - 1) {
      	strcat(cmd, args[i]);
    } else {
      execvp(arg);
    }
  }
}
