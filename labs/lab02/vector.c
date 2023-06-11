/* Include the system headers we need */
#include <stdlib.h>
#include <stdio.h>

/* Include our header */
#include "vector.h"

/* Define what our struct is */
struct vector_t {
    size_t size;
    int *data;
};

/* Utility function to handle allocation failures. In this
   case we print a message and exit. */
/*处理分配失败的效用函数。 在这种情况下，我们打印一条消息并退出。*/
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

/* Bad example of how to create a new vector */
/*如何创建新向量的错误示例*/
vector_t *bad_vector_new() {
    /* Create the vector and a pointer to it */
    vector_t *retval, v;
    retval = &v;

    /* Initialize attributes */
    retval->size = 1;
    retval->data = malloc(sizeof(int));
    if (retval->data == NULL) {
        allocation_failed();
    }

    retval->data[0] = 0;
    return retval;
}

/* Another suboptimal way of creating a vector */
/* 另一种创建向量的次优方法 */
vector_t also_bad_vector_new() {
    /* Create the vector */
    vector_t v;

    /* Initialize attributes */
    v.size = 1;
    v.data = malloc(sizeof(int));
    if (v.data == NULL) {
        allocation_failed();
    }
    v.data[0] = 0;
    return v;
}

/* Create a new vector with a size (length) of 1
   and set its single component to zero... the
   RIGHT WAY */
/* 创建一个大小（长度）为 1 的新向量并将其单个分量设置为零
......正确的方法 */
vector_t *vector_new() {
    /* Declare what this function will return */
    /* 声明此函数将返回什么 */
    vector_t *retval;

    /* First, we need to allocate memory on the heap for the struct */
    /* First, we need to allocate memory on the heap for the struct */
    retval = /* YOUR CODE HERE */

    /* Check our return value to make sure we got memory */
    /* 检查我们的返回值以确保我们有内存 */
    if (/* YOUR CODE HERE */) {
        allocation_failed();
    }

    /* Now we need to initialize our data.
       Since retval->data should be able to dynamically grow,
       what do you need to do? */
    /* 现在我们需要初始化我们的数据。 既然 retval->data 应该是
    可以动态增长的，那么需要做什么呢？ */
    retval->size = /* YOUR CODE HERE */;
    retval->data = /* YOUR CODE HERE */;

    /* Check the data attribute of our vector to make sure we got memory */
    /* 检查我们向量的数据属性以确保我们有内存 */
    if (/* YOUR CODE HERE */) {
        free(retval);				//Why is this line necessary?
        allocation_failed();
    }

    /* Complete the initialization by setting the single component to zero */
    /* 通过将单个组件置零来完成初始化 */
    /* YOUR CODE HERE */ = 0;

    /* and return... */
    return retval;
}

/* Return the value at the specified location/component "loc" of the vector */
/* 返回向量的指定位置/组件“loc”处的值 */
int vector_get(vector_t *v, size_t loc) {

    /* If we are passed a NULL pointer for our vector, complain about it and exit. */
    /* 如果我们的 vector 传递了一个 NULL 指针，抱怨它并退出。 */
    if(v == NULL) {
        fprintf(stderr, "vector_get: passed a NULL vector.\n");
        abort();
    }

    /* If the requested location is higher than we have allocated, return 0.
     * Otherwise, return what is in the passed location.
     */
    /* 如果请求的位置高于我们分配的位置，则返回 0。否则，返回传递位置中的内容。 */
    if (loc < /* YOUR CODE HERE */) {
        return /* YOUR CODE HERE */;
    } else {
        return 0;
    }
}

/* Free up the memory allocated for the passed vector.
   Remember, you need to free up ALL the memory that was allocated. */
/* 释放为传递的向量分配的内存。请记住，您需要释放所有分配的内存。 */
void vector_delete(vector_t *v) {
    /* YOUR SOLUTION HERE */
}

/* Set a value in the vector. If the extra memory allocation fails, call
   allocation_failed(). */
/* 在向量中设置一个值。 如果额外内存分配失败，调用allocation_failed()。 */
void vector_set(vector_t *v, size_t loc, int value) {
    /* What do you need to do if the location is greater than the size we have
     * allocated?  Remember that unset locations should contain a value of 0.
     */
    /* 如果位置大于我们分配的大小，您需要做什么？ 请记住，未设置的位置应包含值 0。 */

    /* YOUR SOLUTION HERE */
}