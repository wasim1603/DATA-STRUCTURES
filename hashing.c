#include <stdio.h>
#define SIZE 10
#define TABLE_SIZE 10
int hashTable[TABLE_SIZE];
void initializeHashTable()
{
	int i;
    for (i = 0; i < TABLE_SIZE; i++) 
	{
        hashTable[i] = -1;
    }
}
void insert(int key) 
{
    int index = key % TABLE_SIZE;
    int originalIndex = index;
    while (hashTable[index] != -1) 
	{
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) 
		{
            printf("Hash table is full, cannot insert %d\n", key);
            return;
        }
    }
    hashTable[index] = key;
    printf("Inserted %d at index %d\n", key, index);
}
void displayHashTable() 
{
    printf("Hash Table:\n");
    int i;
    for (i = 0; i < TABLE_SIZE; i++) 
	{
        if (hashTable[i] != -1) 
		{
            printf("Index %d: %d\n", i, hashTable[i]);
        }
    }
}
int main() {
    initializeHashTable();
    insert(5);
    insert(15);
    insert(25);
    insert(35);
    insert(45);
    insert(55);
    insert(65);
    insert(75);
    insert(85);
    insert(95);
    displayHashTable();
    return 0;
}

