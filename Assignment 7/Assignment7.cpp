//============================================================================
// Name        : Assignment7.cpp
// Description : Minimum Spanning Tree(Prim's+Kruskal's)
//===========================================================================

/* Problem Statement:
You have a business with several offices; you want to lease phone lines to connect 
them up with each other; and the phone company charges different amounts of 
money to connect different pairs of cities. You want a set of lines that connects all 
your offices with a minimum total cost. Solve the problem by suggesting appropriate 
data structures
*/

#define MAX 25
#define INF 9999999
#include <iostream>
#include <stdlib.h>
using namespace std;
class Graph;
class DisjointSets{
	int *parent;
	int n;
public:
	DisjointSets(int n){
		this->n=n;
		parent=new int[n];
		for(int i=0;i<n;i++){
			parent[i]=i;
		}
	}
	int findParent(int u){
		while(parent[u]!=u){
			u=parent[u];
		}
		return u;
	}
	void unionDS(int x, int y){
		x=findParent(x);
		y=findParent(y);
		parent[x]=parent[y];
	}
	friend Graph;
};
class Edge{
	int src,dest,wt;
	friend Graph;
public:
	Edge(){
		src=dest=wt=-1;
	}
};
class Graph{
	int adj[MAX][MAX];
	int nodeNo;
	static int edgeNo;
	Edge e[MAX];
	friend Edge;
public:
	Graph(int x){
		nodeNo=x;
		edgeNo=0;
		for(int i=0;i<x;i++){
			for(int j=0;j<x;j++)
				adj[i][j]=-1;

		}
	}
	void addEdge(int src, int dest,int weight){
		adj[src][dest]=weight;
		adj[dest][src]=weight;
		int i=0;
		while(e[i].wt!=-1)
			i++;
		e[i].src=src;
		e[i].dest=dest;
		e[i].wt=weight;
		cout<<"\nEdge added successfully!"<<endl;
		edgeNo++;
	}
	static void displayEdges(){
		cout<<"Number of edges in graph are: "<<edgeNo<<endl;
	}
	void display(){
		cout<<"Adjacency matrix of graph is: "<<endl;
		for(int i=0;i<nodeNo;i++){
			for(int j=0;j<nodeNo;j++){
				cout<<adj[i][j]<<"  ";
			}
			cout<<endl;
		}
	}
	void primsAlgo(){
		int edgeCount=0;
		bool visited[nodeNo]={false};
		int MST[nodeNo][nodeNo];
		for(int t=0;t<nodeNo;t++){
			for(int s=0;s<nodeNo;s++){
				MST[t][s]=-1;
			}
		}
		visited[0]=true;
		while(edgeCount<nodeNo-1){
			int min=INF;
			int src=0,dest=0;
			for(int i=0;i<nodeNo;i++){
				if(visited[i]){
					for(int j=0;j<nodeNo;j++){
						if(!visited[j] && adj[i][j]!=-1){
							if(min>adj[i][j]){
								min=adj[i][j];
								src=i;
								dest=j;
							}
						}
					}
				}
			}
			if(adj[src][dest]!=-1){
			cout<<endl<<src<<"----"<<dest<<" = "<<adj[src][dest];
			visited[dest]=true;
			edgeCount+=1;
			MST[src][dest]=adj[src][dest];
			MST[dest][src]=adj[src][dest];
			}
		}
		cout<<"\nAdjacency matrix of MST is"<<endl;
		for(int k=0;k<nodeNo;k++){
				for(int l=0;l<nodeNo;l++){
					cout<<MST[k][l]<<"  ";
				}
			cout<<endl;
		}
	}
	void sortEdges(Edge e[],int left,int right){
		if(left<right){
			int loc=partition(e,left,right);
			sortEdges(e,left,loc-1);
			sortEdges(e,loc+1,right);
		}
	}
	int partition(Edge e[],int left,int right){
		int pivot=e[0].wt;
		int start=left,end=right;
		while(start<end){
			while(e[start].wt<=pivot)
				start++;
			while(e[end].wt>pivot)
				end--;
			if(start<end){
				int temp=e[start].wt,temp2=e[start].src,temp3=e[start].dest;
				e[start].wt=e[end].wt;e[start].src=e[end].src;e[start].dest=e[end].dest;
				e[end].wt=temp;e[end].src=temp2;e[end].dest=temp3;

			}
		}
		int temp=e[left].wt,temp2=e[left].src,temp3=e[left].dest;
		e[left].wt=e[end].wt;e[left].src=e[end].src;e[left].dest=e[end].dest;
		e[end].wt=temp;e[end].src=temp2;e[end].dest=temp3;
		return end;
	}
	void kruskalsAlgo(){
		int wt=0;
		sortEdges(e,0,edgeNo-1);
		DisjointSets ds(nodeNo);
		int i=0;
		while(e[i].wt!=-1){
			int u=e[i].src;
			int v=e[i].dest;
			int setu=ds.findParent(u);
			int setv=ds.findParent(v);
			if(setu!=setv){
				cout<<endl<<u<<"----"<<v<<" = "<<e[i].wt;
				wt+=e[i].wt;
				ds.unionDS(setu, setv);
			}
			i++;
		}
		cout<<"\nMinimum cost is: "<<wt;
	}
};
int Graph::edgeNo=0;

int main() {
	int x,cho,src,dest,w;
	cout<<"---------Graph----------\n\nEnter number of nodes in graph: ";cin>>x;
	while(x<=0){
			cout<<"Invalid input! Try again!"<<endl;
			cout<<"Enter number of nodes in graph: ";cin>>x;

	}
	cout<<"Graph created successfully!";
	Graph g(x);
	while(true){
	cout<<"\n--------------Menu--------------\n1.Add edge\n2.Display adjacency matrix\n3.Minimum Spanning Tree(Prim's Algorithm)\n4.Minimum Spanning Tree(Kruskal's Algorithm)\n5.Exit\nEnter choice: ";cin>>cho;
	switch(cho){
	case 1:
		cout<<"\nEnter source node: ";cin>>src;
		cout<<"\nEnter destination node: ";cin>>dest;
		cout<<"\nEnter weight of edge: ";cin>>w;
		while(src<0 || src>=x || dest<0 || dest>=x || w<0){
			cout<<"Invalid input! Try again!"<<endl;
			cout<<"\nEnter source node: ";cin>>src;
			cout<<"\nEnter destination node: ";cin>>dest;
			cout<<"\nEnter weight of edge: ";cin>>w;
		}
		g.addEdge(src, dest, w);
		cout<<"\nEdge added successfully!"<<endl;
		g.displayEdges();
		break;
	case 2:
		cout<<"\nAdjacency matrix is: "<<endl;
		g.display();
		break;
	case 3:
		cout<<"\nMinimum spanning tree is: "<<endl;
		g.primsAlgo();
		break;
	case 4:
		cout<<"\nMinimum spanning tree is: "<<endl;
		g.kruskalsAlgo();
		break;
	case 5:
		cout<<"\nThank You!"<<endl;
		exit(0);
		break;
	}
	}

	return 0;
}

