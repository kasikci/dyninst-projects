#include<pthread.h>

pthread_t thread;

void* func(void* p) {

}

int main(int argc, char *argv[]) {
  int ret = pthread_create(&thread, NULL, func, NULL);
  return 0;
}
