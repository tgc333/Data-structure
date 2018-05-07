#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 20

typedef int element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;	//�迭ť(����ť)

void error(char *message) //���� �˻�
{
	fprintf(stderr, "%s \n", message);
	exit(1);
}

void init(QueueType *q) //�ʱ�ȭ
{
	q->front = q->rear = 0;
}

int is_empty(QueueType *q) {
	return (q->front == q->rear);
}

int is_full(QueueType *q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void *enqueue(QueueType *q, element item) //����
{
	if (is_full(q))
		error("ť ��ȭ");
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->queue[q->rear] = item;
	}
}

element dequeue(QueueType *q) // ����
{
	if (is_empty(q))
		error("\n ť ����� \n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}


int checkelement(QueueType *q) {
	return (q->queue == '+' || q->queue == '-' || q->queue == '*' || q->queue == '/');
}		//ť�� �������� ���������� �ǿ��������� ����

QueueType test(QueueType *q) {
	QueueType new_list;
	init(&new_list);
	for (int i = 1; i < q->rear + 1; i++) {
		if (checkelement(q->queue[i]) && !checkelement(q->queue[i + 1]) && !checkelement(q->queue[i + 2])) {
			switch (q->queue[i]) {
			case '+':
				enqueue(&new_list, q->queue[i + 1] + q->queue[i + 2]);
				break;
			case '-':
				enqueue(&new_list, q->queue[i + 1] - q->queue[i + 2]);
				break;
			case '*':
				enqueue(&new_list, q->queue[i + 1] * q->queue[i + 2]);
				break;
			case '/':
				enqueue(&new_list, q->queue[i + 1] / q->queue[i + 2]);
				break;
			}

			i += 2;	//�����ڶ�� �� �������� ����� �����ϰ� �ε����� �÷��ش�
		}
		else enqueue(&new_list, q->queue[i]);
	}
	return new_list;
}

void display(QueueType *q) {
	for (int i = q->front + 1; i < q->rear + 1; i++) {
		if (checkelement(q->queue[i]))
			printf("[%c] ", q->queue[i]);
		else
			printf("[%d] ", q->queue[i]);
	}
	printf("\n");
}

int main(void)
{
	QueueType q;

	init(&q);
	enqueue(&q, '-');
	enqueue(&q, '+');
	enqueue(&q, '*');
	enqueue(&q, 9);
	enqueue(&q, '+');
	enqueue(&q, 2);
	enqueue(&q, 8);
	enqueue(&q, '*');
	enqueue(&q, '+');
	enqueue(&q, 4);
	enqueue(&q, 8);
	enqueue(&q, 6);
	enqueue(&q, 3);
	display(&q);
	while (q.front + 1 != q.rear) {
		q = test(&q);
		display(&q);
	}

	return 0;
}