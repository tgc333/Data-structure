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
void remove_node(ListNode **phead, ListNode *p, ListNode *remove)
{
	if (p == NULL)
		*phead = (*phead)->link;
	else
		p->link = remove->link;
	free(remove);
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
ListNode *search(ListNode *head, int x)
{
	ListNode *p;
	p = head;
	while (p != NULL) {
		if (p->data == x)
			return p;
		p = p->link;
	}
	return p;
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
void *split(ListNode ** plist, ListNode ** phead1, ListNode ** phead2)
{
	ListNode *pa = NULL;
	ListNode *pb = NULL;
	ListNode *pc = *plist;
	ListNode *new_node;
	int n = 1;

	while (pc) {
		new_node = (ListNode *)malloc(sizeof(ListNode));
		new_node->data = pc->data;
		new_node->link = NULL;

		if (n % 2 == 1) {
			if (*phead1 == NULL) {
				*phead1 = new_node;
				pa = *phead1;
			}
			else {
				pa->link = new_node;
				pa = new_node;
			}
		}
		else {
			if (*phead2 == NULL) {
				*phead2 = new_node;
				pb = *phead2;
			}
			else {
				pb->link = new_node;
				pb = new_node;
			}
		}
		pc = pc->link;
		n++;
	}
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
	printf("1번 리스트 : ");
	display(list1);
	printf("2번 리스트 : ");
	display(list2);
	p = merge(list1, list2);
	printf("합쳐진 리스트 : ");
	display(p);
	ListNode *test1 = NULL;
	ListNode *test2 = NULL;
	split(&p, &test1, &test2);
	printf("split 함수에 의한 A 리스트 : ");
	display(test1);
	printf("split 함수에 의한 B 리스트 : ");
	display(test2);
}
