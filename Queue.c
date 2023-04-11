#include "Queue.h"

void QInit(Queue* pq)
{
	assert(pq);
	pq->head = pq->tail = NULL;
	pq->size = 0;
}

void QDestroy(Queue* pq)
{
	assert(pq);
	QNode* cur = pq->head;
	// ����cur��������
	while (cur)
	{
		QNode* next = cur->next;
		free(cur);
		cur = next;

	}
	pq->head = pq->tail = NULL;
	pq->size = 0;
}

void QPush(Queue* pq, QDataType x)
{
	assert(pq);
	// ����һ���½ڵ����
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		return;
	}
	newnode->data = x;
	newnode->next = NULL;
	//����Ϊ��
	if (pq->head == NULL)
	{
		assert(pq->tail == NULL);
		pq->head = pq->tail = newnode;
	}
	// ���в�Ϊ��
	else
	{
		pq->tail->next = newnode;
		pq->tail = newnode;
	}

	pq->size++;
}

void QPop(Queue* pq)
{
	assert(pq);
	//����һ����Ϊ��
	assert(pq->head != NULL);
	//ֻ��һ���ڵ�
	if (pq->head->next == NULL)
	{
		free(pq->head);
		pq->head = pq->tail = NULL;
	}
	else
	{
		QNode* next = pq->head->next;
		free(pq->head);
		pq->head = next;
		
	}
	pq->size--;
}

bool QEmpty(Queue* pq)
{
	assert(pq);
	return pq->size == 0;
}

int QSize(Queue* pq)
{
	assert(pq);
	return pq->size;
}
QDataType QFront(Queue* pq)
{
	assert(pq);
	return pq->head->data;
}

QDataType QTail(Queue* pq)
{
	assert(pq);
	return pq->tail->data;
}

