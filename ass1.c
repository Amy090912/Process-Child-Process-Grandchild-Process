#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
//use rand() and srand() from stdlib.h

int main(int argc, char *argv[])
{
   int seed;//the seed will be used to determing numbers of children and waiting times
   printf("enter the seed for the parent process\n");
   scanf("%d",&seed);
   printf("the seed number is/are: %d\n", seed);
   srand(seed);
   int number_of_children;
   int number_of_grandchild;
   number_of_children=rand()%5+5;//k=x+rand()%(y-x+1)
   //  printf("number of children: %d\n",number_of_children);
   long int parentPID = getpid();
    printf("My process ID is %ld\n",parentPID);
    printf("%d is about to create a child\n",parentPID);
   int i;
   int j;
   int sleeptime;
   long status;
   pid_t childPID;
   pid_t grandchildPID;
   for (i=0;i<number_of_children;i++)
   {
   	childPID= fork();
   	if (childPID==0)
   	{ 
            childPID= getpid();
            srand(seed);
	    number_of_grandchild=rand()%3+1;
            printf("I am a new child, my process ID is %d, my seed id %d\n",childPID,seed);
            printf("I am child %d, I will have %d children\n",childPID,number_of_grandchild);
            printf("I am child %d, I am about to create a child\n",childPID);
            for(j=0;j<number_of_grandchild;j++)
            {
              grandchildPID=fork();
	      if(grandchildPID==0)
              { 
		grandchildPID=getpid();
		printf("I am child %d, I just created a child: %d\n",childPID,grandchildPID);
                printf("I am grandchild %d , My grandparent is %d, My parent is %d\n",grandchildPID,parentPID,childPID);
	        srand(seed);
		sleeptime=rand()%(14-5+1)+5;
		sleep(sleeptime);
		printf("I am grandchild %d with parent %d, I am about to terminate\n",grandchildPID,childPID);
                exit(0);
              }
              else if(grandchildPID>0)
              {
		printf("I am the child %d, I will have %d children\n",childPID,number_of_grandchild);
		printf("I am waiting for my children to terminate\n");
		waitpid(grandchildPID,&status,0);
		printf("I am child %d.My child %d has been waited\n",childPID,grandchildPID);
	      }
		
             } 
            sleep(5);
	    exit(0);
        }
        if(childPID>0)
	{
                    	 	
		 printf("Parent %d has created a child with process ID %d\n",parentPID,childPID);
		 printf("I am the parent, I am waiting for child %d to terminate\n",childPID);
        	 waitpid(childPID, &status,0);
                 printf("I am process %d. My child %d is dead\n\n",parentPID,childPID); 
        	
        }
	seed=seed+1;
      
   }
   
   printf("I am the parent, child %d has terminated\n",childPID);
   sleep(5);
   exit(0);
   return 0; 
}
