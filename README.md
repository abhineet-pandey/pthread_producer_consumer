# pthread_producer_consumer
C program for producer consumer with producer @ infinte rate and consumer @ defined
The program demonstrate the producer consumer problem using a queue of size(fixed) 32 where the producer fills the queue @ its own speed 
but the consumer consumes @ some delay.
The producer needs to wait until the queue is less than max to produce and add it to queue.
For better explanation see the result_a.txt
In b.c semaphore is not used as a counting variable but an alternate approach is used to gain the same result.
