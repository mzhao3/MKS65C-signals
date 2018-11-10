#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

static void sighandler(int signo) {
  if (signo == SIGUSR1) {
    printf("Parent ID: %d\n", getppid());
  }

  if (signo == SIGINT) {
    int file = open("errors.txt",  O_CREAT | O_WRONLY | O_APPEND , 0777);



    if (file == -1)
      printf("%s\n", strerror(file));

    char buff[]= "program exited due to SIGINT\n";
    int a = write(file, buff, strlen(buff));

    if (a == -1)
      printf("%s\n", strerror(a));
    exit(1);

    close(file);
  }

}
int main() {

  signal(SIGUSR1, sighandler);
  signal(SIGINT, sighandler);
  while (1)  {
    sleep(1);
    printf("%d\n", getpid());
  }
  return 0;
}
