
#include "producer.h"
#include "consumer.h"
#include "queue.h"

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int
main (void)
{
  pthread_t thread_producer;
  pthread_t thread_consumer;
  int res;

  srand(time(NULL));

  // prepare the queue
  queue_init();

  // start producer and consumer threads
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

  // monitor their progress
  monitor();
}
