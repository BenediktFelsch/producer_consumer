
#include "queue.h"

#include "main.h"

#include <stdio.h>
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

