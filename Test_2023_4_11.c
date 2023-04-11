#include <stdio.h>
#include <stdlib.h>

typedef int STDataType;

// ����λ�ýṹ��
typedef struct 
{
    STDataType x;
    STDataType y;
} Position;

// ����ջ�ṹ��
typedef struct 
{
    Position* elements;
    int top;
    int maxSize;
} Stack;

// ����һ��ջ����ʼ��
Stack createStack(int size) 
{
    Stack stack;
    stack.elements = (Position*)malloc(size * sizeof(Position));
    stack.top = -1;
    stack.maxSize = size;
    return stack;
}

// ����ջ���ͷ��ڴ�
void destroyStack(Stack* stack) 
{
    free(stack->elements);
}

// �ж�ջ�Ƿ�����
int isStackFull(Stack* stack) 
{
    return stack->top == stack->maxSize -1;
}

// �ж�ջ�Ƿ�Ϊ��
int isStackEmpty(Stack* stack) 
{
    return stack->top == -1;
}

// ��ջ����
void push(Stack* stack, Position pos) 
{
    if (isStackFull(stack)) 
    {
        return;
    }
    stack->top++;
    stack->elements[stack->top] = pos;
}

// ��ջ����
Position pop(Stack* stack) 
{
    if (isStackEmpty(stack)) 
    {
        printf("Stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    Position pos = stack->elements[stack->top];
    stack->top--;
    return pos;
}

// �ƶ�����������Թ��ĵ�ǰλ��Ϊ0������ջ������λ�ñ��Ϊ���߹�
void move(Stack* stack, int maze[][5], Position pos) {
    if (maze[pos.x][pos.y] == 0) {
        push(stack, pos);
        maze[pos.x][pos.y] = 2;
    }
}

int main() {
    // �����Թ�����
    int maze[][5] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
    };
    int width = 5;
    int height = 5;

    // ����ջ���ڴ洢·��
    Stack st = createStack(width * height);
    // ��ʼλ��
    Position startPosition = { 0, 0 };
    // �յ�
    Position endPosition = { 4, 4 };

    Position current = startPosition;
    // ��ʾ[0,0]�߹�
    maze[startPosition.x][startPosition.y] = 2;

    // Ѱ�Ҵ���㵽�յ��·��
    while (!((current.x == endPosition.x) && (current.y == endPosition.y))) 
    {
        if (current.x + 1 < height) 
        {
            Position pos = { current.x + 1, current.y };
            move(&st, maze, pos);
        }
        if (current.y + 1 < width) 
        {
            Position pos = { current.x, current.y + 1 };
            move(&st, maze, pos);
        }
        if (current.x - 1 >= 0) 
        {
            Position pos = { current.x - 1, current.y };
            move(&st, maze, pos);
        }
        if (current.y - 1 >= 0) 
        {
            Position pos = { current.x, current.y - 1 };
            move(&st, maze, pos);
        }

        // ���ջΪ�գ���ʾû���ҵ�·��
        if (isStackEmpty(&st)) {
            printf("No path found.\n");
            break;
        }
        else 
        {
            current = pop(&st);
        }
    }

    // ���ջ�ǿգ�������ҵ���·��
    if (!isStackEmpty(&st)) 
    {
        printf("Path found:\n");
        while (!isStackEmpty(&st)) 
        {
            Position pos = pop(&st);
            printf("(%d, %d)\n", pos.x, pos.y);
        }
        printf("(%d, %d)\n", endPosition.x, endPosition.y);
    }

    // ����ջ
    destroyStack(&st);
    return 0;
}