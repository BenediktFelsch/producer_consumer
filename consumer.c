
#include "consumer.h"

#include "main.h"
#include "queue.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>

static void
consume_element (void)
{
  static size_t n = 0;

  // retrieve an element from the queue
  struct element e = dequeue();

  // make sure we are consistent
  if (e.id != n)
    {
      fprintf(stderr, "CORRUPTION DETECTED! expected id %zu, got id %zu\n", n, e.id);
      abort();
    }
  n++;

  // pretend to operate on the element
  wait_random_time();
}

thread_helper_return_t
consume (void *arg)
{
  (void)arg;

  while (1)
    consume_element();

  return 0;
}
