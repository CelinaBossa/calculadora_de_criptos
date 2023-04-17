#include <stdio.h>
#include <stdlib.h>

extern double multiply(double a, double b);  // Assembly routine

float multiplication(float x,float y){
    double result = multiply(x,y); // Call the assembly routine
    return result;
}