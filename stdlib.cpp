#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <bits/stdc++.h>
#include <iostream>

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
		std::string s = std::string(argv[i]);
		for (int j = 0; j < n; ++j)
		{	
			clock_gettime(CLOCK_REALTIME, &startTime);

			std::reverse(s.begin(), s.end());

			clock_gettime(CLOCK_REALTIME, &endTime);

			total += endTime.tv_nsec - startTime.tv_nsec;

#ifdef DEBUG
			std::cout << s << std::endl;
			printf("Execution time in nanoseconds: %ld\n", endTime.tv_nsec - startTime.tv_nsec);
#endif
		}
		
		std::cout << s << std::endl << std::endl;
		printf("Total time in nanoseconds: %ld\n", total);
		printf("Average time in nanoseconds: %f\n", total / (double)n);
	}

	return 0;
}
