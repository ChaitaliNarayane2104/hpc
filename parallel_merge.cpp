#include<iostream>
#include<cstdlib>
#include<omp.h>
#include<time.h>
using namespace std;

void merge(int array[],int low1, int high1,int low2,int high2, int n)
{
	int temp[n];
	int i=low1,j=low2,k=0;
	
	while(i<=high1 && j<=high2)
	{
		if(array[i]<array[j])
			temp[k++]=array[i++];
		else
			temp[k++]=array[j++];
	}
	
	while(i<=high1)
		temp[k++]=array[i++];
	
	while(j<=high2) 
		temp[k++]=array[j++];
		
	for(i=low1,j=0;i<=high2;i++,j++)
		array[i]=temp[j];
}

void mergesort(int array[], int low, int high, int n)
{
	if(low<high)
	{
		int mid=(low+high)/2;
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				mergesort(array,low,mid,n);
			}
			
			#pragma omp section
			{
				mergesort(array,mid+1,high,n);
			}
			
		}
		
        merge(array,low,mid,mid+1,high,n);


		// mergesort(array,low,mid,n);
		// mergesort(array,mid+1,high,n);
		// merge(array,low,mid,mid+1,high,n);
	}
}

void display(int array[], int n)
{
	for(int i=0;i<n;i++) cout<<array[i]<<" ";
}


int main()
{
	int n;
	cout<<"Enter the number of elements : ";
	cin>>n;
	
    int array[n] = {0};

	for(int i=0;i<n;i++)
	{
		array[i]=rand()%32;
	}
	
	cout<<"Original Array: ";
	display(array,n);
	cout<<endl;
	
	clock_t start = clock();
	mergesort(array,0,n-1,n);
	clock_t stop = clock();
	
	cout<<"Final Array: ";
	display(array,n);
	cout<<endl;

	cout<<"Time required : "<<(double)(stop-start)*1000/CLOCKS_PER_SEC<<" ms";
	
    return 0;
}

/*
PS D:\C++> g++ -fopenmp parallel_merge.cpp
PS D:\C++> ./a out
Enter the number of elements : 10
Original Array: 9 3 30 4 1 12 22 14 18 16 
Final Array: 1 3 4 9 12 14 16 18 22 30 
Time required : 0 ms

The code you provided is a C++ program that performs parallel merge sort using OpenMP. It takes the number of elements as input, generates random values for the array, sorts the array using the merge sort algorithm in parallel, and prints the sorted array along with the time required for the sorting process.

Here's how the code works:

It includes the necessary header files.
It defines the merge() function, which merges two sorted subarrays into a single sorted array.
It takes the array, indices of the low and high elements of the first subarray, indices of the low and high elements of the second subarray, and the size of the array as input.
It merges the two subarrays into a temporary array temp using a merge operation.
It copies the merged elements from temp back to the original array.
It defines the mergesort() function, which performs the merge sort algorithm recursively.
It takes the array, indices of the low and high elements of the current subarray, and the size of the array as input.
If the low index is less than the high index, it calculates the middle index.
It uses OpenMP's parallel sections to divide the merge sort into two parts:
The first section recursively sorts the left half of the subarray.
The second section recursively sorts the right half of the subarray.
It merges the sorted left and right halves using the merge() function.
It defines the display() function, which displays the elements of the array.
In the main() function:
It prompts the user to enter the number of elements in the array (n).
It generates random values for the array.
It prints the original contents of the array.
It starts the clock to measure the time required for sorting.
It calls the mergesort() function to sort the array in parallel.
It stops the clock to measure the elapsed time.
It prints the final sorted array.
It prints the time required for the sorting process.
Please note that the parallelization in this code is efficient because it parallelizes the recursive calls to mergesort() using OpenMP's parallel sections. The merging operation is performed after the parallel sections.
*/
