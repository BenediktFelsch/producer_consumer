
#include "producer.h"

#include "main.h"
#include "queue.h"
#include "util.h"

#include <stdlib.h>

static void
produce_element (void)
{
  static size_t n = 0;

  // produce an element
  struct element e = { n };
  n++;

  // pretend to take an amount of time
  wait_random_time();

  // add it to the queue
  enqueue(e);
}


thread_helper_return_t
produce (void *arg)
{
  (void)arg;

  while (1)
    produce_element();

  return 0;
}
