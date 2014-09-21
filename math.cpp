#include <math.h>
#include <iostream>

#define NORMAL_CO 0.3989422804

typedef double (*map_func)(double);
typedef double (*combine_func)(double, double);
typedef double (*loop_func)(unsigned, unsigned, map_func);

double add(double a, double b){
    return a+b;
}

double sub(double a, double b){
    return a-b;
}

double mult(double a, double b){
    return a*b;
}

double div(double a, double b){
    return a/b;
}

double sigma(unsigned min, unsigned max, map_func func){
    double sum = 0;
    for(unsigned i=min;i<=max;i++){
        sum+=func(i);
    }
    return sum;
}

double product(unsigned min, unsigned max, map_func func){
    double product = min;
    for(unsigned i=min+1;i<=max;i++){
        product*=func(i);
    }
    return product;
}

double sigmoid(double x){
    return 1.0/(1.0+exp(-x));
}
double base_log(double a, double b){
    return log2(a)/log2(b);
}
double sq(double x){
    return x*x;
}
double abs(double x){
    return (x>0)?x:-x;
}

double identity(double x){
    return x;
}
double fact(double x){
    for(double i = x-1; i>=1; i--){
        x*=i;
    }
    return x;
}
double standNormDist(double x){
    return exp(-sq(x)/2)*NORMAL_CO;
}
static map_func map_funcs[] =  {abs, sq, sqrt, exp, log, sigmoid, standNormDist,
                                ceil, fact, floor, round,cbrt, cos, sin, tan, acos,
                                asin, atan, cosh, sinh, tanh, acosh, asinh, atanh};
static combine_func combine_funcs[] = {add, sub, mult, div, pow, base_log, hypot};
static loop_func loop_funcs[] = {sigma, product};

int main(){
    std::cout << standNormDist(4) << std::endl;
}