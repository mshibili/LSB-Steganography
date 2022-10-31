/***************TYPES.H*************
*       Name                : Muhammed Shibili K
*       Project             : Steganography
*       Date of submition   : Oct 17 2022
*       File                : types.h
*       Description         : This file contains the enum definition used in the program
*/

#ifndef TYPES_H
#define TYPES_H

/* User defined types */
typedef unsigned int uint;

/* Status will be used in fn. return type */
typedef enum
{
    e_success,
    e_failure,
    d_success,
    d_failure
} Status;

typedef enum
{
    e_encode,
    e_decode,
    e_unsupported
} OperationType;

#endif
