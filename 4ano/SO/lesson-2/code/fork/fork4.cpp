#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "delays.h"
#include "process.h"

int main(int argc, char *argv[])
{
  if (argc != 2) {
      fprintf(stderr, "Uso: %s <nome_do_ficheiro>\n", argv[0]);
      return EXIT_FAILURE;
  }

  printf("Before the fork: PID = %d, PPID = %d\n", getpid(), getppid());

  pid_t ret = pfork(); // equivalent to fork(), dealing internally with error situations
  if (ret == 0)
  {
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Fail opening file");
        return EXIT_FAILURE;
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("Fail redirecting stdout");
        close(fd);
        return EXIT_FAILURE;
    }

    close(fd);

    pexecl("./child", "./child", NULL);
    perror("ERROR");
    printf("why doesn't this message show up?\n");
    return EXIT_FAILURE;
  }
  else
  {
    //pwait(NULL); // equivalent to wait(.), dealing internally with error situations
    printf("I'm the parent: PID = %d, PPID = %d\n", getpid(), getppid());
    usleep(1000);
  }

  return EXIT_SUCCESS;
}