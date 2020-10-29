#ifndef WORKING_FILE_H
#define WORKING_FILE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_INCREMENT 256

typedef struct
{
	char *lineptr; //массив указателей на начало
	int len_line; 
} lines;


//const char file_name[] = "Asm.txt";
char* read_file_in_array();
lines* start_of_lines(char* text, int* count_lines);
void print_text_in_tex_main(double *main_array, unsigned int count_values, FILE *out);
void print_text_in_tex_F_x(double *main_array, unsigned int count_values, FILE *out);
void print_text_in_tex_P_x(double *main_array, unsigned int count_values, FILE *out);
void print_text_in_tex_spline(double *main_array, unsigned int count_values, FILE *out);
void end_tex(FILE *out);
void begin_tex(FILE *out);

#endif