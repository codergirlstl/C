/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h> 
 #include <stdlib.h>
 #include <stdint.h>
 
typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
    //open memory card file
    FILE* file = fopen("card.raw", "r");
    
    // check to see that the file is null
    if(file == NULL)
        {
            fclose(file);
            printf("Could not open.\n");
            return 1;
        }
    
              
    //declare an array called buffer    
    BYTE buffer[512];    
       
    //declare and initialize variable to keep track of number of jpegs
    int num_jpeg = 0;
    
    //declare file img
    FILE* img;
    
    //read 512 bytes at a time till the end of the card
    while(fread(&buffer, 512, 1, file))
    {            
        //start of a new jpeg  
        if(buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        (buffer[3] == 0xe0  || buffer[3] == 0xe1))
                {
                    if(num_jpeg >= 1)
                    {
                        fclose(img);
                    }
                 
                
                //declare a character array for title of jpeg    
                char title[10];               
                sprintf(title, "%.3d.jpg", num_jpeg);
                
                //make and open a new jpeg
                img = fopen(title, "a");
                num_jpeg++;
                
                //write 512 bytes to img
                fwrite(&buffer, 512, 1, img);
                
                }
    else
    {                        
         //already found a jpeg
        if(num_jpeg >= 1)
        { 
          //write 512 bytes to img                        
          fwrite(&buffer, 512, 1, img);
        }          
    }
                
                                
 }                                                                     
//close any remaining files
fclose(img);
fclose(file);     
 
}         
