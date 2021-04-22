
#include "producer.h"
#include "consumer.h"
#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#  include <windows.h>
#elif (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
#  include <pthread.h>
#  include <sys/time.h>
#else
#  error Unsupported plattform
#endif

int
main (void)
{
#ifdef _WIN32
  HANDLE thread_producer;
  HANDLE thread_consumer;
#else
  pthread_t thread_producer;
  pthread_t thread_consumer;
#endif

  int res;

  srand(time(NULL));

  // prepare the queue
  queue_init();

  // start producer and consumer threads
#ifdef _WIN32
  thread_producer = CreateThread(NULL, 0, &produce, NULL, 0, NULL);
  if (thread_producer == NULL)
    {
      fprintf(stderr, "error: CreateThread (#%d)\n", GetLastError());
      return 3;
    }
  thread_consumer = CreateThread(NULL, 0, &consume, NULL, 0, NULL);
  if (thread_consumer == NULL)
    {
      fprintf(stderr, "error: CreateThread (#%d)\n", GetLastError());
      return 3;
    }
#else
  res = pthread_create(&thread_producer, NULL, &produce, NULL);
  if (res != 0)
    {
      perror("pthread_create");
      return 1;
    }
  res = pthread_create(&thread_consumer, NULL, &consume, NULL);
  if (res != 0)
    {
      perror("pthread_create");
      return 1;
    }
#endif

  // monitor their progress
  monitor();
}
