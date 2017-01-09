/*Program to find Lowest Common Ancestor (LCA) between two nodes
Let T be a rooted tree. The lowest common ancestor between two nodes n1 and n2 is defined as the lowest node in T that has both n1 and n2 as descendants
(where we allow a node to be a descendant of itself).

The LCA of n1 and n2 in T is the shared ancestor of n1 and n2 that is located farthest from the root. Computation of lowest common ancestors may be useful,
for instance, as part of a procedure for determining the distance between pairs of nodes in a tree: the distance from n1 to n2 can be computed as the distance
from the root to n1, plus the distance from the root to n2, minus twice the distance from the root to their lowest common ancestor. (Source Wiki)

Solutions:
If we are given a BST where every node has parent pointer, then LCA can be easily determined by traversing up using parent pointer and printing the first
intersecting node.

We can solve this problem using BST properties. We can recursively traverse the BST from root. The main idea of the solution is, while traversing from
top to bottom, the first node n we encounter with value between n1 and n2, i.e., n1 < n < n2 or same as one of the n1 or n2, is LCA of n1 and n2 
(assuming that n1 < n2). So just recursively traverse the BST in, if node’s value is greater than both n1 and n2 then our LCA lies in left side of the node,
if it’s is smaller than both n1 and n2, then LCA lies on right side. Otherwise root is LCA (assuming that both n1 and n2 are present in BST)*/
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

//insert a key in node
void insertBST(treeNode **rootRef, int val)
{
	if(*rootRef==NULL)
	{
		//there is node so we create one
		*rootRef=createNewNode(val,NULL,NULL,NULL);
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

//LCA
treeNode *LCA(treeNode *root, int n1, int n2)
{
	if(root==NULL)
		return NULL;
	//if n1 and n2 are both smaller than root->info then LCA lies in left subtree
	if(root->info > n1 && root->info > n2)
		return LCA(root->left,n1,n2);
	//if n1 and n2 are greater than root->info then LCA lies in right subtree
	if(root->info < n1 && root->info < n2)
		return LCA(root->right,n1,n2);
		
	return root;
}

int main()
{
	treeNode *root=NULL;
	insertBST(&root,20);
	insertBST(&root,8);
	insertBST(&root,22);
	insertBST(&root,4);
	insertBST(&root,12);
	insertBST(&root,10);
	insertBST(&root,14);
	treeNode *temp=LCA(root,10,14);
	printf("LCA between 10 and 14 is %d",temp->info);
	return 0;
}
