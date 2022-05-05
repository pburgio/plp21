/*
 * Semaphore demo 
 *
 * Copyright (C) 2002 by Paolo Gai
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mysem;
int shared_val = 11;

void *producer_thread(void * arg)
{
    shared_val ++;
    sem_post(&mysem);
}

void *consumer_thread(void * arg)
{
    sem_wait(&mysem);
    printf("shared_val is %d\n", shared_val);
}

int main()
{
  pthread_t t1,t2;
  pthread_attr_t myattr;
  int err;

  sem_init(&mysem,0,0);

  pthread_attr_init(&myattr);
  err = pthread_create(&t1, &myattr, consumer_thread, (void *)0);
  err = pthread_create(&t2, &myattr, producer_thread, (void *)0);
  pthread_attr_destroy(&myattr);

  pthread_join(t2, NULL);
  pthread_join(t1, NULL);

  printf("\n");

  return 0;
}
