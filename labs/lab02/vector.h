#ifndef CS61C_VECTOR_H_
#define CS61C_VECTOR_H_
/* vector.h originally written by Jeremy Huddleston <jeremyhu@eecs.berkeley.edu> Sp2004
 *
 * So it looks like you've decided to venture into the "other" files of this
 * lab.  Good.  C Header files (the .h extension) are a way of telling other .c
 * files what they can have access to.  You usually include stdlib.h in your
 * C programs, and this process is identical to including this .h file with the
 * one change being:
 *
 * #include "file.h"
 * versus
 * #include <file.h>
 *
 * The difference is that the <> notation is for system header files and the ""
 * is for ones you provide yourself (in your local directory for instance).
 *
 * The header file starts off with
 * #ifndef CS61C_VECTOR_H_
 * #define CS61C_VECTOR_H_
 *
 * and ends with a final #endif.  This prevents the file from being included
 * more than once which could've possibly resulted in an infinite loop of
 * file inclusions.
 *
 * First, we define the 'vector_t' datatype.  This next line says that a 'vector_t'
 * is the same as a 'struct vector_t'.  So anywhere in the code after this, we
 * can use 'vector_t *' to mean a pointer to a 'struct vector_t' (which is defined in
 * vector.c).  We can get away with doing this even though we don't know what a
 * struct vector is because all struct pointers have the same representation in memory.
 */
 /*
 vector.h 最初由 Jeremy Huddleston<jeremyhu@eecs.berkeley.edu> Sp2004 编写
所以看起来你已经决定冒险进入这个实验室的“其他”文件。 好的。 C 头文件（.h 扩展名）是一种告诉其他
 .c 文件它们可以访问什么的方式。 您通常在 C 程序中包含 stdlib.h，此过程与包含此 .h 文件相同，
 唯一的变化是：
  #include "file.h"
 versus
  #include <file.h>
  不同之处在于 <> 符号用于系统头文件，而 用于您自己提供的文件（例如在您的本地目录中）。
  头文件以
   #ifndef CS61C_VECTOR_H_
 * #define CS61C_VECTOR_H_
   开头
   并以最后的#endif 结尾。 这可以防止文件被多次包含，这可能会导致文件包含的无限循环。
   首先，我们定义“vector_t”数据类型。 下一行表示“vector_t”与“struct vector_t”相同。
    因此，在此之后的代码中的任何地方，我们都可以使用“vector_t *”来表示指向“struct vector_t”
    （在 vector.c 中定义）的指针。 即使我们不知道结构向量是什么，我们也可以这样做，
    因为所有结构指针在内存中都具有相同的表示形式。
 */

#include <sys/types.h>

typedef struct vector_t vector_t;

/*
 *  Next, we provide the prototypes for the functions defined in vector.c.  This
 *  is a way of telling the .c files that #include this header what they will
 *  have access to.
 */
 /*
 接下来，我们为 vector.c 中定义的函数提供原型。 这是一种告诉 .c 文件
 #include this header 他们将有权访问的内容的方法。
 */
/* Create a new vector */
vector_t *vector_new();

/* Free up the memory allocated for the passed vector */
/* 释放为传递的向量分配的内存 */
/* YOUR CODE HERE */
void vector_delete(vector_t *v);

/* Return the value in the vector */
int vector_get(vector_t *v, size_t loc);

/* Set a value in the vector */
/* YOUR CODE HERE */
void vector_set(vector_t *v, size_t loc, int value);

#endif
