#include<iostream>
#include<omp.h>
using namespace std;
int main()
{
    cout<<endl;
    cout<<"Enter the number of elements in the vector: ";
    int nvec;
    cin>>nvec;

    int vec[nvec] = {0};

    for(int i=0; i<nvec; i++) vec[i] = rand()%10;
    cout<<endl;

    cout<<"Vector: ";
    for(int i=0; i<nvec; i++) cout<<vec[i]<<" ";
    cout<<endl;

    cout<<endl;
    cout<<"Enter the number of rows in the matrix: ";
    int rows;
    cin>>rows;

    int mat[rows][nvec];
    for(int i=0; i<rows; i++) for(int j=0; j<nvec; j++) mat[i][j] = rand()%10;
    cout<<endl;

    cout<<"Matrix: "<<endl;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<nvec; j++) cout<<mat[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;

    cout<<"Multiplication: "<<endl;
    int rvec[nvec];

    #pragma omp parallel for
    for(int i=0; i<rows; i++)
    {
        rvec[i] = 0;
        int arr[nvec] = {0};

        #pragma omp parallel for
        for(int j=0; j<nvec; j++) arr[j] = mat[i][j] * vec[j];

        int sum = 0;

        #pragma omp parallel for reduction(+: sum)
        for(int k = 0; k < nvec; k++) sum += arr[k];

        rvec[i] = sum;
    }

    for(int i=0; i<nvec; i++) cout<<rvec[i]<<" ";
    cout<<endl;
    
    return 0;
}

/*
The code you provided is a C++ code that performs vector-matrix multiplication using OpenMP for parallel execution. It multiplies each row of the matrix by the vector and stores the result in the rvec vector.

Here's how the code works:

It prompts the user to enter the number of elements in the vector (nvec).
It initializes the vec vector with random values between 0 and 9.
It prompts the user to enter the number of rows in the matrix (rows).
It initializes the mat matrix with random values between 0 and 9.
It prints the contents of the vector and matrix.
It initializes the rvec vector, which will store the result of the vector-matrix multiplication.
It uses OpenMP to parallelize the computation of each row of the matrix.
For each row, it initializes an array arr with zeros and multiplies each element of the row by the corresponding element in the vector.
It calculates the sum of the elements in the arr array using OpenMP's reduction clause.
It assigns the sum to the corresponding element in the rvec vector.
Finally, it prints the result vector rvec.
Note that there are a few issues with the code:

The line int rvec[nvec]; should be int rvec[rows]; since rvec should have the same number of elements as the number of rows in the matrix.
The array arr is declared inside the parallel for loop, which creates a new array for each iteration. To fix this, move the declaration of arr before the parallel for loop.
*/
