#include <stdio.h>
#define STACK_MAX 10
#define TRUE 1
#define FALSE 0

// TODO: Add conditions for overflow
// Implement dynamic memory allocation using a linked list
// Implement a call stack

enum BFCommands {NEXT_CELL, PREVIOUS_CELL, INCREMENT, DECREMENT, OUTPUT, INPUT, LOOP_START, LOOP_END};

int isBFCommand(char c);

typedef struct Node
{
  unsigned char value;
  struct Node* prev;
  struct Node* next;
} Node;


int main (int argc, char *argv[]) {
  if (argc != 2) { // Check for valid arguments
    printf("Expected file as argument");
    return -1;
  }
  
  FILE* pFile = fopen(argv[1], "r");
  if (pFile == NULL) { // Check validity of file
    printf("File does not exist or did not open");
  }

  Node list;
  unsigned char array[30000] = {0};
  unsigned char *ptr = array;
  unsigned int loopStart, loopEnd;

  char c;
  int command;
  while ((c=fgetc(pFile)) != EOF) {
    command = isBFCommand(c);
    //TODO: Remove isBFCommand function and enum and just make this all one switch case
    if (command != -1)
      switch (command) {
        case NEXT_CELL:
          ++ptr;
          break;
        
        case PREVIOUS_CELL:
          --ptr;
          break;
        
        case INCREMENT:
          ++*ptr;
          break;
        
        case DECREMENT:
        --*ptr;
        break;
        
        case OUTPUT:
          if ((void *)ptr < (void*)&array) {
            printf("Underflow at character %d", ftell(pFile));
            return -1;
          }
          putchar(*ptr);
          break;

        case INPUT:
          *ptr = getchar();
          break;

        case LOOP_START:
          if (*ptr == 0) {
            while (c=fgetc(pFile) != ']') {
              continue;
            }
          } else {
            loopStart = ftell(pFile);
            continue;
          }
          break;
        
        case LOOP_END:
          if (*ptr != 0) {
            fseek(pFile, loopStart, SEEK_SET);
          } else {
            continue;
          }
          break;

        default:
          break;
      }
  }
  fclose(pFile);
  return 0;
}

// int findLoopEnd(int offset, FILE** file) {
//   char c;
//   while((c=fgetc(*file)) != ']') {
//     if (c == '[')
//       findLoopEnd(ftell(*file), &*file);
//     if (c == EOF)
//       return -1;
//   }
//   return ftell(*file);
// }

int isBFCommand(char c) {
  const char bfChars[8] = {">" "<" "+" "-" "." "," "[" "]"};

  for (int i = 0; i < 8; ++i)
    if (c == bfChars[i]) return i;
  return -1;
}