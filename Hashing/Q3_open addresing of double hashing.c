#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");
    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

int HashInsert(int key, HashSlot hashTable[])
{
    //Write your code here
    int index = hash1(key), comparison = 0, deletedIndex = -1, i = 0;

    while(i < TABLESIZE){ // loop through hash table
        if(hashTable[index].indicator == USED){ // if current slot is used
            comparison++;
            if(hashTable[index].key == key) return -1; // check duplicate
        }else{ // else current slot either empty of deleted
            if(hashTable[index].indicator == DELETED && deletedIndex == -1) deletedIndex = index; // store index of first deleted slot
            if(hashTable[index].indicator == EMPTY) break; // empty slot, break loop for insertion
        }
        i++;
        index = (hash1(key) + i * hash2(key)) % TABLESIZE;
        if (comparison >= TABLESIZE) return TABLESIZE; // check if table is full
    }

    if (deletedIndex != -1) index = deletedIndex; // replace index if deleted slot is found

    hashTable[index].key = key;
    hashTable[index].indicator = USED;
    return comparison;
}

int HashDelete(int key, HashSlot hashTable[])
{
    //Write your code here
    int index = hash1(key), probe = index, comparison = 0, i= 1;

    if(hashTable[index].indicator == EMPTY) return -1; // key not found

    while(hashTable[probe].indicator == USED){
        if(hashTable[probe].key == key){ // key matches, delete key
            hashTable[probe].indicator = DELETED;
            return comparison + 1;
        }
        probe = (hash1(key) + i * hash2(key)) % TABLESIZE;
        comparison++;
        i++;
    }
    return -1; // key not found
}
