// Hey Aspen (me) there is a mysterious a.out in your directory figure that out before u submit xoxo gossip girl

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> // for rng

#define M_PI 3.14159265358979323846

/*
===============================================================
-----------------Defining Structs for Setup--------------------
===============================================================
*/




typedef struct
{
	int nwarm;        // number of warmup steps
	int nskip;        // number of steps to skip between arguments
	int nmeas;        // number of measurements to report
	int binsize;      // bin size (if you can believe it)
	int nbin;         // number of bins (again this is pretty unintuitive...takes a lot of thought to understand)
	double *bin;      // bin storage array, needs pointer etc etc
	double *binavgs;  // array to store bin averages, needs pointer aslo

} S;

/*
===============================================================
--------------------Function Definitions-----------------------
=============================================================== */

void setup(S *S, int nwarm, int nskip, int nmeas)
{
	// setup member access operator for pointers (pointer-to-member operator). note that 'ABCD->a' is equivalent to '(*ABCD).a', its just easier to write
	
	S->nwarm = nwarm;
	S->nskip = nskip;
	S->nmeas = nmeas;
	S->binsize = 1000; // !!! BINSIZE FIXED HERE !!!!
	S->nbin = nmeas/ S->binsize; //hoe many bins needed
	
	// ~ Memory Allocation ~
	S->bin = (double *)malloc(S->binsize * sizeof(double));

	S->binavgs = (double *)malloc(S->nbin * sizeof(double));
}

void sweep(S *S)
{
	// generate a random sample from a standard normal distribution

	double u1 = (rand() % 10000) / 10000.0; // prevents div by zero. trying to fix issues. Aspen later:  this actually just broke my code lol
	double u2 = (rand() % 10000) / 10000.0;
	

	double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);

	S->bin[0]=z0;
}

void warmup(S *S)
{
	// run sweep func nwarm times
	
	for(int i = 0; i<S->nwarm; i++)
	
	{
		sweep(S);
	}
}

double compute_measurement(S *S)
{
	// simple measurement, return the sample value
	
	return S->bin[0];
}

void measure(S *S, int i)
{
	// measure and store reults into the bin
	
	S->bin[i] = compute_measurement(S);
}

void avgbin(S *S, int k)
{
	// find avg of current bin
	
	double sum = 0.0;
	
	for(int i = 0; i < S->binsize; i++)
	{
		sum += S->bin[i];
	}
	
	S->binavgs[k] = (sum) / (S->binsize);
}

void dostatistics(S *S)
{
	// compute and print avgs of all bins
	double sum = 0;
	
	for(int k = 0; k< S->nbin; k++)
	{
		sum+= S->binavgs[k];
	}

	double avg = sum / S->nbin;

	printf("Average from all bins: %f\n", avg);
}

void output(S *S)
{
	// function space to output results, I choose to print to terminal and to a .dat file
	for(int k =0; k<S->nbin; k++)
	{
		FILE *file = fopen("bin_average.dat", "a"); //"a" instead pof "w" makes sure that the writing in the file isnt overwritten on successive iterations
		fprintf(file, "%d\t%f\n", k, S->binavgs[k]);
		fclose(file);
		
		printf("file print successful.\n");
		printf("Bin %d average: %f\n\n", k, S->binavgs[k]);
	}
}


void run_simulation_for_nskip(S *S, int *nskip_values, int nskip_count, int current_idx)
{
	if(current_idx >= nskip_count)
	{
		return; // end condition
	}

	// set current nskip value
	S->nskip = nskip_values[current_idx];

	printf("\nRunning simulation for nskip = %d\n", S->nskip);
	//---------RUNNING SIMULATION (OLD MAIN FUNC)---------
	
	// FIRST MEASUREMENT SWEEP AFTER WARMUP
	sweep(S);
	measure(S, 1);
	

	// FIRST BIN LOOP AFTER WARMUP
	for (int i = 2; i <= S->binsize; i++)
	{
		for (int j = 1; j <= S->nskip; j++)
		{
			sweep(S);
		}
		sweep(S);
		measure(S, i);
	}
	avgbin(S, 1);

	// BIN LOOPS AFTER INITIAL LOOP
	for (int k = 2; k <= S->nbin; k++)
	{
		for (int i = 1; i <= S->binsize; i++)
		{
			for (int j = 1; j <= S->nskip; j++)
			{
				sweep(S);
			}
			sweep(S);
			measure(S, i);
		}
		avgbin(S, k);
	}

	// final stats and output
	dostatistics(S);
	output(S);

	// recustive call for next nskip val
	run_simulation_for_nskip(S, nskip_values, nskip_count, current_idx + 1);
}	

/*
=============================================================== 
-------------------------------Main---------------------------- 
=============================================================== 
*/

int main()
{
	srand(time(NULL)); // seed generator based on time for rng
	
	// ~ Parameters ~
	
	int nwarm = 1000; //warmup steps, number of times this sweeps
	//int nskip; // number of steps to skip, need to run 1, 2, 5, 10, 50, 100
	int nmeas = 10000; // total measurements

	S simulation;
	
	int nskip_values[] = {1, 2, 5, 10, 50, 100};
	int nskip_count = sizeof(nskip_values)/sizeof(int);

	setup(&simulation, nwarm, nskip_values[0], nmeas); // initializing with forst nskip value
	
	run_simulation_for_nskip(&simulation, nskip_values, nskip_count, 0);

	// free mem
	
	free(simulation.bin);
	free(simulation.binavgs);

	// OLD MAIN STUFF

	/*
	// WARMUP PHASE
	warmup(&simulation);

	// FIRST MEASUREMENT SWEEP AFTER WARMUP
	sweep(&simulation);
	measure(&simulation, 1);

	// FIRST BIN LOOP AFTER WARMUP
	for(int i = 2; i <= simulation.binsize; i++)
	{
		for(int j =1; j <= simulation.nskip; j++)
		{
			sweep(&simulation);
		}
		sweep(&simulation);
		measure(&simulation, i);
	}
	avgbin(&simulation, 1);


	for(int k=2; k <= simulation.nbin; k++)
	{
		for(int i = 1; i <= simulation.binsize; i++)
		{
			for(int j = 1; j <= simulation.nskip; j++)
			{
				sweep(&simulation);
			}
			sweep(&simulation);
			measure(&simulation, i);
		}
		avgbin(&simulation, k);
	}

	// final stats
	dostatistics(&simulation);

	// output
	output(&simulation);
	*/

	return 0;
}








