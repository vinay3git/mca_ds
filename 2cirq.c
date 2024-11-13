#include <stdio.h>
#define MAX 50
int item, front = -1, rear = -1, max;

void main() {

        int ch;
        printf("enter the queue size :");
        scanf("%d",&max);
        void enqueue(),dequeue(),search(),display();

        do {
                printf("\n1) Enqueue\n2) Dequeue\n3) Search\n4) Display\n5) Exit\n enter choice :");
                scanf("%d", &ch);
                switch (ch) {
                case 1: enqueue();
                        break;
                case 2: dequeue();
                        break;
                case 3: search();
                        break;
                case 4: display();
                        break;
                case 5: printf("\n Exitted\n");
                        break;
            default: printf("\n Invalid choice\n");
        }
    } while (ch != 5);
}

int queue[MAX];

void enqueue() {
        if ((rear + 1) % max == front) {
                printf("\n overflow \n");
        }
        else {
                if (rear == -1)
                         front = 0;
                printf("\nEnter element : ");
                scanf("%d", &item);
                rear = (rear + 1) % max;
                queue[rear] = item;
        }
}
void dequeue() {
        if (front == -1) {
                printf("\n underflow \n");
        }
        else if (front == rear) {
                printf("\n deleted: %d\n", queue[front]);
                front = rear = -1;
        }
        else {
                printf("\n deleted : %d\n", queue[front]);
                front = (front + 1) % max;
        }
}


void search() {
        int n, flag = 0;
        printf("\nEnter search value: ");
        scanf("%d", &n);

        if (front == -1) {
                printf("\n underflow\n");
                return;
        }

        int pos = front;
        do {
                if (queue[pos] == n) {
                        flag = 1;
                        break;
                }

                pos = (pos + 1) % max;
        } while (pos != (rear + 1) % max);

        if (flag == 1)
                printf("\n element found\n");
        else
                printf("\n element not found\n");
}

void display() {
        if (front == -1) {
                printf("\n empty queue \n");
        }
        else {
                printf("\nQueue:\n");
                int pos = front;
                do {
                        printf("%d ", queue[pos]);
                        pos = (pos + 1) % max;
                } while (pos != (rear + 1) % max);
                printf("\n");
        }
}



