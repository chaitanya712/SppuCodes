#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty;
sem_t full;
sem_t mutex;
int in=0;
int out=0;
int buffer[10];

void *producer(void *pr_no)
{
 int i;
 for (i=0;i<5;i++)
 {
 int item = rand();
 sem_wait(&empty);
 sem_wait(&mutex);
 
 buffer[in]=item;
 
 printf("\nProducer %d inserted item %d at position %d.",*((int *)pr_no),buffer[in],in);
 
 in=(in+1)%5;

 sem_post(&mutex);
 sem_post(&full);
 } 
}

void *consumer(void *co_no)
{
int i;
 for (i=0;i<5;i++)
 {
 sem_wait(&full);
 sem_wait(&mutex);

 int item = buffer[out];
 
 printf("\nConsumer %d consumed item %d at position %d.",*((int *)co_no),buffer[out],out);
 
 out=(out+1)%5;
 
 sem_post(&mutex);
 sem_post(&empty);
 }
}

int main()
{
 sem_init(&full,0,0);
 sem_init(&empty,0,5);
 sem_init(&mutex,0,1);
 pthread_t pro[5],con[5];
 
 int i;
 int a[5]={1,2,3,4,5};
 //printf("Buffer Size :%d",erSize);
 
 for (i=0;i<5;i++)
     pthread_create(&pro[i],NULL,(void *)producer,(void *)&a[i]);
 for (i=0;i<5;i++)
     pthread_create(&con[i],NULL,(void *)consumer,(void *)&a[i]);
 for (i=0;i<5;i++)
     pthread_join(pro[i],NULL);
 for (i=0;i<5;i++)
     pthread_join(con[i],NULL);
 sem_destroy(&empty);     
 sem_destroy(&full);
 sem_destroy(&mutex);
 
 return 0;
 
 
}
