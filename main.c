#include <stdio.h>
#include <math.h>
#define EPS (double)(1e-6)

double function_first(double x){
    return sin(x);
}
double function_second(double x){
    return x * cos(x);
}
double function_third(double x){
    return x * x + x - tan(x);
}
double function_fourth(double x){
    return exp(x) + 3;
}

double CalcIntegral(double a, double b, double c, int n, double (*InFunction)(double))
{
    int i;
    double result, h;
    result = 0;
    h = (b - a) / n;
    for(i = 0; i < n; i++){
        result += fabs(InFunction(a + h * (i + 0.5)) - c);
    }
    result *= h;

    return result;
}

int main() {
    double S, a, b, c;
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    fscanf(in, "%lf %lf %lf %lf", &S, &a, &b, &c);

    double (*functions[])(double) = {function_first, function_second, function_third, function_fourth};

    double max_S = 0;

    int i;
    for(i = 0; i < 4; i++){

        int segments = 1;
        double first_square = CalcIntegral(a, b, c, segments, functions[i]);
        double second_square = CalcIntegral(a, b, c, segments * 2, functions[i]);

        while(fabs(first_square - second_square) > EPS)
        {
            segments *= 2;
            first_square = second_square;
            second_square = CalcIntegral(a, b, c, segments * 2, functions[i]);
        }

        double square = first_square;

        if(square <= S && square > max_S)
            max_S = square;

        fprintf(out, "%d func S = %lf\n", i + 1, square);
    }
    fprintf(out, "eps = %lf\n", EPS);
    fprintf(out, "Max square - %lf", max_S);

    fclose(in);
    fclose(out);

    return 0;
}