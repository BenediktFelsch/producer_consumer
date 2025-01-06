
#include "consumer.h"

#include "main.h"
#include "queue.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t consume_mutex = PTHREAD_MUTEX_INITIALIZER;

static void consume_element(void)
{
    static size_t n = 0;
    struct element e = dequeue();

    pthread_mutex_lock(&consume_mutex);
    if (e.id != n)
    {
        fprintf(stderr, "CORRUPTION DETECTED! expected id %zu, got id %zu\n", n, e.id);
        abort();
    }
    n++;
    pthread_mutex_unlock(&consume_mutex);

    wait_random_time();
}

thread_helper_return_t
consume (void *arg)
{
  (void)arg;

  while (1)
    consume_element();

  return 0;
}
