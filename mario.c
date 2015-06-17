#include <stdio.h>
#include <cs50.h>



int main (void)
{ 
     //ask user for number 
printf("Pick a number between 0 and 23\n");
 
    int number = GetInt();    
    
 if (number >= 0 && number <=23);
        
    
 //reprompt user 
 else
 
    do    
    { 
    printf("Pick a valid number\n");  
      number = GetInt();
    }
 
    while 
    ( number <=0 || number >= 24); 

  
 
 
 
 //create pyramid
           
 
 int count, spaces, hashtag;  
 int places = number + 1;
        
        //create row      
 for (count = 0; count < number * places; count++)  
     
 {
       //create spaces
    for (spaces = 1 ; spaces <= number - 1; spaces++)       
    {
    printf(" ");
    }  
        //create hashtags
    
    for (hashtag = 0; hashtag <= places - spaces; hashtag++)   
    {
    printf("#"); 
    }
        //go to the next line or row
    printf("\n"); 
    number--;
    
  }
  
  }
   
   
    


