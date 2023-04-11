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
	// 利用cur遍历队列
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
	// 申请一个新节点插入
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		return;
	}
	newnode->data = x;
	newnode->next = NULL;
	//队列为空
	if (pq->head == NULL)
	{
		assert(pq->tail == NULL);
		pq->head = pq->tail = newnode;
	}
	// 队列不为空
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
	//队列一定不为空
	assert(pq->head != NULL);
	//只有一个节点
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

