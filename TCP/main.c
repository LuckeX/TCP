#include <stdio.h>
#include <zconf.h>
#include <pthread.h>
#include "wrapper.h"

void *listenThread(int arg){
    printf("start listen thread\n");
    call_listento(arg);
}

int main() {
//   call_listento(8889);
    int port=8889;
    pthread_t thread;
    int temp=pthread_create(&thread,NULL,listenThread,port);
    if(temp==0){
        printf("success create thread listenThread\n");
    }
    else printf("Error:%d,filed to create thread listenThread\n",temp);

   char *str;
   while(1){
       str = (char*)call_getBuffer();
       if(str)
           printf("received：%s\n",str);
      sleep(1);
   }
}