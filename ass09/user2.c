#include<signal.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<sys/ipc.h> 
#include<sys/shm.h> 
#include<sys/types.h> 
#include<unistd.h> 
  
#define FILLED 0 
#define Ready 1 
#define NotReady -1 
 
struct memory
{ 
    char buff[100]; 
    int status, pid1, pid2; 
}; 
  
struct memory* shmptr; 
  

void handler(int signum) // handler function to print message received from user1 
{ 
    // if signum is SIGUSR2, then user 2 is receiving a message from user1 
  
    if (signum == SIGUSR2)
    { 
        printf("Received From User1 : "); 
        puts(shmptr->buff); 
    } 
} 
  

int main() 
{ 
    
    int pid = getpid();   // process id of user2 
  
    int shmid; 
   
    int key = 12345;    // key value of shared memory 
  
    shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);   // shared memory create   
  
    shmptr = (struct memory*)shmat(shmid, NULL, 0);   // attaching the shared memory 

    shmptr->pid2 = pid;    // store the process id of user2 in shared memory 
  
    shmptr->status = NotReady; 
    
    signal(SIGUSR2, handler);   // calling the signal function using signal type SIGUSR2 
  
    while (1) 
    { 
        sleep(1); 

        printf("User2 : ");   // taking input from user2 
        
        fgets(shmptr->buff, 100, stdin); 
        
        shmptr->status = Ready; 
        
        kill(shmptr->pid1, SIGUSR1);   // sending the message to user1 using kill function 
  
        while (shmptr->status == Ready) 
            continue; 
    } 
  
    shmdt((void*)shmptr);   // detach from shared memory  
    return 0; 
} 
