#include <stdio.h>
#include <stdlib.h>

int A[10] = {5, 3, 6, 3, 7, 8, 5, 2, 4, 2};

void swap(int * a, int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mergesort(int * A, int start, int mid, int end){
    if ((end == start+1) && (A[end] < A[start])){
        swap(A[start], A[end]);
        return;
    }
    
    mergesort(A, start, int((start+end)/2), mid);
    mergesort(A, mid, int((mid+end)/2), end);
    int n1 = mid - start + 1;
    int n2 = end - mid;
    
    int * B, C;
    B = (int *)malloc(n1*sizeof(int));
    C = (int *)malloc(n2*sizeof(int));
    for (int i = 0; i < n1; i++){
        B[i] = A[start+i];
    }
    for (int i = 0; i < n2; i++){
        C[i] = A[mid+i+1];
    }
}
