/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    // store string from command line as an integer
    int n = atoi(argv[1]);

    // make sure n is a positive number less or equal to 100
    if (n < 1 || n > 100 )
    {
        printf("Please give a number from 1 to 100");
        return 0;
    }       
    
        
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
   
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_n;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_n = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_n;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_n = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // update header info for outfile
     
    // determine padding for scanlines
   int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;   
   
   // increase width of bmp
    bi_n.biWidth = bi.biWidth * n;   
   
   // increase height of bmp
    bi_n.biHeight = bi.biHeight * n;
    
    // change padding for outfile
    int outpadding = (4 - (bi_n.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
     
    // increase image size
    bi_n.biSizeImage = ((bi_n.biWidth) * sizeof(RGBTRIPLE) + outpadding) * abs(bi_n.biHeight);
    
    // increase file size
    bf_n.bfSize = bi_n.biSizeImage + 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_n, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_n, sizeof(BITMAPINFOHEADER), 1, outptr);      
    
  
        
    // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)   
            { 
         // resize vertically n times
               for(int vertically = 0; vertically < n; vertically++)
                    {                   
                        // iterate over pixels in scanline 
                        for (int j = 0; j < bi.biWidth; j++)
                        {  
                        
                        // temporary storage
                        RGBTRIPLE triple;
                        
                        // read RGB triple from infile
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                        
                        // write triple n number of times
                        for(int horizontally = 0; horizontally < n; horizontally++)
                            // write  to outfile to resize horizontally
                             fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                        }
                        
                        // then add in new padding for outfile  
                        for (int l = 0; l < outpadding; l++)
                            fputc(0x00, outptr);
                        
                        // return to the beginning of a scanline
                        if (vertically < n-1)
                            fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);       
                        }       
                       
                        // skip over padding, if any
                        fseek(inptr, padding, SEEK_CUR);
         
             }         
                        
                    
                    
              
                    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
