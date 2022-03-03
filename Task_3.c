#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main( int argc , char *argv[ ] , char *envp[ ] )
{
	// check if it is enough params passed
	if (argc != 3)
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
	// try to get num of lines
	int linesnum = 0;
	if (sscanf( argv[2], "%i", &linesnum ) != 1)
	{
		fputs("Cant read num of lines!\n", stderr);
		return -1;
	}
	// try to open file
	printf("try to open file %s...\n", filename);
	//int outfile = open (filename, O_CREAT, 644);
	FILE* infile = fopen (filename, "r");
	if (!infile)
	{
		fputs("Cant open file!\n", stderr);
		return -1;
	}
	fputs("File open success!\n", stderr);
	puts("[started]");
	// other code
	int linesctr = 0;
	while (1) 
	{
		int nextchar = fgetc(infile);
		
		if ( nextchar == EOF ) 
		{
			break;
		}
		if ( linesnum && (nextchar == '\n') && !(++linesctr % linesnum) )
		{
			// desired pack of lines printed, wait
			printf("\n[Next %i lines printed. Press any key to continue...]", linesnum);
			getchar();
			continue;
		}
		
		// print char
		putchar(nextchar);
	}
	// end
	puts("[Ended]");
		
	// close file
	if (fclose(infile))
		fputs("Error while file close occured!\n", stderr);	

	return 0;
}
