# ECE6122-Lab3-Problem3-MonteCarlo-Equation

Last Date Modified: 10/13/2020

Description:

	The program takes in the number of trial runs as a command line argument,
		and for each iteration from 0 to that number, generates a random value for 
		x1, x2, and x3 from uniform distribution within the bounds (0, 1), (0, 2), 
		and (2, 3) respectively.
    
	The value of Z is calculated for the following equation at each iteration:
				Z = (exp(x1) + x2)*(exp(x1) + x2) + 3 * (1 - x3)*(1 - x3);	
        
	The maximum Z is saved and checked against all simulations in an exhaustive search.
	After all simulations, the R.V. values of x1, x2, and x3 that were saved from 
		the maximum Z are output to a text file
    
    Example execution in command line:
    ~$  g++ .\*.cpp a.exe
    ~$  a.exe 10000
    ~$ cat output-file-name.txt
    41
