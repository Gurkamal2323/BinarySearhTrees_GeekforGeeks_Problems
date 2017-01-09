#include<iostream>
#include<stdlib.h>
using namespace std;

//tree structure
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
	treeNode *newNode=(treeNode *)malloc(sizeof(treeNode));
	newNode->info=val;
	newNode->left=left;
	newNode->right=right;
	newNode->parent=parent;
	
	return newNode;
}

//insert a node in BST
void insertBST(treeNode **rootRef, int val)
{
	if((*rootRef)==NULL)
	{
		//no node is there so we create one
		(*rootRef)=createNewNode(val,NULL,NULL,NULL);
		return;
	}
	if(val < (*rootRef)->info)
	{
		//insert the node in left subtree
		insertBST(&((*rootRef)->left),val);
	}
	else
	{
		//insert the node in right subtree
		insertBST(&((*rootRef)->right),val);
	}
}

//second largest
//we use reverse inorder traversal and count the number of nodes and keep track of nodes, when the nodes reaches second node we have our answer
void secondLargestHelper(treeNode *root, int &c)
{
	//base cases, the second condition is important as it avoid unnecessary recursive calls
	if(root==NULL || c>=2)
		return;
	//follow reverse inorder so that largest element is visited first
	secondLargestHelper(root->right,c);
	//increment the counted nodes
	c++;
	//if c becomes 2 now, then this is the second largest element
	if(c==2)
	{
		printf("Second largest element is %d",root->info);
		return;
	}
	//traverse the left subtree
	secondLargestHelper(root->left,c);
}
void secondLargest(treeNode *root)
{
	//initialize the count of nodes as 0
	int c=0;
	//c is passed as a reference
	secondLargestHelper(root,c);
}

int main()
{
	treeNode *root=NULL;
	insertBST(&root,30);
	insertBST(&root,20);
	insertBST(&root,40);
	insertBST(&root,70);
	insertBST(&root,60);
	insertBST(&root,80);
	secondLargest(root);
	return 0;
}
