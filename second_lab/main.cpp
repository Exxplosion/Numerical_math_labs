//#include <graphic.h>
#include "working_file.h"
#include <cmath>

#define P(x) value_at_point(x, x_coefficients, count_values)
#define d_P(x) value_at_point(x, d_dx_poly, count_values)
#define x_(i) main_array[(i)]
#define f_(i) main_array[count_values + (i)]


unsigned int check_count_values(char* init_array)
{
    unsigned int tmp = 0;
    for (int i = 0; init_array[i] != '\n'; i++)
    {
        if (init_array[i] == ' ')
            tmp++;
    }
    tmp++;
    return tmp;
}

void put_values(double* main_array, char* init_array, unsigned int line_size_matrix)
{
    int n = 0;
    int i = 0;
    while (init_array[n] != '\0')
    {
        char supp_str[10];
        int supp_count = 0;
        while (init_array[n] != ' ' && init_array[n] != '\n' && init_array[n] != '\0')
        {
            //printf("MMM: %c\n", init_array[n]);
            supp_str[supp_count] = init_array[n];
            supp_count++;
            n++;    
        }
        supp_str[supp_count] = '\0';
        //printf("HAA %s\n", supp_str);
        double a = atof(supp_str);
        //printf("%le\n", a);
        main_array[(i % line_size_matrix) + line_size_matrix * (i  / line_size_matrix)] = atof(supp_str);
        //printf("%le\n", main_array[(i % line_size_matrix) + (i / line_size_matrix)]);
        i++;
        n++;
    }
}



void put_coefficients(double* main_array, unsigned int line_size_matrix)
{
    for (int i = 0; i < line_size_matrix - 1; i++)
    {
        for (int j = 0; j < line_size_matrix - i - 1; j++)
        {
            //int i_line = line_size_matrix * i;
            //printf("i = %d (%d), j =%d, real = %d\n", i + 2, (i + 2) * line_size_matrix, j, (i + 2) * line_size_matrix + j);
            main_array[(i + 2) * line_size_matrix + j] = (main_array[(i + 1) * line_size_matrix + j + 1] - main_array[(i + 1) * line_size_matrix + j]) \
            / (main_array[j + i + 1] - main_array[j]);
        }
    }
}

void opening_parentheses(double* F_x, double* main_array, int count_values)
{
    for (int i = 1; i < count_values; i++)
    {
        double aux_F[count_values];
        for (int j = 0; j < count_values; j++)
        {
            aux_F[j] = F_x[(j * (count_values)) + i - 1];
            //printf("aux_F_j %le (%d)\n", aux_F[j], j);
        }

        double aux_1[count_values];
        for (int j = 0; j < count_values; j++)
        {
            aux_1[j] = aux_F[j] * main_array[i];
            //printf("aux_1_j %le (%d)\n", aux_1[j], j);
        }

        double aux_2[count_values] = {0};
        for (int j = 0; j < count_values; j++)
        {
            aux_2[j + 1] = aux_F[j];
            //printf("aux_2_j %le (%d)\n", aux_2[j], j);
        }

        double aux_3[count_values];
        for (int j = 0; j < count_values; j++)
        {
            aux_3[j] = aux_2[j] - aux_1[j];
            F_x[(j * (count_values)) + i] = aux_3[j];
            //printf("aux_3_j %le (%d)\n", aux_3[j], j);
        }
    }
}

void opening_parentheses_with_b(double* F_x,double* main_array, int count_values)
{
    for (int i = 0; i < count_values - 1; i++)
    {
        for (int j = 0; j < count_values; j++)
        {
            F_x[(j * count_values) + i] = F_x[(j * count_values) + i] * main_array[(i + 2) * count_values];
        }
    }
}

void get_coefficients(double* x_coefficients, double* F_x, double* main_array, int count_values)
{
    x_coefficients[0] += main_array[count_values];
    for (int i = 0; i < count_values; i++)
    {
        for (int j = 0; j < count_values - 1; j++)
        {
            if( i != 0)
                x_coefficients[i] = x_coefficients[i] + F_x[(i*count_values) + j];
            else
            {
                x_coefficients[i] = x_coefficients[i] + F_x[(i * count_values) + j];
            }
        }
        //printf("Coeff - %le pri %d\n", x_coefficients[i], i);
    }
}

void derivative_polynom(double* x_coefficients, int count_values, double* d_dx_poly)
{
    for (int i = 0; i < count_values - 1; i++)
    {
        d_dx_poly[i] = x_coefficients[i + 1] * (i + 1);
        //printf("Coeff _d/dx  %le pri %d\n", d_dx_poly[i], i);
    }
}

double value_at_point(double point, double* x_coefficients, int count_values)
{
    double value = x_coefficients[0];
    for (int i = 1; i < count_values; i++)
    {
        value += x_coefficients[i] * pow(point, i);
    }
    return value;
}

void get_spline(double* spline, double* x_coefficients, double* d_dx_poly, double* main_array, int count_values)
{
    for (int i = 0; i < count_values; i++)
    {
        //printf("................\n d_P(x(i+1)) = %le\n  x(i+1) = %le, x(i) = %le, \n f(i+1) = %le, f(i) = %le \n", d_P(x_(i+1)), x_(i+1), x_(i), f_(i+1), f_(i));
        spline[i * 4 + 3] = (d_P(x_(i + 1)) * (x_(i + 1) - x_(i)) - 2*(f_(i + 1) - f_(i)) + d_P(x_(i)) * (x_(i + 1) - x_(i))) / pow((x_(i+1)- x_(i)), 3);
        //printf("spline -- %le\n", spline[i * 4 + 3]);
        spline[i * 4 + 2] = (-d_P(x_(i + 1)) * (x_(i + 1) - x_(i)) * (x_(i + 1) + 2*x_(i)) + 3*(f_(i + 1) - f_(i))* (x_(i+1) + x_(i)) - d_P(x_(i)) * (x_(i + 1) - x_(i)) * (x_(i) + 2*x_(i+1))) / pow((x_(i+1)- x_(i)), 3);
        spline[i * 4 + 1] = (d_P(x_(i + 1)) * x_(i) * (x_(i + 1) - x_(i)) * (2*x_(i + 1) + x_(i)) - 6 * (f_(i + 1) - f_(i)) * x_(i + 1) * x_(i) + d_P(x_(i)) * x_(i+1) * (x_(i + 1) - x_(i)) * (2*x_(i) + x_(i + 1))) / pow((x_(i + 1) - x_(i)), 3);
        spline[i * 4 + 0] = (-d_P(x_(i + 1)) * x_(i) * x_(i) * x_(i + 1) * (x_(i + 1) - x_(i)) + (f_(i + 1)) * x_(i) * x_(i) * (3 * x_(i + 1) - x_(i)) + f_(i) * x_(i+1) * x_(i+1)* (x_(i+1) - 3*x_(i)) - d_P(x_(i)) * x_(i) * x_(i+1) * x_(i+1) * (x_(i + 1) - x_(i))) / pow((x_(i + 1) - x_(i)), 3);
    }
}

/*
int check_interval_point_x(double point, double* main_array, int count_values)
{
    for (int i = 0; i < count_values - 1; i++)
    {
        if ((main_array[i] <= point) && (main_array[i] >= point))
        {
            return i;
        }
    }
} */

double value_at_point_3(double point, double *main_array, double *spline, int count_values)
{
    int numb_point = 1;
    for (int i = 0; i < count_values - 1; i++)
    {
        if ((main_array[i] <= point) && (main_array[i + 1] >= point))
        {
            numb_point = i;
            printf("%d\n", i);
            break;
        }
    }

    double value = spline[numb_point * 4];

    for (int i = 1; i < 4; i++)
    {
        value += spline[i] * pow(point, i);
    }

    return value;
}


char* formation_polynom(double* x_coefficients, int count_values)
{
    char* polynom = (char* ) calloc(200, sizeof(char));
    int s = sprintf(polynom, "./plot.py ");
    int n = s;
    for (int i = 0; i < count_values ; i++)
    {
        int s = sprintf(polynom + n, "%le_", x_coefficients[i]);
        n +=s ;
        //if (i != count_values -1)
            //sprintf(polynom, "+");
    }
    sprintf(polynom + n, "0");
        printf("\n%s\n", polynom);
    return polynom;
}


int main()
{
    char* init_array = NULL;
    init_array = read_file_in_array();
    
    //printf("%s", init_array);
    unsigned int count_values = check_count_values(init_array);

    double main_array[(count_values + 1) * count_values]; //не знаю почему, 
    //но я здесь решил воспользоваться одномерным, но по факту двумерным массивом...
    //доступ к ij ячейки определяется как (i * (count_values)) + j


    printf("%d\n", count_values);
    put_values(main_array, init_array, count_values);

    put_coefficients(main_array,  count_values);

/*
    for (int i = 0; i < (count_values + 1) * count_values; i++)
    {
        //printf("%d", i);
        printf("%le ", main_array[(i % count_values) + count_values * (i / count_values)]);
        if ((count_values - 1) == (i % count_values))
            printf("\n");
    }
*/
    //ох...
    double F_x[count_values * count_values] = {0};
    F_x[0] = -1 * main_array[0];  //F- column
    F_x[count_values] = 1;
    opening_parentheses(F_x, main_array, count_values);

    opening_parentheses_with_b(F_x, main_array, count_values);

    double x_coefficients[count_values - 1];
    get_coefficients(x_coefficients, F_x, main_array, count_values);

    double d_dx_poly[count_values - 1];
    derivative_polynom(x_coefficients, count_values, d_dx_poly);

    double spline[(count_values - 1) * 4] = {0};

    get_spline(spline, x_coefficients, d_dx_poly, main_array, count_values);

/*
    for (int i = 0; i < (count_values - 1); i++)
    {

        printf("%le & %le & %le & %le\\\\ \\hline \n", spline[0 + i * 4], spline[1 + i * 4], spline[2 + i * 4], spline[3 + i * 4]);
    }

    for (int i = 0; i < (count_values - 1); i++)
    {

        printf("%d %d %d %d \n", 0 + i * 4, 1 + i * 4, 2 + i * 4, 3 + i * 4);
    }
*/

    printf(" value at 0.2  POLY- %le", value_at_point(0.2, x_coefficients, count_values));
    printf(" value at 0.2  SPLINE- %le", value_at_point_3(0.2, main_array, spline, count_values));

    formation_polynom(x_coefficients, count_values);
    FILE *out = NULL;

    out = fopen("out.tex", "w");

    if (out == NULL)
    {
        perror("Can't open file");
        //return;
    }
    begin_tex(out);
    print_text_in_tex_main(main_array, count_values, out);
    print_text_in_tex_F_x(F_x, count_values, out);
    print_text_in_tex_P_x(x_coefficients, count_values, out);
    print_text_in_tex_spline(spline, count_values, out);

    //print_text_in_tex(x_coefficients, count_values, out);
    end_tex(out);
    //system("pdflatex out.tex");
    //system("./plot.py");
    system(formation_polynom(x_coefficients, count_values));
}