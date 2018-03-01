#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lineInfo{
    int letterCount;
    struct lineInfo * next;
} lineInfo;

void freeLineInfo(lineInfo * li){
    if(li == NULL) return;
    freeLineInfo(li->next);
    free(li);
}

lineInfo * newLineInfo(){
    lineInfo * node = malloc(sizeof(lineInfo));
    node->letterCount = 0;
    node->next = NULL;
    return node;
}

int main(void){
    FILE *stream;

    stream = fopen("odyssey", "r");
    if (stream == NULL)
          return -1;

    //firstpass
    lineInfo * head = newLineInfo();
    lineInfo * node = head;
    int lineCounter = 0;
    char c;
    while(!feof(stream)){
      c = fgetc(stream);
      node->letterCount++;
      if(c == '\n'){
          lineCounter++;
          node->next = newLineInfo();
          node = node->next;
      }
    }
    printf("First Pass: Read %d lines.\n", lineCounter);

    printf("Line sizes are:\n");
    node = head;
    while(node != NULL){
        printf("%d\n", node->letterCount);
        node = node->next;
    }

    node = head;
    char ** lines = malloc(lineCounter*sizeof(char*));
    for(int i=0; i<lineCounter; i++){
        lines[i] = malloc(node->letterCount * sizeof(char));
        node = node->next;
    }
    fclose(stream);

    //second pass
    stream = fopen("odyssey", "r");
    node = head;
    for(int i=0; i<lineCounter; i++){
        for(int j=0; j<node->letterCount; j++){
            c = fgetc(stream);
            if(c != '\n'){
                lines[i][j] = c;
            }
            else{
                lines[i][j] = 0;
            }
        }
        node = node->next;
    }

    for(int i=0; i<lineCounter; i++)
        printf("%s\n", lines[i]);

    for(int i=0; i<lineCounter; i++)
        free(lines[i]);
    free(lines);
    freeLineInfo(head);
    fclose(stream);

    return 0;
}
