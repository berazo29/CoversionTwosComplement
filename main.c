#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Node{
    unsigned char bit;
    struct Node *next;
};

void insertNode(struct Node **head, unsigned char data){
    struct Node *newNode= (struct Node*)malloc(sizeof(struct Node));
    newNode->bit = data;
    newNode->next = (*head);
    (*head) = newNode;

}
void printLinkedList(struct Node *head){
    struct Node *ptr = head;
    if (ptr == NULL){
        printf("NULL\n");
        return;
    }
    while ( ptr != NULL){
        printf("%d", ptr->bit);
        ptr = ptr->next;
    }
    printf("\n");
}
void freeNodes(struct Node **head){

    struct Node* ptr = *head;
    struct Node *next;

    while (ptr != NULL){
        next =  ptr->next;
       free(ptr);
       ptr = next;
    }
    *head = NULL;
    //printf("Free completed\n");
}

void performaceTest(double n){
    struct Node *head = NULL;

    clock_t start, end;
    double cpu_time_used;

    // Test for n times and start running clock
    start = clock();
    for (int i = 0; i < n; ++i) {
        insertNode(&head, 0);
        insertNode(&head,1);
    }
    end = clock();
    // Print the performace results
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time n = %f",n);
    printf("Time running %f\n",cpu_time_used );

    start = clock();
    freeNodes(&head);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time running free %f\n",cpu_time_used );
}

int binary(unsigned long decimal, struct Node **head){

    int counter = 0;
    unsigned long tmp = decimal;
    unsigned char bit;

    if (decimal < 0){
        return -1;
    }
    if ( decimal == 0 ){
        insertNode(head,0);
        return 1;
    }

    while (tmp != 0){
        bit = tmp % 2;
        tmp = tmp/2;
        insertNode(head,bit);
        counter++;
    }
    return counter;
}
void reverseLinkedList(struct Node **head){
    struct Node *ptr = (*head);
    struct Node *next = NULL;
    struct Node *prev = NULL;

    while (ptr != NULL){
        next = ptr->next;
        ptr->next = prev;
        prev = ptr;
        ptr = next;
    }
    (*head) = prev;

}
void binaryTwosComplement(struct Node **source, struct Node **destination){
    struct Node *ptr = *source;
    struct Node *tmp = NULL;
    struct Node **headSource = destination;
    int carry;


    if (ptr == NULL){
        return;
    }

    // Complement of 0 is
    if (ptr->next == NULL && ptr->bit == 0){
        insertNode(destination, 0);
        return;
    }
    //Flip the 1 into 0 and otherwise
    while (ptr != NULL){
        if (ptr->bit == 1){
            insertNode(destination, 0);
        } else{
            insertNode(destination, 1);
        }
        ptr = ptr->next;
    }

    //add 1 to the linked-list
    tmp = *destination;
    carry = 1;
    while (tmp != NULL){

        // If carry adds to 2 means that we have a 1 to the next value
        carry = carry + tmp->bit;
        if (carry == 2){
            tmp->bit = 0;
            carry = 1;
            tmp = tmp->next;
            continue;
        }
        tmp->bit=carry;
        break;
    }
    //|| size == 2
    reverseLinkedList(headSource);
//    if (size % 4 == 0 ){
//        return;
//    } else{
//        insertNode(headDestination,0);
//        insertNode(headSource, 1);
//    }

}
int main(int argc, char *argv[argc+1]){

    //File name from arguments
    if (argc != 2 ){
        printf("no file");
        return EXIT_SUCCESS;
    }

    // Declare the read file
    FILE *fp;

    fp = fopen( argv[1], "r");

    // Check if the file is empty
    if ( fp == NULL ){
        printf("Unable to read");
        return EXIT_SUCCESS;
    }
    // Get the data
    int long inputDecimal;
    unsigned int limit;

    struct Node *binBase = NULL;
    struct Node *twos = NULL;
    while ( fscanf( fp, "%ld %d", &inputDecimal, &limit ) != EOF ) {
        //printf("limit:%d\n",limit);
        //Positive number
        if (inputDecimal >= 0 ){
            double max = (pow(2,limit-1))-1;
            //printf("max: %f\n",max);
            // In the range
            if (inputDecimal <= max){
                int numberBin = binary(inputDecimal,&binBase);
                for (int i = numberBin; i < limit; ++i) {
                    unsigned char n = 0;
                    printf("%d",n);
                }
                printLinkedList(binBase);
            } else{
                // Out of the range
                int numberBin = binary((unsigned long )max,&binBase);
                for (int i = numberBin; i < limit; ++i) {
                    unsigned char n = 0;
                    printf("%d",n);
                }
                printLinkedList(binBase);
            }
            freeNodes(&binBase); //Free nodes
        } else{
            //printf("negative\n");
            //printf("limit:%d\n",limit);
            double max = (pow(2,limit-1));
            int long inputDecimalPositive = inputDecimal*(-1);

            if (inputDecimalPositive <= max){

                int numberBin = binary(inputDecimalPositive,&binBase);

                binaryTwosComplement(&binBase,&twos);

                for (int i = numberBin; i < limit; ++i) {
                    unsigned char n = 1;
                    printf("%d",n);
                }
                printLinkedList(twos);

            } else{
                // Out of the range
                int numberBin = binary((unsigned long )max,&binBase);
                binaryTwosComplement(&binBase,&twos);
                for (int i = numberBin; i < limit; ++i) {
                    unsigned char n = 1;
                    printf("%d",n);
                }
                printLinkedList(twos);

            }
            freeNodes(&binBase); //Free nodes
            freeNodes(&twos); //Free nodes
        }
    }

    //printf("%lu",sizeof(struct Node));
    //Close the file
    fclose(fp);


    return 0;
}
