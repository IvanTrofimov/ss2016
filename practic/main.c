#include "filework.h"
#include "git.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
	char path[30], pathnew[30];
	FILE *fp;
	getcwd(path, 30);
	int count, i, check = 0;
	if (argc == 1)
	{
		printf("You didn't enter the path to a list of students, try again\n");
		exit(1);
	}
	char *way = argv[1];
	int timeout;
	if (argc == 3) timeout = str_to_int(argv[2]);
	else timeout = 20;
	struct for_in str1;
	str1.list = fopen(way, "r");	
	if (str1.list == NULL)
	{
		printf("error\n");
		exit(1);
	}
	FILE *new_f = fopen("statistic.txt", "w");
	if (new_f == NULL)
	{
		printf("error\n");
		exit(1);
	}
	while (check == 0)
	{
		str1.f_name[0] = '\0';
		str1.m_name[0] = '\0';
		str1.l_name[0] = '\0';
		str1.group[0] = '\0';
		str1.github[0] = '\0';
		str1.git_folder[0] = '\0';
		check = GetGit(&str1);
		if (check == 0)
		{
			fprintf(new_f, "%s:   %s %s %s   ", str1.group, str1.f_name, str1.m_name, str1.l_name);
			GroupDir(str1.group, path);
			print_make_result(new_f, str1.github,timeout,str1.git_folder);
			fprintf(new_f, "\n");
			chdir(path);
		}
	}
	fclose(new_f);
	fclose(str1.list);
	return 0;
}
