#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

struct node {
  int data;
  struct node* left;
  struct node* right;
};

static int lookup(struct node* node, int target) {
  if (node == NULL) {
    return 0;
  }

  if (node->data == target) {
    return 1;
  } else if (node->data < target) {
    return lookup(node->right, target);
  } else {
    return lookup(node->left, target);
  }
}

struct node* NewNode(int data) {

  struct node* node = malloc(sizeof(struct node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;

  return node;
}

struct node* insert(struct node* node, int data) {
  if (node == NULL) {
    return NewNode(data);
  }

  if (node->data == data) {
    return node;
  } else if (data < node->data) {
    node->left = insert(node->left, data);
  } else {
    node->right = insert(node->right, data);
  }

  return node;
}

void DeleteNode(struct node **root) {

	if (*root == NULL) {
		return;
	}

	DeleteNode(&((*root)->left));
	DeleteNode(&((*root)->right));

	(*root)->left = NULL;
	(*root)->right = NULL;

	free(*root);
	*root = NULL;
}

struct node *build123a() {
	struct node *left = NewNode(1);
	struct node *right = NewNode(3);
	struct node *root = NewNode(2);

	root->left  = left;
	root->right = right;

	return root;
}

struct node *build123b() {
	struct node *root = NewNode(2);

	root->left  = NewNode(1);
	root->right = NewNode(3);

	return root;
}

struct node *build123c() {

	struct node *root = NULL;

	root = insert(root, 2);
	insert(root, 1);
	insert(root, 3);

	return root;
}

void testBuild123a() {

	struct node *root = build123a();

	printf("a:root:%d\n", root->data);
	printf("a:left:%d\n", root->left->data);
	printf("a:right:%d\n", root->right->data);

	DeleteNode(&root);

	root = build123b();

	printf("b:root:%d\n", root->data);
	printf("b:left:%d\n", root->left->data);
	printf("b:right:%d\n", root->right->data);

	DeleteNode(&root);

	root = build123c();

	printf("c:root:%d\n", root->data);
	printf("c:left:%d\n", root->left->data);
	printf("c:right:%d\n", root->right->data);

	DeleteNode(&root);
}

int size(struct node *root) {

	if (root == NULL) {
		return 0;
	}

	return 1 + size(root->left) + size(root->right);
}

void sizeTest() {

	struct node *root = build123a();
	printf("size = %d\n", size(root));

	DeleteNode(&root);
}

int maxDepth(struct node *node) {

	if (node == NULL) {
		return 0;
	}

	int leftMaxDepth = maxDepth(node->left);
	int rightMaxDepth = maxDepth(node->right);
	int currentMaxDepth = leftMaxDepth > rightMaxDepth ? leftMaxDepth : rightMaxDepth;

	return 1 + currentMaxDepth;
}

void maxDepthTest() {

	struct node *root = build123a();
	root->left->left = build123a();
	printf("maxDepth = %d\n", maxDepth(root));

	DeleteNode(&root);
}

int minValue(struct node *node) {

	assert(node != NULL);

	if (node->left == NULL) {
		return node->data;
	}

	return minValue(node->left);
}

void minValueTest() {

	struct node *root = build123a();
	printf("minValue = %d\n", minValue(root));

	DeleteNode(&root);
}

int maxValue(struct node *node) {

	assert(node != NULL);

	if (node->right == NULL) {
		return node->data;
	}

	return maxValue(node->right);
}

void maxValueTest() {

	struct node *root = build123a();
	printf("maxValue = %d\n", maxValue(root));

	DeleteNode(&root);
}

void printTree(struct node* node) {

	if(node == NULL) {
		return;
	}

	printTree(node->left);
	printf(" %d", node->data);
	printTree(node->right);
}

void printTreeTest() {

	struct node *root = NewNode(4);
	root->left = NewNode(2);
	root->left->left = NewNode(1);
	root->left->right = NewNode(3);
	root->right = NewNode(5);

	printf("print pre order\n");
	printTree(root);
	printf("\n");

	DeleteNode(&root);

}

void printPostOrder(struct node* node) {

	if(node == NULL) {
		return;
	}

	printPostOrder(node->left);
	printPostOrder(node->right);
	printf(" %d", node->data);
}

void printPostOrderTest() {

	struct node *root = NewNode(4);
	root->left = NewNode(2);
	root->left->left = NewNode(1);
	root->left->right = NewNode(3);
	root->right = NewNode(5);

	printf("print post order\n");
	printPostOrder(root);
	printf("\n");

	DeleteNode(&root);

}

int hasPathSum(struct node *node, int sum) {

	if (node == NULL) {
		return sum == 0;
	}

	return hasPathSum(node->left, sum - node->data) ||
	    hasPathSum(node->right, sum - node->data);
}

void hasPathSumTest() {

	struct node *root = NewNode(5);
	root->left = NewNode(4);
	root->left->left = NewNode(11);
	root->left->left->left = NewNode(7);
	root->left->left->right = NewNode(2);
	root->right = NewNode(8);
	root->right->left = NewNode(13);
	root->right->right = NewNode(4);
	root->right->right->right = NewNode(1);

	if (hasPathSum(root, 27)) {
		printf("Found sum");
	} else {
		printf("Not found sum");
	}
	printf("\n");

	DeleteNode(&root);
}

void printPath(int path[], int pathLen) {

	for(int i = 0; i < pathLen; i++) {
		printf("%d ", path[i]);
	}
	printf("\n");
}

void printPathsRecur(struct node *node, int path[], int pathLen) {

	if (node == NULL) {
		return;
	}

	path[pathLen] = node->data;

	if (node->left == NULL && node->right == NULL) {
		return printPath(path, pathLen + 1);
	}

	printPathsRecur(node->left, path, pathLen + 1);
	printPathsRecur(node->right, path, pathLen + 1);
}

void printPaths(struct node *node) {

	if(node == NULL) {
		return;
	}

	int path[1000];
	printPathsRecur(node, path, 0);
}

void printPathsTest() {

	struct node *root = NewNode(5);
	root->left = NewNode(4);
	root->left->left = NewNode(11);
	root->left->left->left = NewNode(7);
	root->left->left->right = NewNode(2);
	root->right = NewNode(8);
	root->right->left = NewNode(13);
	root->right->right = NewNode(4);
	root->right->right->right = NewNode(1);

	printPaths(root);

	DeleteNode(&root);
}

void mirror(struct node *node) {

	if (node == NULL) {
		return;
	}

	struct node *temp;
	temp = node->left;
	node->left = node->right;
	node->right = temp;

	mirror(node->left);
	mirror(node->right);
}

void mirrorTest() {

	struct node *root = NewNode(4);
	root->left = NewNode(2);
	root->left->left = NewNode(1);
	root->left->right = NewNode(3);
	root->right = NewNode(5);

	mirror(root);

	printTree(root);

	printf("\n");

	DeleteNode(&root);
}

int sameTree(struct node *a, struct node *b) {

	if (a == NULL && b == NULL) {
		return 1;
	}

	if ((a == NULL && b != NULL) ||
	    (a != NULL && b == NULL) ||
	    (a->data != b->data)) {
		return 0;
	}

	return sameTree(a->left, b->left) &&
	    sameTree(a->right, b->right);
}

void sameTreeTest() {

	struct node *rootA = NewNode(4);
	rootA->left = NewNode(2);
	rootA->left->left = NewNode(1);
	rootA->left->right = NewNode(3);
	rootA->right = NewNode(5);

	struct node *rootB = NewNode(4);
	rootB->left = NewNode(2);
	rootB->left->left = NewNode(1);
	rootB->left->right = NewNode(3);
	rootB->right = NewNode(5);

	if (sameTree(rootA, rootB)) {
		printf("Same Tree");
	} else {
		printf("Different Tree");
	}

	printf("\n");
	DeleteNode(&rootA);
	DeleteNode(&rootB);
}

void doubleTree(struct node *node) {

	if (node == NULL) {
		return;
	}

	struct node *dup = NewNode(node->data);
	struct node *left = node->left;
	node->left = dup;
	dup->left = left;

	doubleTree(dup->left);
	doubleTree(node->right);
}

void doubleTreeTest() {

	struct node *root = NewNode(2);
	root->left = NewNode(1);
	root->right = NewNode(3);

	doubleTree(root);

	printTree(root);

	printf("\n");

	DeleteNode(&root);
}

int isBST(struct node *node) {

	if (node == NULL) {
		return 1;
	}

	if (node->left != NULL && maxValue(node->left) > node->data) {
		return 0;
	}

	if (node->right != NULL && minValue(node->right) <= node->data) {
		return 0;
	}

	return isBST(node->left) && isBST(node->right);
}

void isBSTTest() {

	struct node *root = NewNode(5);
	root->left = NewNode(2);
	root->left->left = NewNode(1);
	root->left->right = NewNode(6);
	root->right = NewNode(7);

	if (isBST(root)) {
		printf("It is a valid BST");
	} else {
		printf("It is not a valid BST");
	}

	printf("\n");
	DeleteNode(&root);
}

int isBST2Inner(struct node *node, int min, int max) {

	if (node == NULL) {
		return 1;
	}

	if (min > node->data || max < node->data) {
		return 0;
	}

	return isBST2Inner(node->left, min, node->data) &&
	    isBST2Inner(node->right, node->data + 1, max);
}

int isBST2(struct node *node) {

	if (node == NULL) {
		return 1;
	}

	return isBST2Inner(node, INT_MIN, INT_MAX);
}

void isBST2Test() {

	struct node *root = NewNode(5);
	root->left = NewNode(2);
	root->left->left = NewNode(1);
	root->left->right = NewNode(6);
	root->right = NewNode(7);

	if (isBST2(root)) {
		printf("It is a valid BST");
	} else {
		printf("It is not a valid BST");
	}

	printf("\n");
	DeleteNode(&root);
}

int countTrees(int numKeys) {

	if (numKeys <= 1) {
		return 1;
	}

	int totalCount = 0;

	for(int i = 1; i <= numKeys; i++) {

		totalCount += countTrees(i - 1) * countTrees(numKeys - i);
	}

	return totalCount;
}

void countTreesTest() {
	printf("Number of unique binary search trees are %d\n", countTrees(4));
}

void join(struct node *a, struct node *b)
{
	a->right = b;
	b->left  = a;
}

struct node *append(struct node *a, struct node *b) {

	if (a == NULL) {
		return b;
	}

	if (b == NULL) {
		return a;
	}

	struct node *aLast = a->left;
	struct node *bLast = b->left;

	join(aLast, b);
	join(bLast, a);

	return a;
}

struct node *treeToList(struct node *root) {

	if (root == NULL) {
		return NULL;
	}

	struct node *left  = treeToList(root->left);
	struct node *right = treeToList(root->right);

	root->left = root;
	root->right = root;

	left = append(left, root);
	left = append(left, right);

	return left;
}

/* Create a new node */
static struct node * newNode(int data) {
    struct node * node = malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

/* Add a new node into a tree */
static void treeInsert(struct node ** rootRef, int data) {
    struct node * root = *rootRef;
    if (root == NULL) *rootRef = newNode(data);
    else {
        if (data <= root->data) treeInsert(&(root->left), data);
        else treeInsert(&(root->right), data);
    }
}

static void printList(struct node * head) {
	struct node * current = head;
	while(current != NULL) {
		printf("%d ", current->data);
		current = current->right;
		if (current == head) break;
	}
	printf("\n");
}

void DeleteList(struct node *head) {
	struct node *current = head;
	struct node *temp;
	while(current != NULL) {
		temp = current->right;
		free(current);
		if (temp == head) {
			break;
		}
		current = temp;
	}
}

int treeToListTest() {
	struct node *root = NULL;
	struct node *head;
	treeInsert(&root, 4);
	treeInsert(&root, 2);
	treeInsert(&root, 1);
	treeInsert(&root, 3);
	treeInsert(&root, 5);
	head = treeToList(root);
	printList(head);    /* prints: 1 2 3 4 5  */

	DeleteList(head);

	return(0);
}

int main() {

	/*struct node* root = NULL;
	root = insert(root, 1);
	root = insert(root, 5);
	root = insert(root, 3);
	root = insert(root, 2);

	int target = 3;
	int found = lookup(root, target);

	printf("Is the target %d found in the binary tree: %s\n", target, found == 0 ? "false" : "true");*/

	//testBuild123a();
	//sizeTest();
	//maxDepthTest();
	//minValueTest();
	//maxValueTest();
	//printTreeTest();
	//printPostOrderTest();
	//hasPathSumTest();
	//mirrorTest();
	//sameTreeTest();
	//printPathsTest();
	//doubleTreeTest();
	//isBSTTest();
	//isBST2Test();
	//countTreesTest();
	treeToListTest();
}
