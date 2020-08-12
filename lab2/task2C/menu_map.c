
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

    
int main(int argc, char **argv){
    return 1;
}
