// Expose non-standard GNU-specific extensions, low-level Linux system
// functions, and all standard POSIX features.
#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Beginning splicing\n");
  int pipfd[2];
  pipe(pipfd); // Create the required pipe

  int status;
  // Splice 100 bytes from standard input into the pipe
  status = splice(STDIN_FILENO, NULL, pipfd[1], NULL, 100, SPLICE_F_MOVE);
  printf("[Spliced in %d bytes]\n", status);

  // Splice those 100 bytes out of the pipe into standard output
  status = splice(pipfd[0], NULL, STDOUT_FILENO, NULL, 100, SPLICE_F_MOVE);
  printf("[Spliced out %d bytes]\n", status);

  return 0;
}
