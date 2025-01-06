#include "queue.h"

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

volatile struct element queue[QUEUE_CAPACITY] = { 0 };
size_t head_r = 0;
size_t head_w = 0;
sem_t sem_queue_avail;
sem_t sem_queue_used;
pthread_mutex_t queue_mutex;

void
queue_init (void)
{
  sem_init(&sem_queue_avail, 0, QUEUE_CAPACITY);
  sem_init(&sem_queue_used, 0, 0);
  pthread_mutex_init(&queue_mutex, NULL);
}

void
enqueue (struct element e)
{
  // TODO: protect this function from concurrent access using semaphores

  sem_wait(&sem_queue_avail); // Wait for an available slot
  pthread_mutex_lock(&queue_mutex); // Protect critical section

  queue[head_w] = e;
  head_w = (head_w + 1) % QUEUE_CAPACITY;

  pthread_mutex_unlock(&queue_mutex);
  sem_post(&sem_queue_used); // Signal that an element is available
}

struct element
dequeue (void)
{
  struct element e;

  // TODO: protect this function from concurrent access using semaphores

  sem_wait(&sem_queue_used); // Wait for an available element
  pthread_mutex_lock(&queue_mutex); // Protect critical section

  e = queue[head_r];
  head_r = (head_r + 1) % QUEUE_CAPACITY;

  pthread_mutex_unlock(&queue_mutex);
  sem_post(&sem_queue_avail); // Signal that a slot is available


  return e;
}
