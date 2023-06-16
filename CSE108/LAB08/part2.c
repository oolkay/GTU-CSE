#include <stdio.h>
#include <math.h>

typedef struct s_vector
{
    double x;
    double y;
    double z;
}vector;

double find_orthogonal(vector vec_1, vector vec_2, vector* output_vec)
{
    double dot_product=vec_1.x*vec_2.x+vec_1.y*vec_2.y+vec_1.z*vec_2.z;
    double vec1_len=sqrt(pow(vec_1.x,2)+pow(vec_1.y,2)+pow(vec_1.z,2));
    double vec2_len=sqrt(pow(vec_2.x,2)+pow(vec_2.y,2)+pow(vec_2.z,2));
    double angle=acos(dot_product/(vec1_len * vec2_len))*180.0/M_PI;

    output_vec->x=vec_1.y*vec_2.z-vec_1.z*vec_2.y;
    output_vec->y=vec_1.z*vec_2.x-vec_1.x*vec_2.z;
    output_vec->z=vec_1.x*vec_2.y-vec_1.y*vec_2.x;
    return angle;
}

int main()
{
    vector vec_1;
    vector vec_2;
    vector output_vec;
    double angle;

    printf("Enter vector_1 coordinates (x,y,z): ");
    scanf("%lf %lf %lf", &vec_1.x,&vec_1.y,&vec_1.z);
    printf("Enter vector_2 coordinates (x,y,z): ");
    scanf("%lf %lf %lf", &vec_2.x,&vec_2.y,&vec_2.z);
    angle = find_orthogonal(vec_1,vec_2,&output_vec);
    printf("\nThe angle between vectors: %lf\n\n", angle);
    printf("The orthogonal vector is %.2lf %.2lf %.2lf",output_vec.x,output_vec.y,output_vec.z);
}