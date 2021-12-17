// C++ program for Kruskal's algorithm to find Minimum 
// Spanning Tree of a given connected, undirected and 
// weighted graph 
#include<bits/stdc++.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <cmath>

using namespace std; 

class Planet {
    public:
        int x;
        int y;
        int z;
        int weight;
        int profit;
        string name;
};


int distance (int x, int y, int z,int x1, int y1, int z1){
    return(sqrt(pow(x-x1,2)+pow(y-y1,2)+pow(z-z1,2)));
}

typedef pair<int, int> iPair; 

struct Graph 
{ 
	int V, E; 
	vector< pair<int, iPair> > edges; 


	Graph(int V, int E) 
	{ 
		this->V = V; 
		this->E = E; 
	} 

	void addEdge(int u, int v, int w) 
	{ 
		edges.push_back({w, {u, v}}); 
	} 

	int kruskalMST(); 
	void display(char m[7][7]);
	void connection(char m[7][7],int x, int y);
	void connect(char m[7][7], int a, int b);
	void planets(char m[7][7]);
	void initmap(char m[7][7]);
}; 

void Graph::display(char m[7][7])
{
    cout << endl;
    for (int i=0; i<7; i++)
    {
        cout << "  ";
        for (int j=0; j<7; j++)
           cout << m[i][j];
        cout << endl;
    }
}

void Graph::connection(char m[7][7], int x, int y)
{
    connect(m,x,y);     // A-D
}

void Graph::connect(char m[7][7], int a, int b)
{
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

void Graph::initmap(char m[7][7])
{
    for (int i=0; i<7; i++)
        for (int j=0; j<7; j++)
           m[i][j] = ' ';
}

void Graph::planets(char m[7][7])
{
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

struct DisjointSets 
{ 
	int *parent, *rnk; 
	int n; 

	DisjointSets(int n) 
	{ 
		this->n = n; 
		parent = new int[n+1]; 
		rnk = new int[n+1]; 

		for (int i = 0; i <= n; i++) 
		{ 
			rnk[i] = 0; 

			parent[i] = i; 
		} 
	} 

	int find(int u) 
	{ 
		if (u != parent[u]) 
			parent[u] = find(parent[u]); 
		return parent[u]; 
	} 

	void merge(int x, int y) 
	{ 
		x = find(x), y = find(y); 

		if (rnk[x] > rnk[y]) 
			parent[y] = x; 
		else 
			parent[x] = y; 

		if (rnk[x] == rnk[y]) 
			rnk[y]++; 
	} 
}; 

int Graph::kruskalMST() 
{ 
	int mst_wt = 0; 
	char map[7][7];
    initmap(map);
    planets(map);

	sort(edges.begin(), edges.end()); 


	DisjointSets ds(V); 

	vector< pair<int, iPair> >::iterator it; 
	for (it=edges.begin(); it!=edges.end(); it++) 
	{ 
		int u = it->second.first; 
		int v = it->second.second; 
		char u1;
		char v1;

		int set_u = ds.find(u); 
		int set_v = ds.find(v); 


		if (set_u != set_v) 
		{ 

			if(u == 0)
				u1 = 'A';
			if(u == 1)
				u1 = 'B';
			if(u == 2)
				u1 = 'C';
			if(u == 3)
				u1 = 'D';
			if(u == 4)
				u1 = 'E';
			if(u == 5)
				u1 = 'F';
			if(u == 6)
				u1 = 'G';
			if(u == 7)
				u1 = 'H';
			if(u == 8)
				u1 = 'I';
			if(u == 9)
				u1 = 'J';

			if(v == 0)
				 v1 = 'A';
			if( v == 1)
				 v1 = 'B';
			if( v == 2)
				 v1 = 'C';
			if( v == 3)
				 v1 = 'D';
			if( v == 4)
				 v1 = 'E';
			if( v == 5)
				 v1 = 'F';
			if( v == 6)
				 v1 = 'G';
			if( v == 7)
				 v1 = 'H';
			if( v == 8)
				 v1 = 'I';
			if( v == 9)
				 v1 = 'J';
			cout << u1 << " - " << v1 << endl; 
			connection(map,v+1,u+1);
			connection(map,u+1,v+1);
			mst_wt += it->first; 

			ds.merge(set_u, set_v);
		} 
	}

	display(map); 

	return mst_wt; 
} 




int main() 
{ 

	int V = 10, E = 18; 
	Graph g(V, E); 

    string array[60];
    ifstream MyReadFile("A2planets_TT8V_Group3.txt");
    Planet planet[10];
    string tempString;
    for (int i = 0; i < 11; i++)
    {
        getline(MyReadFile, tempString);

        istringstream pp(tempString);

        pp >> planet[i].name;
        pp >> planet[i].x;
        pp >> planet[i].y;
        pp >> planet[i].z;
        pp >> planet[i].weight;
        pp >> planet[i].profit;
    }

	int AD = distance(planet[0].x,planet[0].y,planet[0].z,planet[3].x,planet[3].y,planet[3].z);
    int AJ = distance(planet[0].x,planet[0].y,planet[0].z,planet[9].x,planet[9].y,planet[9].z);
    int AH = distance(planet[0].x,planet[0].y,planet[0].z,planet[7].x,planet[7].y,planet[7].z);
    int AF = distance(planet[0].x,planet[0].y,planet[0].z,planet[5].x,planet[5].y,planet[5].z);
    int DB = distance(planet[3].x,planet[3].y,planet[3].z,planet[1].x,planet[1].y,planet[1].z);
    int DJ = distance(planet[3].x,planet[3].y,planet[3].z,planet[9].x,planet[9].y,planet[9].z);
    int JG = distance(planet[9].x,planet[9].y,planet[9].z,planet[6].x,planet[6].y,planet[6].z); 
    int JH = distance(planet[9].x,planet[9].y,planet[9].z,planet[7].x,planet[7].y,planet[7].z);
    int HI = distance(planet[7].x,planet[7].y,planet[7].z,planet[8].x,planet[8].y,planet[8].z);
    int HF = distance(planet[7].x,planet[7].y,planet[7].z,planet[5].x,planet[5].y,planet[5].z);
    int BE = distance(planet[1].x,planet[1].y,planet[1].z,planet[4].x,planet[4].y,planet[4].z);
    int BG = distance(planet[1].x,planet[1].y,planet[1].z,planet[6].x,planet[6].y,planet[6].z);
    int GE = distance(planet[6].x,planet[6].y,planet[6].z,planet[4].x,planet[4].y,planet[4].z);
    int GI = distance(planet[6].x,planet[6].y,planet[6].z,planet[8].x,planet[8].y,planet[8].z);
    int IE = distance(planet[8].x,planet[8].y,planet[8].z,planet[4].x,planet[4].y,planet[4].z);
    int IC = distance(planet[8].x,planet[8].y,planet[8].z,planet[2].x,planet[2].y,planet[2].z);
    int CE = distance(planet[2].x,planet[2].y,planet[2].z,planet[4].x,planet[4].y,planet[4].z);
    int CF = distance(planet[2].x,planet[2].y,planet[2].z,planet[5].x,planet[5].y,planet[5].z);

	// making above shown graph 
	g.addEdge(0, 3, AD); 
	g.addEdge(0, 9,AJ); 
	g.addEdge(0, 7,AH); 
	g.addEdge(0, 5,AF); 
	g.addEdge(3, 1,DB); 
	g.addEdge(3, 9,DJ); 
	g.addEdge(9, 6,JG); 
	g.addEdge(9, 7,JH); 
	g.addEdge(7, 8,HI); 
	g.addEdge(7, 5,HF); 
	g.addEdge(1, 4,BE); 
	g.addEdge(1, 6,BG); 
	g.addEdge(6, 4,GE); 
	g.addEdge(6, 8,GI); 
	g.addEdge(8, 4,IE); 
	g.addEdge(8, 2,IC); 
	g.addEdge(2, 4,CE); 
	g.addEdge(2, 5,CF); 

	
	

	
	cout << "Edges of MST are \n"; 
	int mst_wt = g.kruskalMST(); 
	cout << "\nWeight of MST is " << mst_wt; 

	return 0; 
} 
