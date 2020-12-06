#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD 5000
#define HTABLE_SIZE 40000

size_t strlen(const char *str);

int uniquewords = 0;
int totalWords = 0;

typedef struct {    // struct for words and their frequency
char oneWord[5000];
int amount;
} word;




word * hashTable[HTABLE_SIZE];



void initializeTable() {     // initializes the hash table with empty pointers
for(int i=0; i < HTABLE_SIZE; i++) {
    hashTable[i] = NULL;
    }
}

unsigned int hash(char *toHash) {   // bernstein's hash function
unsigned int value = 5381;
int length = strlen(toHash);

for(int i=0; i < length; i++) {
    value = 33 * value + toHash[i];
}

value = value % HTABLE_SIZE;
return value;
}

void hashtableInsert(word toInsertParam) {  // inserting a value to the hash table utilizing linear probing

word * toInsert = malloc(sizeof(word));
strcpy(toInsert->oneWord, strdup(toInsertParam.oneWord));
int index = hash(toInsert->oneWord);

for(int i=0; i<HTABLE_SIZE; i++) {
    int linprobe = index+i%HTABLE_SIZE;

    if (hashTable[linprobe] != NULL && strcmp(hashTable[linprobe]->oneWord, toInsert->oneWord) == 0) {
    hashTable[linprobe]->amount++;
    free(toInsert);
    return;
    }
    if (hashTable[linprobe] == NULL) {
    toInsert->amount = 1;
    hashTable[linprobe] = toInsert;
    uniquewords++;
    return;
    }
}
free(toInsert);
return;

}

void hashTableDelete(char * toDelete) {  // function for deleting a node from the hash table
int index = hash(toDelete);
for(int i=0; i < HTABLE_SIZE; i++) {


    int linprobe = index+i%HTABLE_SIZE;
    if (hashTable[linprobe] != NULL && strcmp(hashTable[linprobe]->oneWord, toDelete) == 0) {

            hashTable[linprobe] = NULL;
            return;
        }

    }
}


void sortWords() {  // sorting top 100 words into an array and printing it
int i, j, k;

word topOneHundred[100];
word previousWord;
previousWord.amount=0;


    for(j=0; j < 100; j++) {
            previousWord.amount=0;
        for(i=0; i < HTABLE_SIZE; i++) {
            if(hashTable[i] != NULL && hashTable[i]->amount > previousWord.amount){
            strcpy(previousWord.oneWord, hashTable[i]->oneWord);
            previousWord.amount = hashTable[i]->amount;

            }
        }
            topOneHundred[j] = previousWord;
            hashTableDelete(previousWord.oneWord);



    }
for(k=0; k < 100; k++) {
printf("%d. Word: %s - Frequency: %d \n", k+1, topOneHundred[k].oneWord, topOneHundred[k].amount);
}
}


int main()
{
    char filename[20];
     printf("Please enter the name of the file >");
     scanf("%s", filename);



    FILE *ptFile = fopen(filename, "r");
    initializeTable();
    char *string;
    char inputFile[10000];
    char *token = NULL;
    word readWord;
    while(fgets(inputFile, 10000, ptFile) ) {  // reading the txt file line by line
    token = strtok(inputFile, " ,.-:\n{[]\"()?!*1234567890_;");      // parsing the lines for individual words with strtok
        if (token != NULL) {
            string = strdup(token);
            for(int i = 0; string[i]; i++){
                string[i] = tolower(string[i]);  // making every letter lower case
                }
            strcpy(readWord.oneWord, strdup(string));

            readWord.amount = 1;
            hashtableInsert(readWord);  // calling the hash table insert function with a reference to the current word
            totalWords++;
            }
            while(token != NULL) {
                token = strtok(NULL, " ,.-:\n/[]\"()?!*1234567890_;");
                if (token != NULL) {
                    string = strdup(token);
                    for(int i = 0; string[i]; i++){
                    string[i] = tolower(string[i]);
                    }
                strcpy(readWord.oneWord, strdup(string));
                readWord.amount = 1;


                hashtableInsert(readWord);
                totalWords++;
                }


            }

    }

    fclose(ptFile);
    printf("Text: %s. Total number of words: %d. Number of unique words: %d \n\n", filename, totalWords, uniquewords);
    sortWords();
    return 0;
}




