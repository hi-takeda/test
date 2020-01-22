#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

int number = 0;

void * main_thread(void *arg) {
  sleep(1);
  number=10;
  pthread_exit(NULL);
  return NULL;
}

int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, main_thread, NULL);
  printf("main:%d\n", number);
  ///...
  pthread_join(tid, NULL);
  printf("main end:%d\n", number);
  return 0;
}
