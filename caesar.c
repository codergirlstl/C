#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, string argv[])
{

    // Reprompt if user fails to give command line argument
    if (argc != 2)
    {
        printf("Please try again\n");
        return 1;
    } 

   

    // Store string key as integer     
    int key = atoi(argv[1]);
 


    // Prompt user for text
    string plaintext = GetString();


    
        

    // Check to see if characters in string are uppercase  
    for(int i = 0, n= strlen(plaintext); i < n; i++)
    {
        // Encipher text using ceasar formula
        if (isupper(plaintext[i]))
        {   
            plaintext[i] = (plaintext[i] + key - 65) % 26 + 65;
              
            printf("%c", plaintext[i] );
        }      
    
      
    // Check to see if characters in string are lowercase                 
    else if (islower(plaintext[i]))
        {   
            // Encipher text using ceasar formula         
            plaintext[i] = (plaintext[i] + key - 97) % 26 + 97 ;
              
            printf("%c", plaintext[i] );
    }      

    else
        // if not a letter don't change the character just print  
        { 
            printf("%c", plaintext[i]);
        }  
    
    

} 
    printf( "\n");     
 }           
            













