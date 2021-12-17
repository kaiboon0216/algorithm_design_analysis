#include <fstream>
#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <chrono>
#include <stdlib.h>

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
        if(A[index].compare(A[parent]) > 0){
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
            if(A[leftChild].compare(A[rightChild]) > 0){
                max = leftChild;
            }else{
                max = rightChild;
            }

            if(A[index].compare(A[max]) > 0){
                max = index;
            }

        }else if(leftChild < A.size()){
            if(A[leftChild].compare(A[index]) > 0){
                if(A[leftChild].compare(A[index]) > 0){
                    max = leftChild;
                }else{
                    max = index;
                }
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
                cout << A[i] << " | ";
            }
            cout << endl;
        }  
};


int main(){
    ifstream file;
    ofstream result("result.txt");

    int select;
    string key;
    string line;
    bool status = true;
    int sizeOfPQ = 0;

    while(true){
        cout << "+++++++++++++++++++++++++++++++++++++" <<endl;
        cout << "+" << " Please select the file to be read " <<"+"<< endl;
        cout << "+++++++++++++++++++++++++++++++++++++" <<endl;
        cout << "+" << " 1. Set A (100 items)" << "              +" << endl;
        cout << "+" << " 2. Set B (100,000 items)" << "          + " << endl;
        cout << "+" << " 3. Set C (500,000 items)" << "          + " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++" <<endl;
        cout << endl;
        cout << "Please enter 1,2 or 3 only : " ;
        

        cin >> select;

        if (select == 1){
            file.open("setA.txt");
        } else if (select == 2){
            file.open("setB.txt");
        }else if (select == 3){
            file.open("setC.txt");
        }else {
            cout << "Invalid input !" << endl;
            exit(3);
            return 3;
        }

        while (!file.eof()){
            getline(file,line);
        }
        file.seekg(0, file.beg);

        PriorityQueue<string> pq;

        auto start_enq = high_resolution_clock::now();
        while (file >> key){
            pq.enqueue (key);
        }
        auto stop_enq = high_resolution_clock::now();
        auto duration_enq = duration_cast<microseconds>(stop_enq - start_enq);

        file.close();

        int after_enq_size = pq.size();
        int ten_percent = after_enq_size*0.1;

        //print enqueue 
        cout << endl;
        cout << "PriorityQueue after enqueue: " << endl;
        cout << endl;
        pq.print();
        cout << endl;
        
        //Dequeue 10 % of data
        cout << "Dequeue the first element of the priority queue line by line:" << endl;
        cout << endl;
        auto start_deq = high_resolution_clock::now();
        for(int i = 0; i < ten_percent; i++){
            cout << pq.dequeue() << endl;
        }
        auto stop_deq = high_resolution_clock::now();
        auto duration_deq = duration_cast<microseconds>(stop_deq - start_deq);

        int after_deq_size = pq.size();

        //print dequeue 
        cout << endl;
        cout << "PriorityQueue after dequeue: " << endl;
        cout << endl;
        pq.print();
        cout << endl;
        

        cout << "\nEnqueue\t: PriorityQueue\n";
        result << "Time taken to enqueue into Priority Priority Queue: "
        << duration_enq.count() << " microseconds" << endl;
        
        cout << endl;
        cout << "There are " << after_enq_size << " elements in the priority queue after enqueue." << endl;
        cout << endl;
        cout << "Time taken to enqueue into Priority Priority Queue: "
        << duration_enq.count() << " microseconds" << endl;
        
        cout << "\nDequeue\t: PriorityQueue\n";
        result << "Time taken to dequeue value into Priority Priority Queue: "
        << duration_deq.count() << " microseconds" << endl;

        cout << endl;
        cout << "There are " << after_deq_size << " elements in the priority queue after dequeue." << endl;
        cout << endl;
        cout << "Time taken to dequeue value into Priority Queue: "
        << duration_deq.count() << " microseconds" << endl;

        cout << " " <<endl;
        
    }

}

