#include "utill.h"

int atoh(int8_t *s)
{
	int step = 1, tmp = 0, str_len, i;

	str_len = strlen((char *)s)-1;

	for (i=str_len; i>=0; i--)
	{
		if (s[i] <= 0x39)
			tmp += ((s[i]-0x30) *step);
		else if ((0x61<=s[i]) && (s[i]<=0x66))
			tmp += ((s[i]-0x57)*step);
		else if ((0x41<=s[i]) && (s[i]<=0x46))
			tmp += ((s[i]-0x37)*step);
		else
			tmp = 0;

		step *= 16;
	}

	return tmp;

}
