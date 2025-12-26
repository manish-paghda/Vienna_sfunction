#include<stdio.h>
#include"generic/GenericBlocks.h"
#include "Vienna.h"
#include "CurController.h"



void CurController_initialize(CURCONTROLLER_STATE_TYPE *state,CURCONTROLLER_PARAMS_TYPE *params)
{

    state->pr_ia_io->kp = *params->cur_kp;
    state->pr_ia_io->ki = *params->cur_ki;
    state->pr_ia_io->lower_lmt = *params->cur_con_lower_lmt;
    state->pr_ia_io->upper_lmt = *params->cur_con_upper_lmt;
    state->pr_ia_io->out = 0.0f;
    state->pr_ia_io->res.k = *params->cur_con_sogi_k;
    state->pr_ia_io->res.w = *params->cur_con_sogi_w;
    state->pr_ia_io->res.intg1.out = 0.0f;
    state->pr_ia_io->res.intg1.lower_lmt = *params->cur_con_lower_lmt;
    state->pr_ia_io->res.intg1.upper_lmt = *params->cur_con_upper_lmt;
    state->pr_ia_io->res.intg1.Ts = *params->Ts;
    state->pr_ia_io->res.intg2.out = 0.0f;
    state->pr_ia_io->res.intg2.lower_lmt = *params->cur_con_lower_lmt;
    state->pr_ia_io->res.intg2.upper_lmt = *params->cur_con_upper_lmt;
    state->pr_ia_io->res.intg2.Ts = *params->Ts;



    state->pr_ib_io->kp = *params->cur_kp;
    state->pr_ib_io->ki = *params->cur_ki;
    state->pr_ib_io->lower_lmt = *params->cur_con_lower_lmt;
    state->pr_ib_io->upper_lmt = *params->cur_con_upper_lmt;
    state->pr_ib_io->out = 0.0f;
    state->pr_ib_io->res.k = *params->cur_con_sogi_k;
    state->pr_ib_io->res.w = *params->cur_con_sogi_w;   
    state->pr_ib_io->res.intg1.out = 0.0f;
    state->pr_ib_io->res.intg1.lower_lmt = *params->cur_con_lower_lmt;
    state->pr_ib_io->res.intg1.upper_lmt = *params->cur_con_upper_lmt;
    state->pr_ib_io->res.intg1.Ts = *params->Ts;
    state->pr_ib_io->res.intg2.out = 0.0f;
    state->pr_ib_io->res.intg2.lower_lmt = *params->cur_con_lower_lmt;
    state->pr_ib_io->res.intg2.upper_lmt = *params->cur_con_upper_lmt;
    state->pr_ib_io->res.intg2.Ts = *params->Ts;



    state->pr_ic_io->kp = *params->cur_kp;
    state->pr_ic_io->ki = *params->cur_ki;
    state->pr_ic_io->lower_lmt = *params->cur_con_lower_lmt;
    state->pr_ic_io->upper_lmt = *params->cur_con_upper_lmt;
    state->pr_ic_io->out = 0.0f;
    state->pr_ic_io->res.k = *params->cur_con_sogi_k;
    state->pr_ic_io->res.w = *params->cur_con_sogi_w; 
    state->pr_ic_io->res.intg1.out = 0.0f;
    state->pr_ic_io->res.intg1.lower_lmt = *params->cur_con_lower_lmt;
    state->pr_ic_io->res.intg1.upper_lmt = *params->cur_con_upper_lmt;
    state->pr_ic_io->res.intg1.Ts = *params->Ts;
    state->pr_ic_io->res.intg2.out = 0.0f;
    state->pr_ic_io->res.intg2.lower_lmt = *params->cur_con_lower_lmt;
    state->pr_ic_io->res.intg2.upper_lmt = *params->cur_con_upper_lmt;
    state->pr_ic_io->res.intg2.Ts = *params->Ts;


}


void CurController_calc(CURCONTROLLER_IN_TYPE *in, CURCONTROLLER_STATE_TYPE *state,CURCONTROLLER_PARAMS_TYPE *params, CURCONTROLLER_OUT_TYPE *out)
{
   
    float32 temp;

    //Phase A current control
    state->pr_ia_io->error = in->iabc_ref.A - in->iabc_fdbk.A;
    state->pr_ia_io->res.w = in->w_est;
    GenericBlocks_PR(state->pr_ia_io);
    temp = state->pr_ia_io->out;
    out->duty_abc.A = temp * (*params->scaler);

    //Phase B current control
    state->pr_ib_io->error = in->iabc_ref.B - in->iabc_fdbk.B;
    state->pr_ib_io->res.w = in->w_est;
    GenericBlocks_PR(state->pr_ib_io);
    temp = state->pr_ib_io->out;
    out->duty_abc.B = temp * (*params->scaler);

    //Phase C current control
    state->pr_ic_io->error = in->iabc_ref.C - in->iabc_fdbk.C;
    state->pr_ic_io->res.w = in->w_est;
    GenericBlocks_PR(state->pr_ic_io);
    temp = state->pr_ic_io->out;
    out->duty_abc.C = temp * (*params->scaler);

   printf("kp == %f \n", state->pr_ic_io->kp);
}
