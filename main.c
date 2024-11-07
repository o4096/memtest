#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

enum UnitList
{
	UNIT_BYTE=1<<0,
	UNIT_KILO=1<<1,
	UNIT_MEGA=1<<2,
	UNIT_GIGA=1<<3,
};

void print_usage()
{
	printf(
		"Usage: memtest [options] <bytes>\n"
		"Options:\n"
		"  -K            Specify allocated amount in KBs\n"
		"  -M            Specify allocated amount in MBs\n"
		"  -G            Specify allocated amount in GBs\n"
		"  -h, --help    Show this help message\n"
		"  -v, --version Show version\n"
	);
}
void pause()
{
	int i=1;
	printf("Enter 0 to continue: ");
	while(i!=0)
		scanf("%d", &i);
}
int main(int argc, char **argv)
{
	size_t bytes= -1;
	int32_t unit= UNIT_BYTE;
	uint8_t *p= NULL;

	for(int i=1;i<argc;i++)
	{
		if(!strcmp(argv[i], "-h")||!strcmp(argv[i], "--help"))
		{
			print_usage();
			pause();
			return 0;
		}
		else if(!strcmp(argv[i], "-K"))
		{
			unit= UNIT_KILO;
		}
		else if(!strcmp(argv[i], "-M"))
		{
			unit= UNIT_MEGA;
		}
		else if(!strcmp(argv[i], "-G"))
		{
			unit= UNIT_GIGA;
		}
		else
		{
			sscanf(argv[i], "%zu", &bytes);
			if(bytes>(34359738368ull))//32GBs limit
			{
				printf("WARNING: trying to allocate %zu bytes!\n", bytes);
				print_usage();
				pause();
				return 0;
			}
		}
	}
	if(unit&UNIT_KILO)
		bytes*= 1024;
	if(unit&UNIT_MEGA)
		bytes*= 1048576;//1024^2
	if(unit&UNIT_GIGA)
		bytes*= 1073741824;//1024^3
	if(bytes==-1||!bytes)
	{
		print_usage();
		pause();
		return 0;
	}
	p= malloc(bytes*sizeof(uint8_t));
	if(!p)
	{
		printf("FAILURE to allocate %zu bytes!\n", bytes);
	}
	else//fill with random data
	{
		size_t i = 0;
		uint64_t *p64= (uint64_t*)p;
		uint32_t *p32= (uint32_t*)p;
		uint16_t *p16= (uint16_t*)p;
		uint8_t  *p8=  (uint8_t *)p;

		printf("Allocating %zu bytes...\n", bytes);
		
		if(bytes>=sizeof(uint64_t) && !((uintptr_t)p%sizeof(uint64_t)))
		{//Fill with 64-bit integers if possible
			for(;i+sizeof(uint64_t)<=bytes;i+=sizeof(uint64_t))
				*p64++= (uint64_t)rand();
		}
		if(bytes>=sizeof(uint32_t) && !((uintptr_t)p%sizeof(uint32_t)))
		{//Fill with 32-bit integers if possible
			for(;i+sizeof(uint32_t)<=bytes;i+=sizeof(uint32_t))
				*p32++= (uint32_t)rand();
		}
		if(bytes>=sizeof(uint16_t) && !((uintptr_t)p % sizeof(uint16_t)))
		{//Fill with 16-bit integers if possible
			for(;i+sizeof(uint16_t)<=bytes;i+=sizeof(uint16_t))
				*p16++= (uint16_t)rand();
		}
		//Fill remaining bytes with 8-bit integers
		for(;i<bytes;i++)
			p8[i]= (uint8_t)rand();

		// printf("%d\n", (int*)(p+rand()%bytes));
		printf("Successfully allocated %zu bytes...\n", bytes);
	}
	pause();
	free(p);
	return 0;
}
