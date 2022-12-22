#include <iostream>
#include <math.h>
using namespace std;

double func(double x){
    return 1/(4+x);
}

double romberg(double a, double b, int n){
    double h[n+1], r[n+1][n+1];
    
    for (int i=1; i<n+1; ++i){
        h[i] = (b-a) / pow(2, i-1);
    }
    r[1][1] = h[1] / 2*(func(a) + func(b));
    
    for (int i=2; i<n+1; ++i){
        double koef = 0;
        for (int k=1; k<=pow(2, i-2); ++k){
            koef += func(a + (2*k-1) * h[i]);
        }
        r[i][1] = 0.5 * (r[i-1][1] + h[i-1] * koef);
    }
    
    for (int i=2; i<n+1; ++i){
        for (int j=2; j<=i; ++j){
            r[i][j] = r[i][j-1] + (r[i][j-1] - r[i-1][j-1]) / (pow(4, j-1)-1);
        }
    }
    
    for (int i=1; i<=n; ++i){
    	for (int j=1; j<=n; ++j){
    	    printf("%.7f ", r[i][j]);
	}
	cout<<"\n";
    }
    return r[n][n];
}

double trapezoid(double a, double b, int n){
    double h = (b-a)/n;
    double area = 0, curr=a;
	
    for (int i=1; i<=n; ++i){
	area += (h/2) * (func(curr)+func(curr+h));
	printf("%.7f\n", area);
	curr += h;
    }
	
    return area;
}

int main(){
    
    printf("%.7f\n\n", romberg(0, 1, 10));
    printf("%.7f", trapezoid(0, 1, 10));
}
