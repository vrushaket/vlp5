#include<iostream>
#include<omp.h>

using namespace std;

void bubble(int array[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(array[j] > array[j+1]){
                swap(array[j], array[j+1]);
            }
        }
    }
    for(int i=0; i<n; i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
}


void pbubble(int arr[], int n){
    int array[n];
    for(int i=0; i<n; i++){
        array[i]=arr[i];
    }

    for(int k=0; k<n; k++){
        if(k%2==0){
            #pragma omp parallel for
            for(int j=1; j<n-1; j+=2){
                if(array[j] > array[j+1]){
                    swap(array[j], array[j+1]);
                }
            }
        }else{
            #pragma omp parallel for
            for(int j=0; j<n-1; j+=2){
                if(array[j] > array[j+1]){
                    swap(array[j], array[j+1]);
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
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

    cout<<"bubble sort :";
    auto start = omp_get_wtime();
    bubble(array,n);
    auto end = omp_get_wtime();
    cout<<"time taken :"<<(end-start)<<endl;

    cout<<"parallel bubble sort :";
    start = omp_get_wtime();
    pbubble(array,n);
    end = omp_get_wtime();
    cout<<"time taken :"<<(end-start)<<endl;
}
