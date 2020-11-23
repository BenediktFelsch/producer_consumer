
#include "queue.h"

#include "main.h"

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

volatile struct element queue[QUEUE_CAPACITY] = { 0 };
size_t head_r = 0;
size_t head_w = 0;
volatile size_t queue_used = 0;
volatile size_t queue_avail = QUEUE_CAPACITY;

void
queue_init (void)
{
  // noop
}

void
enqueue (struct element e)
{
  while (queue_avail == 0);

  queue[head_w] = e;
  head_w = (head_w + 1) % QUEUE_CAPACITY;
  queue_used++;

  queue_avail--;
}

struct element
dequeue (void)
{
  while (queue_used == 0);

  struct element e = queue[head_r];
  head_r = (head_r + 1) % QUEUE_CAPACITY;
  queue_avail++;

  queue_used--;

  return e;
}

void
monitor (void)
{
  size_t window[10] = { 0 };
  size_t n = 0;
  size_t last = 0;

  while (1)
    {
      size_t processed = queue[head_r].id - last;
      last = queue[head_r].id;
      window[n++] = processed;
      n %= 10;

      double throughput = 0;
      int i;
      for (i = 0; i < 10; ++i)
        throughput += window[i];
      throughput /= MONITOR_INTERVAL / 100000.0;

      size_t filled = (head_r - head_w) % QUEUE_CAPACITY;
      printf("filled %zu; avail: %zu; current: %zu (%.2f/s)\n", filled, QUEUE_CAPACITY - filled, queue[head_r].id, throughput);

      usleep(MONITOR_INTERVAL);
    }
}
