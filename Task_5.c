#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <dirent.h>


int main( int argc , char *argv[ ] , char *envp[ ] )
{
	DIR * dir_cur   = opendir(".");  
	DIR * dir_root  = opendir("/");  
	// try dirs
	if (!dir_cur || !dir_root)
	{
		fputs("Cant open dir!\n", stderr);
		return -1;
	}
	fputs("Dirs open success!\n", stderr);
	// try to read cur dir
	struct dirent *d;
	puts("> CALL ls -1 . (c equvalent)");
	while (d = readdir(dir_cur))
	{
		puts(d->d_name);
	}
	// try to read root dir
	puts("> CALL ls -1 / (c equvalent)");
	while (d = readdir(dir_root))
	{
		puts(d->d_name);
	}
	// close dirs
	if (closedir(dir_cur) || closedir(dir_root))
		fputs("Error while dir close occured!\n", stderr);	

	return 0;
}
