#include <stdio.h>
#include <math.h>

int main()
{
    double len;//edge len
    double sa;//surface area
    double v; //volume

    /*
     ---------------   CUBE     --------------------------
    */
    printf("Enter the edge length for cube: ");
    scanf("%lf", &len);
    sa = 6 * len * len;
    v = len * len * len;
    printf("Surface Area = %.2lf, Volume = %.2lf\n\n\n", sa, v);

    /*
     ---------------   RECTANGULAR PRISM  -------------------
    */
    double sw; // side width;
    double sh; // side height;
    printf("Enter side length for rectangular prism: ");
    scanf("%lf", &len);
    printf("Enter side width for rectangular prism: ");
    scanf("%lf", &sw);
    printf("Enter side height for rectangular prism: ");
    scanf("%lf", &sh);
    sa = 2 * (sw*len + sh*len + sw*sh);
    v = sw * sh * len;
    printf("Surface Area = %.2lf, Volume = %.2lf\n\n\n", sa, v);

    /*
     ---------------   SPHERE  -------------------
    */
    double r; //radius
    printf("Enter the radius for sphere: ");
    scanf("%lf", &r);
    sa = (4.0) * (3.14) * r * r;
    v = (4 * (3.14) * r * r * r)/3;
    printf("Surface Area = %.2lf, Volume = %.2lf\n\n\n", sa, v);


    /*
     ---------------   CONE  -------------------
    */
    printf("Enter the radius for cone: ");
    scanf("%lf", &r);
    printf("Enter the height for cone: ");
    scanf("%lf", &sh);
    sa =  r * (3.14) * (sqrt(r*r + sh*sh) + r);
    v = ((3.14) * (r * r) * sh) / 3;
    printf("Surface Area = %.2lf, Volume = %.2lf\n\n\n", sa, v);

    
    return (0);
}