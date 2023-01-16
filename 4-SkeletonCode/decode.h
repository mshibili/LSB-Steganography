/***************DECODE.H*************
*       Name                : Muhammed Shibili K
*       Project             : Steganography
*       File                : Decode.h
*       Description         : This file contains the fucntion prototypes, preprocessor definitions for Decode functionality.
*/

#ifndef DECODE_H
#define DECODE_H

#include "types.h" //user deined types

#define MAX_FILE_SIZE 4

typedef struct DecodeInfo_
{
    /* stego image info */
    char *image;
    FILE *fptr_image;

    /*for optional */
    char *output_fname;
    FILE *fptr_output_file;
    long  output_file_extn_size;
    char *output_file_extn;
    int  output_file_size;

}DecodeInfo;

/*Decoding function prototype */

/* read and validate args from argv */
Status read_and_validate_decode_args(char *argv[],DecodeInfo *decInfo);

/* perfrom the decoding */
Status do_decoding(DecodeInfo *decInfo,char *argv[]);

/* Get file pointer for i/p and o/p files */
Status d_open_files(DecodeInfo *decInfo);

/* decodimg magic string */
Status decode_magic_string(const char *magic,DecodeInfo *decInfo);

/* decoding data from the source image */
Status decode_data_from_img(char *data,int size,FILE *fptr_image);

/* decoding lsb bite and update in data */
Status decode_byte_from_lsb(char *data,char *buffer);

/* decoding file extension */
Status decode_secret_file_extn_size(DecodeInfo *decInfo);

/* decoding from the lsb */
int decode_size_from_lsb(char *data,DecodeInfo *decInfo);


/* decoding secret file extension */
Status decode_secret_file_extn(DecodeInfo *decInfo, char *argv[]);

/* decoding secret file size */
Status decode_secret_file_size(DecodeInfo *decInfo);

/* decoding secret data */
Status decode_secret_data(DecodeInfo *decInfo);



#endif
