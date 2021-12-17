#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <stdio.h> 
#include <limits.h> 
#include <fstream>
#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <vector>
using namespace std::chrono;
using namespace std;

int adjMatrix[10][10];

class Planet{
    int x;
    int y;
    int z;
    int iWeight;
    int iProfit;
    string name;

    public:
        Planet(){}

        Planet(string name,int x,int y, int z, int iWeight, int iProfit){
            this->name = name;
            this->x = x;
            this->y = y;
            this->z = z;
            this->iWeight = iWeight;
            this->iProfit = iProfit;
        }

        int getX(){
            return x;
        }

        int getY(){
            return y;
        }

        int getZ(){
            return z;
        }

        int getIweight(){
            return iWeight;
        }

        int getIprofit(){
            return iProfit;
        }

        string getName(){
            return name;
        }

        int getDistance(Planet B){
            int total_dis = pow((x - B.x),2) + pow((y - B.y),2) + pow((z - B.z),2);
            return sqrt(total_dis);
        }

        
};

class Edge{
    int weight;
    string name;

    public:
        Edge(){}

        Edge(string name,int weight){
            this->name = name;
            this->weight = weight;
        }

        string getEdgeName(){
            return name;
        }

        int getEdgeWeight(){
            return weight;
        }

};

void add_edge(vector<Planet> p,int u,int v){
    adjMatrix[u][v] = p[u].getDistance(p[v]);
    adjMatrix[v][u] = p[u].getDistance(p[v]);
}

void merge(vector<Edge>& edgeList, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    Edge L[n1];
    Edge R[n2];
 
    for (int i = 0; i < n1; i++)
        L[i] = edgeList[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = edgeList[m + 1 + j];
 
 
    int i = 0;
 
    int j = 0;
 
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i].getEdgeWeight() <= R[j].getEdgeWeight() ) {
            edgeList[k] = L[i];
            i++;
        }
        else {
            edgeList[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        edgeList[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        edgeList[k] = R[j];
        j++;
        k++;
    }
}
 
void mergeSort(vector<Edge>& edgeList,int l,int r){
    if(l>=r){
        return;
    }
    int m =l+ (r-l)/2;
    mergeSort(edgeList,l,m);
    mergeSort(edgeList,m+1,r);
    merge(edgeList,l,m,r);
}

void printArray(vector<Edge> edgeList, int size)
{   
    cout << left << setw(3) << "No";
    cout << right << setw(3) << "Edge" << "  ";
    cout << right << setw(3) << "Distance" << "  ";
    cout <<endl;

    for (int i = 0; i < size; i++){
        cout << left << setw(3) << i+1 ;
        cout << right << setw(3) <<edgeList[i].getEdgeName() << "  ";
        cout << right << setw(3) <<edgeList[i].getEdgeWeight() << "  ";

        cout <<endl;
    }
}

void mergePlanet(vector<Planet>& planets, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    Planet L[n1];
    Planet R[n2];
 
    for (int i = 0; i < n1; i++)
        L[i] = planets[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = planets[m + 1 + j];
 
 
    int i = 0;
 
    int j = 0;
 
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i].getIweight() >= R[j].getIweight() ) {
            planets[k] = L[i];
            i++;
        }
        else {
            planets[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        planets[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        planets[k] = R[j];
        j++;
        k++;
    }
}
 
void mergeSortPlanet(vector<Planet>& planets,int l,int r){
    if(l>=r){
        return;
    }
    int m =l+ (r-l)/2;
    mergeSortPlanet(planets,l,m);
    mergeSortPlanet(planets,m+1,r);
    mergePlanet(planets,l,m,r);
}

void printPlanet(vector<Planet> planets, int size)
{   
    cout << left << setw(3) << "No";
    cout << right << setw(3) << "Planet" << "  ";
    cout << right << setw(3) << "Weight" << "  ";
    cout <<endl;

    for (int i = 0; i < size; i++){
        cout << left << setw(3) << i+1 ;
        cout << right << setw(3) <<planets[i].getName() << "  ";
        cout << right << setw(3) <<planets[i].getIweight() << "  ";
        cout <<endl;
    }
}



int main()
{
    ifstream File("A2planets_TT8V_Group3.txt");
    vector<Planet> planets;
    string a;
    int b,c,d,e,f;

    while (File >> a >> b >> c >> d >> e >> f)
    {
        Planet temp(a,b,c,d,e,f);
        planets.push_back(temp);
    }

    for(int i=0; i<planets.size(); ++i){
        cout << planets[i].getName() << " " << planets[i].getX() << " " << planets[i].getY() << " " 
        << planets[i].getZ() << " " << planets[i].getIweight() << " " << planets[i].getIprofit() << endl;
    }


    vector<vector<Planet>> connected;
    connected.push_back({planets[3],planets[9],planets[7],planets[5]});
    connected.push_back({planets[3],planets[6],planets[4]});
    connected.push_back({planets[4],planets[8],planets[5]});
    connected.push_back({planets[1],planets[9],planets[0]});
    connected.push_back({planets[1],planets[6],planets[8],planets[2]});
    connected.push_back({planets[0],planets[7],planets[2]});
    connected.push_back({planets[1],planets[4],planets[8],planets[9]});
    connected.push_back({planets[9],planets[0],planets[8],planets[5]});
    connected.push_back({planets[6],planets[4],planets[2],planets[7]});
    connected.push_back({planets[3],planets[6],planets[7],planets[0]});
    cout << endl;

    cout << "Adjacency List :" << endl;


    for(int i=0 ; i<connected.size();i++){
        cout<< planets[i].getName();
        for(int j = 0; j<connected[i].size();j++)
            cout << " --> " << connected[i][j].getName() << " [W = " << connected[i][j].getDistance(planets[i]) << "]" ;
        cout << endl;
    }
    
    add_edge(planets,0, 3);
    add_edge(planets,0, 9);
    add_edge(planets,0, 7);
    add_edge(planets,0, 5);

    add_edge(planets,1, 3);
    add_edge(planets,1, 6);
    add_edge(planets,1, 4);

    add_edge(planets,2, 4);
    add_edge(planets,2, 8);
    add_edge(planets,2, 5);

    add_edge(planets,3, 0);
    add_edge(planets,3, 9);
    add_edge(planets,3, 1);

    add_edge(planets,4, 1);
    add_edge(planets,4, 6);
    add_edge(planets,4, 8);
    add_edge(planets,4, 2);

    add_edge(planets,5, 0);
    add_edge(planets,5, 7);
    add_edge(planets,5, 8);
    add_edge(planets,5, 2);

    add_edge(planets,6, 1);
    add_edge(planets,6, 9);
    add_edge(planets,6, 8);
    add_edge(planets,6, 4);

    add_edge(planets,7, 0);
    add_edge(planets,7, 9);
    add_edge(planets,7, 8);
    add_edge(planets,7, 5);

    add_edge(planets,8, 7);
    add_edge(planets,8, 6);
    add_edge(planets,8, 4);
    add_edge(planets,8, 2);

    add_edge(planets,9, 0);
    add_edge(planets,9, 7);
    add_edge(planets,9, 6);
    add_edge(planets,9, 3);
    cout << endl;

    cout << "Adjacency Matrix :" << endl;
    string name[10] = { "A","B","C","D","E","F","G","H","I","J" };
    cout << left << setw(4) << " " << " ";
    for(int i = 0;i<10;i++){
        cout << left << setw(4) << name[i] << " ";
    }
    cout<<endl;
    for(int i = 0; i < 10; i++) {
        cout << left << setw(4) << name[i] << " ";
        for(int j = 0; j < 10; j++) {
            cout << left << setw(4) << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    vector<Edge> edgeList;
    for(int i=0;i<10;i++){
        string tempRowName = name[i];
        for(int j=0;j < 10;j++){
            string tempColName = name[j];
            if(adjMatrix[i][j] > 0){
                string cat = tempRowName + tempColName;
                Edge e(cat,adjMatrix[i][j]);
                edgeList.push_back(e);
            }
        }
    }
    
    cout << endl;
    cout << "List of edges before merge sorting:" << endl;
    printArray(edgeList, edgeList.size());


    cout << endl;
    cout << "List of edges after merge sorting in ascending order of distance:" << endl;
    mergeSort(edgeList, 0, edgeList.size()-1);
    printArray(edgeList, edgeList.size());

    cout << endl;
    cout << "List of planets before merge sorting:" << endl;
    printPlanet(planets, planets.size());


    cout << endl;
    cout << "List of planets after merge sorting in descending order item weight:" << endl;
    mergeSortPlanet(planets, 0, planets.size()-1);
    printPlanet(planets, planets.size());
}
