#include<stdio.h>
#define SIZE 100

int n, u[SIZE], a[SIZE], b[SIZE], bita[SIZE], bitb[SIZE], na, nb, i, j, k;

void display(int x[]){
    printf("{ ");
    for(i=0; i<n; i++){
        if(x[i])
            printf("%d ", u[i]);
    }
    printf("}\n");
    printf("bit vector :{ ");
    for(i=0; i<n; i++){
            printf("%d ", x[i]);
    }
    printf("}\n");
}

void bunion(int a[], int b[]){
    int c[SIZE];
    for(i=0; i<n; i++)
        c[i] = a[i] | b[i];
    printf("Union :\n");
    display(c);
}

void bintersection(int a[], int b[]){
    int c[SIZE];
    for(i=0; i<n; i++)
        c[i] = a[i] & b[i];
    printf("Intersection :\n");
    display(c);
}

void bdiff(int a[], int b[]){
    int c[SIZE];
    for(i=0; i<n; i++)
        c[i] = a[i] & (~b[i]);
    display(c);
}

int main(){
    int f;

    printf("Enter size of universal set: ");
    scanf("%d", &n);

    printf("Enter the universal set: ");
    for(i=0; i<n; i++)
        scanf("%d", &u[i]);

    printf("Enter size of set A: ");
    scanf("%d", &na);

    printf("Enter set A: ");
    for(i=0; i<na; i++){
        f=0;
        scanf("%d", &a[i]);
        for(j=0; j<n; j++){
            if(a[i] == u[j])
                f=1;
        }
        if(f==0){
            printf("%d is not in the universal set\nEnter valid value: ", a[i]);
            i--; // To retry the input
        }
    }

    printf("Enter size of set B: ");
    scanf("%d", &nb);

    printf("Enter set B: ");
    for(i=0; i<nb; i++){
        f=0;
        scanf("%d", &b[i]);
        for(j=0; j<n; j++){
            if(b[i] == u[j])
                f=1;
        }
        if(f==0){
            printf("%d is not in the universal set\nEnter valid value: ", b[i]);
            i--; // To retry the input
        }
    }

    // Initialize the bit vectors for A and B
    for(i=0; i<n; i++){
        bita[i] = 0;
        bitb[i] = 0;
        for(j=0; j<na; j++){
            if(a[j] == u[i]){
                bita[i] = 1;
                break;
            }
        }
        for(k=0; k<nb; k++){
            if(b[k] == u[i]){
                bitb[i] = 1;
                break;
            }
        }
    }

    // Display sets A and B in bit vector form
    printf("Set A :\n");
    display(bita);
    printf("\nSet B :\n");
    display(bitb);

    // Perform union, intersection, and difference operations
    bunion(bita, bitb);
    bintersection(bita, bitb);
    printf("Difference A-B :\n");
    bdiff(bita, bitb);
    printf("Difference B-A :\n");
    bdiff(bitb, bita);

    return 0;
