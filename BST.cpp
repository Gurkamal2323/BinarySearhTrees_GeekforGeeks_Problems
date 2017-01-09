#include<iostream>
#include<stdlib.h>
using namespace std;

struct tree {
	int info;
	struct tree* left;
	struct tree* right;
	struct tree* parent;
};

typedef tree treeNode;

void printInorder(treeNode* root){
	if(root==NULL){
		return;
	}
	printInorder(root->left);
	printf("%d",root->info);
	printInorder(root->right);
}

void printPreorder(treeNode* root){
	if(root==NULL){
		return;
	}
	printf("%d",root->info);
	printPreorder(root->left);
	printPreorder(root->right);
}

void printPostorder(treeNode* root){
	if(root==NULL){
		return;
	}
	printPostorder(root->left);
	printPostorder(root->right);
   	printf("%d",root->info); 	
}

treeNode* createTreeNode(int val = 0, treeNode* left = NULL, treeNode* right = NULL, treeNode* parent = NULL){
	treeNode* newnode=(treeNode*)malloc(sizeof(treeNode));
	newnode->info=val;
	newnode->left=left;
	newnode->right=right;
	newnode->parent=parent;
	return newnode;
}

void insertBST(treeNode** rootRef, int val){
	if(*rootRef==NULL){
		*rootRef=createTreeNode(val,NULL,NULL,NULL);
		return;
	}
	if(val<(*rootRef)->info){
		insertBST(&((*rootRef)->left),val);
	}
	else{
		insertBST(&((*rootRef)->right),val);
	}
}


treeNode** treeSuccessor(treeNode** rootRef){
	if(*rootRef==NULL || (*rootRef)->right==NULL){
		return NULL;
	}
	treeNode** successorref=&((*rootRef)->right);
	while((*successorref)->left!=NULL){
		successorref=&((*successorref)->left);
	}
	return successorref;
}

void deleteBST(treeNode** rootRef, int val){
   if(*rootRef==NULL){
   	return;
   }
   if(val==(*rootRef)->info){
   	if((*rootRef)->left==NULL){
   		//ONLY RIGHT CHILD
   		treeNode* todelete=*rootRef;
   		*rootRef=(*rootRef)->right;
   		free(todelete);
	   }
	else if((*rootRef)->right==NULL){
   		//ONLY LEFT CHILD
   		treeNode* todelete=*rootRef;
   		*rootRef=(*rootRef)->left;
   		free(todelete);
	   }
	   else{
	   	treeNode** successorref=treeSuccessor(rootRef);
	   	(*rootRef)->info=(*successorref)->info;
	   	deleteBST(successorref,(*rootRef)->info);
	   }
   }	
   if(val<(*rootRef)->info){
   	deleteBST(&((*rootRef)->left),val);
   }
   else{
   	deleteBST(&((*rootRef)->right),val);
   }
}

treeNode* treeMinimum(treeNode* root){
		if(root==NULL){
		return NULL;
	}
	if(root->left==NULL){
		return root;
	}
	treeMinimum(root->left);
}

treeNode* treeMaximum(treeNode* root){
		if(root==NULL){
		return NULL;
	}
		if(root->right==NULL){
		return root;
	}
	treeMaximum(root->right);
}

int getheight(treeNode* root){
	if(root==NULL){
		return 1;
	}
	int lh=getheight(root->left);
	int rh=getheight(root->right);
	return (lh>rh ? lh:rh)+1;
}

int isBalancedRecursive(treeNode* root){
	if(root==NULL){
		return 0;
	}
	int lh=isBalancedRecursive(root->left);
	if(lh==-1){
		return -1;
	}
	int rh=isBalancedRecursive(root->right);
	if(rh==-1){
		return -1;
	}
	if(lh-rh>1 || lh-rh<-1){
		return -1;
	}
	return (lh>rh ? lh:rh)+1;
}

treeNode* balancedTreeFromArray(int* arr, int start, int end){
	if(start>end){
		return NULL;
	}
	int mid=(start+end)/2;
	treeNode* root=createTreeNode(arr[mid],NULL,NULL,NULL);
	root->left=balancedTreeFromArray(arr,start,mid-1);
	root->right=balancedTreeFromArray(arr,mid+1,end);
	return root;
}



int main() {
	treeNode *root = NULL;
	insertBST(&root, 6);
	insertBST(&root, 4);
	insertBST(&root, 9);
	insertBST(&root, 5);
	insertBST(&root, 8);
	insertBST(&root, 7);
	insertBST(&root, 7);
	printInorder(root);
	printf("\npreorder=");
	printPreorder(root);
	printf("\n");
    int h=getheight(root);
	printf("\n height of tree = %d",h);
	printf("\n isBalancedRecursive = %d",isBalancedRecursive(root));

	printf("\n");
	deleteBST(&root, 7);
    	printPostorder(root);
	printf("\n");
	treeNode* min=treeMinimum(root);
	printf("\n tree minimum = %d",min->info);
	printf("\n isBalancedRecursive = %d",isBalancedRecursive(root));
    treeNode* max=treeMaximum(root);
	printf("\n tree maximum = %d",max->info);
	printf("\n");
	printf("\nbalancedTreeFromArray({1,2,3,4,5,6,7})");
	int arr[] = {1,2,3,4,5,6,7};
	treeNode* newRoot = balancedTreeFromArray(arr,0,6);

	printf("\npostorder=");
	printPostorder(newRoot);
	//printf("\ntreeSuccessor(3) : %d", treeSuccessor(&(*newRoot->left)->right)->info);
	//printf("\ntreeSuccessor(4) : %d", treeSuccessor(newRoot)->info);
//	printf("\ntreeSuccessor(5) : %d", treeSuccessor(newRoot->right->left)->info);
//	printf("\ntreeSuccessor(6) : %d", treeSuccessor(newRoot->right)->info);

	printf("\n");
	return 0;
}

