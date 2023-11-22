#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc , char * argv[]){
    DIR *dir;
    dir=opendir(".");
    struct dirent *dp;
    while( (dp=readdir(dir)) !=0 )
    {
        printf("name: %s  \n",dp->d_name);
    

           struct stat sb;
           stat(dp->d_name, &sb);
           printf("name:                     %s\n", dp->d_name);
           printf("I-node number:            %ju\n", (uintmax_t) sb.st_ino);

           printf("Mode:                     %jo (octal)\n",
                  (uintmax_t) sb.st_mode);

           printf("Link count:               %ju\n", (uintmax_t) sb.st_nlink);
           printf("Ownership:                UID=%ju   GID=%ju\n",
                  (uintmax_t) sb.st_uid, (uintmax_t) sb.st_gid);

           printf("Preferred I/O block size: %jd bytes\n",
                  (intmax_t) sb.st_blksize);
           printf("File size:                %jd bytes\n",
                  (intmax_t) sb.st_size);
           printf("Blocks allocated:         %jd\n",
                  (intmax_t) sb.st_blocks);

           printf("Last status change:       %s", ctime(&sb.st_ctime));
           printf("Last file access:         %s", ctime(&sb.st_atime));
           printf("Last file modification:   %s", ctime(&sb.st_mtime));
    }
    closedir(dir);
    
	return 0;
}