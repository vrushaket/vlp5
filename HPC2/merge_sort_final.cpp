#include<iostream>
#include<omp.h>
using namespace std;


void mergeSort(int arr[], int low, int high){
    int count = 0;
    for(int i = 2; i < high ; i*=2){
    for(int j = i; j < high ; j+=i){
        for(int k = 0; k < j; k++){
            count+=1;
            if(arr[k] > arr[k+1]){
                swap(arr[k+1], arr[k]);
            }
        }
    }
    }
        for(int i=0; i<high; i++){
        cout<<arr[i]<<" ";
    }
cout<<endl<<"Total Iteration n(logn) ="<<count;
}

void pmergeSort(int arr[], int low, int high){
    int count = 0;
    #pragma omp parallel for
    for(int i = 2; i < high ; i*=2){
    #pragma omp parallel for
    for(int j = i; j < high ; j+=i){
        for(int k = 0; k < j; k++){
            count+=1;
            if(arr[k] > arr[k+1]){
                swap(arr[k+1], arr[k]);
            }
        }
    }
    }
        for(int i=0; i<high; i++){
        cout<<arr[i]<<" ";
    }
cout<<endl<<"Total Iteration n(logn) ="<<count;
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

    cout<<endl;
    auto end = omp_get_wtime();
    cout<<"time taken :"<<(end-start)<<endl;

    cout<<"parallel merge sort :";
    start = omp_get_wtime();
    pmergeSort(array,0,n-1);

    cout<<endl;
    end = omp_get_wtime();
    cout<<"time taken :"<<(end-start)<<endl;
}
