
#ifndef CURCONTROLLER_H_
#define CURCONTROLLER_H_

#include"generic/ViennaBasicTypes.h"


typedef struct
{

   ABC_TYPE iabc_ref;
   ABC_TYPE iabc_fdbk;
   float32  w_est;

} CURCONTROLLER_IN_TYPE; 

typedef struct
{

    PR_IO_TYPE *pr_ia_io;
    PR_IO_TYPE *pr_ib_io;
    PR_IO_TYPE *pr_ic_io;
   
                                                             
} CURCONTROLLER_STATE_TYPE;

typedef struct
{

    float32	*cur_kp; 
    float32	*cur_ki;
    float32	*cur_con_upper_lmt ;
    float32	*cur_con_lower_lmt ;
    float32 *Ts;

    float32 *cur_con_sogi_k;
    float32 *cur_con_sogi_w;

    float32 *scaler;
                                                             
} CURCONTROLLER_PARAMS_TYPE;

typedef struct
{

    ABC_TYPE  duty_abc ; 

    float32 debug1; 
    float32 debug2;
                                                             
} CURCONTROLLER_OUT_TYPE;

void CurController_initialize(CURCONTROLLER_STATE_TYPE *state,CURCONTROLLER_PARAMS_TYPE *pll_params);
void CurController_calc(CURCONTROLLER_IN_TYPE *in, CURCONTROLLER_STATE_TYPE *state,CURCONTROLLER_PARAMS_TYPE *params, CURCONTROLLER_OUT_TYPE *out);


#endif //end of CURCONTROLLER_H_