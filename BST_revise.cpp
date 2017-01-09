#include<iostream>
#include<stdlib.h>
using namespace std;

//tree declaration
struct binaryTree
{
	int info; //to store the key of a node
	struct binaryTree *left; //pointer to left child node
	struct binaryTree *right; //pointer to right child node
	struct binaryTree *parent; //pointer to parent node
};

//rename of the structure
typedef binaryTree treeNode;

//create new node
treeNode *createNewNode(int val=0, treeNode *left=NULL, treeNode *right=NULL, treeNode *parent=NULL) //this function will return pointer to a node
{
	treeNode *newNode=(treeNode *)malloc(sizeof(treeNode)); //dynamic allocation for a node
	newNode->info = val;
	newNode->left = left;
	newNode->right = right;
	newNode->parent = parent;
	
	return newNode;
}

//create a binary search tree
void insertBST(treeNode **rootRef, int val) //**rootRef is a pointer to a pointer to root
{
	//cases :-
	//1. No node is there, we have to create the first node
	//2. If the value of node is less than root->info then the node is a left child
	//3. If the value of node is greater than root->info then the node is a right child
	//case 1
	if((*rootRef) == NULL)
	{
		*rootRef = createNewNode(val,NULL,NULL,NULL);
		return;
	}
	//case 2
	if(val < (*rootRef)->info)
	{
		insertBST(&((*rootRef)->left),val);
	}
	//case 3
	else
	{
		insertBST(&((*rootRef)->right),val);
	}
}

//tree minimum :- In binary tree the minimum value in tree is the key of the leftmost node in the tree
treeNode *treeMinimum(treeNode *root)
{
	if(root==NULL)
		return NULL;
	if(root->left == NULL)
		return root;
	treeMinimum(root->left);
}

//tree maximum :- In binary tree the maximum value in tree is the key of the rightmost node in the tree
treeNode *treeMaximum(treeNode *root)
{
	if(root==NULL)
		return NULL;
	if(root->right==NULL)
		return root;
	treeMaximum(root->right);
}

//In-order traversal (LNR)
void printInorder(treeNode *root)
{
	if(root==NULL)
		return;
	printInorder(root->left);
	printf("%d",root->info);
	printInorder(root->right);
}

//post-order traversal (LRN)
void printPostorder(treeNode *root)
{
	if(root==NULL)
		return;
	printPostorder(root->left);
	printPostorder(root->right);
	printf("%d",root->info);
}

//pre-order traversal (NLR)
void printPreorder(treeNode *root)
{
	if(root==NULL)
		return;
	printf("%d",root->info);
	printPreorder(root->left);
	printPreorder(root->right);
}

//height of a binary tree :- height of tree equal to max(left_height,right_height)+1
int getHeight(treeNode *root)
{
	if(root==NULL)
		return 1;
	int lh=getHeight(root->left);
	int rh=getHeight(root->right);
	
	return 1 + (lh > rh ? lh : rh);
}

//level-order traversal :- In this we print every node in each level of the tree
//first we write function to get levels in the tree
//second function will print the nodes in that level
void printGivenLevel(treeNode *, int);
void getLevel(treeNode *root)
{
	int h=getHeight(root);
	int i;
	for(i=1;i<=h;i++)
		printGivenLevel(root,i);
}
void printGivenLevel(treeNode *root, int level)
{
	if(root==NULL)
		return;
	if(level==1) //tree with only one node
		printf("%d",root->info);
	else if(level>1) //tree with nore than one levels
	{
		printGivenLevel(root->left,level-1); //start from printing left child nodes
		printGivenLevel(root->right,level-1); //then print right child nodes in the same level
	}
}

//count number of nodes in the tree
int countNodes(treeNode *root)
{
	int c=1;
	if(root==NULL)
		return 0;
	else
	{
		c+=countNodes(root->left);
		c+=countNodes(root->right);
		return c;
	}
}

//count leaf nodes :- leaf nodes are those nodes with no children
//if node is NULL return 0
//if node's left and right are NULL return 1
//else recursively traverse the left and right subtree and return getLeafCount(root->left)+getLeafCount(root->right)
int getLeafCount(treeNode *root)
{
	if(root==NULL)
		return 0;
	if(root->left==NULL && root->right==NULL)
		return 1;
	else
	return getLeafCount(root->left) + getLeafCount(root->right);
}

//count number of non-leaf nodes
int countNonLeaf(treeNode *root)
{
	int Nodes = countNodes(root);
	int LeafCount = getLeafCount(root);
	int NonLeaf = Nodes - LeafCount;
	return NonLeaf;
}

//main function
int main()
{
	treeNode *root = NULL;
	insertBST(&root, 6);
	insertBST(&root, 4);
	insertBST(&root, 9);
	insertBST(&root, 5);
	insertBST(&root, 8);
	insertBST(&root, 7);
	insertBST(&root, 7);
	printInorder(root);
	int leafCount=getLeafCount(root);
	printf("\n%d",leafCount);
	int Nodes=countNodes(root);
	printf("\n%d",Nodes);
	int NonLeaf=countNonLeaf(root);
	printf("\n%d",NonLeaf);
	return 0;
}
