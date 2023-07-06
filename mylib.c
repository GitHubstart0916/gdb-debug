#include"mylib.h"
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

void run() {
    printf("func run\n");
    int ans = 0;
    while(1) {
        printf("ans is %d\n", ans);
        ans++;
        sleep(1);
    }
    return;
}