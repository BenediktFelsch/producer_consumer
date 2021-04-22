
#include "producer.h"

#include "main.h"
#include "queue.h"

#include <stdlib.h>

#ifndef _WIN32
#  include <unistd.h>
#endif

static void
produce_element (void)
{
  static size_t n = 0;

  // produce an element
  struct element e = { n };
  n++;
  
#ifdef _WIN32
  Sleep((USLEEP_START + rand() % USLEEP_RANGE) / 1000);
#else
  usleep(USLEEP_START + rand() % USLEEP_RANGE);
#endif

  // add it to the queue
  enqueue(e);
}

#ifdef _WIN32
DWORD WINAPI
produce (LPVOID arg)
#else
void*
produce (void *arg)
#endif
{
  while (1)
    produce_element();

  return 0;
}
