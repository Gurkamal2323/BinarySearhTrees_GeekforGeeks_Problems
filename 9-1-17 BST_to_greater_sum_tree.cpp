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

/*By leveraging the fact that the tree is a BST, we can find an O(n) solution. The idea is to traverse BST in reverse inorder.
Reverse inorder traversal of a BST gives us keys in decreasing order. Before visiting a node, we visit all greater nodes of that node.
While traversing we keep track of sum of keys which is the sum of all the keys greater than the key of current node.*/
//BST to greater sum tree
//In greater sum tree each node is equal to the sum of all nodes greater than that node
void treeTransformHelper(treeNode *root, int *sum)
{
	//base case
	if(root==NULL)
		return;
	
	//recur right subtree
	treeTransformHelper(root->right , sum);
	
	//update sum
	*sum=*sum+root->info;
	
	//store old sum in current node
	root->info=*sum - root->info;
	
	//recur for left subtree
	treeTransformHelper(root->left,sum);
}
void treeTransform(treeNode *root)
{
	//initialize sum
	int sum=0;
	treeTransformHelper(root,&sum);
}

//print Inorder (LNR)
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
	treeNode *root=NULL;
	insertBST(&root,11);
	insertBST(&root,2);
	insertBST(&root,29);
	insertBST(&root,1);
	insertBST(&root,7);
	insertBST(&root,15);
	insertBST(&root,40);
	insertBST(&root,35);
	printInorder(root);
	treeTransform(root);
	printf("\n");
	printInorder(root);
	return 0;
}
