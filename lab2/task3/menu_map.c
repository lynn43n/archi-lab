
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
char censor(char c) {
  if(c == '!')
    return '.';
  else
    return c;
}
 
char* map(char *array, int array_length, char (*f) (char)){
char* mapped_array = (char*)(malloc(array_length*sizeof(char)));


  for ( int i= 0 ; i < array_length; i++){
        mapped_array[i]= f(array[i]);
  }
    return mapped_array;
}


/* Gets a char c and returns its encrypted form by adding 3 to its value. If c is not between 0x20 and 0x7E it is returned unchanged */
char encrypt(char c){
    if((c>=0x20) && (c<=0x7E)){
    return c+3;
    }
  else
    return c;
}
          
/* Gets a char c and returns its decrypted form by reducing 3 to its value. If c is not between 0x20 and 0x7E it is returned unchanged */
char decrypt(char c){
    if((c>=0x20) &&(c<=0x7E))
        return c-3;
    else
        return c;
}

/* xprt prints the value of c in a hexadecimal representation followed by a new line, and returns c unchanged. */
char xprt(char c){
    printf("0X%X\n", (unsigned char)c);
    return c;
}

/* If c is a number between 0x20 and 0x7E, cprt prints the character of ASCII value c followed by a new line. Otherwise, cprt prints the dot ('.') character. After printing, cprt returns the value of c unchanged. */
char cprt(char c){
     if((c>=0x20) && (c<=0x7E)){
         printf("%c\n",c);
         return c;
     }
     else{
         printf("%c\n",'.');
         return c;
    }
}

/* Ignores c, reads and returns a character from stdin using fgetc. */
char my_get(char c){
    char output;
    output = fgetc(stdin);
    return output;
}

/* Gets a char c, and ends the program returning 0 */
char quit(char c){
    exit(0);
    return 0;
}
 
/*-------------------PART3-------------- */

#define FNUM 3
struct fun_desc {
  char *name;
  char (*fun)(char);
};

struct fun_desc menu_display[] = { { "Censor", censor}, {"Encrypt",encrypt}, {"Decrypt",decrypt}, { "Print hex",xprt}, { "Print String",cprt}, { "Get string", my_get}, { "Quit",quit},{ NULL, NULL }};

char *getfname(void *p){
    for (int i = 0; i <7; i++) {
        if ( menu_display[i].fun == p)
            return menu_display[i].name;
        }
        return NULL;
}


int menu(){
char *pointer;
char *carray =(char*)(malloc(5));
int func_option;
char c;
int true=1;
    
while(true==1){
    printf( "Please choose a function:\n");
    for (int i = 0; i < 7; ++i){
        printf("%i) %s\n", i, menu_display[i].name);
        }       
        c= fgetc(stdin);
        fgetc(stdin);
        if((c>='0') && (c<='6')){
            pointer = carray;
            func_option=atoi(&c);
            printf("Option: %d\n",func_option);
            printf("Within bounds\n");
            carray= map(pointer,(sizeof(carray)+1)/sizeof(char), menu_display[func_option].fun);
         //   printf("%s\n", carray);
            printf("DONE.\n");
            free(pointer);
           
        }
        else{ 
            if(c!='\n'){
                printf("Not within bounds\n");
                 free(carray);
                exit(0);
            }
        }
}
    return 0;    
}
    
    
int main(int argc, char **argv){
          menu();
 
    return 1;
}
