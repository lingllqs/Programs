#include <stdio.h>
#include <dirent.h>


int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: ls <directory>\n");
        return 0;
    }

    DIR *dir = NULL;
    struct dirent *dirent = NULL;

    dir = opendir(argv[1]);
    if (dir == NULL) {
        perror("opendir");
        return 0;
    }
    while ((dirent = readdir(dir)) != NULL) {
        printf("%s ", dirent->d_name);
    }

    closedir(dir);
    return 0;
}
