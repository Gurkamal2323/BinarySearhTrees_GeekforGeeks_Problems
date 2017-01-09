#include<iostream>
#include<stdlib.h>
using namespace std;

//tree declaration
struct binaryTree
{
	int info;
	struct binaryTree *left;
	struct binaryTree *right;
	struct binaryTree *parent;
};

//rename
typedef binaryTree treeNode;

//create new node
treeNode *createNewNode(int val=0, treeNode *left=NULL, treeNode *right=NULL, treeNode *parent=NULL)
{
	//create new temp node
	treeNode *newNode=(treeNode *)malloc(sizeof(treeNode));
	newNode->info=val;
	newNode->left=left;
	newNode->right=right;
	newNode->parent=parent;
	
	return newNode;
}

//insert the node in BST
void insertBST(treeNode **rootRef, int val)
{
	if((*rootRef)==NULL)
	{
		//no node is there so we create one
		*rootRef=createNewNode(val,NULL,NULL,NULL);
		return;
	}
	if(val < (*rootRef)->info)
	{
		//insert node in left subtree
		insertBST(&((*rootRef)->left),val);
	}
	else
	{
		//insert node in right subtree
		insertBST(&((*rootRef)->right),val);
	}
}


treeNode *sortedArraytoBST(int a[], int start, int end)
{
	//best case
	if(start>end)
		return NULL;
	//get the middle of the array and make it root
	int middle=(start+end)/2;
	treeNode *root=createNewNode(a[middle],NULL,NULL,NULL);
	
	//recursively construct left subtree and make it left child of root
	root->left=sortedArraytoBST(a,start,middle-1);
	
	//recursively construct right subtree and make it right child of root
	root->right=sortedArraytoBST(a,middle+1,end);
	
	return root;
}

//print inorder to check tree (LNR)
void printInorder(treeNode *root)
{
	if(root==NULL)
		return;
	printInorder(root->left);
	printf("%d ",root->info);
	printInorder(root->right);
}

int main()
{
	int a[]={1,2,3,4,5,6,7};
	int a_size=sizeof(a)/sizeof(a[0]);
	treeNode *root=sortedArraytoBST(a,0,a_size-1);
	printInorder(root);
	return 0;
}
