#include <stdio.h>
#include "BinarySearchTree.h"

int main()
{
	BTreeNode * BTreeRoot;
	BSTMakeAndInit(&BTreeRoot);

	BSTInsert(&BTreeRoot, 10);
	BSTInsert(&BTreeRoot, 20);
	BSTInsert(&BTreeRoot, 30);
	BSTInsert(&BTreeRoot, 5);

	printf("%d ", BSTGetNodeData(BTreeRoot));
	printf("%d ", BSTGetNodeData(BTreeRoot->right));
	printf("%d ", BSTGetNodeData(BTreeRoot->right->right));

	printf("%d ", BSTGetNodeData(BTreeRoot->left));

	return 0;
}