#include <stdio.h>

typedef struct s_matrix
{
    double matrix[3][3];
    double det;
}t_matrix;

void print_matrix(t_matrix initial_matrix)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            printf("%.4lf ",initial_matrix.matrix[i][j]);
        printf("\n");
    }
}

void determinant_of_matrix(t_matrix *initial_matrix)
{
	double a = initial_matrix->matrix[0][0];
	double b = initial_matrix->matrix[0][1];
	double c = initial_matrix->matrix[0][2];
	double d = initial_matrix->matrix[1][0];
	double e = initial_matrix->matrix[1][1];
	double f = initial_matrix->matrix[1][2];
	double g = initial_matrix->matrix[2][0];
	double h = initial_matrix->matrix[2][1];
	double i = initial_matrix->matrix[2][2];
    double det = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    initial_matrix->det = det;
}

int inverse_matrix(t_matrix* initial_matrix, t_matrix *inverted_matrix)
{
    determinant_of_matrix(initial_matrix);
	if (initial_matrix->det == 0) {
		printf("Error: the matrix is not invertible.\n");
		return (-1);
	}
	double a = initial_matrix->matrix[0][0];
	double b = initial_matrix->matrix[0][1];
	double c = initial_matrix->matrix[0][2];
	double d = initial_matrix->matrix[1][0];
	double e = initial_matrix->matrix[1][1];
	double f = initial_matrix->matrix[1][2];
	double g = initial_matrix->matrix[2][0];
	double h = initial_matrix->matrix[2][1];
	double i = initial_matrix->matrix[2][2];
	double inv_det = 1.0 / initial_matrix->det;
	inverted_matrix->matrix[0][0] = inv_det * (e*i - f*h);
	inverted_matrix->matrix[0][1] = inv_det * (c*h - b*i);
	inverted_matrix->matrix[0][2] = inv_det * (b*f - c*e);
	inverted_matrix->matrix[1][0] = inv_det * (f*g - d*i);
	inverted_matrix->matrix[1][1] = inv_det * (a*i - c*g);
	inverted_matrix->matrix[1][2] = inv_det * (c*d - a*f);
	inverted_matrix->matrix[2][0] = inv_det * (d*h - e*g);
	inverted_matrix->matrix[2][1] = inv_det * (b*g - a*h);
	inverted_matrix->matrix[2][2] = inv_det * (a*e - b*d);
	return (1);
}

int main()
{
    t_matrix initial_matrix;
    t_matrix inverted_matrix;
	int flag;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			printf("Enter the element [%d][%d] of the matrix: ", i, j);
			scanf("%lf", &initial_matrix.matrix[i][j]);
		}
	}
    printf("\n");
    print_matrix(initial_matrix);
    printf("\n");
    flag = inverse_matrix(&initial_matrix, &inverted_matrix);
    printf("\n");
	if (flag == 1)
    	print_matrix(inverted_matrix);
}