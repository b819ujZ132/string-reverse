#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <byteswap.h>
#include <time.h>

//#define DEBUG

static inline void reverse(char *s, int l)
{
	static_assert(1 == sizeof(char), "'char' is an invalid size.");
	static_assert(2 == sizeof(uint16_t), "'uint16_t' is an invalid size.");
	static_assert(4 == sizeof(uint32_t), "'uint32_t' is an invalid size.");
	static_assert(8 == sizeof(uint64_t), "'uint64_t' is an invalid size.");

	if (0 == l || 1 == l)
		return;

	if (31 >= l)
	{
		char *f = s;
		char *b = s + l - 1;
		
		char tmp;
		while (f < b)
		{
			tmp = *f;
			*f = *b;
			*b = tmp;

			++f;
			--b;
		}

		return;
	}

	int mod = l % 8;

	if (0 != mod)
	{
		char* f	= s;
		char* b	= s + l - 1;

		char tmp;
		for (int i = 0; i < mod; ++i)
		{
			tmp = *f;
			*f = *b;
			*b = tmp;

			++f;
			--b;
		}
	}

	uint64_t *front = (uint64_t *)(s + mod);
	uint64_t *back = (uint64_t *)(s + l - mod) - 1;
	uint64_t tmp;
	while (front < back)
	{
		tmp = *front;
		*front = bswap_64(*back);
		*back = bswap_64(tmp);

		++front;
		--back;	
	}

	if (front == back)
	{
		*front = bswap_64(*front);
	}

	return;

	/*
	if (2 == l)
	{
		uint16_t *i = (uint16_t *)s;
		*((uint16_t*)s) = bswap_16(*(uint16_t*)s);
		return;
	}
	
	if (3 == l)
	{
		char t = *s;
		*s = *(s + 2);
		*(s + 2) = t;	
	}

	if (4 == l)
	{
		*((uint32_t*)s) = bswap_32(*(uint32_t*)s);
		return;
	}

	if (5 == l)
	{
		uint16_t t = *((uint16_t*)s);
		*((uint16_t*)s) = bswap_16(*(uint16_t*)(s + sizeof(uint16_t) + sizeof(char)));
		*((uint16_t*)(s + sizeof(uint16_t) + sizeof(char))) = bswap_16(t);
		
	}

	if (6 == l)
	{
		uint32_t t = *((uint32_t*)s);
		*((uint16_t*)s) = bswap_16(*(uint16_t*)(s + sizeof(uint32_t)));
		*((uint32_t*)(s + sizeof(uint16_t))) = bswap_32(t);
	}
	
	if (7 == l)
	{
		uint16_t t1 = *((uint16_t*)s);
		*((uint16_t*)s) = bswap_16(*(uint16_t*)(s + sizeof(uint16_t) + sizeof(char) + sizeof(char) + sizeof(char)));
		char t2 = *(s + sizeof(uint16_t));
		*(s + sizeof(uint16_t)) = *(s + sizeof(uint16_t) + sizeof(char) + sizeof(char));
		*(s + sizeof(uint16_t) + sizeof(char) + sizeof(char)) = t2;
		*((uint16_t*)(s + sizeof(uint16_t) + sizeof(char) + sizeof(char) + sizeof(char))) = bswap_16(t1);
	}

	if (8 == l)
	{
		*((uint64_t*)s) = bswap_64(*((uint64_t*)s));
		return;
	}

	if (9 == l)
	{
		uint64_t t = *((uint64_t*)s);
		*s = *(s + sizeof(uint64_t));
		*((uint64_t*)(s + sizeof(char))) = bswap_64(t);
	}

	if (10 == l)
	{
		uint64_t t = *((uint64_t*)s);
		*((uint16_t*)s) = bswap_16(*(uint16_t*)(s + sizeof(uint64_t)));
		*((uint64_t*)(s + sizeof(uint16_t))) = bswap_64(t);
	}

	if (11 == l)
	{
		uint64_t t = *((uint64_t*)s);
		*((uint16_t*)s) = bswap_16(*(uint16_t*)(s + sizeof(uint64_t) + sizeof(char)));
		*(s + sizeof(uint16_t)) = *(s + sizeof(uint64_t));
		*((uint64_t*)(s + sizeof(uint16_t) + sizeof(char))) = bswap_64(t);
	}

	if (12 == l)
	{
		uint64_t t = *((uint64_t*)s);
		*((uint32_t*)s) = bswap_32(*(uint32_t*)(s + sizeof(uint64_t)));
		*((uint64_t*)(s + sizeof(uint32_t))) = bswap_64(t);
	}

	if (13 == l)
	{
		uint64_t t = *((uint64_t*)s);
		*((uint32_t*)(s + sizeof(char))) = bswap_32(*(uint32_t*)(s + sizeof(uint64_t)));
		*s = *(s + sizeof(uint64_t) + sizeof(uint32_t));
		*((uint64_t*)(s + sizeof(char) + sizeof(uint32_t))) = bswap_64(t);
	}

	if (14 == l)
	{
		uint64_t t = *((uint64_t*)s);
		*((uint32_t*)(s + sizeof(uint16_t))) = bswap_32(*(uint32_t*)(s + sizeof(uint64_t)));
		*((uint16_t*)s) = bswap_16(*(uint16_t*)(s + sizeof(uint64_t) + sizeof(uint32_t)));
		*((uint64_t*)(s + sizeof(uint16_t) + sizeof(uint32_t))) = bswap_64(t);
	}

	if (15 == l)
	{
		uint64_t t = *((uint64_t*)s);
		*s = *(s + sizeof(uint64_t) + sizeof(uint32_t) + sizeof(uint16_t));
		*((uint32_t*)(s + sizeof(char) + sizeof(uint16_t))) = bswap_32(*(uint32_t*)(s + sizeof(uint64_t)));
		*((uint16_t*)(s + sizeof(char))) = bswap_16(*(uint16_t*)(s + sizeof(uint64_t) + sizeof(uint32_t)));
		*((uint64_t*)(s + sizeof(char) + sizeof(uint16_t) + sizeof(uint32_t))) = bswap_64(t);
	}
	}

	uint64_t *front = (uint64_t*)s;
	uint64_t *back = (uint64_t*)(s + l - sizeof(uint64_t));
	
	
	int mod = l % 16;
	if (0 == mod)
	{
		while (front < back)
		{
			uint64_t tmp = *front;
			*front = bswap_64(*back);
			*back = bswap_64(tmp);
			++front;
			--back;
		}
		return;
	}
	else if (8 == mod)
	{
		while (front < back)
		{
			uint64_t tmp = *front;
			*front = bswap_64(*back);
			*back = bswap_64(tmp);
			++front;
			--back;
		}

  	*front = bswap_64(*front);
		return;
	}	

	if (0 == l % 16)
	{
		back = front + (l / 8) - 1;
		while (front < back)
		{
			uint64_t tmp = *front;
			*front = bswap_64(*back);
			*back = bswap_64(tmp);
			++front;
			--back;
		}
	}
	else if (0 == l % 8)
	{
		back = front + (l / 8) - 1;
		while (front < back - 1)
		{
			uint64_t tmp = *front;
			*front = bswap_64(*back);
			*back = bswap_64(tmp);
			++front;
			--back;
		}

		*front = bswap_64(*front);
	}
	*/
}

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		printf("\n%s\n\n", argv[i]);

		struct timespec startTime, endTime;

		int n = 10001;
		unsigned long long total = 0L;
		for (int j = 0; j < n; ++j)
		{
			clock_gettime(CLOCK_REALTIME, &startTime);

			reverse(argv[i], strlen(argv[i]));	

			clock_gettime(CLOCK_REALTIME, &endTime);

			total += endTime.tv_nsec - startTime.tv_nsec;

#ifdef DEBUG
			printf("%s\n\n", argv[i]);
			printf("Execution time in nanoseconds: %ld\n", endTime.tv_nsec - startTime.tv_nsec);
#endif
		}
		printf("\n%s\n\n", argv[i]);
		printf("Total time in nanoseconds: %ld\n", total);
		printf("Average time in nanoseconds: %f\n", total / (double)n);
	}

	return 0;
}
