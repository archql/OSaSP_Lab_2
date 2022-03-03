#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <dirent.h>

#include <string.h>

#include <limits.h> // here is PATH_MAX

#include <time.h> 

int findFile( char *dirname, const char *filename, int *ctr_visited )
{
	// get dir
	DIR * dir_cur = opendir(dirname);  
	// try dirs
	if (!dir_cur)
		return 0;
	// find loop
	struct dirent *d;
	while (d = readdir(dir_cur))
	{
		// visit file
		char *cur_elname = d->d_name;
		
		//printf("Cur: %s %s %i \n", cur_elname, filename, strcmp(cur_elname, filename));
		// check if its dir
		if ( d->d_type & DT_DIR && strcmp(cur_elname, ".") && strcmp(cur_elname, "..") )
		{
			// prepare new path string 
			char path[PATH_MAX];
			if (snprintf(path, PATH_MAX, "%s/%s", dirname, cur_elname) < 0)
				return 0;
			// visit it recursively
			if (findFile(path, filename, ctr_visited))
				return 1;
		}
		else if ( d->d_type & DT_REG && !strcmp(cur_elname, filename) )
		{
			// check if its file & name equals requested
			return 1;
		} 
		
		// go next
		(*ctr_visited)++;
	}
	
	// close dirs
	if (closedir(dir_cur))
		fputs("Error while dir close occured!\n", stderr);
		
	return 0;	
}

void strmode(mode_t mode, char *perm)
{
	for (int i = 0; i < 10; i++)
		perm[i] = '-'; 	
	if (mode & 0400)
		perm[1] = 'r';  	
	if (mode & 0200)
	  	perm[2] = 'w';
	if (mode & 0100)
	  	perm[3] = 'x';
	if (mode & 0040)
	  	perm[4] = 'r';
	if (mode & 0020)
	  	perm[5] = 'w';
	if (mode & 0010)
	  	perm[6] = 'x';
	if (mode & 0004)
	  	perm[7] = 'r';
	if (mode & 0002)
	  	perm[8] = 'w';
	if (mode & 0001)
	  	perm[9] = 'x';
}


int main( int argc , char *argv[ ] , char *envp[ ] )
{
	// check if it is enough params passed
	if (argc != 3)
	{
		fputs("Wrong args! Format: Task_i_2.exe [dir from which search start] [filename to search]\n", stderr);
		return -1;
	}
	// get ptr to filename
	char *filename = argv[2];
	// check if not null
	//if ( !(*filename) )
	//{
	//	fputs("Wrong args!\n", stderr);
	//	return -1;
	//}
	// try to read cur dir
	int ctr_visited = 0;
	// find 
	if ( findFile( argv[1] ,filename , &ctr_visited ) )
	{
		printf("file %s founded!\n", filename);
		printf("visited %i records!\n", ctr_visited);
		puts("File stats: ");
		// try to get access rights
		struct stat bufstat;
		if ( lstat( filename, &bufstat ) )
		{
			fputs("Cant read file stats!\n", stderr);
			return -1;
		}
		// try to get rights as str
		char modebuf[16] = { 0 };
		strmode(bufstat.st_mode, modebuf);
		// get realpath to file
		char realpathbuf[PATH_MAX];
		if (realpath(filename, realpathbuf))
			printf("\tFull path:\t%s\n", realpathbuf);
		else
			printf("\tFull path:\tCan not resolve full path!\n");
		// get date
		char *date = ctime(&bufstat.st_ctime);
		printf("\tDate of birth:\tIsn't supported!\n");
		if (date)
			printf("\tDate st change:\t%s", date);
		else
			printf("\tDate st change:\tfailed to recognize\n");
		// print stats
		printf("\tDesc No:\t%lu\n",  bufstat.st_ino);
		printf("\tAccess rights:\t%s\n",  modebuf);
		printf("\tSize:\t\t%li bytes\n", (bufstat.st_size) );
		
		
		
	}
	else
	{
		puts("file not founded!");
	}

	return 0;
}
