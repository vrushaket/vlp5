#include<iostream>
#include<omp.h>
using namespace std;

void merge(int arr[], int low, int mid, int high){
    int n1 = mid-low+1;
    int n2 = high-mid;
    
    int left[n1];
    int right[n2];

    for(int i=0; i<n1; i++){
        left[i] = arr[low+i];
    }

    for(int j=0; j<n2; j++){
        right[j] = arr[mid+1+j];
    }

    int i=0, j=0, k= low;

    while(i<n1 && j<n2){
        if(left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k] = right[j];
            j++;        
        }
        k++;
    }

    while(i<n1){
        arr[k] = left[i];
        i++;
        k++;
    }

    while(j<n2){
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int low, int high){
    if(low<high){
        int mid = (low+high)/2;
        mergeSort(arr,low,mid);
        mergeSort(arr,mid+1,high);
        merge(arr,low, mid, high);
    }
}

void pmergeSort(int arr[], int low, int high){
    if(low<high){
        int mid = (low+high)/2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(arr,low,mid);
            }
             #pragma omp section
            {
                mergeSort(arr,mid+1,high);
            }
        }
        
        merge(arr,low, mid, high);
    }
}

int main(){
    int val;
    int n = 5;
    int array[n];

    for(int i=0; i<n; i++){
        cout<<"enter number : ";
        cin>>val;
        array[i] = val;
    }

    for(int i=0; i<n; i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;

    cout<<"merge sort :";
    auto start = omp_get_wtime();
    mergeSort(array,0,n-1);
    for(int i=0; i<n; i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
    auto end = omp_get_wtime();
    cout<<"time taken :"<<(end-start)<<endl;

    cout<<"parallel merge sort :";
    start = omp_get_wtime();
    pmergeSort(array,0,n-1);
    for(int i=0; i<n; i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
    end = omp_get_wtime();
    cout<<"time taken :"<<(end-start)<<endl;
}
