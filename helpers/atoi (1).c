#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



int check_for_digits_only(char s[])
{
	int i=0;

	while (s[i])
	{
		if (isdigit(s[i]))
			i++;
		else
			return 0;
	}
	return 1;
}

int main()
{
	/* safe reading of an integer */
	int i;
	char line[100];

	/* scanf is problematic - maybe a non-digit character appears accidently (?) */
	gets(line);

	if (check_for_digits_only(line))
	{
		//i = atoi(line); alternative
		sscanf(line,"%d",&i);
		printf ("%d\n",i);
	}
	else
		printf ("Error in input\n");
}


