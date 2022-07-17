#include <stdio.h>
#include <locale.h>

#define N 3
#define M 4

void printMatrix(int a[][N]);
void printArrays(int a[]);
void taskPrintMatrix();
void taskReservePrintArray();
void taskUpperTriangleMatrixZeroAndOne();
void taskSnailMatrix();


int main()
{
    setlocale(LC_ALL, "Rus");

    taskPrintMatrix();
    taskReservePrintArray();
    taskUpperTriangleMatrixZeroAndOne();
    taskSnailMatrix();

    return 0;
}

void printMatrix(int a[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printArrays(int a[])
{
    for (int i = 0; i < N*N; i++)
    {
        printf("%d",a[i]);
    }
}

void taskPrintMatrix()
{
    int arr[N][N]= {1, 2, 3, 4, 5, 6, 7, 8, 9};

    printMatrix(arr);
}

void taskReservePrintArray()
{
    int arr[N*N]= {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int temp;

    printArrays(arr);
    printf("\n");

    for (int i = 0; i < N*N/2; i++)
    {
        temp = arr[i];
        arr[i] = arr[N*N-i-1];
        arr[N*N-i-1] = temp;
    }

    printArrays(arr);
    printf("\n");

    printf("\n");
}

void taskUpperTriangleMatrixZeroAndOne()
{
    int arr[N][N]= {0};
    
    printMatrix(arr);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i+j < N/2 + 1)
                arr[i][j] = 0;
            else arr[i][j] = 1;
        }
        
    }

    printMatrix(arr);
}

void taskSnailMatrix()
{
    int arr[N][M]= {0};
    int num = 1;

    /*for(int i = 0; i < N/2; i++)
    {
        for(int j = i; j < M-i; j++)
            arr[i][j] = num++;
        for(int k = i + 1; k < N-i; k++)
            arr[k][M - 1 - i] = num++;
        for(int j = M - i - 2; j >= i; j--)
            arr[N - 1 -i][j] = num++;
        for(int k = N - 2 - i; k > i; k--)
            arr[k][i] = num++;
    }*/


    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf("%d", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}