#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Start program that will take a single command line argument
int main(int argc, string argv[])
{
    // Check that use only enters one command line argument
    if (argc != 2)
    {
        printf("Please try again\n");
        return 1;
    }  
   
    // set argv as variable keyword        
    string keyword = argv[1];    
    
    // assign length of text variable
    int k_length =strlen(keyword);
    
    // Check to see if keyword is an alphabetical character
    for (int j = 0; j < k_length; j++) 
    
        if (isalpha(keyword[j]))
            ;
             
             
        else
        {
            printf("Please give a keyword with letters\n");
            return 1;
        }
     // prompt user for a string of plaintext and assign text variable
    string plaintext = GetString();
    int p_length = strlen(plaintext); 
    
    // iterate through the plaintext
    for (int i = 0, j = 0; i < p_length; i++)                                              
    {                                             
        // repeat keyword in plaintext            
        if ( j >= ( k_length))        
        {
            j = 0;          
        }                  
        // Check if plaintext string is an uppercase letter
        if (isupper(plaintext[i]))
                                                   
        // Enchipher and print text using vigenere formula
        {                                     
            plaintext[i] = (plaintext[i] + (keyword[j] - 65) - 65) % 26 + 65 ;
                                                                         
            printf("%c", plaintext[i]);
                            
            j++;                  
        }                                 
        // Check if plaintext string is a lowercase letter   
        else if(islower(plaintext[i]))
        {             
        // Encipher and print text using vigenere formula 
        
            if (isupper(keyword[j]))
            {                                     
                plaintext[i] = (plaintext[i] + (keyword[j] - 65) - 97) % 26 + 97 ;
                                                 
                printf("%c", plaintext[i]);
                            
                j++;                           
            }
        
            else if (islower(keyword[j]))
            {
                plaintext[i] = (plaintext[i] + (keyword[j] - 97) - 97) % 26 + 97 ;
                                                 
                printf("%c", plaintext[i]);
                            
                j++;                           
            }    
        
        }
        
        // Print text of characters that are not alphabetical as unchanged.  
        else
        {
                            
            printf("%c", plaintext[i]);
                           
        }
        
        }                     
                        
    printf("\n");       
}                   
              
                    
      
                        
 
 
 
 
 
 
 
 
           

    
    
                              

