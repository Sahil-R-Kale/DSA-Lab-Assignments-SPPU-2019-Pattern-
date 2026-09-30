//============================================================================
// Name        : Assignment8.cpp
// Author      : Sahil
// Description : Topological Sort of Graph
//============================================================================

#include <iostream>
#include <stdlib.h>
using namespace std;
#include "myQueue.h"
#define MAX 25

/* Problem Statement:
Write a C++/Java program to implement topological sorting on graph using object 
oriented programming features Design necessary class. .( Use of graph)

*/

class Graph{
	int adj[MAX][MAX];
	int vertices,edges;
public:
	Graph(){
		vertices=edges=0;
	}
	Graph(const int x){
		vertices=x;
		for(int i=0;i<x;i++){
			for(int j=0;j<x;j++){
				adj[i][j]=0;
			}
		}
		edges=0;
	}
	void addDirectedEdge(int src, int dest){
		adj[src][dest]=1;
		edges++;
		cout<<"Edge successfully added!"<<endl;
	}
	void displayMatrix(){
		cout<<"\nAdjacency matrix is: "<<endl;
		for(int i=0;i<vertices;i++){
			for(int j=0;j<vertices;j++){
				cout<<adj[i][j]<<"   ";
			}
			cout<<endl;
		}
	}
	void topologicalSort(){
		int inDeg[vertices]={0};
		for(int i=0;i<vertices;i++){
			for(int j=0;j<vertices;j++){
				if(adj[j][i]==1)
					inDeg[i]++;
			}
		}
		Queue<int> q;
		int sorted[vertices];
		for(int i=0;i<vertices;i++){
			sorted[i]=-1;
			if(inDeg[i]==0)
				q.enque(i);
		}
		int j=0;
		cout<<"\nTopological sort is: ";
		while(!q.isEmpty()){
			int out=q.deque();
			if(inDeg[out]!=-1)
				sorted[j++]=out;
			inDeg[out]=-1;
			for(int i=0;i<vertices;i++){
				if(adj[out][i]==1 && inDeg[i]>0)
					inDeg[i]--;
			}
			for(int i=0;i<vertices;i++){
				if(inDeg[i]==0)
					q.enque(i);
			}
		}
		if(j==vertices){
			for(int i=0;i<vertices;i++){
				cout<<sorted[i]<<" ";
			}
		}
		else{
			cout<<"Topological Sort is impossible for the given graph!"<<endl;
		}
	}
};
int main() {
	cout<<"--------Topological Sort---------"<<endl;
	int x,src,dest,cho;
	cout<<"Enter number of vertices in graph: ";cin>>x;
	while(x<=0){
		cout<<"Invalid Input! Enter number of vertices: ";cin>>x;
	}
	Graph g(x);
	while(true){
		cout<<"\n----------Menu----------\n1.Add edge\n2.Show adjacency matrix\n3.Topological Sort\n4.Exit\nEnter your choice: ";cin>>cho;
		switch(cho){
		case 1:
			cout<<"Enter source vertex(0-"<<x-1<<"): ";cin>>src;
			cout<<"Enter destination vertex(0-"<<x-1<<"): ";cin>>dest;
			if(src>=0 && src<x && dest>=0 && dest<x){
				g.addDirectedEdge(src, dest);
			}
			else{
				cout<<"Invalid input! Try again!"<<endl;
			}
			break;
		case 2:
			g.displayMatrix();
			break;
		case 3:
			g.topologicalSort();
			break;
		case 4:
			cout<<"Thank You!";
			exit(0);
			break;
		}
	}
}
