#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

void search(char *find, const char *path);

int main(int argc, char *argv[])
{
    search(argv[1], ".");
}

void search(char *find, const char* path)
{
    int nRows = 30, nCol = 30, len = 0;
    char* dirName = (char*) malloc(100* sizeof(char));
    DIR *dir = opendir(path);
    struct dirent *p;
    char **tempArr = malloc(sizeof(char*)*nRows);
    for (int i = 0; i < nCol; i++)
    {
        tempArr[i] = malloc(30 * sizeof(char));
    }

    if(!dir)
    {
        free(dirName);
        for (int i = 0; i < nRows; i++)
        {
            free(tempArr[i]);
        }
        free(tempArr);
        return;
    }

    while((p=readdir(dir)) != NULL)
    {
        if (p->d_name[0] != '.')
        {
            strcpy(tempArr[len], p->d_name);
            len++;
        }
    }

    for(int i=0; i<len; i++)
    {
        strcpy(dirName, path);
        strcat(dirName, "/");
        strcat(dirName, tempArr[i]);

        if(strstr(tempArr[i], find))
        {
            printf("%s/%s\n",path, tempArr[i]);
        }
        else
        {
            search(find, dirName);
        }
    }

    closedir(dir);
    free(dirName);
    free(p);
    for (int i = 0; i < nRows; i++)
    {
        free(tempArr[i]);
    }
    free(tempArr);
}