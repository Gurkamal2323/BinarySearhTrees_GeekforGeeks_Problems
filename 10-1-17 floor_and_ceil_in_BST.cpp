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
	//when there is no node, so we create one
	if((*rootRef)==NULL)
	{
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

//ceil value function
int ceil(treeNode *root, int val)
{
	//base case
	if(root==NULL)
		return -1;
	//when root->info is equal to key value
	if(root->info == val)
		return root->info;
	//if key value is greater than root->info then ceil node must be in right subtree
	if(val > root->info)
		return ceil(root->right,val);
	//else, either left subtree or root has ceil value
	int ceilValue=ceil(root->left,val);
	return (ceilValue >= val ? ceilValue : root->info);
}

//floor value function
int floor(treeNode *root, int val)
{
	//base case
	if(root==NULL)
		return -1;
	//when root->info is equal to key value
	if(root->info==val)
		return val;
	//if key value is less than root->info then floor value must lie in left subtree
	if(val < root->info)
		return floor(root->left,val);
	//else, either right subtree or root->info has the floor value
	int floorValue=floor(root->right,val);
	return (root->info >= floorValue ? root->info : floorValue);
}

int main()
{
	treeNode *root=NULL;
	insertBST(&root,8);
	insertBST(&root,4);
	insertBST(&root,12);
	insertBST(&root,2);
	insertBST(&root,6);
	insertBST(&root,10);
	insertBST(&root,14);
	for(int i=0;i<16;i++)
	{
		printf("ceil of %d is %d\n",i,ceil(root,i));
		printf("floor of %d is %d\n",i,floor(root,i));
	}
	return 0;
}
