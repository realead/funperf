#pragma once

//mocks mkl.h for Linux_64

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


// MKL_INT is 64bit integer for mkl-ilp64:
// https://software.intel.com/en-us/mkl-developer-reference-c-c-datatypes-specific-to-intel-mkl

#define MKL_INT long long int
#define MKL_UINT unsigned long long int

//utility
#define VML_LA 0x00000001
#define VML_HA 0x00000002
#define VML_EP 0x00000003

#define VML_ERRMODE_IGNORE   0x00000100

unsigned int vmlSetMode( MKL_UINT mode );
unsigned int vmlGetMode( void );


//functions

void  vdSin(MKL_INT n, const double *x, double *y);
void  vdCos(MKL_INT n, const double *x, double *y);
void  vdTan(MKL_INT n, const double *x, double *y);


void  vdAsin(MKL_INT n, const double *x, double *y);
void  vdAcos(MKL_INT n, const double *x, double *y);
void  vdAtan(MKL_INT n, const double *x, double *y);


void  vdSinh(MKL_INT n, const double *x, double *y);
void  vdCosh(MKL_INT n, const double *x, double *y);
void  vdTanh(MKL_INT n, const double *x, double *y);


void  vdAsinh(MKL_INT n, const double *x, double *y);
void  vdAcosh(MKL_INT n, const double *x, double *y);
void  vdAtanh(MKL_INT n, const double *x, double *y);

void  vdExp(MKL_INT n, const double *x, double *y);
void  vdLn(MKL_INT n, const double *x, double *y);
void  vdSqrt(MKL_INT n, const double *x, double *y);

#ifdef __cplusplus
}
#endif /* __cplusplus */
