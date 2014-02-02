#ifndef MP_OSDEP_THREADS_H_
#define MP_OSDEP_THREADS_H_

#include <stdbool.h>
#include <pthread.h>

struct timespec mpthread_get_deadline(double timeout);

int mpthread_cond_timed_wait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                             double timeout);

int mpthread_mutex_init_recursive(pthread_mutex_t *mutex);


typedef void (*mp_dispatch_fn)(void *data);
struct mp_dispatch_queue;

struct mp_dispatch_queue *mp_dispatch_create(void *talloc_parent);
void mp_dispatch_set_wakeup_fn(struct mp_dispatch_queue *queue,
                               void (*wakeup_fn)(void *wakeup_ctx),
                               void *wakeup_ctx);
void mp_dispatch_enqueue(struct mp_dispatch_queue *queue,
                         mp_dispatch_fn fn, void *fn_data);
void mp_dispatch_enqueue_autofree(struct mp_dispatch_queue *queue,
                                  mp_dispatch_fn fn, void *fn_data);
void mp_dispatch_run(struct mp_dispatch_queue *queue,
                     mp_dispatch_fn fn, void *fn_data);
void mp_dispatch_queue_process(struct mp_dispatch_queue *queue, double timeout);
void mp_dispatch_suspend(struct mp_dispatch_queue *queue);
void mp_dispatch_resume(struct mp_dispatch_queue *queue);
void mp_dispatch_lock(struct mp_dispatch_queue *queue);
void mp_dispatch_unlock(struct mp_dispatch_queue *queue);

#endif
