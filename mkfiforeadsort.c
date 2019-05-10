#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include<time.h>
#define n 50000


void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}


int main()
{
	int c,i,k,l;
	int pipe;
	int arr[50000];
	FILE *ff1;
	clock_t st = clock();
	
	// open a named pipe
	pipe = open("/tmp/myfifo", O_RDONLY);

	// actually read out the data and close the pipe
	read(pipe,arr,sizeof(arr));

	printf("reading and sorting....\n\n");      
	// bubble sort algorithm starts
	for ( c = 0 ; c < n ; c++ )
	{
		for (k = 0; k < n-c-1; k++)  
		{
			if (arr[k] > arr[k+1]) 
			swap(&arr[k], &arr[k+1]);
		}
	}
	
	ff1=fopen("outputsortedmkfifo.txt","w");
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


	printf("\n\ntotal time is: %lf\n\n",tis);
    
	// close the pipe
	close(pipe);
	return 0;
}
