/*********main.c***************
* 
*   	Name 				: Muhammed Shibili K
*   	Project 			: Steganography
* 		File 				: encode.c
* 		Description			: This file contains the main fucntion that calls to encode/decode fucntions accroding to the user given option.
* 
*/

#include<stdio.h>				// Library : I/O functions
#include<string.h>				// Library : String Operations
#include"encode.h"				// File	Inc: Encode function prototypes, definitions and Struct variables.
#include"decode.h"				// File Inc: Decode function prototypes, definitions and Struct variables.
#include"types.h"				// File Inc: Enum return variables.

 
 OperationType check_operation_type(char *argv[]); 		// Declaration for operation check function in main.c


int main(int argc, char *argv[])						// Input : argc -> argument count & *argv[] -> argument vector pointer
{
	if(argc<3)											// Check argument count is sufficient or not
	{
		printf("Error: please pass the command line argugments\nUsage: ./a.out -e  beautiful.bmp secret.txt/secret.c\n");
		return 0;										// Exit program
	}
	if(check_operation_type(argv)==e_encode)						// If operation_type is encode 
	{
		printf("<----------Select Encoding---------->\n\n");
		EncodeInfo encInfo;											// Variable declaration of type EncodeInfo (structure)
		if(read_and_validate_encode_args(argv ,&encInfo)==e_success)// Checking the argument passed are valid
		{
			printf("<Read And Validation Is Success\n");
		 	if(do_encoding(&encInfo)==e_success)					// Proceed to Encode data 
			{
				printf("<----------Encoded Successfully---------->\n");
			}
			else
			{
				printf("<----------Encoding Failed---------->\n");
				return -1;											// Exit if encode is failed
			}
		}
		else
		{
			printf("Read And Validation Is Failure\n");
			return -1;												// Exit if validation failed
		}
	}
	else if(check_operation_type(argv)==e_decode)					// If operation type is decode
	{
		printf("<----------Selected decoding---------->\n\n");

		DecodeInfo decInfo;											// Variable declaration of type DecodeInfo (structure)

		if(read_and_validate_decode_args(argv,&decInfo) == d_success)
		{
			printf("Validating decode arguments is success>\n");
			if(do_decoding(&decInfo, argv)==d_success)				// Proceed to decoding data
			{
	                        printf("<---------Decoding is success---------->\n");
			}
			else
			{
                                printf("<---------Decoding is failure---------->\n");
				return -1;											// Exit if decoding fails
			}
		}
	}
	else
	{
		printf("invalid input\nFor Encoding: ./a.out -e beautiful.bmp secret.txt[stego.bmp]\nFor Decoding: ./a.out -d beautiful.bmp stego.bmp[decode.txt]\n");
	}
	return 0;														// Exit if arguments are invalid after printing correct execution.
}

/*
*	Fuction name	:	check_operation_type
*	Input			:	Argument vector pointer
*	Output 			: 	enum operation type
*	Description		: 	To select encoding or decoding according to user input.
*/
OperationType check_operation_type(char *argv[])
{
	if(strcmp(argv[1],"-e")==0)							// Compare argument and -e to return encode
	{
		return e_encode;
	}
	else if(strcmp(argv[1],"-d")==0)					// Compare argument and -d to decode
	{
		return e_decode;
	}
	else
	{
		return e_unsupported;							// If argument is not -e or -d 
	}
	
}
