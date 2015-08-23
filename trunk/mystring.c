#include "mystring.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void build_string(string* s)
{
  s->size=0;
  s->capacity=MYSTRING_DEFAULT_CAPACITY;
  s->ptr=malloc(s->capacity*sizeof(*(s->ptr)));
  memset(s->ptr,'\0',s->capacity);
}

void destruct_string(string* s)
{
  s->size=s->capacity=0;
  free(s->ptr);
}
/*===========================*/
int size(string s)
{
  return s.size;
}
int capacity(string s)
{
  return s.capacity;
}

const char* get_str(string s)
{
  return s.ptr;
}

void print_string(string s)
{
    printf("%s \n",s.ptr);
}
/*===========================*/
void append_string(string* s,const char* c)
{
  int append_size=strlen(c);
  int i=0;
  if((s->size+strlen(c))>(s->capacity-1))
    {
      reserve(s,s->capacity+append_size+MYSTRING_DEFAULT_CAPACITY);
      memset(s->ptr+s->size,'\0',append_size+MYSTRING_DEFAULT_CAPACITY);
    }

  for(i=0;i<append_size;++i)
    {
      s->ptr[s->size]=c[i]; 
      s->size++;
    }
}

void reserve(string* s,int new_capa)
{  
  char* tmp = realloc (s->ptr,new_capa*sizeof(*tmp));

      if (tmp != NULL)
      {
         s->ptr = tmp;
	 s->capacity=new_capa;
      }
      else
      {
         /* l'ancien bloc est valide, mais il n'a pas ete agrandi */
      }
}

void pop_string(string* s)
{
    if(size(*s)!=0)
      {
          s->size--;
          s->ptr[s->size]='\0';
      }
}


char* stringify_int(int i)
{
    char* tmp=malloc(10*sizeof(char));
    memset(tmp,'\0',10);
    sprintf(tmp,"%d",i);
    return tmp;
}


