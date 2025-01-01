#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int leftArr[n1];
    int rightArr[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } 
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right){
    if(left<right){
        int mid= left + (right-left)/2;
        int leftPipe[2];
        int rightPipe[2];
        
        
        pipe(leftPipe);
        pipe(rightPipe);
        
        pid_t leftPid =fork();
        
        if(leftPid==0){
            close(leftPipe[0]);
            mergeSort(arr,left,mid);
            write(leftPipe[1],&arr[left],(mid-left+1)*sizeof(int));
            close(leftPipe[1]);
            exit(0);
        }

        else{
            pid_t rightPid = fork();
            if(rightPid==0){
                close(rightPipe[0]);
                mergeSort(arr,mid+1,right);
                write(rightPipe[1],&arr[mid+1],(right-mid)*sizeof(int));
                close(rightPipe[1]);
                exit(0);
            }

            else{
                close(leftPipe[1]);
                close(rightPipe[1]);
                
                wait(NULL);
                wait(NULL);
                
                read(leftPipe[0],&arr[left],(mid-left+1)*sizeof(int));
                read(rightPipe[0],&arr[mid+1],(right-mid)*sizeof(int));
                
                close(leftPipe[0]);
                close(rightPipe[0]);
                
                merge(arr,left,mid,right);

            }
        }
    }
}

int main(){
    int arr[16]={16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    printf("Initial array: \n");
    for (int i = 0; i < 16; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    mergeSort(arr,0,15);
    
    printf("Sorted array: \n");
    for (int i = 0; i < 16; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
