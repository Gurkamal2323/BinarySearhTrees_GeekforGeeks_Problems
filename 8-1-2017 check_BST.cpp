/*Program to check is a given binary tree is a BST or not
A binary search tree (BST) is a node based binary tree data structure which has the following properties.
• The left subtree of a node contains only nodes with keys less than the node’s key.
• The right subtree of a node contains only nodes with keys greater than the node’s key.
• Both the left and right subtrees must also be binary search trees.

From the above properties it naturally follows that:
• Each node (item in the tree) has a distinct key.*/
#include<iostream>
#include<stdlib.h>
using namespace std;

struct binaryTree
{
	int info;
	struct binaryTree *left;
	struct binaryTree *right;
	struct binaryTree *parent;
};

//rename tree structure
typedef binaryTree treeNode;

//create new node
treeNode *createNewNode(int val=0, treeNode *left=NULL, treeNode *right=NULL, treeNode *parent=NULL)
{
	//create a new temp node
	treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
	newNode->info=val;
	newNode->left=left;
	newNode->right=right;
	newNode->parent=parent;
	
	return newNode;
}

//insert in a BST
void insertBST(treeNode **rootRef, int val)
{
	if(*rootRef==NULL) //tree is empty, we have insert first node
	{
		*rootRef=createNewNode(val,NULL,NULL,NULL);
		return;
	}
	if(val < (*rootRef)->info)
	{
		//insert the node in the left subtree
		insertBST(&((*rootRef)->left),val);
	}
	else
	{
		//insert the node in the right subtree
		insertBST(&((*rootRef)->right),val);
	}
}

//print inorder (LNR)
void printInorder(treeNode *root)
{
	if(root==NULL)
		return;
	printInorder(root->left);
	printf("%d",root->info);
	printInorder(root->right);
}

//tree minimum
int treeMinimum(treeNode *root)
{
	if(root==NULL)
		return 0;
	if(root->left==NULL)
		return root->info;
	treeMinimum(root->left);
}

//tree maximum
int treeMaximum(treeNode *root)
{
	if(root==NULL)
		return 0;
	if(root->right==NULL)
		return root->info;
	treeMaximum(root->right);
}

//check BST
//checkBSTHelper is used to check each node only once
int checkBSTHelper(treeNode *, int, int);
int checkBST(treeNode *root)
{
	return checkBSTHelper(root,treeMinimum(root),treeMaximum(root));
}
/* Returns true if the given tree is a BST and its 
   values are >= min and <= max. */
int checkBSTHelper(treeNode *root, int min, int max)
{
	//an empty tree is a BST
	if(root==NULL)
		return 1;
	/* false if this node violates the min/max constraint */
	if(root->info < min || root->info > max)
		return 0;
	/* otherwise check the subtrees recursively, 
   tightening the min or max constraint */
   return (checkBSTHelper(root->left,min,root->info - 1) && checkBSTHelper(root->right,root->info + 1,max)); //allow only distinct values
}

int main()
{
	treeNode *root=NULL;
	insertBST(&root,4);
	insertBST(&root,2);
	insertBST(&root,5);
	insertBST(&root,1);
	insertBST(&root,3);
	printInorder(root);
	printf("\n%d",treeMinimum(root));
	printf("\n%d",treeMaximum(root));
	if(checkBST(root))
		printf("\nBST");
	else
		printf("\nNot BST");
	return 0;
}
