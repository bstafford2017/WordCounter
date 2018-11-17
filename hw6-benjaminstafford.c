// Benjamin Stafford
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50

struct Record {
    int count;
    char word[MAX];
};

struct Record * add(struct Record *ptr, struct Record record, int size){
    if(ptr == NULL){
        ptr = (struct Record *)calloc(1, sizeof(record));
        *ptr = record;
		//printf("During 1st: %s\t%d\n", ptr->word, ptr->count);
        return ptr;
    } else {
        struct Record *newPTR = (struct Record *)calloc(size, sizeof(record));
        memcpy(newPTR, ptr, sizeof(record)*(size-1));
		struct Record *head = newPTR;
        free(ptr);
        *(newPTR+(size-1)) = record;
        return head;
    }
}

char * removeChar(char string[], char c){
    int j = 0;
    bool flag = false;
    for(int i = 0; string[i] != '\0'; i++){
        if(string[i] == c){
            for(j = i; string[j] != '\0'; j++){
                flag = true;
                string[j] = string[j+1];
            }
        }
    }
    if(flag == true){
        string[j] = '\0';
    }
    return string;
}

bool check(struct Record *ptr, struct Record record, int size){
    if(ptr == NULL){
        return false;
    }
    bool flag = false;
    for(int i = 1; i < size; i++, ptr++){
        if(strcmp(record.word, ptr->word) == 0){
            ptr->count += 1;
            return true;
        }
    }
    if(flag == false){
        return false;
    }
}

struct Record * sort(struct Record *ptr, int size){
	struct Record *head = ptr;
	for(int i = 0; i < size-1; i++){
		for(int j = 0; j < size-1; j++){
			if(ptr[j].count < ptr[j+1].count){
				struct Record temp = ptr[j+1];
				ptr[j+1] = ptr[j];
				ptr[j] = temp;
			}
		}
	}
	return head;
}

void print(struct Record *ptr, int size){
    for(int i = 0; i < size; i++, ptr++){
        printf("'%s'\t%d\n", ptr->word, ptr->count);
    }
}

int main(int argc, char* argv[]){
    struct Record *ptr = NULL;
    struct Record record;
    FILE *file;
//    file = fopen(argv[1], "r");
    file = fopen("test.txt", "r");
    if(file == NULL) exit(0);
    int count = 0;
    while(fscanf(file, "%s", record.word) != EOF){
        record.count = 1;

        // Remove .,!:-()
        strcpy(record.word, removeChar(record.word, '.'));
        strcpy(record.word, removeChar(record.word, ','));
        strcpy(record.word, removeChar(record.word, '!'));
        strcpy(record.word, removeChar(record.word, ':'));
        strcpy(record.word, removeChar(record.word, '-'));
        strcpy(record.word, removeChar(record.word, '\''));
        strcpy(record.word, removeChar(record.word, '('));
        strcpy(record.word, removeChar(record.word, ')'));

        // To lowercase
        for(int i = 0; record.word[i] != '\0'; i++){
            record.word[i] = tolower(record.word[i]);
        }
       // printf("%s\t%d\n", record.word, record.count);

        // Check if already in struct array
        if(check(ptr, record, count) == 0){
       		count++; // 1, 2, ... , 80 total
        	ptr = add(ptr, record, count);
        }
    }
    fclose(file);
	ptr = sort(ptr, count);
    print(ptr, count);
    free(ptr);
    ptr = NULL;
    return 0;
}
