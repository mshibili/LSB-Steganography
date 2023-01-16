/********ENCODE.C*************
*   	Name 			: Muhammed Shibili K
*   	Project 		: Steganography
* 	File 			: encode.c
* 	Description		: This file contains the fucntion definitions for Encode functionality.
* 					1- Open files : -> source image -> Secret file
* 					2- Validate Encoding arguments : -> check extensions .bmp, .txt, .c & outoutfile name
* 					3- Check capacity of image to store secret data
* 					4- Copy bmp header 54 bytes as it is
*					5- Encode the magic string
* 					6- Encode the secret file extension SIZE  
*					7- Encode the secret file EXTENSION
* 					8- Encode the secret FILE SIZE
* 					9- Encode the secret FILE DATA
* 					10-Copy the REMAINING DATA
*/


#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "common.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    									
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");		// Src Image file
    if (encInfo->fptr_src_image == NULL)					// Do Error handling

    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
 }

/*
*	Fuction name		:	read_and_validate_encode_args
*	Input			:	EncodeInfo structure
*	Output 			: 	Status enum e_success/e_failure
*	Description		: 	To validate encode arguments and update output file name according to argv[3]
*/

 Status  read_and_validate_encode_args( char *argv[], EncodeInfo *encInfo)
 {
         //strchr(argv[2], ".") : returns address of '.' of beautiful.bmp
         if(strcmp( strstr(argv[2], ".") , ".bmp") == 0)         // Check the source image extension ".bmp"
                 encInfo -> src_image_fname = argv[2];
         else
                 return e_failure;

         if(strcmp(strstr(argv[3],".") , ".txt") == 0)           // Check secret file extension ".txt"
                 encInfo -> secret_fname = argv[3];

         else if(strcmp(strstr(argv[3],".") , ".c") == 0)           	// Check secret file extension ".c"
                 encInfo -> secret_fname = argv[3];
         else if(strcmp(strstr(argv[3],".") , ".sh") == 0)           	// Check secret file extension ".c"
                 encInfo -> secret_fname = argv[3];

         else
                 return e_failure;

         if (argv[4] != NULL)
                 encInfo -> stego_image_fname = argv[4];         // Check output file name passed or not
         else
                 encInfo -> stego_image_fname = "stego.bmp";
         return e_success;
}

/*
*	Fuction name		:	do_encoding
*	Input			:	EncodeInfo structure
*	Output 			: 	Status enum e_success/e_failure
*	Description		: 	This function calls other decode fuctions
*/

Status do_encoding( EncodeInfo *encInfo)
{
	if(open_files(encInfo) == e_success)
	{
		printf("Opening file is a success\n");
		if(check_capacity(encInfo) == e_success)
		{
			printf("Checking capacity is success\n");
			if (copy_bmp_header(encInfo -> fptr_src_image, encInfo -> fptr_stego_image) == e_success)
			{
				printf("Copying BMP header file is a success\n");

				if (encode_magic_string(MAGIC_STRING, encInfo) == e_success)
				{
					printf("Encoding magic string %s with length %d is Success\n", MAGIC_STRING, strlen(MAGIC_STRING));

					strcpy(encInfo -> extn_secret_file , strstr(encInfo -> secret_fname, "."));
					printf("Extension is %s with length %d\n" , encInfo -> extn_secret_file, strlen(encInfo->extn_secret_file));
					if(encode_secret_file_extn_size (strlen(encInfo -> extn_secret_file), encInfo) == 0)
					{
						printf("Encoding Extension is successfull\n");
						if(encode_secret_file_size(encInfo -> size_secret_file, encInfo) == e_success)
						{ 
							printf("Encoding secret file size is Success\n");

							if(encode_secret_file_data(encInfo) == e_success)
							{
								printf("Encoding secret file data is successfull\n");

								if(copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success)
								{
									printf("Copied remaining data successfully\n");
								}
								else
								{
									printf("Copying remaining data failed\n");
									return e_failure;
								}
									
							}
							else	
							{
								printf("Encoding secret file data is Failed\n");
								return e_failure;
							}

						}
						else
						{
							printf("Encoding secret file size if Failed\n");
							return e_failure;
						}
					}
					else
					{
						printf("Encoding Extension Failed\n");
						return e_failure;
					}

 				}
				else
				{
					printf("Encoding magic string is Failure");
					return e_failure;
				}
			}
			else
			{
				printf("Copying BMP header file is Failure\n");
			}
		}
		else 
		{
			printf("Checking capacity is Failure\n");
			return e_failure;
		}
	}

	else
	{
		printf("Opening file is a failure\n");
		return e_failure;
	}
	return e_success;
}

/*
*	Fuction name		:	check_capacity
*	Input			:	Address of structure variable encInfo
*	Output 			: 	enum stauts : e_success/e_failure
*	Description		: 	To calculate the total bytes to be encoded and compare with source image size to proceed encoding.
*/
Status check_capacity(EncodeInfo *encInfo)
{ 
	encInfo -> image_capacity = get_image_size_for_bmp(encInfo -> fptr_src_image);		// bmp file size saved to structure variable
	encInfo-> size_secret_file = get_file_size(encInfo -> fptr_secret);			// secret file size saved to structure variable 
	if(encInfo -> image_capacity > (54+16+32+32+32+(encInfo -> size_secret_file * 8)))	// Compare bmp size and total bytes to encode
	{
		/* 	54 bytes - Header
		*	16 bytes - Magic
		*	32 bytes - size if secret extension
		*	
		*/		
		return e_success;
	}
	else
		return e_failure;
}

/*
*	Fuction name		:	get_file_size
*	Input			:	FILE pointer of secret file
*	Output 			: 	Typedef of unsigned int
*	Description		: 	It set the FILE pointer at end of file and return ftell value
*/
uint get_file_size(FILE *fptr)
{
	fseek(fptr, 0, SEEK_END);
	return ftell(fptr);
}

/*
*	Fuction name		:	copy_bmp_header
*	Input			:	FILE pointers of source and destination
*	Output 			: 	Status enum e_success/e_failure
*	Description		: 	To copy 54 Bytes of Header to destination
*/

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
	char buffer[54];
	fseek(fptr_src_image, 0, SEEK_SET);				// Set source image pointer at beginning
	fread(buffer, 54, 1, fptr_src_image);				// Read 54 byte header
	fwrite(buffer, 54, 1, fptr_dest_image);				// Write the buffer to destination image
	return e_success;
}

/*
*	Fuction name		:	encode_magic_string
*	Input			:	Magic string character pointer and EncodeInfo structure
*	Output 			: 	Status enum e_success/e_failure
*	Description		: 	To encode bytes of magic string
*/

Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
	encode_data_to_image(magic_string, strlen(magic_string), encInfo);		// Pass magic string to encode function
	return e_success;
}

/*
*	Fuction name		:	encode_data_to_image
*	Input			:	Data buffer pointer, size to be encoded, EncodeInfo structure
*	Output 			: 	Status enum e_success/e_failure
*	Description		: 	To encode byte of data to image
*/
Status encode_data_to_image(const char *data, int size, EncodeInfo *encInfo)
{
	//printf("fptr_src_image is at %d \n", ftell(encInfo->fptr_src_image));
	for(int i=0; i<size; i++)
	{
		fread(encInfo -> image_data, 8, 1, encInfo -> fptr_src_image);		// Read 8 bytes from src image save to image_data buffer
		encode_byte_to_lsb(data[i], encInfo -> image_data);			// Encode each bytes of 8 
		fwrite(encInfo -> image_data, 8, 1, encInfo -> fptr_stego_image);	// Write the encoded data
	}
	printf("fptr_src_image is at %d \n", ftell(encInfo->fptr_src_image));

	return e_success;
}

/*
*	Fuction name		:	encode_byte_to_lsb
*	Input			:	Data buffer to be encoded and 8 byte image buffer from fread 
*	Output 			: 	Status enum e_success/e_failure
*	Description		: 	To encode LSB bit of data to image
*/

Status encode_byte_to_lsb(char data, char *image_buffer)
{
	for (int i=0; i<8; i++)
	{
		image_buffer[i] = (image_buffer[i] & 0xFE) | ((data >> (7-i)) & 01); 	// clear the LSB of buffer byte and with data shifted 7-i 
	}		
	return e_success;
}


/*
*	Fuction name		:	encode_secret_file_extn_size
*	Input			:	Extension size ,EncodeInfo structure
*	Output 			: 	Status enum e_success/e_failure
*	Description		: 	To encode size of secret file extension
*/
Status encode_secret_file_extn_size(int extn_size, EncodeInfo *encInfo)
{
	encode_size_to_lsb(extn_size, encInfo);					// size encode function call
	encode_secret_file_extn(encInfo -> extn_secret_file, encInfo);		// Encode the extension
	return e_success;
}

/*
*	Fuction name		:	encode_size_to_lsb
*	Input			:	size to be encoded ,EncodeInfo structure
*	Output 			: 	Status enum e_success/e_failure
*	Description		: 	To encode size of files to dest image
*/

Status encode_size_to_lsb(int size, EncodeInfo *encInfo)
{
	char buffer[32];							// Buffer to save image data
	fread(buffer, 32, 1, encInfo -> fptr_src_image);			// Read 32 bytes from image
	
	for (int i=0; i<32; i++)
	{
		buffer[i] = (buffer[i] & 0xFE) | (( size  >> (31-i)) & 01); 	// Clear buffer LSB and add with size shifted 32-i times
	}		

	fwrite(buffer, 32, 1, encInfo -> fptr_stego_image);
	return e_success;

}	

/*
*	Fuction name		:	encode_secret_file_extn
*	Input			:	Character to file extension ,EncodeInfo structure
*	Output 			: 	Status enum e_success/e_failure
*	Description		: 	To encode secret file extension
*/
Status encode_secret_file_extn(char *file_extn, EncodeInfo *encInfo)
{
	encode_data_to_image(file_extn, strlen(file_extn), encInfo);		// Encode secret file extn to image
	return e_success;
}

/*
*	Fuction name		:	encode_secret_file_size
*	Input			:	Secret file size ,EncodeInfo structure
*	Output 			: 	Status enum e_success/e_failure
*	Description		: 	To encode secret file size to image
*/
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
	encode_size_to_lsb(file_size, encInfo);			// Encode the secret file size to image
	return e_success;
}

/*
*	Fuction name		:	encode_secret_file_data
*	Input			:	EncodeInfo structure
*	Output 			: 	Status enum e_success/e_failure
*	Description		: 	To encode secret file data
*/

Status encode_secret_file_data(EncodeInfo *encInfo)
{
	char buffer[encInfo -> size_secret_file];				// Buffer to strore secret file
	fseek(encInfo -> fptr_secret, 0, SEEK_SET);				// Set scecret fptr at beginning
	fread(buffer ,encInfo -> size_secret_file, 1, encInfo ->fptr_secret);	// Read secret file and save to buffer
	encode_data_to_image(buffer, encInfo->size_secret_file, encInfo);	// Encode the buffer to image
	return e_success;
}

/*
*	Fuction name		:	copy_remaining_img_data
*	Input			:	FILE pointers to destination and source image
*	Output 			: 	Status enum e_success/e_failure
*	Description		: 	To encode remaining data of .bmp source file to destination
*/

Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
	char ch;
	
	while(fread(&ch, 1, 1, fptr_src) > 0)			// Read 1 byte from source
	{
		fwrite(&ch, 1, 1, fptr_dest);			// Write the byte into the destination
	}
	return e_success;

}
