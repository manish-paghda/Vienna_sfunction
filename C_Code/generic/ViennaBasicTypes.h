
#ifndef VIENNABASICTYPES_H_
#define VIENNABASICTYPES_H_

#include<stdio.h>

#define TWO_BY_THREE 0.666666667f
#define ONE_BY_TWO 0.5f
#define SQRT_3 1.7320508075688772935274463415059f
#define SQRT_2 1.4142135623730950488016887242097f
// #define TS_V_LOOP 1.0f/35000.0f
#define TS_CUR_LOOP 1.0f/70000.0f
#define TWO_PI 2.0f*3.1415926535897932384626433832795f
#define PI 3.1415926535897932384626433832795f

typedef float  float32;

typedef struct
{
    float32 A;                                     
    float32 B;                                     
    float32 C;                                     
} ABC_TYPE;                           


typedef struct
{
    float32 ZeroSequence;
    float32 Alpha;                                 
    float32 Beta;                                  
} ALPHA_BETA_TYPE;                  


typedef struct
{
    ALPHA_BETA_TYPE AlBeZero;
    float th;

} PARK_IN_TYPE;  

typedef struct
{
    float32 in;
    float32 in_old;
    float32 upper_lmt;  
    float32 lower_lmt; 
    float32 out;
    float32 Ts;
} INTEGRATION_IO_TYPE;  

typedef struct
{
    float32 error;
    float32 kp;
    float32 ki;
    float32 upper_lmt;  
    float32 lower_lmt; 
    float32 out;
    INTEGRATION_IO_TYPE intg;
} PI_IO_TYPE;  


typedef struct
{
    float32 in;
    float32 w;  
    float32 k;
    
    INTEGRATION_IO_TYPE intg1;
    INTEGRATION_IO_TYPE intg2;

    float32 out;
    float32 out_quadrature;  

} SOGI_IO_TYPE;    

typedef struct
{
    float32 error;
    float32 kp;
    float32 ki;
    float32 upper_lmt;  
    float32 lower_lmt; 
    float32 out;
    SOGI_IO_TYPE res;
    
} PR_IO_TYPE;  
 
typedef struct
{

    float32 out;
    float32 out_quadrature;  

} SOGI_OUT_TYPE;    

typedef struct
{
    float32 in;
                                                             
} ADD_IN_TYPE;  

typedef struct
{
    float32 out;
                                                             
} ADD_OUT_TYPE;  

typedef struct
{
    float32 state;
                                                             
} ADD_STATE_TYPE;  

typedef struct
{
    float32 v_al_pos;
    float32 v_al_neg;
    float32 v_be_pos;
    float32 v_be_neg;

} SEQ_COMP_TYPE;  

typedef struct
{
    float32 d;
    float32 q;
    float32 o;

} DQ_TYPE;  



#endif  //end VIENNABASICTYPES_H_