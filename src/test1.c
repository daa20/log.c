#include <stdio.h>
#include "log.h"

#if 0
pthread_mutex_t MUTEX_LOG;

void log_lock(bool lock, void* udata)
{
    pthread_mutex_t *LOCK = (pthread_mutex_t*)(udata);
    if (lock) {
        pthread_mutex_lock(LOCK);
    } else {
        pthread_mutex_unlock(LOCK);
    }
}

void log_test2(void)
{
    log_set_level(0);
    log_set_quiet(0);

    pthread_mutex_init(&MUTEX_LOG, NULL);
    log_set_lock(log_lock, &MUTEX_LOG);

    /* Insert threaded application code here... */
    log_info("I'm threadsafe");

    pthread_mutex_destroy(&MUTEX_LOG);
}
#endif

void log_test1(void)
{
    log_set_level(0);
    log_set_quiet(0);

    FILE *fp1, *fp2;
    fp1 = fopen("./log_info.txt", "ab");
    if (fp1 == NULL) {
        fprintf(stderr, "Faied to open file");
        return;
    }

    fp2 = fopen("./log_debug.txt", "ab");
    if (fp2 == NULL) {
        fprintf(stderr, "Faied to open file");
        return;
    }

    log_add_fp(fp1, LOG_INFO);
    log_add_fp(fp2, LOG_DEBUG);

    log_trace("trace");
    log_debug("debug");
    log_info("info");
    log_warn("warn");
    log_error("error");
    log_fatal("fatal");

    fclose(fp2);
    fclose(fp1);
}

int main(int argc, char *const argv[])
{
    log_test1();
    //log_test2();
    return 0;
}


