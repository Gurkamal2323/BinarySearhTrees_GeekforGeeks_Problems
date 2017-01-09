/*treeNode *creteNewNode(treeNode *)
  void nsertBST(treeNode **)
  void printInorder(treeNode *)
  void printPostorder(treeNode *)
  void printPreorder(treeNode *)
  int getHeight(treeNode *)
  //Level-Order Traversal
  treeNode *treeMinimum(treeNode *)
  treeNode *treeMaximum(treeNode *)
  int isBalanced(treeNode *)
  treeNode *deleteBST(treeNode *, int)
  int countNodes(treeNode *)
  int getLeafCount(treeNode *)
  int countNonLeaf(treeNode *)
*/
#include<iostream>
#include<stdlib.h>
using namespace std;

//defining tree structure
struct binaryTree
{
	int info;
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
	printf("%d ",root->info);
	printInorder(root->right);
}

//preorder traversal
void printPreorder(treeNode *root)
{
	if(root==NULL)
	{
		return;
	}
	printf("%d ",root->info);
	printPreorder(root->left);
	printPreorder(root->right);
}

//postorder traversal
void printPostorder(treeNode *root)
{
	if(root==NULL)
	{
		return;
	}
	printPostorder(root->left);
	printPostorder(root->right);
	printf("%d ",root->info);
}

//height of tree
int getHeight(treeNode *root)
{
	if(root==NULL)
		return 1;
	int lh=getHeight(root->left);
	int rh=getHeight(root->right);
	return 1 + (lh>rh ? lh : rh);
}

//level order traversal
//function deeclarations
void printGivenLevel(treeNode *,int);
void printLevelOrder(treeNode *);
//getting levels in tree
void printLevelOrder(treeNode *root)
{
	int d=getHeight(root);
	int i;
	for(i=1;i<=d;i++)
	{
		printGivenLevel(root,i);
	}
}
//printing all nodes in that level
void printGivenLevel(treeNode *root,int level)
{
	if(root==NULL)
		return;
	if(level==1)
		printf("%d ",root->info);
	else if(level>1)
	{
		printGivenLevel(root->left,level-1);
		printGivenLevel(root->right,level-1);
	}
}

//get level of a node, root node is considered to be at level 1
int getLevelHelper(treeNode*, int, int);
int getLevel(treeNode *root, int val)
{
	getLevelHelper(root,val,1);
}
int getLevelHelper(treeNode *root, int val, int level)
{
	if(root==NULL)
		return 0;
	if(root->info==val)
		return level;
	int downlevel=getLevelHelper(root->left,val,level+1);
	if(downlevel!=0)
		return downlevel;
		
	downlevel=getLevelHelper(root->right,val,level+1);
	return downlevel;
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

//tree maximum
treeNode *treeMaximum(treeNode *root)
{
	if(root==NULL)
		return NULL;
	if(root->right==NULL)
	{
		return root;
	}
	treeMaximum(root->right);
}

//tree balanced
int isBalanced(treeNode *root)
{
	if(root==NULL)
		return 0;
	int lh=isBalanced(root->left);
	if(lh==-1)
		return -1;
	int rh=isBalanced(root->right);
	if(rh==-1)
		return -1;
	if(lh-rh>1 || lh-rh<-1)
		return -1;
	
	return 1 + (lh>rh ? lh : rh);
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


//inorder successor

int main()
{
	treeNode *root = NULL;
	insertBST(6, &root);
	insertBST(4, &root);
	insertBST(9, &root);
	insertBST(5, &root);
	insertBST(8, &root);
	insertBST(7, &root);
	insertBST(7, &root);
	printf("In-order traversal\n");
	printInorder(root);
	printf("\nPre-order traversal\n");
	printPreorder(root);
	printf("\nPost-order traversal\n");
	printPostorder(root);
	printf("\nHeight of tree is %d",getHeight(root));
	printf("\nDepth of tree is same as its Height");
	printf("\nLevel order traversal\n");
	printLevelOrder(root);
	printf("\nLevel of node whose value is 8 is %d",getLevel(root,8));
	treeNode *min=treeMinimum(root);
	printf("\nTree Minimum is %d",min->info);
	treeNode *max=treeMaximum(root);
	printf("\nTree Maximum is %d",max->info);
	printf("\nisBalanced = %d",isBalanced(root));
	root=deleteBST(root,9);
	printf("\nInorder traversal after deletion of 9\n");
	printInorder(root);
	int leafCount=getLeafCount(root);
	printf("\nNumber of leaf Nodes are %d",leafCount);
	int Nodes=countNodes(root);
	printf("\nNumber of Nodes are %d",Nodes);
	int NonLeaf=countNonLeaf(root);
	printf("\nNumber of Non-Leaf nodes are %d",NonLeaf);
	return 0;
}
