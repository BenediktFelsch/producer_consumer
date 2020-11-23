
#include "consumer.h"

#include "main.h"
#include "queue.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void
consume_element (void)
{
  static size_t n = 0;

  // retreive an element from the queue
  struct element e = dequeue();

  // make sure we are consistent
  if (e.id != n)
    {
      fprintf(stderr, "CORRUPTION DETECTED! expected id %zu, got id %zu\n", n, e.id);
      abort();
    }
  n++;

  // operate on the element
  usleep(USLEEP_START + rand() % USLEEP_RANGE);
}

void*
consume (void *arg)
{
  while (1)
    consume_element();

  return NULL;
}
