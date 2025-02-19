#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

struct S
{
	double current;
	double proposed;
};

double rand_unif_betw(double a, double b);
bool accept(struct S *s);
void warmup(int nwarm, double pwidth, struct S *st);
double normal(double x);

int main(){

	int nwarm = 3000;
	int nmeas = 3000;
	int nskip = 50;

	srand(time(NULL)); // random seed :)
	
	FILE *file = fopen("outputs_nskip_50.dat", "w");

	double proposed_width = 1.0;

	struct S st;

	st.current = rand_unif_betw(-5,5);

	warmup(nwarm, proposed_width, &st);

	for(int i = 0; i< nmeas; i++)
	{
		st.proposed = st.current + rand_unif_betw(-proposed_width * 0.5, proposed_width * 0.5);

		if(accept(&st))
		{
			st.current = st.proposed;
		}

		if(i%nskip==0)
		{
			fprintf(file, "%.20lf\n", st.current);
		}
	}

	fclose(file);

	return 0;
}

double rand_unif_betw(double a, double b)
{
	return a + (b - a) * ((double)rand()/RAND_MAX);
}

double normal(double x)
{
	return (1 / sqrt(2 * M_PI)) * exp(-(x * x) * 0.5);
}

bool accept(struct S *s)
{
	return (rand_unif_betw(0, 1) <= normal(s->proposed) / normal(s->current));
}

void warmup(int nwarm, double pwidth, struct S *st)
{
	for(int i = 0; i<nwarm; i++)
	{
		st->proposed = st->current + rand_unif_betw(-pwidth * 0.5, pwidth * 0.5);

		if(accept(st))
		{
			st->current = st->proposed;
		}
	}
}



/*
double rand_unif_betw(double a, double b)
{
    return a + (b - a) * ((double)rand() / RAND_MAX);
}


// Struct defn

struct S 
{
	double current;
	double proposed;
};

bool accept(struct S *s)
{
	return(rand_unif_betw(0,1) <= normal(s->proposed)/normal(s->current));
}

// aux function defns

void warmup(int nwarm, double pwidth, struct S *st)
{
	for(int i = 0; i<nwarm; i++)
	{
		st->proposed = st->current + rand_unif_betw(-pwidth/2, pwidth/2);

	}

	if accept(st)
	{
		st->current = st->proposed;
	}
}

double normal(double x)
{
	return (1/sqrt(2*M_PI))*exp(-(x * x) * 0.5);
}


// main

int main()
{
	int nwarm = 3000;
	int nmeas = 3000;
	int nskip = 100;

	srand(time(NULL)); // random seed
	
	FILE*file = fopen("outputs.dat", "w");

	double proposed_width = 1.0;

	struct S st;

	st.current = rand_unif_betw(-5,5);

	warmup(nwarm, proposed_width, &st);

	for(int i =0; i < nmeas; i++)
	{
		st.proposed = st.current + rand_unif_betw(-proposed_width/2, proposed_width/2);

		if(accept(&st)){
			st.current = st.proposed;
		}
		if(i%nskip==0) fprintf(file, "%.20lf\n", st.current);
	}

	fclose(file);

	return 0;
}
*/
