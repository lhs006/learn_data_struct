#include <stdio.h>
#include <stdlib.h>

typedef int STDataType;

// 定义位置结构体
typedef struct 
{
    STDataType x;
    STDataType y;
} Position;

// 定义栈结构体
typedef struct 
{
    Position* elements;
    int top;
    int maxSize;
} Stack;

// 创建一个栈并初始化
Stack createStack(int size) 
{
    Stack stack;
    stack.elements = (Position*)malloc(size * sizeof(Position));
    stack.top = -1;
    stack.maxSize = size;
    return stack;
}

// 销毁栈并释放内存
void destroyStack(Stack* stack) 
{
    free(stack->elements);
}

// 判断栈是否已满
int isStackFull(Stack* stack) 
{
    return stack->top == stack->maxSize -1;
}

// 判断栈是否为空
int isStackEmpty(Stack* stack) 
{
    return stack->top == -1;
}

// 入栈操作
void push(Stack* stack, Position pos) 
{
    if (isStackFull(stack)) 
    {
        return;
    }
    stack->top++;
    stack->elements[stack->top] = pos;
}

// 出栈操作
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

// 移动操作，如果迷宫的当前位置为0，则入栈并将该位置标记为已走过
void move(Stack* stack, int maze[][5], Position pos) {
    if (maze[pos.x][pos.y] == 0) {
        push(stack, pos);
        maze[pos.x][pos.y] = 2;
    }
}

int main() {
    // 定义迷宫数组
    int maze[][5] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
    };
    int width = 5;
    int height = 5;

    // 创建栈用于存储路径
    Stack st = createStack(width * height);
    // 起始位置
    Position startPosition = { 0, 0 };
    // 终点
    Position endPosition = { 4, 4 };

    Position current = startPosition;
    // 表示[0,0]走过
    maze[startPosition.x][startPosition.y] = 2;

    // 寻找从起点到终点的路径
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

        // 如果栈为空，表示没有找到路径
        if (isStackEmpty(&st)) {
            printf("No path found.\n");
            break;
        }
        else 
        {
            current = pop(&st);
        }
    }

    // 如果栈非空，则输出找到的路径
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

    // 销毁栈
    destroyStack(&st);
    return 0;
}