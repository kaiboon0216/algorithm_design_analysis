#include <iostream>
#include <thread>
#include <string>
#include <array>
#include <fstream>
using namespace std;

string randomStringWithNum(int num){

    string letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string randomString = "";
    int pos;
    while(randomString.size() != num){
        pos = rand() % (letter.size() - 1);
        randomString += letter.substr(pos,1);
    }
    return randomString;
}

string randomStringNoNum(int num){

    string letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string randomString = "";
    int pos;
    while(randomString.size() != num){
        pos = rand() % (letter.size() - 1);
        randomString += letter.substr(pos,1);
    }
    return randomString;
}

string randomDomain(){
    array<string, 3> setDomain {"com","my","org"};
    string randomDomain = "";
    int pos;
    pos = rand() % (setDomain.size());
    randomDomain = setDomain[pos];

    return randomDomain;
}



int main(){
    string email;
    int A = 100, B = 100000 , C=500000;


    srand(time(0));
    ofstream setA("setA.txt");
    ofstream setB("setB.txt");
    ofstream setC("setC.txt");


    for(int i = 0; i < A; i++){
        email = randomStringWithNum(5) + "." + randomStringWithNum(4) + "@" + randomStringNoNum(4) + "." + randomDomain();
        if(i == A-1)
            setA << email;
        else
            setA << email << "\n";
    }

    for(int i = 0; i < B; i++){
        email = randomStringWithNum(5) + "." + randomStringWithNum(4) + "@" + randomStringNoNum(4) + "." + randomDomain();
        if(i == B-1)
            setB << email;
        else
            setB << email << "\n";
    }

    for(int i = 0; i < C; i++){
        email = randomStringWithNum(5) + "." + randomStringWithNum(4) + "@" + randomStringNoNum(4) + "." + randomDomain();
        if(i == C-1)
            setC << email;
        else
            setC << email << "\n";
    }

    setA.close();
    setB.close();
    setC.close();
}
