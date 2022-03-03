#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main( int argc , char *argv[ ] , char *envp[ ] )
{
	// check if it is enough params passed
	if (argc != 2)
	{
		fputs("Wrong args!\n", stderr);
		return -1;
	}
	// get ptr to filename
	char *filename = argv[1];
	// check if not null
	if ( !(*filename) )
	{
		fputs("Wrong args!\n", stderr);
		return -1;
	}
	// try to open file
	printf("try to open file %s...\n", filename);
	//int outfile = open (filename, O_CREAT, 644);
	FILE* outfile = fopen (filename, "w");
	if (!outfile)
	{
		fputs("Cant open file!\n", stderr);
		return -1;
	}
	fputs("File open success!\n", stderr);
	
	// prepare console setup
	//system("/bin/stty raw");
	
	// other code
	int error = 0;
	while (!error) 
	{
		// read char
		int nextchar = getchar();
		// handle errors
		if (nextchar == EOF)
		{
			error = 1; 
			break;
		}
		// check if its exit key combination
		if ( nextchar == '.' )
			break;
		
		// try to write symbol
		if (fputc( nextchar , outfile) == EOF)
		{
			error = 1; 
			break;
		}
		//printf("\nchar got: %i\n", nextchar);
	}
	// end
	//puts("Wow! Eok!");
	if (error)
		fputs("Error occured!", stderr);
	// return input
	system("/bin/stty cooked");
	
	// close file
	if (fclose(infile))
		fputs("Error while file close occured!\n", stderr);	

	return 0;
}
