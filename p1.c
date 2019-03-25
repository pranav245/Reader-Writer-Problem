#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

int mutex_read=1;
int mutex_write=1;
int read_count=0;


void reader(){
	while(true){
		wait(mutex_read);
		read_count+=1;
		if(read_count==1){
			wait(mutex_write);
		}
		signal(mutex_read);
		//critical section
		{
		 //
		}
		wait(mutex_read)
		read_count-=1;
		if(read_count==0){
			signal(mutex_write);
		}
		signal(mutex_read);
		//process data;
	}
}

void writer(){
		while(true)
		{
		wait(mutex_write);
		//critical section
		{
		//asdsdas
		}
		signal(mutex_write);
		}
}


int main()
{
		
}
