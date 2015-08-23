#include "level.h"
#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include <string.h>

#define MAX_SIZE 500

/*premiere fonction de chargement de niveau*/
level* load_level2(const char* name)
{
    FILE* flevel=fopen(name,"r");
    level* l=malloc(sizeof(*l));
    int x=0,y=0,i=0,size=0;
    
    if(NULL==flevel)
    {
                printf("Impossible d'ouvrir le fichier %s",name);
		return 0;
    }
    
    fscanf(flevel,"%d",&size);

    l->size=size;
    l->points=malloc(size*sizeof(point));

    while(fscanf(flevel,"%d %d",&x,&y)!=EOF)
    {
	l->points[i].x=x;
	l->points[i].y=y;
	++i;
    }
    
    fclose(flevel);
    
    return l;
}

void destroy_level(level* l)
{
    free(l->points);
    free(l);
}

void save_level(level l,const char* name)
{

}


void get_int(int *x,char separator,FILE* flevel,char* currentchar)
{
    int j=0;
    char* str_char=malloc(MAX_SIZE*sizeof(char));
    memset(str_char,'\0',MAX_SIZE);
    while (*currentchar != separator){
	str_char[j]=*currentchar;
	*currentchar=fgetc(flevel);
	j++;
    }
    
    *x=atoi(str_char);
    free(str_char);
}

/*fonction de chargement de niveau a partir d'un fichier*/
level* load_level(const char* name){

	FILE* flevel = NULL;
	char currentchar;
	int get_size=0;
	int i=0;
	string str;
	level* l=malloc(sizeof(*l));

	build_string(&str);
	append_string(&str,"./data/level/");
	append_string(&str,name);

	flevel = fopen(str.ptr,"r");
 	
	if (flevel != NULL){
		
	    currentchar=fgetc(flevel);
	
	    while (currentchar != EOF){
		if(currentchar=='#'){
		    while (currentchar!='\n'){
			currentchar=fgetc(flevel);
		    }
		}
		else{ 
		    if(get_size==0){
			get_int(&(l->size),'\n',flevel,&currentchar);
			get_size=1;
			l->points=malloc(l->size*sizeof(point));
		    }
		    else if(get_size==1){
			get_int(&(l->points[i].x),' ',flevel,&currentchar);					
			get_int(&(l->points[i].y),'\n',flevel,&currentchar);
			i++;
		    }
		}
		currentchar=fgetc(flevel); 			
	    }
	    fclose(flevel);
	    return l;
    	}
    	else
    	{
        	
	    printf("Impossible d'ouvrir le fichier");
	    return NULL;
    	}
}




