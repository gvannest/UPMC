#include <stdio.h>
#include <stdlib.h>

void	ecarts(int tab[], int taille, int *e_min, int *e_max)
{
	int i = 0, j, k;

	*e_min = abs(tab[1] - tab[0]);
	*e_max = *e_min;
	while (i < taille)
	{
		j = i + 1;
		while (j < taille)
		{
			k = abs(tab[j] - tab[i]);
			if (k < *e_min)
				*e_min = k;
			if (k > *e_max)
				*e_max = k;
			j++;
		}
		i++;
	}
}



int	main()
{
	int tab[8] = {1,1,1,1,1,1,1,1};
	int a = 0;
	int b = 0;
	
	ecarts(tab, 8, &a, &b);
	printf("%d %d\n", a, b);
	return (0);
}
