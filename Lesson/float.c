#include <stdio.h>
#include <stdbool.h>

int main()
{
	float count = 0.0;
	while(count < 100000000)
	{
		printf("%f\n",count);
		count += 1.0;
	}
	return 0;
}
