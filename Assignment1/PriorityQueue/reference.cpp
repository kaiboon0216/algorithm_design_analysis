#include <fstream>
#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <chrono>

using namespace std::chrono;
using namespace std;

template <typename T>
void printArray(T A[], int n){
    for (int i = 0; i < n; i++){
        cout << A[i] << " ";
    }
    cout << endl;
}


template <typename T>
class PriorityQueue{
    vector<T> A;

    void heapify_enqueue(int index){
        if(index == 0){
            return ;
        }

        //parent index
        int parent = (index-1)/2;
        
        //swap if parent is smaller;
        if(A[index] > A[parent]){
            swap(A[index], A[parent]);
            //recursion of the function
            heapify_enqueue(parent);
        }
    }
    
    void heapify_dequeue(int index){
        int max;
        
        //left child index
        int leftChild = ((2 * index) + 1); 

        //right child index
        int rightChild = ((2 * index) + 2);

        // compare and find the greatest child
        if(rightChild < A.size()){
            if(A[leftChild] > A[rightChild]){
                max = leftChild;
            }else{
                max = rightChild;
            }
            if(A[index] > A[max]){
                max = index;
            }
        }else if(leftChild < A.size()){
            if(A[leftChild] > A[index]){
                max = leftChild;
            }else{
                max = index;
            }
        }else{
            max = index;
        }

        if(max != index){
            swap(A[index],A[max]);
            heapify_dequeue(max);
        }
    }
    

    public:
        void enqueue(T element){
            A.push_back(element);
            heapify_enqueue(A.size()-1);
        }

        
        T dequeue(){
            T removed_element = A[0];
            A[0] = A[A.size()-1];
            A.pop_back();
            heapify_dequeue(0);
            return removed_element;
        }
        

        int size(){
            return A.size();
        }

        void print(){
            for(int i=0; i<A.size(); i++){
                cout << A[i] << " ";
            }
            cout << endl;
        }  

};


int main(){
    int A[] = {4, 2, 5, 8, 6, 9, 3, 7};
    //int A[] = {43,29,35,17,22,30,26};
    int n = sizeof(A)/sizeof(A[0]);
    cout << "Array = ";
    printArray (A, n);
    
    
    cout << "\nEnqueue\t: PriorityQueue\n";
    PriorityQueue<int> pq;
    for (int i = 0; i < n; i++) {
        cout << A[i] << "\t: ";
        pq.enqueue (A[i]);
        pq.print();
    }

    cout << pq.size () << endl;

    cout << "\nDequeue\t: PriorityQueue\n";
    for (int i = 0; i < sizeof(pq); i++) {    
        cout << pq.dequeue() << "\t: ";
        pq.print();
    }
    
    
}
