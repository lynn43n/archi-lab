#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	int counter=0;
	int debug=0;
	int add=0;
	int sub=0;
	int itsKey=0;
    int fileIn=0;
    int fileOut=0;
    char c;
	
	FILE * input=stdin;	
  	FILE * output=stdout;

	char * key;
	char * in;
	char * out;
	
    
    //flags input
	for(int i=1; i<argc; i++){
        
        if(strcmp(argv[i],"-D")==0){
          debug=1;
        }
        else if(strncmp(argv[i],"+e",2)==0){
            key= argv[i]+2;
            itsKey=1;
            add=1;
        }
         else if(strncmp(argv[i],"-e",2)==0){
            key= argv[i]+2;
            itsKey=1;
            sub=1;
        }
         else if(strncmp(argv[i],"-i",2)==0){
            fileIn=1;
            in= argv[i]+2;
            input=fopen(in,"r");
        }
         else if(strncmp(argv[i],"-o",2)==0){
            fileOut=1;
            out= argv[i]+2;
            output=fopen(out,"w");
        }
        else{
            printf("invalid parameter - %s\n",argv[i]);
            break;
        }
}


    if(debug==1){
        fputc('-', stderr);
        fputc('D', stderr);
        fputc('\n', stderr);
        
        if(add==1){
            fputc('+', stderr);
            fputc('e', stderr);
                for(int i=0;i<strlen(key);i++){
                    fputc(key[i], stderr);
                }
             fputc('\n', stderr);
        
        }
        else if(sub==1){
            fputc('-', stderr);
            fputc('e', stderr);
                for(int i=0;i<strlen(key);i++){
                    fputc(key[i], stderr);
                    
                }
             fputc('\n', stderr);
        }
    if(fileIn==1){
        fputc('-', stderr);
        fputc('i', stderr);
        
         for(int i=0;i<strlen(in);i++){
                 fputc(in[i], stderr);   
        }
             fputc('\n', stderr);
    }
    if(fileOut==1){
        fputc('-', stderr);
        fputc('o', stderr);
        for(int i=0;i<strlen(out);i++){
                 fputc(out[i], stderr);
            }
             fputc('\n',stderr);
    }
}

//check that i got a key 
  if(sizeof(key)==0){
            itsKey=0;
    }

while((c=fgetc(input))!=EOF){
    
    if(debug==1){
        fprintf(stderr, "0x%02x\t",c);
    }
    
    if(itsKey==1){
          if(add==1){
               c=c+ key[counter%strlen(key)];
               
          }
          else{
               c=c- key[counter%strlen(key)];
          }
          counter++;
            
        }else if((c>= 'A') && (c<='Z')){
                c= c+ ('a'-'A');
               
            }
        
        if(debug==1){
         //print the hex   
            fprintf(stderr, "0x%02x\n",c);
        }
        
    fputc(c, output);
    
    while((c=fgetc(input))!='\n'){
        if(debug==1){
             fprintf(stderr, "0x%02x\t",c);
        }
        if(itsKey==1){
           
            if(add==1){
               c= key[counter%strlen(key)]+c;
               
            }
            else{
                  c=c- key[counter%strlen(key)];
                   
            }
            counter++;
        }else if((c>= 'A') && (c<='Z')){
                c= c+ ('a'-'A');
                
            }
        
    
    if(debug==1){
       fprintf(stderr, "0x%02x\n",c);
    }
    
    fputc(c,output); 
    }
    if(debug==1){
       fprintf(stderr, "0x%02x\t",c);
    }
    
     if(itsKey==1){
           
            if(add==1){
               c= key[counter%strlen(key)]+c;
                
            }
            else{
                  c= c-key[counter%strlen(key)];  
            }
            counter++;
        }
        else if((c>= 'A') & (c<='Z')){
                c= c+ ('a'-'A');
        }

    if(debug==1){
       fprintf(stderr, "0x%02x\n",c);
    }
    counter=0;
    fputc(c,output); 
    fputc('\n',output);

}  
    
     fputc('^', stdout);
     fputc('D', stdout);
     fputc('\n', stdout);
     
     
    
   
    if(fileOut==1){
       
        fclose(output);
    }
        
    if(fileIn==1){
       
        fclose(input);
    } 
    
    
}
