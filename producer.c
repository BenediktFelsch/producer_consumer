
#include "producer.h"

#include "main.h"
#include "queue.h"
#include "util.h"

#include <stdlib.h>
#include <pthread.h>

static pthread_mutex_t produce_mutex = PTHREAD_MUTEX_INITIALIZER;

static void produce_element(void)
{
    static size_t n = 0;

    pthread_mutex_lock(&produce_mutex);
    struct element e = { n++ };
    pthread_mutex_unlock(&produce_mutex);

    wait_random_time();
    enqueue(e);
}


thread_helper_return_t
produce (void *arg)
{
  (void)arg;

  while (1)
    produce_element();

  return 0;
}
