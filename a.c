//////////////////////////////////////////////////
//Program Part.           1                     //
// Abhineet Pandey                              //
//                                              //
//////////////////////////////////////////////////
//////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#include <semaphore.h>

#define MAX 100
int queue_array[MAX];
int rear = - 1;
int front = - 1;
int add_item =1;
sem_t sem_count;
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;

void* produce(void *ptr)
{
    int i;

        for (i = 0; i < MAX; i++) {
            pthread_mutex_lock(&the_mutex); /* protect buffer */
           while (sem_count ==32)
               // while (rear-front ==31)

                    pthread_cond_wait(&condp, &the_mutex);
            pthread_mutex_unlock(&the_mutex); /* release the buffer */
            pthread_mutex_lock(&the_mutex); /* protect buffer */
                insert();
                pthread_cond_signal(&condc); /* wake up consumer */
                pthread_mutex_unlock(&the_mutex); /* release the buffer */
        }
        pthread_exit(0);
}
void* consume(void *ptr)
{
    int i;
    for (i = 0; i < MAX; i++) {
        pthread_mutex_lock(&the_mutex); /* protect buffer */
        while ((front == - 1 || front > rear)) /* If there is nothing in the buffer then wait */
            pthread_cond_wait(&condc, &the_mutex);
        pthread_mutex_unlock(&the_mutex); /* release the buffer */

        sleep(1);

        pthread_mutex_lock(&the_mutex); /* protect buffer */
        delete();
        pthread_cond_signal(&condp); /* wake up consumer */

        pthread_mutex_unlock(&the_mutex); /* release the buffer */

    }
    pthread_exit(0);
}
main()

{
    void * exit_status;
    sem_init(&sem_count, 0, 0);
    pthread_t pro;
    pthread_t con;

    pthread_mutex_init(&the_mutex, NULL);
    pthread_cond_init(&condc, NULL);
    pthread_cond_init(&condp, NULL);

    pthread_create(&pro, NULL, produce,NULL);
    pthread_create(&con, NULL, consume,NULL);


    pthread_join(pro, &exit_status);
    pthread_join(con, &exit_status);
    pthread_mutex_destroy(&the_mutex); /* Free up the_mutex */
    pthread_cond_destroy(&condc); /* Free up consumer condition variable */
    pthread_cond_destroy(&condp);
    pthread_exit(NULL);
    exit(0);
} /*End of main()*/





insert()
{


    if (rear == MAX - 1)

        printf("Queue Overflow \n");

    else

    {

        if (front == - 1)
            front = 0;
        rear = rear + 1;

        queue_array[rear] = add_item*4096;
        sem_count++;
        add_item++;
        printf("Inset the element in queue : %d  and semaphore count is %d \n",queue_array[rear],sem_count);

    }

}

delete()
{

    if (front == - 1 || front > rear)

    {

        printf("Queue Underflow \n");


    }

    else

    {
        printf("\t\tElement deleted from queue is : %d\t", queue_array[front]);

        front = front + 1;
        sem_count--;
        printf("new front item is %d and rear item is %d and semaphore value is %d\n",queue_array[front],queue_array[rear],sem_count);

    }

} /*End of delete() */
