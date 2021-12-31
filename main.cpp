/*
Author: Deanna Gierzak
Class: ECE 6122
Last Date Modified: 10/13/2020

Description:

	The program uses takes in the number of trial runs as a command line argument,
		and for each iteration from 0 to that number, generates a random value for 
		x1, x2, and x3 from uniform distribution within the bounds (0, 1), (0, 2), 
		and (2, 3) respectively.

	The value of Z is calculated for the following equation at each iteration:

				Z = (exp(x1) + x2)*(exp(x1) + x2) + 3 * (1 - x3)*(1 - x3);	

	The maximum Z is saved and checked against all simulations in an exhaustive search.
	After all simulations, the R.V. values of x1, x2, and x3 that were saved from 
		the maximum Z are output to a text file

*/
#include <omp.h>		// included for openMP
#include <random>		// included to generate the random variables x1, x2, x3
#include <iomanip>		// needed for setprecision
#include <fstream>		// included file output
using namespace std;

int main(int argc, char* argv[])
{
	//double start_time = omp_get_wtime();	// get the start time
	const int N = atoi(argv[1]);			// convert command line argument to an int
	//int N = int(argv[1]);						// note to self: don't do this, bad idea!!! the reason for my super slow code!! was making crazy values!!
	double maxZ = 0.0;						// initialized max Z value to 0
	double maxX1 = 0.0;						// x1 value at max Z initialized to 0
	double maxX2 = 0.0;						// x2 value at max Z initialized to 0
	double maxX3 = 0.0;						// x3 value at max Z initialized to 0
	double x1, x2, x3;						// declare x1, x2, x3 random variables that will be generated from the uniform distribution and random engine generator
	double Z;								// declare Z that will be calculated from the randomly generated x1, x2, x3 values
											//private(x1, x2, x3, Z)
// Only need to declare a parallel once!! This starts the fork from the main/master thread into multiple (on my system, 8) threads
#pragma omp parallel private(x1, x2, x3, Z)
		{
		default_random_engine generator(time(0));							// the random engine generator to be used for all the x's, seeded with current time
		uniform_real_distribution<double> x1_distribution(0.0, 1.0);		// the uniform distribution for x1 to go from 0 to 1
		uniform_real_distribution<double> x2_distribution(0.0, 2.0);		// the uniform distribution for x2 to go from 0 to 1
		uniform_real_distribution<double> x3_distribution(2.0, 3.0);		// the uniform distribution for x3 to go from 2 to 3
// Use a "for" directive to split up the work of generating random values for x1, x2, and x3, and calculating a Z among all the threads
#pragma omp for
			for (int i = 0; i < N; ++i)
			{
				x1 = x1_distribution(generator);			// generate random value for x1
				x2 = x2_distribution(generator);			// generate random value for x2
				x3 = x3_distribution(generator);			// generate random value for x3

				Z = (exp(x1) + x2)*(exp(x1) + x2) + 3 * (1 - x3)*(1 - x3);	// calculate Z from random variables x1, x2, x3

// Protect the check of finding the maximum Z value, so threads don't walk all over each other trying to figure out whether their Z is the new max
//#pragma omp critical		
//				{
					if (Z > maxZ)
					{
#pragma omp critical
						{
							maxZ = Z;						// set the new maximum for Z if current Z is greater than the previous maximum Z
							maxX1 = x1;						// save the x1 corresponding to this maximum Z value
							maxX2 = x2;						// save the x2 corresponding to this maximum Z value
							maxX3 = x3;					    // save the x3 corresponding to this maximum Z value
						}
					}
//				}
			}
		}
		//double total_time = omp_get_wtime() - start_time;			// get the end time and calculate the total run time in execution of the omp code

		fstream outFile("Lab3Prob3.txt", fstream::out);										// open/create the output file for saving x values
		outFile << "X1: " << fixed << setprecision(15) << maxX1 << endl;					// output the value for maximum x1 with 15 decimal points of precision
		outFile << "X2: " << fixed << setprecision(15) << maxX2 << endl;					// output the value for maximum x2 with 15 decimal points of precision
		outFile << "X3: " << fixed << setprecision(15) << maxX3 << endl;					// output the value for maximum x3 with 15 decimal points of precision
		//outFile << "total time: " << fixed << setprecision(10) << total_time << endl;		// remember to remove this line before submitting
		//outFile << "N number of iterations: " << fixed << setprecision(10) << N;			// remember to remove this line before submitting
		outFile.close();																	// close the file before exiting the program
	return 0;
}
