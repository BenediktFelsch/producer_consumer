
#include "producer.h"

#include "main.h"
#include "queue.h"

#include <unistd.h>
#include <stdlib.h>

static void
produce_element (void)
{
  static size_t n = 0;

  // produce an element
  struct element e = { n };
  n++;
  usleep(USLEEP_START + rand() % USLEEP_RANGE);

  // add it to the queue
  enqueue(e);
}

void*
produce (void *arg)
{
  while (1)
    produce_element();

  return NULL;
}
