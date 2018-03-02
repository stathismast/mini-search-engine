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

//Returns the number of lines in input file and
//a list with the lengths for each of those lines
int firstRead(FILE * input, lineInfo ** head){
    *head = newLineInfo();
    lineInfo * node = *head;
    int lineCounter = 0;
    char c;
    while(!feof(input)){
      c = fgetc(input);
      node->letterCount++;
      if(c == '\n'){
          lineCounter++;
          node->next = newLineInfo();
          node = node->next;
      }
    }
    printf("First Pass: Read %d lines.\n", lineCounter);
    return lineCounter;
}

void secondRead(FILE * input, char ** lines, int lineCounter, lineInfo * head){
    lineInfo * node = head;
    char c;
    for(int i=0; i<lineCounter; i++){
        for(int j=0; j<node->letterCount; j++){
            c = fgetc(input);
            if(c != '\n'){
                lines[i][j] = c;
            }
            else{
                lines[i][j] = 0;
            }
        }
        node = node->next;
    }
}

int main(void){
    FILE *stream;
    lineInfo * head, * node;


    //First read through file to count lines and line length
    if ((stream = fopen("odyssey", "r")) == NULL) return -1;
    int lineCounter = firstRead(stream, &head);
    fclose(stream);

                                                                                                        printf("Line sizes are:\n");
                                                                                                        node = head;
                                                                                                        while(node != NULL){
                                                                                                            printf("%d\n", node->letterCount);
                                                                                                            node = node->next;
                                                                                                        }

    //Allocate space for each line
    node = head;
    char ** lines = malloc(lineCounter*sizeof(char*));
    for(int i=0; i<lineCounter; i++){
        lines[i] = malloc(node->letterCount * sizeof(char));
        node = node->next;
    }

    //Second read through file to store every line
    stream = fopen("odyssey", "r");
    secondRead(stream, lines, lineCounter, head);
    fclose(stream);

                                                                                                        for(int i=0; i<lineCounter; i++)
                                                                                                            printf("%s\n", lines[i]);

    for(int i=0; i<lineCounter; i++)
        free(lines[i]);
    free(lines);
    freeLineInfo(head);

    return 0;
}
