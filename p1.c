#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t read1,write1,flag1;

int read_count=0;
int glob=1,flag=0;
int rcg=0,wcg=0;

    pthread_t readid[50], writeid[50];

void *reader(void *arg){
	
            int i=(*(int*)arg);                      
            pthread_mutex_lock(&read1);		
            read_count+=1;
            int op=read_count;

            if(read_count==1)
            {
                flag=1;
	     pthread_mutex_lock(&write1);
            }
            pthread_mutex_unlock(&read1);
            //critical section
            {   
                pthread_mutex_lock(&flag1);
                printf("\n\n\n\n\t# READER_%d \n",rcg);
                printf("\tNumber of reader at this time is %d\n",read_count);
                printf("\tData read by the reader_%d is %d\n",rcg++,glob);    
                printf("\tThread will terminate after %d seconds\n",i);             
                pthread_mutex_unlock(&flag1);    
                
            sleep(i);            
            }                        
            pthread_mutex_lock(&read1);
            read_count-=1;
            if(read_count==0){
                flag=0;
                pthread_mutex_unlock(&write1);
            }
            pthread_mutex_unlock(&read1);
            
       
}

void *writer(void *arg){
        int i=(*(int*)arg);
    

        while(flag!=0);    
          
        pthread_mutex_lock(&write1);
        //critical section
        {   pthread_mutex_lock(&flag1);
                 
            printf("\n\n\n\n\t# WRITER_%d \n",wcg);
            printf("\tThe number of readers at this time is %d\n",read_count);
            printf("\tData read by the writer_%d is %d\n",wcg++,glob);
            glob=(rand())%100;
            printf("\tNow the Writer has updated the shared data\n\tNow Data = %d\n",glob);
            printf("\tThread will terminate after %d seconds\n",i);
            pthread_mutex_unlock(&flag1);    
            sleep(i);
            
        }
        pthread_mutex_unlock(&write1);        
    
}

void mainmenu(int num)
{
     printf("\n\tChoose the option you want to make thread_%d do:- \n\n",num);

    printf("\t ------------------------------------- \n");
    printf("\t|        Option       |   Key         |\n");
    printf("\t|---------------------|---------------|\n");
    printf("\t|            To write |  press 1      |\n");
    printf("\t|             To read |  press 2      |\n");
    printf("\t| To start all thread |  press 3      |\n");
    printf("\t ------------------------------------- \n\n\t");   
    
   
    }



int main()
{
    pthread_mutex_init(&read1,NULL);
    pthread_mutex_init(&write1,NULL);
    pthread_mutex_init(&flag1,NULL);
    int array1[50];
    int array2[50];
    int array3[100];
    int thread_count=0;
    
    printf("\n\tThe Shared data between reader and write is initially %d\n\n\n",glob);
    
    printf("\t#Note\n\tChoose the task you want to perform with the respective thread.\n");
    printf("\tOnce you done with input press 3 to start all the threads to do their \n\t -respective tasks\n");

    printf("\n\tPress Enter to countinue");
    int c;    
    scanf("%c",&c);
        
    system("clear");    
    int rc=0,wc=0,tc=0,sum=0,z=0,time;
    while(1>0)
    {   
        mainmenu(thread_count);
        int option;
        scanf("%d",&option);
        
        if(option==2)
        {   z=2;
            array3[tc++]=2;
            printf("\n\tEnter running time for this thread: ");
            scanf("%d",&time);            
            array2[rc++]=time;
          //  sum+=time;
            printf("\n");                   
            thread_count++;        
        }
            
        else if(option==1)
        {   z=1;
            array3[tc++]=1;
            printf("\n\tEnter running time for this thread:");
            scanf("%d",&time);
            array1[wc++]=time;
            sum+=time;
            printf("\n");            
            
            thread_count++;      
        }
        else if(option==3)
        {  if(tc==0)
                printf("\n\nNo threads\n\n");                   
            system("clear");
            printf("\tALL THREADS ARE INVOKED\n");            
            break;
                
        }
        
        else
        {
            printf("\n\n\n\tOOPSS!!!!!!!\nEnter appropriate choice \n\n");
            sleep(2);        
        }
    sleep(0.5);
    system("clear");
       
    }
    
            
        
            int ic=0,jc=0;

        if(array3[0]==1)
            pthread_create(&writeid[0],NULL,writer,(void*)&array1[ic++]);
        else if(array3[0]==2) 
            pthread_create(&readid[0],NULL,reader,(void*)&array2[jc++]);                                                    

        sleep(1);
            
       

         for(int b=jc;b<rc;b++)
                pthread_create(&readid[b],NULL,reader,(void*)&array2[jc++]);                                                    

        for(int b=ic;b<wc;b++)
                pthread_create(&writeid[b],NULL,writer,(void*)&array1[ic++]);

        for(int b=0;b<rc;b++)
                pthread_join(readid[b],NULL);
        
        for(int b=0;b<rc;b++)
                pthread_join(writeid[b],NULL);

 
     // sleep(sum);
        
        //printf("\n\tPress Enter to exit\n");
        scanf("\n\n%c",&c);
}
