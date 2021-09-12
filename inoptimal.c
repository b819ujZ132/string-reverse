#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define DEBUG

int main(int argc, char *argv[])
{
	if (2 > argc)
	{
		printf("Missing arguments.\n");
		exit(1);
	}

	for (int i = 1; i < argc; ++i)
	{
		printf("\n%s\n\n", argv[i]);

		struct timespec startTime, endTime;
		
		int n = 10001;
		unsigned long long total = 0L;
		for (int j = 0; j < n; ++j)
		{
			clock_gettime(CLOCK_REALTIME, &startTime);

			char *start = argv[i];
			char *end = start + strlen(start) - 1;	

			char c;
			while (start < end)
			{
				c = *start;
				*start = *end;
				*end = c;

				++start;
				--end;
			}

			clock_gettime(CLOCK_REALTIME, &endTime);

			start = argv[i];

			total += endTime.tv_nsec - startTime.tv_nsec;

#ifdef DEBUG
			printf("%s\n\n", start);
			printf("Execution time in nanoseconds: %ld\n", endTime.tv_nsec - startTime.tv_nsec);
#endif
		}
		printf("\n%s\n\n", argv[i]);
		printf("Total time in nanoseconds: %ld\n", total);
		printf("Average time in nanoseconds: %f\n", total / (double)n);
	}

	return 0;
}
