#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//my global file
char in[100];
int Size_Of_FILE;

FILE *the_infected;

void PrintHex(char buffer[], int length){
    for(int i = 0; i < length; i++)
        printf("%hhX ", buffer[i]);
}    

typedef struct virus {
    unsigned short SigSize;
    char virusName[16];
    char sig[];
} virus;

typedef struct link link;  
struct link {
    link *nextVirus;
    virus *vir;
};

//global list 
link * l;

link* list_print(link *virus_list){
    printf("\n");
    while ( virus_list != NULL) {
         printf("virus name: %s\n", virus_list->vir->virusName);
         printf("virus size: %d ", virus_list->vir->SigSize);
         printf("\n");
         printf("signature: ");
         int size= (virus_list->vir->SigSize);
         PrintHex(virus_list->vir->sig,size);
         printf("\n");
          printf("\n");
         virus_list = virus_list->nextVirus;
     }
     return virus_list;
    
};

link* link_print(link *virus_list){
     printf("\n");
     printf("virus name: %s\n", virus_list->vir->virusName);
     printf("virus size: %d ", virus_list->vir->SigSize);
     printf("\n");
     printf("signature: ");
     int size= (virus_list->vir->SigSize);
     PrintHex(virus_list->vir->sig,size);
     printf("\n");

    return virus_list;
}


link * list_append(link* virus_list, virus* data){
    link * newLink = (malloc(sizeof(link)));
    newLink->vir=data;
    newLink->nextVirus=virus_list;
    
    return newLink;
    
}


/* Free the memory allocated by the list. */
void list_free(link *virus_list){
    if(virus_list != NULL) {
        free(virus_list->vir);
        list_free(virus_list->nextVirus);
        free(virus_list);
    }
}



link* loadSig(link* c){
    if(l!=NULL){
        list_free(l);
        l=NULL;
    }
    
    FILE * inp;
    char input_file[100];
    
    unsigned char num[2];
    fgets(input_file, 100, stdin);
    sscanf(input_file , "%s",input_file);
    virus* v;
    inp=fopen(input_file,"r+");
    
    if(inp== NULL){
         perror("fopen");
         exit(1);
    }
    //Get file length
    ftell(inp);
	size_t start=fseek(inp, 0, SEEK_END);
    size_t length=ftell(inp);
    Size_Of_FILE=length;
	fseek(inp, start, SEEK_SET);
     
    while(1){
        int read = fread(num, sizeof(char), 2, inp);
        if(read == 0)
            break;
        v =  malloc(sizeof(struct virus) + sizeof(char)*(num[0]+num[1]*256-18));
        v->SigSize=num[0]+num[1]*256-18;
        fread(v->virusName, sizeof(char), 16, inp);
        fread(v->sig, sizeof(char), v->SigSize, inp);
        l= list_append(l,v);
        
    }
    fclose(inp);  
    return l;
}


// 


 void detect_virus(char *buffer, unsigned int size){
    
    while(l!=NULL){
        int virusSize=l->vir->SigSize;
        int position;
       
        for(int j=0; j<(size-virusSize-1); j++){
               
            if(memcmp(l->vir->sig, buffer+j,virusSize)==0){
                position=j;
                printf("the starting byte location: %d \n", position);
                printf("virus name: %s\n", l->vir->virusName);
                printf("virus size: %d\n ", virusSize);
                printf("\n");
                
            } 
                
        }
        l=l->nextVirus;
        if(l!=NULL){
            virusSize=l->vir->SigSize;
        }
    }
    
    
 	free(buffer);
     
 }

link* detect(link* c){
    int maxSize=Size_Of_FILE;
   
    fseek(the_infected, 0, SEEK_END);
    long fsize = ftell(the_infected);
    fseek(the_infected, 0, SEEK_SET);  /* same as rewind(f); */
    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, the_infected);
    fclose(the_infected);
    string[fsize] = 0;

    if(Size_Of_FILE>fsize){
        maxSize=fsize;
    }

    detect_virus(string, maxSize);
    return c;    
}





link* quit(link* c){
    list_free(c);
     exit(0);
     return 0;
}
    
struct fun_desc {
  char *name;
  link* (*fun)(link*);
};



struct fun_desc displayNUM[]= {{"Print all List",list_print},{"Print link",link_print}, {NULL, NULL}};

link* printSig(link* c){
   int func_option;
   char m;
    for (int i = 0; i < 2; ++i)
            printf("%i) %s\n", i, displayNUM[i].name);
    
    m= fgetc(stdin);
    fgetc(stdin);
    if((m>='0') && (m<='1')){
        func_option=atoi(&m);
        l = displayNUM[func_option].fun(l);
        
    }
    else{
        if(m!='\n'){
            printf("Not within bounds\n");
            quit(l);
        }           
    }
    return c;
}

struct fun_desc menu_display[] = {{"Load signatures", loadSig}, {"Print signatures", printSig}, {"Detect viruses",detect }, {"Quit", quit}, {NULL, NULL}};


char *getfname(void *p){
    for (int i = 0; i <4; i++) {
        if ( menu_display[i].fun == p)
            return menu_display[i].name;
        }
        return NULL;
};
 char *getfnameNUM(void *p){
     for (int i = 0; i <2; i++) {
        if ( displayNUM[i].fun == p)
             return displayNUM[i].name;
         }
         return NULL;
};

int main  (int argc, char **argv) {
    
    int func_option;
    int true= 1;
    char c;
    
    char *input_file=argv[1];
    
    the_infected= fopen(input_file, "r+");
    
    while(true==1){
        for (int i = 0; i < 4; ++i)
            printf("%i) %s\n", i+1, menu_display[i].name);
        
        c= fgetc(stdin);
        fgetc(stdin);
       if((c>='1') && (c<='4')){
           func_option=atoi(&c)-1;
           l = menu_display[func_option].fun(l);
       }
       else{
           if(c!='\n'){
                printf("Not within bounds\n");
                quit(l);
            }           
        }
    
    }
    
    fclose(the_infected);

    return 0;
}



