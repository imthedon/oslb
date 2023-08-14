#include<stdio.h>  
#include<stdlib.h>  
#include<unistd.h>  
#include<sys/shm.h>  
#include<string.h>  
int main()  
{  
    int i;  
    void *shared_memory;  
    char buff[100];  
    int shmid;
    shmid=shmget((key_t)2345, 1024, 0666|IPC_CREAT);   
    printf("\nKey Of Shared Memory Is : %d\n\n",shmid);  
    shared_memory=shmat(shmid,NULL,0);   
    printf("Process Attached At : %p\n\n",shared_memory);   
    printf("Enter Some Data To Write To Shared Memory\n\n");  
    read(0,buff,100);
    printf("\nYou Wrote : %s\n",buff);  
    strcpy(shared_memory,buff); 
    printf("Data Read From Shared Memory Is : %s\n",(char *)shared_memory);  
}
