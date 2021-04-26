
#include "util.h"
#include "queue.h"
#include "main.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#  include <windows.h>
#else
#  include <unistd.h>
#  include <pthread.h>
#endif

void
wait_random_time (void)
{
	volatile size_t i;
	size_t max_i = (2 << 13) + rand() % (2 << 13);

	for (i = 0; i < max_i; ++i);
}

extern volatile struct element queue[];
extern size_t head_r;
extern size_t head_w;

void
monitor (void)
{
  long long int window[10] = { 0 };
  size_t n = 0;
  size_t last = 0;

  while (1)
    {
      size_t processed;
      double throughput;
      size_t filled;
      int i;

      int r = head_r;
      processed = queue[r].id - last;
      last = queue[r].id;
      window[n++] = processed;
      n %= 10;

      throughput = 0;
      for (i = 0; i < 10; ++i)
        throughput += window[i];
      throughput /= MONITOR_INTERVAL / 100000.0;

      filled = (head_r - head_w) % QUEUE_CAPACITY;
      printf("filled %zu; avail: %zu; current: %zu (%.2f/s)\n", filled, QUEUE_CAPACITY - filled, queue[head_r].id, throughput);

#ifdef _WIN32
      Sleep(MONITOR_INTERVAL / 1000);
#else
      usleep(MONITOR_INTERVAL);
#endif
    }
}
