#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 100
#define LIST_SIZE 1000000

typedef struct _word {
    char *string;
    int count;
    int hash; 
} Word;

typedef struct _countList {
    Word *list;
    int size;
    int available;
} CountList;

int cmpfunc (const void * a, const void * b) {

    Word *word1 = (Word *)a;
    Word *word2 = (Word *)b;

    return strcmp(word1->string, word2->string );
}

Word* newWord(Word *word, char *string,  int count,  int hash) {

    word->string = malloc(sizeof(char *) * strlen(string));
    strcpy(word->string, string);
    word->count = count;
    word->hash = hash;   

    return word;
}

void freeWord(Word *word) {
    if(word) {
        if(word->string) {
            free(word->string);
        }
    }
}

CountList* createCountList(CountList *countList,  int size) {
    countList->list = malloc(sizeof(Word) * size);
    countList->size = size;
    countList->available = size;

    for(int i = 0; i < size; i++) {
        newWord(&countList->list[i], "", 0, -1);
    }

    return countList;
}

CountList* incCountList(CountList *countList,  int size) {
    countList->list = realloc(countList->list, sizeof(Word) * countList->size + sizeof(Word) * size);
    countList->size += size;
    countList->available += size;

    for(int i = 0; i < size; i++) {
        newWord(&countList->list[i + countList->size - size], "", 0, -1);
    }

    return countList;
}

int hash(char* word) {
    int sum = 0;

    for(int i = 0; word[i] != '\0'; i++) {
        sum += word[i];
    }

    return sum;
}

int _insertWord(CountList *countList, char *word,  int hash, int try) {

    if(countList->list[hash].hash == hash) {
        if(strcmp(word, countList->list[hash].string) == 0) {
            countList->list[hash].count++;
            return hash;
        }
        return  _insertWord(countList, word, (hash + try*try) % countList->size, try + 1 );    
    }

    if(countList->list[hash].hash == -1) {
        freeWord(&countList->list[hash]);
        newWord(&countList->list[hash], word, 1, hash);
        countList->available--;
        return hash;
    }

    return  _insertWord(countList, word, (hash + try*try) % countList->size, try + 1 );    
}

int insertWord(CountList *countList, char *word) {

    if(countList->available < 0.2 * LIST_SIZE) {
        incCountList(countList, LIST_SIZE);
    }

    return _insertWord(countList, word, hash(word) % countList->size, 1);
}


void freeCountList(CountList *countList) {
    if(countList) {
        for(int i = 0; i < countList->size; i++) {
            if(countList->list[i].string != NULL) {
                free(countList->list[i].string);
            }
        }

        if(countList->list) {
            free(countList->list);
        }
    }
}

int main(int argc, char **argv) {
    CountList countList;
    char word[MAX_LEN];

    srand(time(0));
    createCountList(&countList, LIST_SIZE);

    while(scanf("%s", word) != EOF) {
        insertWord(&countList, word);
    }


    qsort(countList.list, countList.size, sizeof(Word), cmpfunc);

    for(int i = 0; i < countList.size; i++) {
        if(countList.list[i].string && countList.list[i].hash != -1) {
            printf("%s : %d\n", countList.list[i].string, countList.list[i].count);
        }
    }

    freeCountList(&countList);
}
