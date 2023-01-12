#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void tree(char* path, int l)
{
    int nRows = 30, nCol = 30, len = 0, nTem = 50;

    char *dirName = malloc(100* sizeof(char));
    char *temp = malloc(nTem * sizeof(char));
    char **tempArr = malloc(nRows * sizeof(char*));
    for (int i = 0; i < nRows; i++)
    {
        tempArr[i] = malloc(nCol * sizeof(char));
    }
    struct stat buff;
    DIR *dir = opendir(path);
    struct dirent *p;

    if (dir == NULL)
    {
        closedir(dir);

        free(temp);
        for (int i = 0; i < nRows; i++)
        {
            free(tempArr[i]);
        }
        free(p);
        free(tempArr);
        free(dirName);

        return;
    }
    
    if((p = readdir(dir)) != NULL)
        l++;

    while ((p = readdir(dir)) != NULL)
    {
        if (p->d_name[0] != '.')
        {
            strcpy(tempArr[len], p->d_name);
            len++;
        }
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (strcasecmp(tempArr[i], tempArr[j]) > 0)
            {
                strcpy(temp, tempArr[i]);
                strcpy(tempArr[i], tempArr[j]);
                strcpy(tempArr[j], temp);
            }
        }
    }
    
    for (int i = 0; i < len; i++)
    {
        strcpy(dirName, path);
        strcat(dirName, "/");
        strcat(dirName, tempArr[i]);

        for(int i=0; i<l; i++)
        {
            printf("  ");
        }
        DIR *dir2 = opendir(dirName);
        if(dir2 == NULL)
        {
            for (int i = 0; i < len; i++)
            {
                if(i!=0)
                {
                    for(int i=0; i<l; i++)
                    {
                        printf("  ");
                    }
                }
                printf("- %s\n", tempArr[i]);
            }
            closedir(dir2);
            break;
        }
        else
        {
            closedir(dir2);
            printf("- %s\n", tempArr[i]);
            tree(dirName, l);
        }
    }

    free(temp);
    free(p);
    for (int i = 0; i < nRows; i++)
    {
        free(tempArr[i]);
    }
    free(tempArr);
    free(dirName);
    closedir(dir);
}

int main(char argc, char *argv[])
{
    printf(".\n");
    tree("/common/home/php51/Documents/cs214", -1);
    return 0;
}