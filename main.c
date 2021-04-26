
#include "producer.h"
#include "consumer.h"
#include "queue.h"
#include "thread_helper.h"

#include <stdlib.h>
#include <stdio.h>

int
main (void)
{
  thread_helper_t thread_producer;
  thread_helper_t thread_consumer;

  srand(time(NULL));

  // prepare the queue
  queue_init();

  // start producer and consumer threads
  int res = thread_helper_create(&thread_producer, &produce);
  if (res != 0)
    {
      perror("thread_helper_create");
      return 1;
    }
  res = thread_helper_create(&thread_consumer, &consume);
  if (res != 0)
    {
      perror("thread_helper_create");
      return 1;
    }

  // monitor their progress
  monitor();
}
