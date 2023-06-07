/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philspel.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in 
 * the grading process.
 */
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 0;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(2255, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */
  return 0;
}

/*
 * This should hash a string to a bucket index.  Void *s can be safely cast
 * to a char * (null terminated string) and is already done for you here 
 * for convenience.
 */
 /*
 这应该将字符串散列到桶索引。 Void *s 可以安全地转换为 char *（空终止字符串），
 为了方便起见，这里已经为您完成了。
 */
unsigned int stringHash(void *s) {
  char *string = (char *)s;
  // -- TODO --
  unsigned int result = 0;
  int c;
  while (*string != 0) {
    result = result * 31 + *string;
    string++;
  }
  return result;
}

/*
 * This should return a nonzero value if the two strings are identical 
 * (case sensitive comparison) and 0 otherwise.
 */
 /*
 如果两个字符串相同（区分大小写的比较），这应该返回一个非零值，否则返回 0。
 */
int stringEquals(void *s1, void *s2) {
  char *string1 = (char *)s1;
  char *string2 = (char *)s2;
  // -- TODO --
  if (strcmp(s1, s2) == 0) {
    return 1;
  }
  else {
    return 0;
  }
}

/*
 * This function should read in every word from the dictionary and
 * store it in the hash table.  You should first open the file specified,
 * then read the words one at a time and insert them into the dictionary.
 * Once the file is read in completely, return.  You will need to allocate
 * (using malloc()) space for each word.  As described in the spec, you
 * can initially assume that no word is longer than 60 characters.  However,
 * for the final 20% of your grade, you cannot assumed that words have a bounded
 * length.  You CANNOT assume that the specified file exists.  If the file does
 * NOT exist, you should print some message to standard error and call exit(1)
 * to cleanly exit the program.
 *
 * Since the format is one word at a time, with new lines in between,
 * you can safely use fscanf() to read in the strings until you want to handle
 * arbitrarily long dictionary chacaters.
 */
 /*
 此函数应从字典中读取每个单词并将其存储在哈希表中。 您应该首先打开指定的文件，然后一次一个
 地读取单词并将它们插入字典。 一旦文件完全读入，返回。 您需要为每个单词分配（使用 malloc()）
 空间。 如规范中所述，您最初可以假设没有任何单词超过 60 个字符。 但是，对于你成绩的最后 20%
 ，你不能假设单词的长度是有限的。 您不能假设指定的文件存在。 如果该文件不存在，您应该向标准
 错误打印一些消息并调用 exit(1) 以干净地退出程序。 由于格式是一次一个单词，中间有新行，您可
 以安全地使用 fscanf() 来读取字符串，直到您想要处理任意长的字典字符为止。
 */
void readDictionary(char *dictName) {
  // -- TODO --
  FILE *fp;
  char *word = (char *)malloc(80);
  int total = 80;
  int i = 0;
  char c;
  fp = fopen(dictName, "r");
  if (fp == NULL) {
    fprintf(stderr, "Can't find the dictionary file.");
    exit(1);
  }

  while ((c = fgetc(fp)) != EOF) {
    // 遇到换行符
    if (c == '\n') {
      char *key = (char *)malloc((i + 1) * sizeof(char));
      memcpy(key, word, i);
      key[i] = '\0';
      if (findData(dictionary, key) == NULL) {
        insertData(dictionary, key, key);
      }
      i = 0;
      continue;
    }
    //word内存满了
    if (i == total) {
      word = (char *)realloc(word, total *= 2);
    }
    word[i] = c;
    i += 1;
  }
  free(word);
  fclose(fp);
}

/*
 * This should process standard input (stdin) and copy it to standard
 * output (stdout) as specified in the spec (e.g., if a standard 
 * dictionary was used and the string "this is a taest of  this-proGram" 
 * was given to stdin, the output to stdout should be 
 * "this is a teast [sic] of  this-proGram").  All words should be checked
 * against the dictionary as they are input, then with all but the first
 * letter converted to lowercase, and finally with all letters converted
 * to lowercase.  Only if all 3 cases are not in the dictionary should it
 * be reported as not found by appending " [sic]" after the error.
 *
 * Since we care about preserving whitespace and pass through all non alphabet
 * characters untouched, scanf() is probably insufficent (since it only considers
 * whitespace as breaking strings), meaning you will probably have
 * to get characters from stdin one at a time.
 *
 * Do note that even under the initial assumption that no word is longer than 60
 * characters, you may still encounter strings of non-alphabetic characters (e.g.,
 * numbers and punctuation) which are longer than 60 characters. Again, for the 
 * final 20% of your grade, you cannot assume words have a bounded length.
 */
 /*
 这应该处理标准输入（stdin）并将其复制到规范中指定的标准输出（stdout）（例如，如果使用
 标准字典并且将字符串“this is a taest of this-proGram”提供给 stdin，则 stdout 的输出
 应该是“this is a teast [sic] of this-proGram”）。 所有单词在输入时都应根据字典进行检查
 ，然后将除第一个字母以外的所有字母都转换为小写，最后将所有字母转换为小写。 只有当所有 3 
 个案例都不在字典中时，才应该通过在错误后附加“[sic]”来报告未找到。 由于我们关心保留空格并
 原封不动地传递所有非字母字符，因此 scanf() 可能是不够的（因为它只将空格视为中断字符串），
 这意味着您可能必须一次从 stdin 获取一个字符。 请注意，即使在最初假设没有单词超过 60 个字符
 的情况下，您仍然可能会遇到超过 60 个字符的非字母字符字符串（例如，数字和标点符号）。 同样，
 对于你成绩的最后 20%，你不能假设单词的长度是有限的。
 */
void processInput() {
  // -- TODO --
  int total = 80;
  char *str1 = (char *)malloc(sizeof(char) * total);
  char *str2 = (char *)malloc(sizeof(char) * total);
  char *str3 = (char *)malloc(sizeof(char) * total);
  int i = 0;
  int c = 0;
  while ((c = fgetc(stdin)) != EOF) {
    //内存满了
    if (i == total) {
      str1 = (char *)realloc(str1, total *= 2);
      str2 = (char *)realloc(str2, total *= 2);
      str3 = (char *)realloc(str3, total *= 2);
    }
    //读到的为字母
    if (isalpha(c) != 0) {
      //1.原字符
      str1[i] = (char)c;
      //2.全为小写的字符
      str2[i] = (char)tolower(c);
      //3.开头不一定小写
      str3[i] = (i == 0) ? c : (char)tolower(c);
      i += 1;
    }
    //读到的为非字母
    else {
      //之前有单词
      if (isalpha(str1[0])) {
        str1[0] = '\0';
        str2[0] = '\0';
        str3[0] = '\0';
        //检查是否在字典里出现
        if (findData(dictionary, str1) == NULL && findData(dictionary, str2) == NULL && findData(dictionary, str3) == NULL) {
          fprintf(stdout, "%s [sic]%c", str1, c);
        }
        else {
          fprintf(stdout, "%s%c", str1, c);
        }
      }
      //之前没有单词
      else {
        fprintf(stdout, "%c", c);
      }
      i = 0;
      memset(str1, 0, strlen(str1));
      memset(str2, 0, strlen(str2));
      memset(str3, 0, strlen(str3));
    }
  }
  free(str1);
  free(str2);
  free(str3);
}
