#include <stdio.h>
#include <unistd.h>
#include<time.h>
#include <sys/types.h>



int main(void)
{
	int fd[2], nbytes;
	pid_t childpid;
	int arr[50000],i,var,temp,j,n=50000;
	clock_t st;
	FILE *ff;
	int  c,search, count = 0;
	printf("Enter the number to search\n");
	scanf("%d",&search);

	pipe(fd); // declares pipe structure

	if((childpid = fork()) == -1)
	{	
		perror("fork");
  	}

	if(childpid == 0)
	{
		// Child process closes up input side of pipe 
   		close(fd[0]);
		ff = fopen("inputsorted.txt","r");  //open the file in which numbers are stored
		for(i=0;i<n;i++)
		{
			fscanf(ff, "%d", &arr[i]);
		}

		fclose(ff);  // close the file
		/* Send "array" through the output side of pipe */

		write(fd[1], &arr, sizeof(arr));
	}
	
	else
	{
		st = clock();   //time starts
		printf("reading and searching the data....\n");
		/* Parent process closes up output side of pipe */
		close(fd[1]);
		/* Read in a array from the pipe */
		nbytes = read(fd[0], &arr, sizeof(arr));
		
		// binary search algorithm starts    
		int left=0,right=n-1;
		
		while(left<=right)
		{
			int mid=left+(right-left)/2;
			if(arr[mid]==search)
			{
				printf("%d is present at location %d.\n", search, mid+1);
				count++;
      		}
            if (arr[mid]<search) 
			{
				left=mid+1;
			}
			else
			{
				right=mid-1;
			}

		}
		
		if ( count == 0 )
			printf("%d is not present in array.\n", search);
		else
			printf("%d is present %d times in array.\n", search, count);
	
		// binary search algorithm ends
		printf("searching complete....\n");
		
		clock_t et = clock();
		clock_t ctt = et - st;
		double tis = ctt / (double) CLOCKS_PER_SEC;
		printf("\n\ntotal time is: %lf",tis);
	}

return(0);

}


