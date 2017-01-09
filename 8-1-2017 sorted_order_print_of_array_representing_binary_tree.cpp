#include<iostream>
#include<stdlib.h>
using namespace std;

void printSorted(int a[], int start, int end)
{
	if(start>end)
		return;
	//print left subtree 
	printSorted(a,2*start+1,end); //left child position is taken to be 2*i+1 because the tree starts from index 0
	//print root
	printf("%d ",a[start]);
	//print right subtree
	printSorted(a,2*start+2,end);
}

int main()
{
	int a[]={4,2,5,1,3};
	int a_size=sizeof(a)/sizeof(a[0]);
	printSorted(a,0,a_size-1);
	return 0;
}
