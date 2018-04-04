#include <stdio.h>
#include <string.h>

struct Code{
	struct	Code *parent;
	struct	Code *gauche;
	struct	Code *droit;
	char	caractere;
	int		nb_occurences;
	int		code;
};

void	initialiseCode(struct Code *element)
{
	element->parent = 0;
	element->gauche = 0;
	element->droit = 0;
	element->nb_occurences = 0;
}

void	initialiseArbre(struct Code code[256])
{
	int i = 0;

	while (i < 256)
	{
		initialiseCode(&code[i]);
		code[i].caractere = i;
		i++;
	}
}

void	compteOccurences(char *chaine, struct Code code[])
{
	int i = 0, k;

	do {
		k = chaine[i];
		code[k].nb_occurences++;
		i++;
	} while (chaine[i]);
}

int		get2Min(struct Code code[], int taille, int *min_index1, int *min_index2)
{
	int i = 0, m1 = 0, m2 = 0, k;

	*min_index1 = 0;
	*min_index2 = 0;
	if (code[0].nb_occurences != 0)
		m1 = 1;
	while (i < taille)
	{
		if ((k = code[i].nb_occurences) > 0)
		{
			if (m1 == 0)
			{
				*min_index1 = i;
				m1 = 1;
			}
			else if (m2 == 0)
			{
				*min_index2 = i;
				m2 = 1;
			}
			else
			{
				if (k < code[*min_index1].nb_occurences || k < code[*min_index2].nb_occurences)
				{
					if (code[*min_index1].nb_occurences <= code[*min_index2].nb_occurences)
						*min_index2 = i;
					else
						*min_index1 = i;
				}
			}
		}
		i++;
	}
	if (m1 == 1 && m2 == 1)
		return (1);
	return (0);
}

int creeArbre(char chaine[], struct Code code[512])
{
	int taille = 256, index_elt1 = 0, index_elt2 = 0;
	initialiseArbre(code);
	compteOccurences(chaine, code);
	while (get2Min(code, taille, &index_elt1, &index_elt2) == 1)
	{
		initialiseCode(&code[taille]);
		code[taille].gauche = &code[index_elt1];
		code[taille].droit = &code[index_elt2];
		code[taille].nb_occurences = code[index_elt1].nb_occurences + code[index_elt2].nb_occurences;
		code[index_elt1].parent = &code[taille];
		code[index_elt2].parent = &code[taille];
		code[index_elt1].nb_occurences = 0;
		code[index_elt2].nb_occurences = 0;
		code[index_elt1].code = 0;
		code[index_elt2].code = 1;
		taille += 1;
	}
	return (taille);
}

int encode_char(char car, struct Code arbre[], char output[])
{
	struct Code *ptr_code;
	int i = 0, j = 0, k = 0;
	char s1[2000];

	while (arbre[i].caractere != car)
		i++;
	ptr_code = &arbre[i];
	printf("%c\n", ptr_code->caractere);
	while (ptr_code->parent)
	{
		s1[j] = ptr_code->code + 48;
		j++;
		ptr_code = ptr_code->parent;
	}
	s1[j] = '\0';
	while (j > 0)
	{
		output[k] = s1[j - 1];
		j--;
		k++;
	}
	output[k] = '\0';
	return (k);
}

int encode (char chaine_entree[], struct Code arbre[], char chaine_sortie[])
{
	int i = 0;
	char output[1000];

	do{
		encode_char(chaine_entree[i], arbre, output);
		chaine_sortie = strcat(chaine_sortie, output);
		i++;
	} while (chaine_entree[i]);
	return (strlen(chaine_sortie));
}



void	decode(char chaine_entree[], struct Code arbre[], int taille_arbre, char chaine_sortie[])
{
	int i = 0, j = 0;
	struct Code *ptr;

	while (chaine_entree[i]){
		ptr = &arbre[taille_arbre - 1];
		while (ptr->droit)
		{
			if (chaine_entree[i] == '1')
				ptr = ptr->droit;
			else
				ptr = ptr->gauche;
			i++;
		}
		chaine_sortie[j] = ptr->caractere;
		j++;
	}
}

int main()
{
	int taille_arbre, i = 0;
	struct Code code[512];
	char chaine_entree[1000] = "Je suis a la mer dude!";
	char chaine_codee[1000];
	char chaine_sortie[1000];

	while (i < 1000)
	{
		chaine_codee[i] = 0;
		chaine_sortie[i] = 0;
		i++;
	}
	taille_arbre = creeArbre(chaine_entree, code);
	printf("%s\n", chaine_entree);
	encode(chaine_entree, code, chaine_codee);
	printf("%s\n", chaine_codee);
	decode(chaine_codee, code, taille_arbre, chaine_sortie);
	printf("%s\n", chaine_sortie);
	return (0);
}


