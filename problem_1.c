// inlcude statements, come back
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> //for random number generator


//==================FUNCTION DECLARATIONS FOR MONTE CARLO==================
long double function(double x)
{
	return sqrt(1 - (x*x));
}

// generate random samples with rand() in stdlib.h



//==================MONTE CARLO METHODS==================
long double monte_carlo_integration(int n, long double (*function)(double))
{
	double x, sum = 0.0;

	for(int i = 0; i < n; i++)
	{
		//random x in [0,1]
		x = (double)rand()/RAND_MAX; //had to look this up. since rand() and RAND_MAX are int, (double) declares this fraction to be truncated as a double. RAND_MAX contained within stlib.h
		
		//f(X_i)
		sum += function(x);
	}

	return 4 * sum / n;
}

long double monte_carlo_ham(int n, long double (*function)(double))
{
    int inside_count = 0;
    double x, y;

    for (int i = 0; i < n; i++) {
        x = (double)rand() / RAND_MAX;  // random x \in [0,1]
        y = (double)rand() / RAND_MAX;  // random y \in [0,1]

        if (y <= function(x)) 
	{
            inside_count += 1;
        }
    }

    return 4.0 * inside_count / n;	
}



//==================MAIN==================

int main()
{
	
	// Monte Carlo Integration

	FILE *file_int = fopen("monte_carlo_integration_pi.dat", "w");
	
	fprintf(file_int, "number of iterations, estimate for pi\n");

	for (int m = 1; m <= 6; m++) 
	{
		int n = pow(10, m);
		long double pi_estimate = monte_carlo_integration(n, &function);
	
		fprintf(file_int, "%i\t%.20Lf\n", n, pi_estimate);
	
		printf("n = %i, Estimated Pi = %.20Lf\n", n, pi_estimate);
	}

	fclose(file_int);
	
	printf("Results saved to monte_carlo_integration_pi.dat\n");
	
	
	// Monte Carlo Hit and Miss
	
	FILE *file_ham = fopen("monte_carlo_hit-and-miss_pi.dat", "w");
	
	fprintf(file_ham, "number of iterations, estimate for pi, relative error\n");	
	
	for (int m = 1; m <= 6; m++)
        {
                int n = pow(10, m);
                long double pi_estimate = monte_carlo_ham(n, &function);
		long double relative_error = fabs(M_PI-pi_estimate)/(n);
        
		fprintf(file_ham, "%d\t%.20Lf\t%.20Lf\n", n, pi_estimate, relative_error);
        
		printf("n = %i, Estimated Pi = %.20Lf, Relative Error = %.20Lf\n", n, pi_estimate, relative_error);
        }

        fclose(file_ham);
        
	printf("Results saved to monte_carlo_hit-and-miss_pi.dat\n");

	return 0;
}
