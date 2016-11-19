#include <stdio.h>
#include <string.h>
#include <math.h>
#define IN 99
int N = 100;
struct tile {
    int dist;
    int selected;
    int type;
    int prev;
    };

int convert(int i,int j){
    return N*i + j;
    }

 void printAllPaths(int u,int d, int path[],struct tile tiles[N*N],int path_index,int min[],int *minlen)
 {
        int i;
        tiles[u].selected = 1;
        path[path_index] = u;
        path_index++;
        
        if(u==d)
            {
                if(path_index<*minlen || *minlen==0){
                    
                    for(i=0;i<path_index;i++){
                        min[i] = path[i];
                        }
                    *minlen = path_index+1;
                    }
                    
                    
                for(i=0;i<path_index;i++)
                {
                    printf("%d ",path[i]);
                }
                printf("\n");
            }
        else
            {
                if( tiles[u-N].type!=1 && tiles[u-N].selected==0)
                {
                    printAllPaths(u-N,d,path,tiles,path_index,min,minlen);
                }
                 if( tiles[u+N].type!=1 && tiles[u+N].selected==0)
                {
                    printAllPaths(u+N,d,path,tiles,path_index,min,minlen);
                }
                 if( tiles[u-1].type!=1 && tiles[u-1].selected==0)
                {
                    printAllPaths(u-1,d,path,tiles,path_index,min,minlen);
                }
                 if( tiles[u+1].type!=1 && tiles[u+1].selected==0)
                {
                    printAllPaths(u+1,d,path,tiles,path_index,min,minlen);
                }
            }
        
path_index--;
tiles[u].selected=0;
}


int main(){
    struct tile tiles[N*N];
    int min[1000];
    int minlen = 0;
    int path[1000];
    int i,j,source,target;
    char temp;
    char f[100];
    char f2[100]="..\\";
    for(i=0;i<N*N;i++){
        tiles[i].dist = IN;
        tiles[i].selected = 0;
        tiles[i].prev = -1;
        tiles[i].type = 0;
        }
    FILE *fp;
    printf("Enter the name of the text file you want to read : \n");
    scanf("%s",f);
    strcat(f2,f);
    fp = fopen(f2,"r");
    fscanf(fp,"%d",&N);
    fgetc(fp);
    for(i=0;i<N;i++){
        for(j=0;j<N+1;j++){
           temp = fgetc(fp);
            if(temp == 'X'&&j<N)tiles[convert(i,j)].type = 1;
            else if(temp=='S'&&j<N)source = convert(i,j);
            else if(temp=='E'&&j<N)target = convert(i,j);
            }
        }
    fclose(fp);
     for(i=0;i<N;i++){
        for(j=0;j<N+1;j++){
            if(tiles[convert(i,j)].type==1&&j<N)
                printf("X ");
            else if(convert(i,j)==source)printf("S ");
            else if(convert(i,j)==target)printf("E ");
            else {if(j<N) printf("_ ");}
            }
            printf("\n");
        }
    printAllPaths(source,target,path,tiles,0,min,&minlen);
    printf("\n");
    for(i=0;i<minlen;i++){
        printf("%d ",min[i]);
        }
    return 0;
    }
