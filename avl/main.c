#include <stdio.h>
#include "avl.h"
#include <time.h>
#include <stdlib.h>

int main()
{
    srand(time(NULL));
    clock_t start, end;
    AVLTree *tree = NULL;
    int max = 5000;

    // int id;
    // while(1){
    //     printf("\ninsertToAVL: ");
    //     scanf("%d",&id);
    //     t = insertToAVL(id,t);
    //     printTree(t);
    // }

    start = clock();
    for(int i=0; i<max; i++){
        insertToAVL(rand()%100, 3.14, &tree);
    }
    end = clock();
    printf("CPU TIME: %d\n", (int)((double)end-start));

    printTree(tree);
    printTreeInOrder(tree);
    printf("CPU TIME: %d\n", (int)((double)end-start));

    freeAVLTree(tree);

    return 0;
}
