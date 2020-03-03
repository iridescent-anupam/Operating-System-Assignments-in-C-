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
  

void handler(int signum)   // handler function to print message received from user2 
{ 
    // if signum is SIGUSR1, then user 1 is receiving a message from user2 
  
    if (signum == SIGUSR1) 
    { 
        printf("Received from User2 : "); 
        puts(shmptr->buff); 
    } 
} 
  

int main() 
{ 
    int pid = getpid();   // process id of user1 
  
    int shmid; 
  
    int key = 12345;   // key value of shared memory   
    
    shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);   // shared memory create 
  
    shmptr = (struct memory*)shmat(shmid, NULL, 0);   // attaching the shared memory   
   
    shmptr->pid1 = pid;    // store the process id of user1 in shared memory 
    
    shmptr->status = NotReady; 
  
    signal(SIGUSR1, handler);   // calling the signal function using signal type SIGUSER1 
  
    while (1) 
    { 
        while (shmptr->status != Ready) 
            continue; 
        
        sleep(1); 
        
        printf("User1: ");   // taking input from user1 
  
        fgets(shmptr->buff, 100, stdin); 
  
        shmptr->status = FILLED; 
  
        kill(shmptr->pid2, SIGUSR2);    // sending the message to user2 using kill function 
    } 
  
    shmdt((void*)shmptr);   // detach from shared memory  
    shmctl(shmid, IPC_RMID, NULL);    // destroy the shared memory 
    return 0; 
} 
