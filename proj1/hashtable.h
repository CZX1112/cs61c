/*
 * This is so the C preprocessor does not try to include multiple copies
 * of the header file if someone uses multiple #include directives.
 */
 /*
 这样一来，如果有人使用多个#include 指令，C 预处理器就不会尝试包含头文件的多个副本。
 */
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

/*
 * Everyone uses NULL, or 0, as the null pointer,
 * but C never defines it so you have to define it yourself.  :(
 */
#ifndef NULL
#define NULL ((void *)0)
#endif

/*
 * This header file defines an interface to a generic chained hash table. 
 * It stores void * data and uses two functions, int (*) (void *)
 * and int (*) (void *, void *), to compute the hash and check
 * for equality.
 */
 /*
 该头文件定义了通用链式哈希表的接口。 它存储 void * 数据并使用两个函数
  int (*) (void *) 和 int (*) (void *, void *) 来计算哈希值并检查是否相等。
 */
struct HashBucket {
  void *key;
  void *data;
  struct HashBucket *next;
};

typedef struct HashTable {
  // -- TODO --
  // HINT: Take a look at createHashTable.
  int size;
  struct HashBucket **data;
  unsigned int (*hashFunction)(void *);
  int (*equalFunction)(void *, void *);
} HashTable;

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
 /*
 这将创建一个具有指定大小并具有给定哈希函数和比较函数的新哈希表。
 */
extern HashTable *createHashTable(int size,
                                  unsigned int (*hashFunction)(void *),
                                  int (*equalFunction)(void *, void *));

/*
 * This inserts a key/data pair into a hash table.  To use this
 * to store strings, simply cast the char * to a void * (e.g., to store
 * the string referred to by the declaration char *string, you would
 * call insertData(someHashTable, (void *) string, (void *) string).
 * Because we only need a set data structure for this spell checker,
 * we can use the string as both the key and data.
 */
 /*
 这会将键/数据对插入到哈希表中。 要使用它来存储字符串，只需将 char * 转换为 void *
 （例如，要存储声明 char *string 引用的字符串，您可以调用 
 insertData(someHashTable, (void *) string, (void *) string ). 
 因为这个拼写检查器我们只需要一组数据结构，所以我们可以使用字符串作为键和数据。
 */
extern void insertData(HashTable *table, void *key, void *data);

/*
 * This returns the corresponding data for a given key.
 * It returns NULL if the key is not found. 
 */
 /*
 这将返回给定键的相应数据。 如果未找到密钥，则返回 NULL。
 */
extern void *findData(HashTable *table, void *key);

#endif
