
#include "consumer.h"

#include "main.h"
#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

#ifndef _WIN32
#  include <unistd.h>
#endif

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
#ifdef _WIN32
  Sleep((USLEEP_START + rand() % USLEEP_RANGE) / 1000);
#else
  usleep(USLEEP_START + rand() % USLEEP_RANGE);
#endif
}

#ifdef _WIN32
DWORD WINAPI
consume (LPVOID arg)
#else
void*
consume (void *arg)
#endif
{
  while (1)
    consume_element();

  return 0;
}
