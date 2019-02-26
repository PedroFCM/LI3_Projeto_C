#include <stdio.h>
#include <time.h>

int main (int argc,  const char* argv[]) {
	
	clock_t start, end;
	double cpu_time_used;
	
	start = clock();
	
	main();
	
	end = clock();
	
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	
	printf("CPU Time:%f\n", cpu_time_used );
	
	return 0;
}