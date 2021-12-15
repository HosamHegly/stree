/* nftw_dir_tree.c
   Demonstrate the use of nftw(3). Walk though the directory tree specified
   on the command line (or the current working directory if no directory
   is specified on the command line), displaying an indented hierarchy
   of files in the tree. For each file, display:
      * a letter indicating the file type (using the same letters as "ls -l")
      * a string indicating the file type, as supplied by nftw()
      * the file's i-node number.
*/
#define _XOPEN_SOURCE 600 /* Get nftw() */
#include <ftw.h>
#include <sys/types.h>    /* Type definitions used by many programs */
#include <stdio.h>        /* Standard I/O functions */
#include <stdlib.h>       /* Prototypes of commonly used library functions,
                             plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>       /* Prototypes for many system calls */
#include <errno.h>        /* Declares errno and defines error constants */
#include <string.h>       /* Commonly used string-handling functions */
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#define FTW_ACTIONRETVAL 16

#define _GNU_SOURCE 
# define FTW_SKIP_tree  2
   
int numdir=0,numfiles=0;

int arr [100000];
void count( const char * pathname, int x)
{
int file_count = 0;
DIR * dirp;
struct dirent * entry;

dirp = opendir(pathname); /* There should be error handling after this */
while ((entry = readdir(dirp)) != NULL) {

         arr[x]++;
    
}
 arr[x]=arr[x]-2;
closedir(dirp);

}

static int              /* Callback function called by ftw() */
dirTree(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb)
{
    if(ftwb->level == 0){
    printf("%s\n",  &pathname[ftwb->base]); 
     count(&pathname[ftwb->base],ftwb->level+1); }  /* Print basename */
    else{

   

    
    

    
    
      
    if (type == FTW_NS) {                  /* Could not stat() file */
        printf("?");
    } else {
    

     
      
     if(type == FTW_F)
     numfiles++;
     if(type == FTW_D){
          count(&pathname[ftwb->base],ftwb->level+1);
          numdir++;
     }
    int counter=0, lvl=1;
    counter = ftwb->level;
    while(counter>1){
    if(arr[lvl]>0)
     printf("│");
     else {printf(" ");}
     lvl++;
    printf("%*s",3, " "); 
    counter--;}
  
   
    if(arr[ftwb->level]==1)
    printf("└──");
    else
    printf("├──");
    printf(" ");     
    printf("[");
    arr[ftwb->level]--;
        switch (sbuf->st_mode & S_IFMT) {  /* Print file type */
        case S_IFREG:  {     printf("-"); break;}
        case S_IFDIR:  {     printf("d"); break;}
        case S_IFCHR:  printf("c"); break;
        case S_IFBLK:  printf("b"); break;
        case S_IFLNK:  printf("l"); break;
        case S_IFIFO:  printf("p"); break;
        case S_IFSOCK: printf("s"); break;
        default:       printf("?"); break; /* Should never happen (on Linux) */
        }
        printf( (sbuf->st_mode & S_IRUSR) ? "r" : "-");
    printf( (sbuf->st_mode & S_IWUSR) ? "w" : "-");
    printf( (sbuf->st_mode & S_IXUSR) ? "x" : "-");
    printf( (sbuf->st_mode & S_IRGRP) ? "r" : "-");
    printf( (sbuf->st_mode & S_IWGRP) ? "w" : "-");
    printf( (sbuf->st_mode & S_IXGRP) ? "x" : "-");
    printf( (sbuf->st_mode & S_IROTH) ? "r" : "-");
    printf( (sbuf->st_mode & S_IWOTH) ? "w" : "-");
    printf( (sbuf->st_mode & S_IXOTH) ? "x" : "-");
    }
struct group *grp;
struct passwd *pwd;

    if (type != FTW_NS) {

        if ((pwd = getpwuid(sbuf->st_uid)) != NULL)
           printf(" %-8.8s", pwd->pw_name);
        if ((grp = getgrgid(sbuf->st_gid)) != NULL)
           printf(" %-8.8s", grp->gr_name);
        printf("%7ld ", (long) sbuf->st_size);
                printf("]");
          
        }
    else
        printf("        ");
	
    
    printf("  %s\n",  &pathname[ftwb->base]);  }   /* Print basename */
    return 0;                                   /* Tell nftw() to continue */
}

int
main(int argc, char *argv[])
{

    int flags = FTW_CHDIR 
;

    

    if (nftw((argc<2)? "." : argv[1], dirTree, 10, flags) == -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }
    printf("\n");
    printf("%d directories, %d files", numdir,numfiles);
        printf("\n");
    exit(EXIT_SUCCESS);
}
