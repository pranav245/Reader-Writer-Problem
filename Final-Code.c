#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

time_t t;// declaration to catch the current time
 
pthread_mutex_t read1,write1,flag1; // decalration of mutex variable

int read_count=0; // this is used to count number of readers
int glob=1;   // shared data

int flag=0,rcg=0,wcg=0;  // helping variables

int a1[25],a2[25],a3[25],a4[25],a5[25];

//Reader function    
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
                a4[rcg]=glob;                
                printf("\tData read by the reader_%d is %d\n",rcg++,glob);
                time(&t);
                printf("\tCurrent time is : %s",ctime(&t));    
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

//Writer function
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
            a5[wcg-1]=glob;            
            printf("\tNow the Writer has updated the shared data\n\tNow Data = %d\n",glob);
            time(&t);
            printf("\tCurrent time is : %s",ctime(&t));                    
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

void table1(int num,int opt, int t)
{   
    
        a1[num]=num;
        a2[num]=t;
        a3[num]=opt;
    
    
        
    printf("\n\t\t-------------------------------------\n");
    printf("\t\t| Thread Number |    Type   |  Time   |\n");
    printf("\t\t---------------------------------------\n");
        
    for(int i=0;i<num+1;i++)
    {
    if(a3[i]==1)
    {
    printf("\t\t|   Thread %d   |  Writing  |  %d sec |\n",a1[i],a2[i]);
    printf("\t\t---------------------------------------\n");    
    }
    else if(a3[i]==2)
    {
    printf("\t\t|   Thread %d   |  Reading  |  %d sec |\n",a1[i],a2[i]);
    printf("\t\t---------------------------------------\n");    
    }
    }

}
void table2(int num)
{   

    printf("\n\t\t------------------------------------------------------\n");
    printf("\t\t| Thread Number |    Type   |  Time   |   Operation   | \n");
    printf("\t\t------------------------------------------------------\n");
        
    for(int i=0,j=0,k=0;i<num;i++)
    {
    if(a3[i]==1)
    {
    printf("\t\t|   Thread %d    |  Writing  |  %d sec | Data write:%d |\n",a1[i],a2[i],a5[j++]);
    printf("\t\t------------------------------------------------------\n");    
    }
    else if(a3[i]==2)
    {
    printf("\t\t|   Thread %d    |  Reading  |  %d sec | Data read:%d  |\n",a1[i],a2[i],a4[k++]);
    printf("\t\t------------------------------------------------------\n");    
    }
    }
    printf("\n\n");

}



int main()
{
    pthread_mutex_init(&read1,NULL);
    pthread_mutex_init(&write1,NULL);
    pthread_mutex_init(&flag1,NULL);
    pthread_t readid[50], writeid[50];

    int array1[50];
    int array2[50];
    int array3[100];
    int thread_count=0;

    
    int rc=0,wc=0,tc=0,sum=0,z=0,time1,option=0,sl=0,ic=0,jc=0;
    char c;
    system("clear");
    
    printf("\n\tThe Shared data between reader and write is initially %d\n\n\n",glob);
    
    printf("\t#Note\n\tChoose the task you want to perform with the respective thread.\n");
    printf("\tOnce you done with input press 3 to start all the threads to do their \n\t -respective tasks\n");
    
    printf("\n\tNumber of threads shouls not be more than 50");

    printf("\n\tPress Enter to countinue");
    
    scanf("%c",&c);
        
    system("clear");    
       
    while(1>0)
    {   
        mainmenu(thread_count);
        
        scanf("%d",&option);
        
        if(option==2)
        {   z=2;
            array3[tc++]=2;
            printf("\n\tEnter running time for this thread: ");
            scanf("%d",&time1);            
            array2[rc++]=time1;
          //  sum+=time1;
            printf("\n");                   
            thread_count++;        
        }
            
        else if(option==1)
        {   z=1;
            array3[tc++]=1;
            printf("\n\tEnter running time for this thread:");
            scanf("%d",&time1);
            if(wc==0)
                sl=time1;
            array1[wc++]=time1;
            sum+=time1;
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
            sleep(1);        
        }
    sleep(0.5);
    system("clear");
    table1((thread_count-1),z,time1);  
    }
    
               

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
        
        for(int b=0;b<wc;b++)
                pthread_join(writeid[b],NULL);

        
        sleep(sum);
        
        
        table2(thread_count);
        
 }
