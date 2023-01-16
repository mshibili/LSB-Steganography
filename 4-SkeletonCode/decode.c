/***************DECODE.C*************
*       Name                : Muhammed Shibili K
*       Project             : Steganography
*       File                : decode.c
*       Description         : This file contains the fucntion definitions for Decode functionality.
*                               1- Open files : -> source image -> Secret file
*                               2- Validate Decoding arguments : -> check extensions .bmp, .txt, .c & outoutfile name
*                               3- Decode the magic string
*                               4- Decode the secret file extension SIZE  
*                               5- Decode the secret file EXTENSION
*                               6- Decode the secret FILE SIZE
*                               7- Decode the secret FILE DATA
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decode.h"
#include "types.h"
#include "common.h"

/* 
 * Get File pointers for i/p files
 * Inputs: Structure variable
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */

Status d_open_files(DecodeInfo *decInfo)                    
{
    printf("INFO; Opening required files\n");               
    printf("INFO: Opening %s\n",decInfo->image);

    decInfo->fptr_image =fopen(decInfo->image,"r");                         // Opern image in read mode and update image fptr

    if(decInfo->fptr_image == NULL)                                         // If the pointer is NULL
    {
       perror("fopen");                                                     // Error handling
       fprintf(stderr,"ERROR: Unable to open file %s\n",decInfo->image);
       return d_failure;
    }

    else
    {
    return d_success;
    }
}

/*
*   Fuction name    :   read_and_validate_decode_args
*   Input           :   EncodeInfo structure
*   Output          :   Status enum e_success/e_failure
*   Description     :   To validate encode arguments and update output file name according to argv[3]
*/

Status read_and_validate_decode_args(char *argv[],DecodeInfo *decInfo)	
{
    short bmp_file_BM_head;                         // 2bytes for BM 
    if(argv[2] == NULL)								// If file is not passed
    {
	printf("Eroor : pass the correct path\n");				
	return d_failure;
    }
    else
    {
	if(strstr(argv[2],".") == NULL)                        // If the file name doesnt contain . return failure
	{
	    return d_failure;
	}
	else
	{
	    if(strcmp(strstr(argv[2],"."),".bmp") == 0)        // Compare the image extn with .bmp		
	    {
		decInfo->fptr_image = fopen(argv[2],"r");          // open the file pointer in read mode	
		fread(&bmp_file_BM_head,2,1,decInfo->fptr_image);  // Read 2 bytes of head (BM)
		if(bmp_file_BM_head == 0x4d42)					   // If the 2 Bytes are BM		
		{
		    decInfo->image = argv[2];					   // Save the argument as image
		    fclose(decInfo->fptr_image);                   // Close the fptr
		    return d_success;
		}
		else
		    return d_failure;				
	    }
	    else
		return d_failure;
	}
    }
    return d_success;
}


/*
*   Fuction name    :   do_encoding
*   Input           :   EncodeInfo structure and argument vector
*   Output          :   Status enum d_success/d_failure
*   Description     :   This function calls other decode fuctions
*/

Status do_decoding(DecodeInfo *decInfo,char *argv[])				
{
    if(d_open_files(decInfo) == d_success)			                       // Function call do decode function		
        {
		printf("Opening file is success\n");
		
	       if((decode_magic_string(MAGIC_STRING,decInfo) == d_success))	   // Function call for decoding file extn
	       {
                	printf("Magic string decoding is success\n");

			if(decode_secret_file_extn_size(decInfo) == d_success)         // Function call for decoding secret file size
			{
				printf("Decoding secret file extension size  is success\n");
				if(decode_secret_file_extn(decInfo, argv) == d_success)    // Function call for decoding the secret data
				{
					printf("Decoding secret file extension is success\n");

					if(decode_secret_file_size(decInfo)==d_success)
					{
						printf("Decoding secret file size is Success\n");						

						if(decode_secret_data(decInfo) == d_success)
						{
							printf("Decoding secret data is success\n");
						}
						else
						{
							printf("Decoding secret data is failure\n");
							return d_failure;
						}
					}
					else
					{
						printf("Decoding secret file size is Failure\n");						
					}
				}
				else
				{
					printf(" Decoding secret file extension is failure\n");
					return d_failure;
				}

			}
			else
			{
				printf(" Decoding secret file extension size  is success\n");
				return d_failure;
			}			

	       }
	       else
	       {
                        printf("<---------Magic string decoding is failure---------->\n");
	                return d_failure;
        	}
	}
    	else
        	return d_failure;


    return d_success;
}


/*
*   Fuction name    :   decode_magic_string
*   Input           :   Magic string character pointer and EncodeInfo structure
*   Output          :   Status enum d_success/d_failure
*   Description     :   To encode bytes of magic string
*/
Status decode_magic_string(const char *magic,DecodeInfo *decInfo)
{
    int magic_string_size = strlen(magic);                              // Get the length of magic string   
    char arr[magic_string_size];				
    fseek(decInfo->fptr_image,54,SEEK_SET);				                // Set fptr of image at 54
    decode_data_from_img(arr,magic_string_size,decInfo->fptr_image);

    if(strcmp(arr,magic) == 0)			                                // Compare the arr with MAGIC_STRING
    {
	return d_success;	
    }
    else
	return d_failure;
}

/*
*   Fuction name    :   decode_data_from_image
*   Input           :   Data buffer pointer, size to be encoded, EncodeInfo structure
*   Output          :   Status enum d_success/d_failure
*   Description     :   To encode byte of data to image
*/

Status decode_data_from_img(char *data,int size,FILE *fptr_image)
{
    char buff[8];				                       	 

    for(int i=0;i<size;i++)
    {
	data[i] = 0;
	fread(buff,8,1,fptr_image);		          // Read 8 bytes and save to buffer             		
	decode_byte_from_lsb(&data[i],buff);	  // Decode the byte from lsb and update data[]   
    }
    data[size]='\0';                          // Add Null at end
    return d_success;
}

/*
*   Fuction name    :   decode_byte_from_lsb
*   Input           :   Data buffer to be encoded and 8 byte image buffer from fread 
*   Output          :   Status enum d_success/d_failure
*   Description     :   To encode LSB bit of data to image
*/


Status decode_byte_from_lsb(char *data,char *buffer)
{
    char ch =0;     

    for(int i=0;i<8;i++)
    {
	ch |= ((buffer[i] & (1)) << (7-i));			//get lsb bit of image buffer nd moving left (7-i) times 

    }
    *data = ch;					
}

/*
*   Fuction name    :   decode_secret_file_extn_size
*   Input           :   EncodeInfo structure
*   Output          :   Status enum e_success/e_failure
*   Description     :   To encode size of secret file extension
*/

Status decode_secret_file_extn_size(DecodeInfo *decInfo)
{
    
    char str[32];			                                            // Buffer to read
    fread(str,32,1,decInfo->fptr_image);                                // Read 32 bytes from image and save to buff
    decInfo->output_file_extn_size = decode_size_from_lsb(str,decInfo);	// Decode extn size and update the structure	
    return d_success;
}

/*
*   Fuction name    :   decode_size_from_lsb
*   Input           :   size to be decoded ,DecodeInfo structure
*   Output          :   Status enum e_success/e_failure
*   Description     :   To decode size of files to output file
*/


int decode_size_from_lsb(char *data,DecodeInfo *decInfo)
{
    int num = 0;
    for(int i=0;i<32;i++)			
    {
	if(data[i] & 1)					// If the LSB is 1
	{
	    num |=  (1 << (31-i));	    // Increment num with 1 left shifted by 31-i times		
	}
    }
    return num;
}

/*
*   Fuction name    :   decode_secret_file_extn
*   Input           :   DecodeInfo structure , argument vector
*   Output          :   Status enum e_success/e_failure
*   Description     :   To decode secret file extension
*/

Status decode_secret_file_extn(DecodeInfo *decInfo,char *argv[])		
{
	decInfo->output_file_extn = (char *)malloc(decInfo->output_file_extn_size);                    // Allocate memory as per size of extn
	if( decode_data_from_img(decInfo->output_file_extn, decInfo->output_file_extn_size, decInfo->fptr_image) == d_success)
	{
	    
	    printf("Secret file extension %s decoded successfully\n", decInfo -> output_file_extn);
	    char name[32] = "dest";                                                                    // Default name for output file
	    if(argv[3] == NULL)                                                                        // If file name not given
	    {
		    strcat(name,decInfo->output_file_extn);                                                // Concatinate with extn 
		    decInfo->output_fname = name;                                                          // Update O/p file name in structure
		
		    printf("INFO: Output File Not Mentioned. Creating %s as default\n",decInfo->output_fname);
	    }
	    else                                                                                       // If file name mentioned set as o/p fname
	    {
		    decInfo->output_fname = argv[3];      
		    strcat(decInfo->output_fname, decInfo -> output_file_extn);                            // Concatinate with extn and update fname
		    decInfo->output_fname = argv[3];
		    strcat(name,decInfo->output_fname);
	    }
	    printf("INFO: Opned %s\n",decInfo->output_fname);
	    decInfo->fptr_output_file = fopen(decInfo->output_fname,"w");                             // fopen the output file
	    if(decInfo->fptr_output_file == NULL)
	    {
		    printf("error to open file\n");
		    return d_failure;
	    }
	    return d_success;
    }
}

/*
*   Fuction name    :   decode_secret_file_size
*   Input           :   DecodeInfo structure
*   Output          :   Status enum e_success/e_failure
*   Description     :   To Decode secret file size to image
*/

Status decode_secret_file_size(DecodeInfo *decInfo)
{
	char buff[32];                                                     // Buffer to fecth 32bytes from image
	fread(buff,32,1,decInfo -> fptr_image);                            // Reas 32 bytes from image
	decInfo->output_file_size = decode_size_from_lsb(buff, decInfo);   // Decode size and save to structure
	return d_success;
}

/*
*   Fuction name    :   decode_secret_file_data
*   Input           :   DecodeInfo structure
*   Output          :   Status enum e_success/e_failure
*   Description     :   To decode secret file data
*/

Status decode_secret_data(DecodeInfo *decInfo)
{
    char array[decInfo->output_file_size];			           // Buffer to store ouput data	
    for(int i=0;i<decInfo->output_file_size;i++)			
    {
	decode_data_from_img(&array[i], 1,decInfo->fptr_image);	   // Decode and save data to buffer    
	fwrite(&array[i],1,1,decInfo->fptr_output_file);		   // Write buffer to output file
    }

    return d_success;
}


