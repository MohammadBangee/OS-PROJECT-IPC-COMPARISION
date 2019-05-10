#include <stdio.h>
#include <unistd.h>
#include<time.h>
#include <sys/types.h>


void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}

int main(void)
{
	int fd[2], nbytes;
	pid_t childpid;
	int arr[50000],i,var,temp,j,n=50000;
	clock_t st;
	FILE *ff,*ff1;
	int  c,k,l;
	pipe(fd); // declares pipe structure
	if((childpid = fork()) == -1)
	{
		perror("fork");
	}
	if(childpid == 0)
	{
   		// Child process closes up input side of pipe 
		close(fd[0]);
		ff = fopen("input.txt","r");
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
		printf("reading and sorting....\n\n");      
		/* Parent process closes up output side of pipe */
		close(fd[1]);
		/* Read in a array from the pipe */
		nbytes = read(fd[0], &arr, sizeof(arr));
		// bubble sort algorithm starts
		for ( c = 0 ; c < n ; c++ )
		{
			for (k = 0; k < n-c-1; k++)  
			{
				if (arr[k] > arr[k+1]) 
					swap(&arr[k], &arr[k+1]);
      		}
		}

		ff1=fopen("outputsortedpipes.txt","w");
		for(l=0;l<n;l++)
		{
			fprintf(ff1, "%d\n", arr[l]);
		}
		fclose(ff1);

		// bubble sort algorithm ends
		printf("sorting complete....\n");

		clock_t et = clock();
		clock_t ctt = et - st;
		double tis = ctt / (double) CLOCKS_PER_SEC;

		printf("\n\ntotal time is: %lf",tis);
	}
	
	return(0);
}


