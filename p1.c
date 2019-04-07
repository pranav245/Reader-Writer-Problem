#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<semaphore.h>

pthread_mutex_t read,write;

int read_count=0;
int glob=1;

void *reader(void *time){
	{
            sem_wait(&read1);		
            read_count+=1;
            if(read_count==1)
            {
	     sem_wait(&write1);
            }
            sem_post(&read1);
            //critical section
            {
                printf("Number of reader at this time is %d\n",read_count);
                printf("Value of Data is %d\n",glob);                    
            }
                
              int y=*(int *)time;
            
            printf("Reader will read data for %d seconds\n\n",y);
            sleep(y);            
            sem_wait(&read1);
            read_count-=1;
            if(read_count==0){
                sem_post(&write1);
            }
            sem_post(&read1);
        }
}

void *writer(void *time){
    {
        sem_wait(&write1);
        //critical section
        {
            printf("The number of readers at this time is %d\n",read_count);
            printf("Current the data value is %d\n",glob);
            printf("Enter the value you want to over write: ");
            scanf("%d",&glob);
            int y=*(int *)time;
            
            printf("Writer will write data for %d seconds\n\n",y);
            sleep(y);
        }
        sem_post(&write1);
    }
}


int main()
{
    //sem_init(&read1,0,5);
    //sem_init(&write1,0,1);
    pthread_mutex_init(&read,NULL);
    pthread_mutex_init(&write,NULL);


    printf("The Shared data between reader and write is initially %d\n",glob);

    pthread_t r1;
    pthread_t w1;
        while(1>0)
        {   
             printf("\n\n\n*****Choose respective number*****\n\n\n");
            printf("To  read Data: 1\n");
            printf("To write Data: 2\n");
            printf("To stop: 3\n");        
             
            int po=0;
            scanf("%d",&po);
           
             if(po==1)
             {
                  int time=0;
                  printf("Enter time for which you have to run thread: ");
                  scanf("%d",&time);   
                pthread_create(&r1,NULL,reader,(void *)&time);
                //pthread_join(r1,NULL);  
             }
             else if(po==2)
             {
                  int time=0;
                  printf("Enter time for which you have to run thread: \n");
                  scanf("%d",&time);               
                pthread_create(&w1,NULL,writer,(void *)&time);
                //pthread_join(w1,NULL);
             }
             else if(po==3)
                {   break;
                }
            else{
                printf("Enter appropriate choice\n");
             }
             
       }
//                        pthread_join(r1,NULL);
  //                      pthread_join(w1,NULL);
    
   
}
