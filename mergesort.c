#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode *link;
}ListNode;

void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if (*phead == NULL) {
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) {
		new_node->link = *phead;
		*phead = new_node;
	}
	else {
		new_node->link = p->link;
		p->link = new_node;
	}
}
void display(ListNode *head)
{
	ListNode *p = head;
	while (p != NULL) {
		printf("%d->  ", p->data);
		p = p->link;
	}
	printf("\n");
}
ListNode *create_node(element data, ListNode *link)
{
	ListNode * new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if (new_node == NULL) {
		printf("메모리할당에러\n");
		return -1;
	}
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}

ListNode *merge(ListNode * phead1, ListNode * phead2)
{
	ListNode *new_list = NULL;
	ListNode *listtmp = NULL;
	element temp;
	if (phead1 == NULL) {
		new_list = phead2;
		return new_list;
	}
	else if (phead2 == NULL) {
		new_list = phead1;
		return new_list;
	}
	else {
		new_list = phead1;
		while (new_list->link != NULL)
			new_list = new_list->link;
		new_list->link = phead2;
		new_list = phead1;

		listtmp = new_list;
		while (listtmp->link != NULL) {
			while (new_list->link != NULL) {
				if (new_list->data > new_list->link->data) {
					temp = new_list->data;
					new_list->data = new_list->link->data;
					new_list->link->data = temp;
				}
				new_list = new_list->link;
			}
			listtmp = listtmp->link;
		}
	}
	new_list = phead1;
	return new_list;
}


int main(void)
{
	ListNode *list1 = NULL;
	ListNode *list2 = NULL;
	ListNode *p;

	insert_node(&list1, NULL, create_node(1, NULL));
	insert_node(&list1, list1, create_node(2, NULL));
	insert_node(&list1, list1->link, create_node(3, NULL));
	insert_node(&list1, list1->link->link, create_node(5, NULL));
	insert_node(&list2, NULL, create_node(4, NULL));
	insert_node(&list2, list2, create_node(6, NULL));
	insert_node(&list2, list2->link, create_node(7, NULL));
	display(list1);
	display(list2);
	p = merge(list1, list2);
	display(p);
}
