#include <fstream>
#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <typeinfo>
#include <chrono>

using namespace std::chrono;
using namespace std;

class HashMap
{
  public:
    string email;
    HashMap(string email)
    {
      this->email = email;
    }
};

class Hash
{
    int hashTableSize;
    HashMap **hashMap;

public:
    Hash(int V);
    void insertItem(string key);
    int hashFunction(string key) {
        int sum = 0;
        int index;
        for(int i =0;i<key.length();i++){
            sum += (int)key[i];
        }
        return sum % hashTableSize;
    }

    int getIndex(string key);

    int getSize(){
        return (hashTableSize);
    }


};

Hash::Hash(int b)
{
    this->hashTableSize = b;
    hashMap = new HashMap*[this->hashTableSize];
}

void Hash::insertItem(string key)
{
    int index = hashFunction(key);

    while(hashMap[index] != NULL)
    {
      if (++index>hashTableSize)
        index = 0;
    }

    hashMap[index] = new HashMap(key);
}


int Hash::getIndex(string key)
{
  int index = hashFunction(key);
  int counter=0;

  while(hashMap[index] != NULL)
  {
      if(counter++ > hashTableSize)
      break;

      if(hashMap[index++]->email == key)
      {
          return index;
      }
  }
  return -1;

}



int main()
{
    ifstream file;
    ofstream result("result.txt");

    int select;
    string key;
    string line;
    int sizeOfHash = 0;


    cout << "Please select the file to be read " << endl;
    cout << "1. Set A (100 items)" << endl;
    cout << "2. Set B (100,000 items)" << endl;
    cout << "3. Set C (500,000 items)" << endl;
    cout << "Please enter 1,2 or 3 only :";

    cin >> select;

    if (select == 1){
        file.open("setA.txt");
    } else if (select == 2){
        file.open("setB.txt");
    }else if (select == 3){
        file.open("setC.txt");
    }else {
        cout << "Invalid input !" << endl;
    }

    while (!file.eof()){
        getline(file,line);
        ++sizeOfHash;
    }
    file.seekg(0, file.beg);
    Hash h(sizeOfHash*1.5);
    auto start = high_resolution_clock::now();
    while (file >> key){
        h.insertItem(key);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);



    

    result << "Time taken to insert value into Hash Table: "
     << duration.count() << " microseconds" << endl;

     cout << "Time taken to insert value into Hash Table: "
     << duration.count() << " microseconds" << endl;

     file.close();


    string fileName;
    string fileInput;
    int indexOfKey;
    while(true){
        cout << "Select the options below " << endl;
        cout << "1. Search data manually " << endl;
        cout << "2. Search data by file input" << endl;
        cout << "Enter 1 or 2 only :";
        cin >> select;

        if(select == 1){
            cout << "Enter the string to find: ";
            cin >> key;
            auto start = high_resolution_clock::now();
            indexOfKey = h.getIndex(key);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << endl;
            if (indexOfKey >= 0){

                cout << "Time taken to find the key in the Hash Table: "
                << duration.count() << " microseconds" << endl;
                cout << "The key is found at index "<< indexOfKey << endl << endl;
            }
            else{
                cout << "The key is not available in the table  "<< endl << endl;
            }
        }
        else if (select == 2){
            cout << "Enter the file name including the file format (eg:found.txt) :";
            cin >> fileName;
            file.open(fileName);
            cout << endl;
            while (file >> fileInput){
                auto start = high_resolution_clock::now();
                indexOfKey = h.getIndex(fileInput);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                if(indexOfKey >= 0){

                    cout << "Time taken to find the key in the Hash Table: "
                    << duration.count() << " microseconds" << endl;
                    cout << "The key is found at index "<< indexOfKey << endl << endl;
                }
                else{
                    cout << "The key " << fileInput << " is not available in the table  "<< endl << endl;
                }
            }
        }
        else{
            cin.clear();
            cin.ignore();
            cout << "invalid input !" <<endl << endl;
            continue;
        }
        file.close();

    }








}
