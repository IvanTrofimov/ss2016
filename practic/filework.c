#include "filework.h"

int CountLines(FILE *list)
{
	int count = 1;
	char letter = 0;
	while(letter != EOF)
	{
		if ((letter = getc(list)) == '\n') 
		{
			if ((letter = getc(list)) != EOF) count++;
		}
	}
	fseek(list, 0, SEEK_SET);
	return count;
}
int GetGit(struct for_in *str1)
{
	int j = 0;
	char letter;
	if ((letter = getc(str1 -> list)) < 0) return -1;
	while (((letter >= 'A')&&(letter <= 'Z'))||((letter >= 'a')&&(letter <= 'z'))) 
	{
		str1 -> f_name[j] = letter;
		j++;
		letter = getc(str1 -> list);
	}
	str1 -> f_name[j] = '\0';
	j = 0;
	if (letter == ' ')
	{
		while (((letter = getc(str1 -> list)) != ';')&&(letter != ' '))
		{
			str1 -> m_name[j] = letter;
			j++;
		}
		str1 -> m_name[j] = '\0';
		j = 0;
		if (letter == ' ')
		{
			while (((letter = getc(str1 -> list)) != ';')&&(letter != ' '))
			{
				str1 -> l_name[j] = letter;
				j++;
			}
			str1 -> l_name[j] = '\0';
			j = 0;
		}
	}
	while ((letter = getc(str1 -> list)) != ';')
	{
		if (letter != ' ')
		{
			str1 -> group[j] = letter;
			j++;
		}
	}
	str1 -> group[j] = '\0';
	j = 0;
	while (((letter = getc(str1 -> list)) != '\n')&&(letter != ';')&&(letter > 0))
	{
		if (letter != ' ')
		{
			str1 -> github[j] = letter;
			j++;
		}
	}
	str1 -> github[j] = '\0';
	j = 0;
	if (letter == ';')
	{
		if (letter == ' ') letter = getc(str1 -> list);
		while (((letter = getc(str1 -> list)) != '\n')&&(letter > 0))
		{
			str1 -> git_folder[j] = letter;
			j++;
		}
		str1 -> git_folder[j] = '\0';
	}
	if (letter < 0) return -1;
	else return 0;
}
void GroupDir(char *group, char *name)
{
	mkdir(group, 0777);
	chdir(group);
	mkdir(name, 0777);
	chdir(name);
}
