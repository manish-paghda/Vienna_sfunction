
#ifndef PLL_H_
#define PLL_H_

#include"generic/ViennaBasicTypes.h"


typedef struct
{
    ABC_TYPE Vabc;
} PLL_IN_TYPE; 

typedef struct
{
    ALPHA_BETA_TYPE *ValphaBeta;
    SOGI_IO_TYPE *sogi_alpha_io;
    SOGI_IO_TYPE *sogi_beta_io;
    SEQ_COMP_TYPE *ValphaBetaSeq;
    PI_IO_TYPE *pi_io;
    DQ_TYPE *DQ;
                                                             
} PLL_STATE_TYPE;

typedef struct
{
    float32 *Fac;
    float32	*sogi_k;
    float32	*sogi_upper_lmt;
    float32	*sogi_lower_lmt;
    float32 *Ts;
        
    float32	*pll_kp;
    float32	*pll_ki;
    float32	*pll_pi_upper_lmt;
    float32	*pll_pi_lower_lmt;
                                                             
} PLL_PARAMS_TYPE;

typedef struct
{
    SEQ_COMP_TYPE seq_comps;
    ABC_TYPE grid_3ph_sine;
    float32 w_est;
    float32 th_est;

    float32 debug1;
    float32 debug2;
                                                             
} PLL_OUT_TYPE;

// void Pll_calc(PLL_IO_TYPE *in, PLL_STATE_TYPE *state,PLL_PARAMS_TYPE *params, PLL_OUT_TYPE *out);
// void Pll_calc(ABC_TYPE *in, PLL_STATE_TYPE *state,PLL_PARAMS_TYPE *params, PLL_OUT_TYPE *out);
void Pll_calc(PLL_IN_TYPE *in, PLL_STATE_TYPE *state,PLL_PARAMS_TYPE *params, PLL_OUT_TYPE *out);
void Pll_initialize(PLL_STATE_TYPE *state,PLL_PARAMS_TYPE *pll_params);
void Pll_GetSeqComps(PLL_STATE_TYPE *state);



#endif //end of PLL_H_