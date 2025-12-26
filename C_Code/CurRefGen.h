
#ifndef CURREFGEN_H_
#define CURREFGEN_H_

#include"generic/ViennaBasicTypes.h"


typedef struct
{

    float32 vbus_con_out;
    ABC_TYPE Vabc;
    SEQ_COMP_TYPE seq_comps;
    ABC_TYPE grid_3ph_sine;

} CURREFGEN_IN_TYPE; 

typedef struct
{
    float32 dummy;
                                                             
} CURREFGEN_STATE_TYPE;

typedef struct
{
    float32 dummy;
                                                             
} CURREFGEN_PARAMS_TYPE;

typedef struct
{

    ABC_TYPE iabc;

    float32 debug1;
    float32 debug2;
                                                             
} CURREFGEN_OUT_TYPE;

void CurRefGen_initialize();
void CurRefGen_calc(CURREFGEN_IN_TYPE *in,  CURREFGEN_OUT_TYPE *out);


#endif //end of CURREFGEN_H_