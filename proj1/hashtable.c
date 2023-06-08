#include "hashtable.h"
#include <stdlib.h>

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
 /*
 这将创建一个具有指定大小并具有给定哈希函数和比较函数的新哈希表。
 */
HashTable *createHashTable(int size, unsigned int (*hashFunction)(void *),
                           int (*equalFunction)(void *, void *)) {
  int i = 0;
  HashTable *newTable = malloc(sizeof(HashTable));
  newTable->size = size;
  newTable->data = malloc(sizeof(struct HashBucket *) * size);
  for (i = 0; i < size; ++i) {
    newTable->data[i] = NULL;
  }
  newTable->hashFunction = hashFunction;
  newTable->equalFunction = equalFunction;
  return newTable;
}

/*
 * This inserts a key/data pair into a hash table.  To use this
 * to store strings, simply cast the char * to a void * (e.g., to store
 * the string referred to by the declaration char *string, you would
 * call insertData(someHashTable, (void *) string, (void *) string).
 * Because we only need a set data structure for this spell checker,
 * we can use the string as both the key and data.
 */
 /*
 这会将键/数据对插入到哈希表中。 要使用它来存储字符串，只需将 char * 转换为 
 void *（例如，要存储声明 char *string 引用的字符串，您可以调用
  insertData(someHashTable, (void *) string, (void *) string ). 
  因为这个拼写检查器我们只需要一组数据结构，所以我们可以使用字符串作为键和数据。
 */
// void insertData(HashTable *table, void *key, void *data) {
//   // -- TODO --
//   // HINT:
//   // 1. Find the right hash bucket location with table->hashFunction.
//   // 2. Allocate a new hash bucket struct.
//   // 3. Append to the linked list or create it if it does not yet exist. 
//   // 1. 使用 table->hashFunction 找到正确的哈希桶位置。
//   // 2. 分配一个新的哈希桶结构。
//   // 3. 追加到链表或创建它（如果尚不存在）。
//   unsigned int loc = table->hashFunction(key);
//   loc = loc % table->size;
//   struct HashBucket *bucket = (struct HashBucket *)malloc(sizeof(struct HashBucket));
//   bucket->key = key;
//   bucket->data = data;
//   bucket->next = NULL;
//   if (table->data[loc] == NULL) {
//     table->data[loc] = bucket;
//   }
//   else {
//     struct HashBucket *currBucket = table->data[loc];
//     while (currBucket->next != NULL) {
//       currBucket = currBucket->next;
//     }
//     currBucket->next = bucket;
//   }
// }

void insertData(HashTable *table, void *key, void *data)
{
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket location with table->hashFunction.
  // 2. Allocate a new hash bucket struct.
  // 3. Append to the linked list or create it if it does not yet exist.
  unsigned int loc = table->hashFunction(key);
  struct HashBucket *bucketp = (struct HashBucket *)malloc(sizeof(struct HashBucket));
  bucketp->key = key;
  bucketp->data = data;
  if (table->data[loc] == NULL)
  {
    table->data[loc] = bucketp;
  }
  else
  {
    struct HashBucket *workp = table->data[loc];
    struct HashBucket *nextp = table->data[loc]->next;
    while (nextp != NULL)
    {
      workp = nextp;
      nextp = workp->next;
    }
    workp->next = bucketp;
  }
}

/*
 * This returns the corresponding data for a given key.
 * It returns NULL if the key is not found. 
 */
 /*
 这将返回给定键的相应数据。 如果未找到密钥，则返回 NULL。
 */
void *findData(HashTable *table, void *key)
{
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket with table->hashFunction.
  // 2. Walk the linked list and check for equality with table->equalFunction.
  unsigned int loc = table->hashFunction(key);
  struct HashBucket *workp = table->data[loc];
  while(workp != NULL){
    if((table->equalFunction)(key, workp->key) != 0){
      return workp->data;
    }
    workp = workp->next;
  }
  return NULL;
}
