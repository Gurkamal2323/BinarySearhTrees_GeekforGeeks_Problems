/*Write a program for removing the duplicates in array using BST.
Gurkamal Singh
101403070
COE 3*/
#include<iostream>
#include<stdlib.h>
using namespace std;

//defining tree structure
struct binaryTree
{
	int info;
	int count;
	struct binaryTree *left;
	struct binaryTree *right;
	struct binaryTree *parent;
};

//renaming
typedef binaryTree treeNode;

//create new node
treeNode *createNewNode(int val=0, treeNode *left=NULL, treeNode *right=NULL, treeNode *parent=NULL)
{
	treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
	newNode->info = val;
	newNode->left = left;
	newNode->right = right;
	newNode->parent = parent;
	newNode->count=1;//initialize the count
	
	return newNode;
}

//insert a new node in the tree
void insertBST(int val, treeNode **rootRef)
{
	if(*rootRef==NULL)
	{
		//no node is there, so we create new node
		*rootRef=createNewNode(val,NULL,NULL,NULL);
		return;
	}
	 // If key already exists in BST, icnrement count and return
    if (val==(*rootRef)->info)
    {
       ((*rootRef)->count)++;
        return;
    }
	
	if(val<(*rootRef)->info)
	{
		//insert the node in left subtree
		insertBST(val,&((*rootRef)->left));
	}
	else
	{
		//insert node in right subtree
		insertBST(val,&((*rootRef)->right));
	}
}

//inorder traversal
void printInorder(treeNode *root)
{
	if(root==NULL)
	{
		return;
	}
	printInorder(root->left);
	printf("%d(%d) ",root->info,root->count);
	printInorder(root->right);
}

//tree minimum
treeNode *treeMinimum(treeNode *root)
{
	if(root==NULL)
		return NULL;
	if(root->left==NULL)
	{
		return root;
	}
	treeMinimum(root->left);
}

//delete a node from BST
//we require inorder traversal and minimum value finding functions
treeNode *deleteBST(treeNode *root, int val)
{
	//base case
	if(root==NULL)
		return root;
	//if the value to be deleted is smaller than the root->info then it lies in left subtree
	if(val < root->info)
		root->left = deleteBST(root->left,val);
	//if the value to be deleted is greater than root->info then it lies in the right subtree
	if(val > root->info)
		root->right = deleteBST(root->right,val);
	//if the value is same as root->info then it is the node to be deleted
	else
	{
		// If key is present more than once, simply decrement
        // count and return
        if (root->count > 1)
        {
           (root->count)--;
           return root;
        }
 
        // ElSE, delete the node
		//node with only one child or no child
		if(root->left==NULL)
		{
			treeNode *temp=root->right;
			free(root);
			return temp;
		}
		else if(root->right==NULL)
		{
			treeNode *temp=root->left;
			free(root);
			return temp;
		}
		//node with two children
		//get the minimum value in the right subtree
		treeNode *temp=treeMinimum(root->right);
		//copy the content of temp node to root node
		root->info=temp->info;
		//delete the minimum value
		root->right=deleteBST(root->right,temp->info);
	}
	return root;
}

int main()
{
	treeNode *root = NULL;
	insertBST(12, &root);
	insertBST(10, &root);
	insertBST(20, &root);
	insertBST(9, &root);
	insertBST(11, &root);
	insertBST(10, &root);
	insertBST(12, &root);
	insertBST(12, &root);
	printf("In-order traversal\n");
	printInorder(root);
	printf("\nAfter deletion of 20, Inorder traversal is :\n");
	deleteBST(root,20);
	printInorder(root);
	printf("\nAfter deletion of 12, Inorder traversal is :\n");
	deleteBST(root,12);
	printInorder(root);
	return 0;
}
