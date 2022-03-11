#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_QUOTES 96
#define MAX_FILE_NAME 100
#define MAX_MESSAGES 1024
#define MAX_LEN 512
#define MAX_NUM 50
sem_t sem1, sem2, sem3;
FILE *fp;
char ph[MAX_QUOTES][MAX_MESSAGES];
    char ph_aux [MAX_QUOTES][MAX_MESSAGES];
    char final [MAX_QUOTES][MAX_MESSAGES*2];
    char line[MAX_QUOTES];
    int random_numer;
void *f1()
{
  //load all the quotes into memory
    
    fp = fopen("quotes.txt", "r");

    for(int x=0; x<MAX_QUOTES;x++){
      if(fgets(ph[x],MAX_LEN/2,fp)== NULL) break;
      if(fgets(ph_aux[x],MAX_LEN/2,fp)== NULL) break;
      sprintf(final[x-2],"%s-%s",ph[x],ph_aux[x]); 
      if(fgets(line,MAX_LEN/2,fp)==NULL)break;
    }
    fclose(fp);
}

void *f2()
{
  for(int i=1; i<=MAX_NUM; i++)
  {
    srand(time(NULL));
    random_numer = rand() % 32;

    printf("Pseudo-random number: %d", random_numer);
  }
}

void *f3()
{
  for(int i=1; i<=MAX_NUM; i++)
  {
  fprintf(final[random_numer]);
 }
}


int main()
{
   pthread_t p1, p2, p3;
   sem_init(&sem1, 0, 1);
   sem_init(&sem2, 0, 0);
   sem_init(&sem3, 0, 0);

  pthread_create(&p1, NULL, f1, NULL);
  pthread_create(&p2, NULL, f2, NULL);
  pthread_create(&p3, NULL, f3, NULL);
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(p3, NULL);

  return 0;

}