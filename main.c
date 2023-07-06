#include<stdio.h>
#include<pthread.h>
#include<syscall.h>
#include<stdlib.h>
#include<dlfcn.h>
#include<unistd.h>

void *loop(void* arg) {
    void* handler = dlopen("./libmylib.so", RTLD_LAZY);
    if (handler == NULL)
    {
        printf("Error:%s\n", dlerror());
        exit(-1);
    }
    
    void (*run)() = (void (*)()) dlsym(handler, "run");
    run();
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, loop, NULL);
    if (rc) {

    }

    pthread_join(thread, NULL);
    return 0;
}