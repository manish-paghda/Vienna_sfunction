#include<stdio.h>
#include"generic/GenericBlocks.h"
#include "Vienna.h"
#include "Pll.h"




// extern PLL_IO_TYPE pll_in;
// extern PLL_STATE_TYPE pll_state;
// extern PLL_OUT_TYPE pll_out;
// extern PLL_PARAMS_TYPE pll_params;

// float32 test_var = 45.0f;

void Pll_initialize(PLL_STATE_TYPE *state,PLL_PARAMS_TYPE *pll_params)
{
    state->sogi_alpha_io->w = *pll_params->Fac *TWO_PI;
    state->sogi_alpha_io->k = *pll_params->sogi_k;
    state->sogi_alpha_io->intg1.upper_lmt = *pll_params->sogi_upper_lmt;
    state->sogi_alpha_io->intg1.lower_lmt = *pll_params->sogi_lower_lmt;
    state->sogi_alpha_io->intg1.out = 0.0f;
    state->sogi_alpha_io->intg2.upper_lmt = *pll_params->sogi_upper_lmt;
    state->sogi_alpha_io->intg2.lower_lmt = *pll_params->sogi_lower_lmt;
    state->sogi_alpha_io->intg2.out = 0.0f;
    state->sogi_alpha_io->intg1.Ts = *pll_params->Ts;
    state->sogi_alpha_io->intg2.Ts = *pll_params->Ts;

    state->sogi_beta_io->w = *pll_params->Fac *TWO_PI;
    state->sogi_beta_io->k = *pll_params->sogi_k;
    state->sogi_beta_io->intg1.upper_lmt = *pll_params->sogi_upper_lmt;
    state->sogi_beta_io->intg1.lower_lmt = *pll_params->sogi_lower_lmt;
    state->sogi_beta_io->intg1.out = 0.0f;
    state->sogi_beta_io->intg2.upper_lmt = *pll_params->sogi_upper_lmt;
    state->sogi_beta_io->intg2.lower_lmt = *pll_params->sogi_lower_lmt;
    state->sogi_beta_io->intg2.out = 0.0f;
    state->sogi_beta_io->intg1.Ts = *pll_params->Ts;
    state->sogi_beta_io->intg2.Ts = *pll_params->Ts;

    state->pi_io->kp = *pll_params->pll_kp;
    state->pi_io->ki = *pll_params->pll_ki;
    state->pi_io->upper_lmt = *pll_params->pll_pi_upper_lmt;
    state->pi_io->lower_lmt = *pll_params->pll_pi_lower_lmt;
    state->pi_io->intg.out = 0.0f;
    state->pi_io->out = 0.0f;

}

void Pll_calc(PLL_IN_TYPE *in, PLL_STATE_TYPE *state,PLL_PARAMS_TYPE *params, PLL_OUT_TYPE *out)
{
    float32 temp;
    PARK_IN_TYPE park_in;
    ABC_TYPE *clarke_in;
    ALPHA_BETA_TYPE *clarke_out;

    clarke_out = state->ValphaBeta;
    GenericBlocks_Clarke(&in->Vabc, state->ValphaBeta);

    printf("alpha = %f\n",state->ValphaBeta->Alpha);
    printf("beta = %f\n",state->ValphaBeta->Beta );


    state->sogi_alpha_io->w = out->w_est;
    state->sogi_alpha_io->in = state->ValphaBeta->Alpha;
    GenericBlocks_Sogi(state->sogi_alpha_io);


    state->sogi_beta_io->w = out->w_est;
    state->sogi_beta_io->in = state->ValphaBeta->Beta;
    GenericBlocks_Sogi(state->sogi_beta_io);

    Pll_GetSeqComps(state);

    park_in.AlBeZero.Alpha = state->ValphaBetaSeq->v_al_pos;
    park_in.AlBeZero.Beta = state->ValphaBetaSeq->v_be_pos;
    park_in.AlBeZero.ZeroSequence = 0.0f;
    park_in.th = out->th_est;


    GenericBlocks_Park(&park_in,state->DQ);


    state->pi_io->error = state->DQ->q;
    // pll_io.pi_io->error = 50.0f;
    GenericBlocks_PI(state->pi_io);
    temp = state->pi_io->out;

    // out->w_est = temp + vienna_params.w_rated;
    out->w_est = temp + 2.0f*3.1416f*50.0f;

    out->th_est = out->th_est +  out->w_est* (*params->Ts);

    if(out->th_est > TWO_PI)
    {
        out->th_est =  out->th_est - TWO_PI;
    }
    else if(out->th_est < 0.0f)
    {
        out->th_est = -1.0 * out->th_est ;
    }

    out->seq_comps =   *state->ValphaBetaSeq;

    out->debug1 = *params->pll_kp;
    out->debug2 = *params->sogi_k;

}

void Pll_GetSeqComps(PLL_STATE_TYPE *state)
{

    float32 v_al,qv_al,v_be,qv_be;

    v_al = state->sogi_alpha_io->out;
    qv_al = state->sogi_alpha_io->out_quadrature;
    v_be = state->sogi_beta_io->out;
    qv_be = state->sogi_beta_io->out_quadrature;

    state->ValphaBetaSeq->v_al_pos = (v_al - qv_be)*0.5f;
    state->ValphaBetaSeq->v_be_pos = (v_be + qv_al)*0.5f;
    state->ValphaBetaSeq->v_al_neg = (v_al + qv_be)*0.5f;
    state->ValphaBetaSeq->v_be_neg = (v_be - qv_al)*0.5f;

}
