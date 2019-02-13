#include "includes/shell42.h"

int main(void)
{
	int *s;
	int i = 0;
	unsigned long buf;

	while (read(0, &buf, 8))
	{
		s[i++] = buf;
		printf("read-> %lu\n",buf );
	}
	return 0;
}