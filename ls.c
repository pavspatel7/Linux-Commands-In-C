#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int nRows = 30, nCol = 30, len =0, nTem = 50;

    char *temp = malloc(nTem*sizeof(char));
    char **tempArr = malloc(nRows*sizeof(char*));
    for(int i=0; i<nRows; i++)
    {
        tempArr[i] = malloc(nCol*sizeof(char));
    }
    DIR *dir = opendir(".");
    struct dirent *p;

    if(dir == NULL)
    {
        perror("Unable to open directory!");
    }
    
    while((p=readdir(dir) )!= NULL)
    {
        if (p->d_name[0] != '.')
        {
            strcpy(tempArr[len], p->d_name);
            len++;
        }
    }

    for(int i = 0; i< len; i++)
    {
        for(int j = i+1; j<len;j++)
        {
            if(strcasecmp(tempArr[i],tempArr[j]) > 0)
            {
                strcpy(temp, tempArr[i]);
                strcpy(tempArr[i], tempArr[j]);
                strcpy(tempArr[j], temp);
            }
        }
    }

    if(argc==1)
    {
        
        for(int i = 0; i<len; i++)
        {
            printf("%s\n", tempArr[i]);
        }
    }
    else if(argc==2 && strstr(argv[1], "-l"))
    {
       struct stat buff;
       struct passwd *pws;
       struct group *grp;
       char *a = malloc(sizeof(char)*30);
       for(int i=0; i<len; i++)
       {
            stat(tempArr[i], &buff);

            if(S_ISREG(buff.st_mode))
                printf("-");
            else
                printf("d");


            if(buff.st_mode & S_IRUSR)
                printf("r");
            else
                printf("-");
            if(buff.st_mode & S_IWUSR)
                printf("w");
            else
                printf("-");
            if(buff.st_mode & S_IXUSR)
                printf("x");
            else
                printf("-");


            if(buff.st_mode & S_IRGRP)
                printf("r");
            else
                printf("-");
            if(buff.st_mode & S_IWGRP)
                printf("w");
            else
                printf("-");

            if(buff.st_mode & S_IXGRP)
                printf("x");
            else
                printf("-");


            if(buff.st_mode & S_IROTH)
                printf("r");
            else
                printf("-");
            if(buff.st_mode & S_IWOTH)
                printf("w");
            else
                printf("-");
            if(buff.st_mode & S_IXOTH)
                printf("x");
            else
                printf("-");

            pws = getpwuid(buff.st_uid);
            grp = getgrgid(buff.st_gid);

            printf(" %s %s %5ld", pws->pw_name, grp->gr_name, buff.st_size);
            
            strcpy(a, ctime(&buff.st_mtime));
            for(int i=3; i<16; i++)
            {
                printf("%c", a[i]);
            }
            printf(" %s\n", tempArr[i]);
        }
        free(a);
    }

    free(temp);
    for(int i = 0; i<nRows; i++)
    {
        free(tempArr[i]);
    }
    free(tempArr);
    closedir(dir);

    return 0;
}