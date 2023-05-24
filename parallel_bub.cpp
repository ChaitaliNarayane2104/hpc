#include<omp.h>
#include<iostream>
#include<time.h>
using namespace std;
int main()
{

	// freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
	
	int n;
	cout<<"Enter the number of elements : ";
	cin>>n;
	cout<<endl;

	int array[n] = {0};

	for(int i=0;i<n;i++) array[i]=rand()%32;
	
	cout<<"Original Array: ";
	for(int i=0; i<n; i++) cout<<array[i]<<" ";
	cout<<endl;
	
	clock_t start=clock();
	int var = 0;

	for(int i=0; i<n; i++)
	{
		#pragma omp parallel for
		for(int j=var; j<n-1; j+=2)
		{
			if(array[j] > array[j+1])
			{
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
		
		if(var == 0) var = 1;
		else var = 0;

	}	

	clock_t stop=clock();
	
	
	cout<<"\nFinal Array: ";
	for(int i=0; i<n; i++) cout<<array[i]<<" ";
	cout<<endl;	
	
	cout<<"\nTime required : "<<(double)(stop-start)<<" ms"<<endl;
	return 0;
}

/*
PS D:\C++> g++ -fopenmp parallel_bub.cpp
PS D:\C++> ./a out
Enter the number of elements : 15

Original Array: 9 3 30 4 1 12 22 14 18 16 9 17 17 27 9 

Final Array: 1 3 4 9 9 9 12 14 16 17 17 18 22 27 30 

Time required : 0 ms




ChatGPT
The code you provided is a C++ program that performs parallel bubble sort using OpenMP. It takes the number of elements as input, generates random values for the array, sorts the array using the bubble sort algorithm in parallel, and prints the sorted array along with the time required for the sorting process.

Here's how the code works:

It prompts the user to enter the number of elements (n) in the array.
It generates random values for the array and prints its original contents.
It starts the clock to measure the time required for sorting.
It initializes the variable var to 0.
It performs the bubble sort algorithm in parallel.
For each iteration, it uses OpenMP to parallelize the comparison and swapping of adjacent elements in the array.
The outer loop controls the number of iterations, and the inner loop performs the comparisons and swaps.
The variable var is used to alternate between even and odd iterations to avoid unnecessary comparisons.
After the sorting is complete, it stops the clock to measure the elapsed time.
It prints the final sorted array and the time required for the sorting process.
Please note that the parallelization in this code is not efficient because it parallelizes the inner loop, which performs individual element comparisons. Parallelizing at such a fine-grained level can result in overhead due to thread synchronization. A more efficient approach would be to parallelize the outer loop, which represents each iteration of the bubble sort.

*/
