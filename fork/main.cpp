#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int number=0;
  pid_t pid=fork();
  if(pid==0) {
    //子プロセス側
    sleep(5);
    number=10;
    printf("child:%d\n", number);
    exit(0);
  } else {
    //親プロセス側
    printf("parent:%d\n", number);
    waitpid(pid, NULL, 0);
    printf("parent end:%d\n", number);
  }
  return 0;
}
