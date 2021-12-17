#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <stdio.h> 
#include <limits.h> 
using namespace std;

#define size 10 

class Planet {
    public:
        int x;
        int y;
        int z;
        int weight;
        int profit;
        string name;
};

int calDisPla(Planet A, Planet B){
    int total_dis = pow((A.x - B.x),2) + pow((A.y - B.y),2) + pow((A.z - B.z),2);
    return sqrt(total_dis);
}

// Function to find the vertex with minimum distance value
int minDistance(int dist[],bool sptSet[]){ 
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < size; v++){
        if (sptSet[v] == false && dist[v] <= min){
            min = dist[v], min_index = v; 
        } 
    }    
    return min_index; 
} 
  
// Function to print shortest path from source to j using parent array 
void printPath(int parent[], int j){ 
    string name[10] = { "A","B","C","D","E","F","G","H","I","J" };
    // Base Case : If j is source 
    if (parent[j] == - 1)
        return; 
  
    printPath(parent, parent[j]); 
    
    string n = name[j];
    //printf("%d ", j);
    //printf("{}", n);
    cout << n << " ";
} 
  
// Function to print constructed distance array 
void printSolution(int dist[], int n, int parent[]){ 
    int src = 0; 
    char name[10] = { 'A','B','C','D','E','F','G','H','I','J'};
    printf("Vertex\t\t\t Distance\tPath"); 
    for (int i = 1; i < size; i++){ 
        char s  = name[i];
        printf("\n A -> %C \t\t %d\t\t A ", s, dist[i]); 
        printPath(parent, i); 
    } 
} 
  
// Funtion that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation 
void dijkstra(int graph[size][size], int src) { 
    // The output array. dist[i] will hold the shortest distance from src to i 
    int dist[size];  
  
    // sptSet[i] will true if vertex i is included / in shortest path tree or shortest distance from src to i is finalized 
    bool sptSet[size]; 
  
    // Parent array to store shortest path tree 
    int parent[size]; 
  
    // Initialize all distances as  
    // INFINITE and stpSet[] as false 
    for (int i = 0; i < size; i++){ 
        parent[0] = -1; 
        dist[i] = INT_MAX; 
        sptSet[i] = false; 
    } 
  
    // Distance of source vertex from itself is always 0 
    dist[src] = 0; 
  
    // Find shortest path for all vertices 
    for (int count = 0; count < size - 1; count++) { 
        // Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in first iteration. 
        int u = minDistance(dist, sptSet); 
  
        // Mark the picked vertex as processed 
        sptSet[u] = true; 
  
        // Update dist value of the adjacent vertices of the picked vertex. 
        for (int v = 0; v < size; v++) 
            // Update dist[v] only if is not in sptSet, there is an edge from u to v, and total weight of path fro src to v through u is smaller than current value of dist[v] 
            if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]){ 
                parent[v] = u; 
                dist[v] = dist[u] + graph[u][v]; 
            }  
    } 
  
    // print the constructed distance array 
    printSolution(dist, size, parent); 
} 

//Plot graph
void initmap(char m[7][7]){
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            m[i][j] = ' ';
        }
    }
}

void graph_planets(char m[7][7]){
    m[0][3] = 'A';
    m[4][0] = 'B';
    m[4][6] = 'C';
    m[2][0] = 'D';
    m[6][3] = 'E';
    m[2][6] = 'F';
    m[4][2] = 'G';
    m[2][4] = 'H';
    m[4][4] = 'I';
    m[2][2] = 'J';
}

void graph_connect(char m[7][7], int a, int b){
    switch (a) {
    case 1:     // A
        if (b == 4)     // connect to D
        {
            m[0][0] = '+';
            m[0][1] = '-';
            m[0][2] = '-';
            m[1][0] = '|';
        }
        if (b == 6)     // connect to F
        {
            m[0][6] = '+';
            m[0][5] = '-';
            m[1][6] = '|';
        }
        if (b == 10)     // connect to J
        {
            m[0][2] = '+';
            m[1][2] = '|';
        }
        if (b == 8)      // connect to H
        {
            m[0][4] = '+';
            m[1][4] = '|';
        }
        break;
    case 2:     // B
        if (b == 4)     // connect to D
        {
            m[3][0] = '|';
        }
        if (b == 5)     // connect to E
        {
            m[6][0] = '+';
            m[6][1] = '-';
            m[6][2] = '-';
            m[5][0] = '|';
        }
        if (b == 7)     // connect to G
        {
            m[4][1] = '-';
        }
        break;
    case 3:     // C
        if (b == 6)     // connect to F
        {
            m[3][6] = '|';
        }
        if (b == 5)     // connect to E
        {
            m[6][6] = '+';
            m[6][5] = '-';
            m[6][4] = '-';
            m[5][6] = '|';
        }
        if (b == 9)     // connect to I
        {
            m[4][5] = '-';
        }
        break;
    case 4:     // D
        if (b == 10)     // connect to J
        {
            m[2][1] = '-';
        }
        break;
    case 5:     // E
        if (b == 7)     // connect to G
        {
            m[6][2] = '+';
            m[5][2] = '|';
        }
        if (b == 9)     // connect to I
        {
            m[6][4] = '+';
            m[5][4] = '|';
        }
        break;
    case 6:     //
        if (b == 8)     // connect to H
        {
            m[2][5] = '-';
        }
        break;
    case 7:     // G
        if (b == 10)     // connect to J
        {
            m[3][2] = '|';
        }
        if (b == 9)     // connect to I
        {
            m[4][3] = '-';
        }
        break;
    case 8:     // H
        if (b == 10)     // connect to J
        {
            m[2][3] = '-';
        }
        if (b == 9)     // connect to I
        {
            m[3][4] = '|';
        }
        break;

    }

}

void graph_edges(char m[7][7]){
    graph_connect(m,1,4);     // A-D
    graph_connect(m,1,10);    // A-j
    graph_connect(m,1,8);     // A-H
    graph_connect(m,1,6);     // A-F
    graph_connect(m,2,4);     // B-D
    graph_connect(m,2,5);     // B-E
    graph_connect(m,2,7);     // B-G
    graph_connect(m,3,5);     // C-E
    graph_connect(m,7,9);     // G-I
}

void graph_display(char m[7][7]){
    cout << endl;
    for (int i=0; i<7; i++)
    {
        cout << "  ";
        for (int j=0; j<7; j++)
           cout << m[i][j];
        cout << endl;
    }
}

int main()
{
    string array[60];
    ifstream MyReadFile("A2planets_TT8V_Group3.txt");
    Planet planet[size];
    string tempString;
    for (int i = 0; i < 11; i++){
        getline(MyReadFile, tempString);

        istringstream read(tempString);

        read >> planet[i].name;
        read >> planet[i].x;
        read >> planet[i].y;
        read >> planet[i].z;
        read >> planet[i].weight;
        read >> planet[i].profit;
    }

    
    int adjMatrix[size][size] = {{0, 0, 0, calDisPla(planet[0],planet[3]), 0, calDisPla(planet[0],planet[5]), 0, calDisPla(planet[0],planet[7]), 0, calDisPla(planet[0],planet[9])},
        {0, 0, 0, calDisPla(planet[1],planet[3]), calDisPla(planet[1],planet[4]), 0, calDisPla(planet[1],planet[6]), 0, 0, 0},
        {0, 0, 0, 0, calDisPla(planet[2],planet[4]), calDisPla(planet[2],planet[5]), 0, 0, calDisPla(planet[2],planet[8]), 0},
        {calDisPla(planet[3],planet[0]), calDisPla(planet[3],planet[1]), 0, 0, 0, 0, 0, 0, 0, calDisPla(planet[3],planet[9])},
        {0, calDisPla(planet[4],planet[1]), calDisPla(planet[4],planet[2]), 0 , 0, 0, calDisPla(planet[4],planet[6]), 0, calDisPla(planet[4],planet[8]), 0},
        {calDisPla(planet[5],planet[0]), 0, calDisPla(planet[5],planet[2]), 0, 0, 0, 0, calDisPla(planet[1],planet[7]), 0, 0},
        {0, calDisPla(planet[6],planet[1]), 0, 0, calDisPla(planet[6],planet[4]), 0 , 0, 0, calDisPla(planet[6],planet[8]), calDisPla(planet[6],planet[9])},
        {calDisPla(planet[7],planet[0]), 0, 0, 0, 0, calDisPla(planet[7],planet[5]), 0, 0, calDisPla(planet[7],planet[8]), calDisPla(planet[7],planet[9])},
        {0, 0, calDisPla(planet[8],planet[2]), 0, calDisPla(planet[8],planet[4]), 0, calDisPla(planet[8],planet[6]), calDisPla(planet[8],planet[7]), 0, 0},
        {calDisPla(planet[9],planet[0]), 0, 0, calDisPla(planet[9],planet[3]), 0, 0, calDisPla(planet[9],planet[6]), calDisPla(planet[9],planet[7]), 0, 0}
    };

    dijkstra(adjMatrix, 0); 

    cout << " " << endl;
    cout << " " << endl;
    cout << "Display graph: " << endl;

    char map[7][7];
    initmap(map);
    graph_planets(map);
    graph_edges(map);
    graph_display(map);

    return 0;
}

