/* Title: Merge Sort without using copies of array
 * Author: Joel Sleeba
 *
 */

#include <stdio.h>
#include <stdlib.h>

// swap integer values
void swap(int * a, int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// print integer array
void printArray(int * array, int len){
    for (int i = 0; i<len; printf("%d, ", array[i]), i++);
    printf("\n");
}


// merge sort
void mergesort(int * array, int start, int end, int desc){

    // sorting
    if (end == start+1) {
        if ((array[start]<array[end] && desc) || (array[start]>array[end] && !desc)){
            swap(array+start, array+end);
        }
    }
    // bookkeeping
    else if (start==end){
        return;
    }
    // merging
    else{
        int mid = (start+end)/2;
        mergesort(array, start, mid, desc);
        mergesort(array, mid+1, end, desc);
        int key1=start, key2=mid+1;
        int flag=array[key1]>array[key2];  // to check if to move values from key2 position to key1 position
        
        while (key1 <= mid && key2 <= end) {
            if ((flag && desc) || (!flag && !desc)){
                key1++;
            }
            else{
                int temp = array[key2];
                for (int i = key2; i>key1; i--)
                    array[i] = array[i-1];
                array[key1] = temp;
                mid++;
                key2++;
            }
            
            flag = (array[key1]>array[key2]);
        }
    }
}

int main(){
    int len = 11;
    int array[] = {5, 34, 7, 90, 423, 43, 10212, 4561, 15, 4849, 2130};
    int end = len-1;
    mergesort(array, 0, end, 0);
    printArray(array, len);
}
