/*We can solve this in O(n) time and with a single traversal of the given BST. Since inorder traversal of BST is always a sorted array,
the problem can be reduced to a problem where two elements of a sorted array are swapped. There are two cases that we need to handle:

1. The swapped nodes are not adjacent in the inorder traversal of the BST.

 For example, Nodes 5 and 25 are swapped in {3 5 7 8 10 15 20 25}. 
 The inorder traversal of the given tree is 3 25 7 8 10 15 20 5 
If we observe carefully, during inorder traversal, we find node 7 is smaller than the previous visited node 25. Here save the context of node 25 (previous node).
Again, we find that node 5 is smaller than the previous node 20. This time, we save the context of node 5 ( current node ). Finally swap the two node’s values.

2. The swapped nodes are adjacent in the inorder traversal of BST.

  For example, Nodes 7 and 8 are swapped in {3 5 7 8 10 15 20 25}. 
  The inorder traversal of the given tree is 3 5 8 7 10 15 20 25 
Unlike case #1, here only one point exists where a node value is smaller than previous node value. e.g. node 7 is smaller than node 8.

How to Solve? We will maintain three pointers, first, middle and last. When we find the first point where current node value is smaller than previous node value,
we update the first with the previous node & middle with the current node. When we find the second point where current node value is smaller than 
previous node value, we update the last with the current node. In case #2, we will never find the second point. So, last pointer will not be updated.
After processing, if the last node value is null, then two swapped nodes of BST are adjacent.*/
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


//swap two integers
void swap(int *a, int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

// This function does inorder traversal to find out the two swapped nodes.
// It sets three pointers, first, middle and last.  If the swapped nodes are
// adjacent to each other, then first and middle contain the resultant nodes
// Else, first and last contain the resultant nodes
void correctBSTUtil( treeNode* root, treeNode** first,
                     treeNode** middle, treeNode** last,
                     treeNode** prev )
{
    if( root )
    {
        // Recur for the left subtree
        correctBSTUtil( root->left, first, middle, last, prev );
 
        // If this node is smaller than the previous node, it's violating
        // the BST rule.
        if (*prev && root->info < (*prev)->info)
        {
            // If this is first violation, mark these two nodes as
            // 'first' and 'middle'
            if ( !*first )
            {
                *first = *prev;
                *middle = root;
            }
 
            // If this is second violation, mark this node as last
            else
                *last = root;
        }
 
        // Mark this node as previous
        *prev = root;
 
        // Recur for the right subtree
        correctBSTUtil( root->right, first, middle, last, prev );
    }
}
 
// A function to fix a given BST where two nodes are swapped.  This
// function uses correctBSTUtil() to find out two nodes and swaps the
// nodes to fix the BST
void correctBST( treeNode* root )
{
    // Initialize pointers needed for correctBSTUtil()
    treeNode *first, *middle, *last, *prev;
    first = middle = last = prev = NULL;
 
    // Set the poiters to find out two nodes
    correctBSTUtil( root, &first, &middle, &last, &prev );
 
    // Fix (or correct) the tree
    if( first && last )
        swap( &(first->info), &(last->info) );
    else if( first && middle ) // Adjacent nodes swapped
        swap( &(first->info), &(middle->info) );
 
    // else nodes have not been swapped, passed tree is really BST.
}

//inorder traversal
void printInorder(treeNode *root)
{
	if(root==NULL)
	{
		return;
	}
	printInorder(root->left);
	printf("%d ",root->info);
	printInorder(root->right);
}


int main()
{
	treeNode *root=NULL;
	insertBST(&root,6);
	insertBST(&root,10);
	insertBST(&root,2);
	insertBST(&root,1);
	insertBST(&root,3);
	insertBST(&root,12);
	insertBST(&root,7);
	printf("Inorder traversal of original tree\n");
	printInorder(root);
	correctBST(root);
	printf("\nInorder traversal of corrected BST\n");
	printInorder(root);
	return 0;
}
