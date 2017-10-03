#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main (void)

{
printf("Give me an amount in dollars for change.\n");
float change = GetFloat();
change*=100;
int amount =roundf(change);

int coins = 0; 
   

if (change <= 0)
  
{
     printf("Please pick a positive number\n");
     amount = GetFloat();       
 }  


else

    
while
(amount >= 25)
{   
    amount-=25;
    coins++;
 }   
       
 while
 (amount >= 10)
{  
    amount-=10;
    coins++;
    }   
while 
    (amount >= 5)
        {
    amount-=5;
    coins++;
     }   
while
 (amount <= 5 && amount > 0)
        {
    amount-=1;
    coins++;        
    }
    printf("%d\n", coins);
}    

   
 
