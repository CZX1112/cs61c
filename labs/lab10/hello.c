#include <stdio.h>
#include <omp.h>

int main() {
	// 默认线程数为8，可以通过omp_set_num_threads修改线程数
	// omp_set_num_threads(20);
	#pragma omp parallel
	{
		int thread_ID = omp_get_thread_num();
		printf(" hello world %d\n", thread_ID);
	}
}
