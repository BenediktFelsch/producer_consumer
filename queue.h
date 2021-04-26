#ifndef QUEUE_H
#define QUEUE_H

#include <sys/types.h>

struct element
{
  size_t id;
};

void queue_init(void);

void enqueue(struct element);

struct element dequeue(void);

#endif
