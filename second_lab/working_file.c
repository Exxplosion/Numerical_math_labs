#include "working_file.h"



char* read_file_in_array()
{

	int lenght_file = 0;
	char *text = NULL;
	FILE *fp = NULL;
	fp = fopen("Values_x_y.txt", "r");

	if (fp == NULL)
	{
		perror("Can't open file");
		printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHH!");
		return NULL;
	}

	/* formation of source text in text[] */
	fseek(fp, 0, SEEK_END);

	if ((lenght_file = ftell(fp)) == -1L)
	{
		perror("ftell err");
		return NULL;
	}

	fseek(fp, 0, SEEK_SET);

	text = (char *)calloc(lenght_file + 1, sizeof(char));

	if (text == NULL)
	{
		perror("nope memory");
		return  NULL;	
	}

	long int read_b = fread(text, sizeof(char), lenght_file, fp);

	while (read_b != lenght_file)
	{
		read_b += fread(text, sizeof(char), lenght_file, fp);
	}

	//printf("hi!");
	//printf("%s\n", text);
	//init_array = text;
	fclose(fp);
	return text;
}


	/* formation array pointers to start of lines text */

lines* start_of_lines(char* text, int* count_lines)
{
	lines *line = NULL;
	lines *supp = NULL; //промежуточный указатель
	int n = SIZE_INCREMENT; //initial size array
	line = (lines *) calloc(SIZE_INCREMENT, sizeof(lines));

	if (line == NULL)
	{
		perror("nope memory");
		return  NULL;
	}

	char *s = text;
	char *s_next = strchr(s, '\n'); //next pointer after word

	int i = 0;
	line[i].len_line = s_next - s;
	line[i].lineptr = s;
	line[i].lineptr[line[i].len_line] = '\0';
	i++;
	s = s_next;
	if ((s_next = strchr(s + 1, '\n')) == NULL)
	{
		perror("nope strings");
		return NULL;
	}

	while (s_next != NULL)
	{
		line[i].len_line = s_next - s - 1;
		line[i].lineptr = s + 1;
		line[i].lineptr[line[i].len_line] = '\0';
		s = s_next;
		s_next = strchr(s+1, '\n'); 
		i++;
		if (i == n)
		{
			n += SIZE_INCREMENT;
			supp = (lines *) realloc(line, n * sizeof(lines));
			if (supp == NULL)
			{
				perror("nope memory");
				return  NULL;
			}
			line = supp;
		}
	}

	supp = (lines *) realloc(line, i * sizeof(lines));

	if (supp == NULL)
	{
		perror("nope memory");
		return NULL;
	}

	line = supp;
	
	*count_lines = i; //всего строк

	return line;
}

void begin_tex(FILE* out)
{
	fprintf(out, "\\documentclass[12pt]{article}\n"
				 "\\usepackage[utf8]{inputenc}\n"
				 "\\usepackage{amsmath, amssymb, mathtools}\n"
				 "\\usepackage[left = 20mm, bottom=15mm, top=15mm, right=10mm]{geometry}\n\n"
				 "\\begin{document}\n");


}


void end_tex(FILE* out)
{
	//fprintf(out, "\\\\ \\hline \n");

	fprintf(out, "\\end{document}\n");
}


void print_text_in_tex_main(double *main_array, unsigned int count_values, FILE* out)
{
/*
	FILE *out = NULL;

	out = fopen("out.tex", "w");

	if (out == NULL)
	{
		perror("Can't open file");
		return;
	}

	fprintf(out, "\\documentclass[12pt]{article}\n"
				 "\\usepackage[utf8]{inputenc}\n"
				 "\\usepackage{amsmath, amssymb, mathtools}\n"
				 "\\usepackage[left = 20mm, bottom=15mm, top=15mm, right=10mm]{geometry}\n\n"
				 "\\begin{document}\n");

	fprintf(out, "\\begin{table}[h]\n"
				 "\\caption { \"x_y\" }\n"
				 "\\center\n"
				 "\\begin{tabular} {");

*/

fprintf(out, "\\begin{table}[h]\n"
			 "\\caption { \"x_y\" }\n"
			 "\\center\n"
			 "\\begin{tabular} {");
for (int i = 0; i < count_values; i++)
{
	fprintf(out, "|l");
	}
	fprintf(out, "|}\n");
	fprintf(out, " \\hline\n");
/*
	for (int i = 0; i < (count_values + 1) * count_values; i++)
	{
		//printf("%d", i);
		printf("%lf ", main_array[(i % count_values) + count_values * (i / count_values)]);
		if ((count_values - 1) == (i % count_values))
			printf("\n");
	}
*/
	for (int i = 0; i < (count_values + 1) * count_values; i++)
	{
		if ((count_values - 1) == (i % count_values))
		{
			fprintf(out, " %lf", main_array[(i % count_values) + count_values * (i / count_values)]);
			fprintf(out, " \\\\ \\hline \n");
			continue;
		}
		fprintf(out, " %lf &", main_array[(i % count_values) + count_values * (i / count_values)]);
	}
	fprintf(out, "\n\\end{tabular}\n"
				 "\\end{table} \n");
	//fprintf(out, "\\\\ \\hline \n");
	/*
	fprintf(out, "\n\\end{tabular}\n"
					"\\end{table} \n");
	fprintf(out, "\\end{document}\n"); */
}

void print_text_in_tex_F_x(double *main_array, unsigned int count_values, FILE *out)
{
	fprintf(out, "\\begin{table}[h]\n"
				 "\\caption { \"x_y\" }\n"
				 "\\center\n"
				 "\\begin{tabular} {");
	for (int i = 0; i < count_values; i++)
	{
		fprintf(out, "|l");
	}
	fprintf(out, "|}\n");
	fprintf(out, " \\hline\n");
	/*
	for (int i = 0; i < (count_values + 1) * count_values; i++)
	{
		//printf("%d", i);
		printf("%lf ", main_array[(i % count_values) + count_values * (i / count_values)]);
		if ((count_values - 1) == (i % count_values))
			printf("\n");
	}
*/
	for (int i = 0; i < (count_values) * count_values; i++)
	{
		if ((count_values - 1) == (i % count_values))
		{
			fprintf(out, " %lf", main_array[(i % count_values) + count_values * (i / count_values)]);
			fprintf(out, " \\\\ \\hline \n");
			continue;
		}
		fprintf(out, " %lf &", main_array[(i % count_values) + count_values * (i / count_values)]);
	}
	fprintf(out, "\n\\end{tabular}\n"
				 "\\end{table} \n");
}

void print_text_in_tex_P_x(double *main_array, unsigned int count_values, FILE *out)
{
	fprintf(out, "\\begin{table}[h]\n"
				 "\\caption { \"x_y\" }\n"
				 "\\center\n"
				 "\\begin{tabular} {");
	for (int i = 0; i < count_values; i++)
	{
		fprintf(out, "|l");
	}
	fprintf(out, "|}\n");
	fprintf(out, " \\hline\n");
	/*
	for (int i = 0; i < (count_values + 1) * count_values; i++)
	{
		//printf("%d", i);
		printf("%lf ", main_array[(i % count_values) + count_values * (i / count_values)]);
		if ((count_values - 1) == (i % count_values))
			printf("\n");
	}
*/
	for (int i = 0; i < count_values; i++)
	{
		if ((count_values - 1) == (i % count_values))
		{
			fprintf(out, " %lf", main_array[(i % count_values) + count_values * (i / count_values)]);
			fprintf(out, " \\\\ \\hline \n");
			continue;
		}
		fprintf(out, " %lf &", main_array[(i % count_values) + count_values * (i / count_values)]);
	}
	fprintf(out, "\n\\end{tabular}\n"
				 "\\end{table} \n");
}

void print_text_in_tex_spline(double *main_array, unsigned int count_values, FILE *out)
{
	fprintf(out, "\\begin{table}[h]\n"
				 "\\caption { \"x_y\" }\n"
				 "\\center\n"
				 "\\begin{tabular} {");
	for (int i = 0; i < count_values - 1; i++)
	{
		fprintf(out, "|l");
	}
	fprintf(out, "|}\n");
	fprintf(out, " \\hline\n");
	/*
	for (int i = 0; i < (count_values + 1) * count_values; i++)
	{
		//printf("%d", i);
		printf("%lf ", main_array[(i % count_values) + count_values * (i / count_values)]);
		if ((count_values - 1) == (i % count_values))
			printf("\n");
	}
*/
	for (int i = 0; i < (count_values - 1); i++)
	{
		fprintf(out, "%lf & %lf & %lf & %lf\\\\ \\hline \n", main_array[0 + i * 4], main_array[1 + i * 4], main_array[2 + i * 4], main_array[3 + i * 4]);
	}
	fprintf(out, "\n\\end{tabular}\n"
				 "\\end{table} \n");
}
