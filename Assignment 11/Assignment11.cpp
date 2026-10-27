//============================================================================
// Name        : Assignment11.cpp
// Description : Heap Sort using array
//============================================================================

/* Problem Statement:
Implement the Heap sort algorithm implemented in CPP/Java demonstrating heap
data structure with modularity of programming language
*/

#include <iostream>
using namespace std;
#define MAX 25
class Heap{
	int arr[25];
	int ele;
public:
	Heap(){
		ele=0;
	}
	Heap(int x){
		ele=x;
		for(int i=0;i<x;i++){
			arr[i]=0;
		}
	}
	void takeInput(){
		for(int i=0;i<ele;i++){
			cout<<"Enter element "<<i<<" : ";
			cin>>arr[i];
		}
	}
	void display(){
		cout<<"\nThe elements are: "<<endl;
		for(int i=0;i<ele;i++){
					cout<<arr[i]<<"	   ";
				}
	}
	void heapify(int arr[], int n, int root){
		int mini=root;
		int l=2*root+1;
		int r=2*root+2;
		if(l<n && arr[l]<arr[mini]){
			mini=l;
		}
		if(r<n && arr[r]<arr[mini]){
			mini=r;
		}
		if(mini!=root){
			int temp=arr[root];
			arr[root]=arr[mini];
			arr[mini]=temp;
			heapify(arr,n,mini);
		}
	}
	void heapSort(){
		for(int i=ele/2-1;i>=0;i--)
				heapify(arr, ele, i);
		cout<<"\n\nSorted order: "<<endl;
		for(int i=ele-1;i>=0;i--){
			cout<<arr[0]<<"    ";
			int temp=arr[0];
			arr[0]=arr[i];
			arr[i]=temp;
			heapify(arr,i,0);
		}
	}
};
int main() {
	Heap h(7);
	h.takeInput();
	h.display();
	h.heapSort();
	return 0;
}
