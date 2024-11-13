#include <stdio.h>
#define MAX 10

// Function Prototypes
void enqueue();
void dequeue();
void search();
void display();

// Global Variables
int c, queue[MAX], item, front = -1, rear = -1;

void main() {
    do {
        printf("\n1) Insertion\n2) Deletion\n3) Search\n4) Display\n5) Exit\n");
        scanf("%d", &c);
        switch (c) {
            case 1:
                enqueue();
                break;
            case 2:
                dequeue();
                break;
            case 3:
                search();
                break;
            case 4:
                display();
                break;
            case 5:
                printf("\n**************** Exit point ****************\n");
                break;
            default:
                printf("\nPlease enter a valid choice (1-5)\n");
        }
    } while (c != 5);
}

void enqueue() {
    if ((rear + 1) % MAX == front) {
        printf("\n****************** QUEUE OVERFLOW ******************\n");
    } else {
        if (rear == -1) front = 0;
        printf("\nEnter the element to insert: ");
        scanf("%d", &item);
        rear = (rear + 1) % MAX;
        queue[rear] = item;
    }
}

void dequeue() {
    if (front == -1) {
        printf("\n****************** QUEUE UNDERFLOW ******************\n");
    } else if (front == rear) {
        printf("\nThe deleted element is: %d\n", queue[front]);
        front = rear = -1;
    } else {
        printf("\nThe deleted element is: %d\n", queue[front]);
        front = (front + 1) % MAX;
    }
}

void search() {
    int n, flag = 0;
    printf("\nEnter the value to search: ");
    scanf("%d", &n);

    if (front == -1) {
        printf("\n****************** QUEUE UNDERFLOW ******************\n");
        return;
    }

    int pos = front;
    do {
        if (queue[pos] == n) {
            flag = 1;
            break;
        }
        pos = (pos + 1) % MAX;
    } while (pos != (rear + 1) % MAX);

    if (flag == 1)
        printf("\nElement is found\n");
    else
        printf("\nElement is not found\n");
}

void display() {
    if (front == -1) {
        printf("\n****************** QUEUE UNDERFLOW ******************\n");
    } else {
        printf("\nQueue contents:\n");
        int pos = front;
        do {
            printf("%d ", queue[pos]);
            pos = (pos + 1) % MAX;
        } while (pos != (rear + 1) % MAX);
        printf("\n");
    }
}
