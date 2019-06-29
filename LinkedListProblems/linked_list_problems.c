#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct node {
	int data;
	struct node* next;
};

/*
 * Build the list {1, 2, 3} in the heap and store
 * its head pointer in a local stack variable.
 * Returns the head pointer to the caller.
 */
struct node* BuildOneTwoThree() {
	struct node* head = NULL;
	struct node* second = NULL;
	struct node* third = NULL;

	head = malloc(sizeof(struct node));
	second = malloc(sizeof(struct node));
	third = malloc(sizeof(struct node));

	head->data = 1;
	head->next = second;

	second->data = 2;
	second->next = third;

	third->data = 3;
	third->next = NULL;

	return head;
};

/**
 * Given a linked list head pointer, compute and return the number of nodes in the list
 */
int Length(struct node* head) {

	int length = 0;

	struct node* current = head;

	while(current != NULL) {
		current = current->next;
		length++;
	}

	return length;
}

void LinkTest() {
	struct node* head = BuildOneTwoThree();
	struct node* newNode;

	newNode = malloc(sizeof(struct node));
	newNode->data = 0;
	newNode->next = head;

	head = newNode;
}

void Push(struct node** headRef, int data) {
	struct node* newNode = malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = *headRef;

	*headRef = newNode;
}

void PushTest() {
	struct node* head = BuildOneTwoThree();

	Push(&head, 0);
	Push(&head, -1);
}

struct node* BuildWithSpecialCase() {
	struct node* head = NULL;
	struct node* tail;
	int i;

	Push(&head, 1);
	tail = head;

	// Do all the other nodes using 'tail'
	for(i = 2; i < 6; i++) {
		Push(&(tail->next), i);
		tail = tail->next;
	}

	return head;
}

struct node* BuildWithDummyNode() {
	struct node dummy;
	struct node* tail = &dummy;

	int i;
	dummy.next = NULL;

	for(i=1; i < 6; i++) {
		Push(&(tail->next), i);
		tail = tail->next;
	}

	return dummy.next;
}

struct node* BuildWithLocalRef() {
	struct node* head = NULL;
	struct node** lastPtrRef = &head;
	int i;

	for(i = 1; i < 6; i++) {
		Push(lastPtrRef, i);
		lastPtrRef = &((*lastPtrRef)->next);
	}

	return head;
}

void AppendNode(struct node** headRef, int num) {
	struct node* current = *headRef;
	struct node* newNode;

	newNode = malloc(sizeof(struct node));
	newNode->data = num;
	newNode->next = NULL;

	if (current == NULL) {
		*headRef = newNode;
	} else {
		while(current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
}

void AppendNodeWithPush(struct node** headRef, int num) {
	struct node* current = *headRef;

	if (current == NULL) {
		Push(headRef, num);
	} else {
		while(current->next != NULL) {
			current = current->next;
		}
		Push(&(current->next), num);
	}
}

struct node* CopyList(struct node* head) {
	struct node* current = head;
	struct node* newList = NULL;
	struct node* tail = NULL;

	while(current != NULL) {
		if(newList == NULL) {
			newList = malloc(sizeof(struct node));
			newList->data = current->data;
			newList->next = NULL;
			tail = newList;
		} else {
			tail->next = malloc(sizeof(struct node));
			tail = tail->next;
			tail->data = current->data;
			tail->next = NULL;
		}
		current = current->next;
	}

	return newList;
}

struct node* CopyList2(struct node* head) {
	struct node* current = head;
	struct node* newList = NULL;
	struct node* tail = NULL;

	while(current != NULL) {
		if(newList == NULL) {
			Push(&newList, current->data);
			tail = newList;
		} else {
			Push(&(tail->next), current->data);
			tail = tail->next;
		}
		current = current->next;
	}

	return newList;
}

struct node* CopyList3(struct node* head) {
	struct node* current = head;
	struct node* tail;
	struct node dummy;

	dummy.next = NULL;
	tail = &dummy;

	while(current != NULL) {
		Push(&(tail->next), current->data);
		tail = tail->next;
		current = current->next;
	}

	return dummy.next;
}

struct node* CopyList4(struct node* head) {
	struct node* current = head;
	struct node* newList = NULL;
	struct node** lastPtrRef;

	lastPtrRef = &newList;

	while(current != NULL) {
		Push(lastPtrRef, current->data);
		lastPtrRef = &((*lastPtrRef)->next);
		current = current->next;
	}

	return newList;
}

struct node* CopyList5(struct node* head) {
	if(head == NULL) {
		return NULL;
	}

	struct node* newList = malloc(sizeof(struct node));
	newList->data = head->data;
	newList->next = CopyList5(head->next);

	return newList;
}

int Count(struct node* head, int searchFor) {

	int count = 0;

	for(struct node* current = head; current != NULL; current = current->next) {
		if (current->data == searchFor) {
			++count;
		}
	}

	return count;
}

void countTest() {
	struct node* head = BuildOneTwoThree();
	printf("Count = %d", Count(head, 2));
}

int GetNth(struct node* head, int index) {
	int curr_index = 0;
	for(struct node* current = head; current != NULL; current = current->next, curr_index++) {
		if (curr_index == index) {
			return current->data;
		}
	}
	assert(index >= 0 && index < curr_index);
	return -1;
}

void GetNthTest() {

	struct node* myList = BuildOneTwoThree();
	int lastNode = GetNth(myList, 2);

	printf("The node at index %d is %d", 2, lastNode);
}

void DeleteList(struct node **head) {

	struct node *current = *head;
	struct node *next;

	while(current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
}

void DeleteListTest() {
	struct node* myList = BuildOneTwoThree();
	DeleteList(&myList);
	myList = NULL;
}

int Pop(struct node **head) {

	assert(*head != NULL);

	struct node *top = *head;
	struct node *next = top->next;
	int value = top->data;

	free(top);
	*head = next;

	return value;
}

void PopTest() {

	struct node* head = BuildOneTwoThree();
	int a = Pop(&head);
	int b = Pop(&head);
	int c = Pop(&head);

	int len = Length(head);
	printf("a = %d, b = %d, c = %d, len = %d\n", a, b, c, len);

	DeleteList(&head);
}

void InsertNth(struct node **headRef, int index, int value) {

	int currentIndex = 0;
	struct node *current = *headRef;
	struct node *previous = NULL;

	while(currentIndex < index) {
		previous = current;
		current = current->next;
		currentIndex++;
	}

	Push(&current, value);

	if(previous == NULL) {
		*headRef = current;
	} else {
		previous->next = current;
	}
}

void InsertNthTest() {

	struct node *head = NULL;

	InsertNth(&head, 0, 13);
	InsertNth(&head, 1, 42);
	InsertNth(&head, 1, 5);

	//print
	struct node *current = head;
	while(current != NULL) {
		printf("value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&head);
}

void SortedInsert(struct node **headRef, struct node *newNode) {

	struct node *current  = *headRef;
	struct node *previous = NULL;

	while(current != NULL) {
		if (current->data >= newNode->data) {
			break;
		}
		previous = current;
		current  = current->next;
	}

	if (previous == NULL) {
		newNode->next = *headRef;
		*headRef = newNode;
	} else {
		newNode->next = previous->next;
		previous->next = newNode;
	}
}

void SortedInsertTest() {

	struct node *head = NULL;

	InsertNth(&head, 0, 50);
	InsertNth(&head, 0, 42);
	InsertNth(&head, 0, 5);

	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = 48;
	newNode->next = NULL;
	SortedInsert(&head, newNode);

	//print
	struct node *current = head;
	while(current != NULL) {
		printf("value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&head);
}

void InsertSort(struct node **headRef) {

	struct node *current = *headRef;
	struct node *head = NULL;
	struct node *next;

	while(current != NULL) {
		next = current->next;
		SortedInsert(&head, current);
		current = next;
	}

	*headRef = head;
}

void InsertSortTest() {

	struct node *head = NULL;

	Push(&head, 5);
	Push(&head, 42);
	Push(&head, 39);

	//print before
	struct node *current = head;
	while(current != NULL) {
		printf("value = %d\n", current->data);
		current = current->next;
	}

	InsertSort(&head);

	//print after
	current = head;
	while(current != NULL) {
		printf("value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&head);
}

void Append(struct node **aRef, struct node **bRef) {

	struct node *aCurrent = *aRef;

	while(aCurrent != NULL) {
		if (aCurrent->next == NULL) {
			break;
		}
		aCurrent = aCurrent->next;
	}

	if(aCurrent == NULL) {
		*aRef = *bRef;
	} else {
		aCurrent->next = *bRef;
	}

	*bRef = NULL;
}

void AppendTest() {

	struct node *headA = NULL;

	Push(&headA, 5);
	Push(&headA, 42);
	Push(&headA, 39);

	struct node *headB = NULL;

	Push(&headB, 51);
	Push(&headB, 421);
	Push(&headB, 391);

	Append(&headA, &headB);

	//print after
	struct node *current = headA;
	while(current != NULL) {
		printf("value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&headA);
	DeleteList(&headB);

}

void FrontBackSplit(struct node *source, struct node **frontRef, struct node **backRef) {

	if(source == NULL) {
		return;
	}

	struct node *fast = source;
	struct node *slow = source;
	struct node *prev = NULL;

	while(fast != NULL) {
		prev = slow;
		slow = slow->next;
		fast = fast->next;
		if (fast == NULL) {
			break;
		}
		fast = fast->next;
	}

	*frontRef = source;
	prev->next = NULL;

	*backRef = slow;
}

void FrontBackSplitTest() {

	struct node *head = NULL;

	Push(&head, 5);
	Push(&head, 42);
	Push(&head, 39);

	//print before
	struct node *current = head;
	while(current != NULL) {
		printf("value = %d\n", current->data);
		current = current->next;
	}

	printf("----\n");

	struct node *first = NULL;
	struct node *second = NULL;

	FrontBackSplit(head, &first, &second);

	//print first
	current = first;
	while(current != NULL) {
		printf("value = %d\n", current->data);
		current = current->next;
	}

	printf("----\n");

	//print second
	current = second;
	while(current != NULL) {
		printf("value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&first);
	DeleteList(&second);
}

void RemoveDuplicates(struct node *head) {

	struct node *current = head;
	struct node *temp = NULL;

	while(current != NULL) {
		if (current->next != NULL && current->data == current->next->data) {
			temp = current->next;
			current->next = current->next->next;
			temp->next = NULL;
			free(temp);
		} else {
			current = current->next;
		}
	}
}

void RemoveDuplicatesTest() {

	struct node *head = NULL;

	Push(&head, 59);
	Push(&head, 52);
	Push(&head, 42);
	Push(&head, 42);
	Push(&head, 42);
	Push(&head, 5);

	RemoveDuplicates(head);

	//print
	struct node *current = head;
	while(current != NULL) {
		printf("value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&head);
}

void MoveNode(struct node **destRef, struct node **sourceRef) {

	if (sourceRef == NULL) {
		return;
	}

	struct node *newSourceHead = (*sourceRef)->next;

	(*sourceRef)->next = *destRef;
	*destRef = *sourceRef;

	*sourceRef = newSourceHead;
}

void MoveNodeTest() {

	struct node *a = BuildOneTwoThree();
	struct node *b = BuildOneTwoThree();

	MoveNode(&a, &b);

	//print a
	struct node *current = a;
	while(current != NULL) {
		printf("a:value = %d\n", current->data);
		current = current->next;
	}

	//print b
	current = b;
	while(current != NULL) {
		printf("b:value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&a);
	DeleteList(&b);
}

void AlternatingSplit(struct node *source, struct node **aRef, struct node **bRef) {
	while(source != NULL) {
		MoveNode(aRef, &source);
		MoveNode(bRef, &source);
	}
}

void AlternatingSplitTest() {

	struct node *a = BuildOneTwoThree();
	struct node *b = BuildOneTwoThree();

	MoveNode(&a, &b);
	MoveNode(&a, &b);
	MoveNode(&a, &b);

	//print a
	struct node *current = a;
	while(current != NULL) {
		printf("a:value = %d\n", current->data);
		current = current->next;
	}

	struct node *odd = NULL;
	struct node *even = NULL;

	AlternatingSplit(a, &odd, &even);

	//print odd
	current = odd;
	while(current != NULL) {
		printf("odd:value = %d\n", current->data);
		current = current->next;
	}

	//print even
	current = even;
	while(current != NULL) {
		printf("even:value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&odd);
	DeleteList(&even);
}

struct node* ShuffleMerge(struct node *a, struct node *b) {
	struct node *result = NULL;
	struct node **last = &result;

	while(a != NULL || b != NULL) {

		if (a == NULL) {
			*last = b;
			break;
		} else if (b == NULL) {
			*last = a;
			break;
		} else {
			MoveNode(last, &a);
			last = &((*last)->next);
			MoveNode(last, &b);
			last = &((*last)->next);
		}
	}

	return result;
}

void ShuffleMergeTest() {

	struct node *a = BuildOneTwoThree();
	struct node *b = BuildOneTwoThree();

	struct node *output = ShuffleMerge(a, b);

	//print output
	struct node *current = output;
	while(current != NULL) {
		printf("output:value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&output);
}

struct node *SortedMerge(struct node *a, struct node *b) {
	struct node *result = NULL;
	struct node **last = &result;

	while(a != NULL || b != NULL) {
		if (a == NULL) {
			*last = b;
			break;
		} else if (b == NULL) {
			*last = a;
			break;
		} else {
			if (a->data <= b->data) {
				MoveNode(last, &a);
			} else {
				MoveNode(last, &b);
			}
			last = &((*last)->next);
		}
	}

	return result;
}

void SortedMergeTest() {

	struct node *a = BuildOneTwoThree();
	struct node *b = BuildOneTwoThree();

	struct node *output = SortedMerge(a, b);

	//print output
	struct node *current = output;
	while(current != NULL) {
		printf("output:value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&output);
}

void MergeSort(struct node **headRef) {

	if (headRef == NULL || *headRef == NULL) {
		return;
	}

	if ((*headRef)->next == NULL) {
		return;
	}

	struct node *leftRef  = NULL;
	struct node *rightRef = NULL;

	FrontBackSplit(*headRef, &leftRef, &rightRef);

	MergeSort(&leftRef);
	MergeSort(&rightRef);

	*headRef = SortedMerge(leftRef, rightRef);
}

void MergeSortTest() {

	struct node *a = BuildOneTwoThree();
	Push(&a, 15);
	Push(&a, 30);

	MergeSort(&a);

	//print output
	struct node *current = a;
	while(current != NULL) {
		printf("value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&a);
}

struct node *SortedIntersect(struct node *a, struct node *b) {
	struct node *result = NULL;
	struct node **lastRef = &result;

	while(a != NULL && b != NULL) {
		if (a->data == b->data) {
			Push(lastRef, a->data);
			lastRef = &((*lastRef)->next);
			a = a->next;
			b = b->next;
		} else if (a->data < b->data) {
			a = a->next;
		} else {
			b = b->next;
		}
	}

	return result;
}

void SortedIntersectTest() {

	struct node *a = NULL;
	Push(&a, 30);
	Push(&a, 15);
	Push(&a, 3);
	Push(&a, 2);
	Push(&a, 1);

	struct node *b = NULL;
	Push(&b, 15);
	Push(&b, 2);

	struct node *output = SortedIntersect(a, b);

	//print output
	struct node *current = output;
	while(current != NULL) {
		printf("Intersection value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&a);
	DeleteList(&b);
	DeleteList(&output);
}

void Reverse(struct node **headRef) {

	assert(headRef != NULL);

	struct node *prev = NULL;
	struct node *head = *headRef;
	struct node *next = NULL;

	while(head != NULL) {
		next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}

	*headRef = prev;
}

void ReverseTest() {

	struct node *head;
	head = BuildOneTwoThree();

	Reverse(&head);

	//print head
	struct node *current = head;
	while(current != NULL) {
		printf("reverse value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&head);
}

void RecursiveReverse(struct node **headRef) {

	assert(headRef != NULL);

	if (*headRef == NULL) {
		return;
	}

	if((*headRef)->next == NULL) {
		return;
	}

	struct node *prevHead = *headRef;

	*headRef = (*headRef)->next;

	RecursiveReverse(headRef);

	prevHead->next->next = prevHead;

	prevHead->next = NULL;
}

void RecursiveReverseTest() {

	struct node *head;
	head = BuildOneTwoThree();
	Push(&head, 15);

	RecursiveReverse(&head);

	//print head
	struct node *current = head;
	while(current != NULL) {
		printf("reverse value = %d\n", current->data);
		current = current->next;
	}

	DeleteList(&head);
}

int main() {

	//  countTest();
	//  GetNthTest();
	//  DeleteListTest();
	//  PopTest();
	//  InsertNthTest();
	//  SortedInsertTest();
	//  InsertSortTest();
	//  AppendTest();
	//  FrontBackSplitTest();
	//  RemoveDuplicatesTest();
	//  MoveNodeTest();
	//  AlternatingSplitTest();
	//  ShuffleMergeTest();
	//  SortedMergeTest();
	//  MergeSortTest();
	//  SortedIntersectTest();
	//  ReverseTest();
	RecursiveReverseTest();

	return 0;
}
