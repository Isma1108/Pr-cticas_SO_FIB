#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

//Faltaria el control de errores

int main() {
  int pipe_fd[2];
  pipe(pipe_fd);
  int pid = fork();
  if (pid == 0) {
    close(0);
    dup(pipe_fd[0]);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    execlp("cat", "cat", (char *)NULL);
  }
  close(pipe_fd[0]);
  char buff[128];
  sprintf(buff, "Inicio\n");
  write(pipe_fd[1], buff, strlen(buff));
  close(pipe_fd[1]);

  waitpid(-1, NULL, 0);
  sprintf(buff, "Fin\n");
  write(1, buff, strlen(buff));
}
