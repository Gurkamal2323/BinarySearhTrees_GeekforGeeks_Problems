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

//print BST keys in given range
void printKeys(treeNode *root, int k1, int k2)
{
	if(root==NULL)
		return;
	/* Since the desired o/p is sorted, recurse for left subtree first
      If root->info is greater than k1, then only we can get o/p keys
      in left subtree */
	if(root->info > k1)
		printKeys(root->left,k1,k2);
	/* if root's data lies in range, then prints root's data */
	if(root->info >= k1 && root->info <= k2)
		printf("%d ",root->info);
	 /* If root->info is smaller than k2, then only we can get o/p keys
      in right subtree */
	 if(root->info < k2)
	 	printKeys(root->right,k1,k2);	
}

int main()
{
	treeNode *root=NULL;
	insertBST(&root,20);
	insertBST(&root,8);
	insertBST(&root,22);
	insertBST(&root,4);
	insertBST(&root,12);
	printKeys(root,10,25);
	return 0;
}
