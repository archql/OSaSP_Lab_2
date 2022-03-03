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
	char *filename_in  = argv[1];
	char *filename_out = argv[2];
	// check if not null
	if ( !(*filename_in) || !(*filename_out) )
	{
		fputs("Wrong args!\n", stderr);
		return -1;
	}
	// try to open files
	FILE* file_in  = fopen (filename_in , "r");
	FILE* file_out = fopen (filename_out, "w");
	if (!file_in || !file_out)
	{
		fputs("Cant open file!\n", stderr);
		return -1;
	}
	fputs("Files open success!\n", stderr);
	// try to get access rights
	struct stat bufstat;
	if ( stat( filename_in, &bufstat ) )
	{
		fputs("Cant read file stats!\n", stderr);
		return -1;
	}
	// try to set file stats
	if ( chmod( filename_out, bufstat.st_mode ) )
	{
		fputs("Cant set file stats!\n", stderr);
		return -1;
	}
	// other code
	int nextchar;
	while ( (nextchar = fgetc(file_in)) != EOF ) 
	{
		// print char to file 
		if (putc(nextchar, file_out) == EOF)
		{
			fputs("Cant write to file!\n", stderr);
			return -1;
		}
	}
	// end
	puts("Operation ended!");
		
	// close file
	if (fclose(file_out) || fclose(file_in))
		fputs("Error while file close occured!\n", stderr);	

	return 0;
}
