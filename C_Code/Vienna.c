#include<stdio.h>
#include <time.h>
#include"generic/GenericBlocks.h"
#include "Vienna.h"
#include "Pll.h"
#include "VbusController.h"
#include "CurRefGen.h"
#include "CurController.h"


#define COMPILE_FOR_SIMULATION

void sim_pll_calc(PLL_IN_TYPE *in, PLL_OUT_TYPE *out );
void sim_VbusController_calc(VBUSCONTROLLER_IN_TYPE *in, VBUSCONTROLLER_OUT_TYPE *out);
void sim_CurRefGen_calc(CURREFGEN_IN_TYPE *in, CURREFGEN_OUT_TYPE *out);
void sim_CurController_calc(CURCONTROLLER_IN_TYPE *in, CURCONTROLLER_OUT_TYPE *out);

VIENNA_TYPE vienna_io;
VIENNA_PARAM_TYPE vienna_params;

PLL_IN_TYPE pll_in;
PLL_STATE_TYPE pll_state;
PLL_OUT_TYPE pll_out;
PLL_PARAMS_TYPE pll_params;

VBUSCONTROLLER_IN_TYPE vbus_con_in;
VBUSCONTROLLER_STATE_TYPE vbus_con_state;
VBUSCONTROLLER_OUT_TYPE vbus_con_out;
VBUSCONTROLLER_PARAMS_TYPE vbus_con_params;

CURREFGEN_IN_TYPE cur_ref_gen_in;
CURREFGEN_OUT_TYPE cur_ref_gen_out;

CURCONTROLLER_IN_TYPE cur_con_in;
CURCONTROLLER_STATE_TYPE cur_con_state;
CURCONTROLLER_OUT_TYPE cur_con_out;
CURCONTROLLER_PARAMS_TYPE cur_con_params;

ABC_TYPE Vabc;

void vienna_initialize()
{
    //------------vienna params --------------//
    vienna_params.Pout = 12000.0f;
    vienna_params.Vac_ll_rms = 400.0f;
    vienna_params.Fac = 50.0f;
    vienna_params.Wac = vienna_params.Fac*TWO_PI;
    vienna_params.Tac = 1.0f/vienna_params.Fac;
    vienna_params.Vout = 800.0f;
    vienna_params.Iout = vienna_params.Pout/vienna_params.Vout;
    vienna_params.Eff = 0.97f;
    vienna_params.Fs = 70000.0f;
    vienna_params.Tsw = 1.0f/vienna_params.Fs;
    vienna_params.Tcur_loop = vienna_params.Tsw*2.0f;
    vienna_params.Tvolt_loop = vienna_params.Tcur_loop;
    vienna_params.Pin_max = vienna_params.Pout/vienna_params.Eff * 1.5f;

    vienna_params.Pin = vienna_params.Pout/ vienna_params.Eff;
    vienna_params.Igrid_ph_pk = SQRT_2*vienna_params.Pin/(SQRT_3*vienna_params.Vac_ll_rms);
    // vienna_params.cur_ripple = vienna_params.Igrid_ph_pk*0.05f; // 1%
    // vienna_params.L = vienna_params.Vout/(8*vienna_params.cur_ripple*vienna_params.Fs);
    // vienna_params.L_ESR = 0.0468;

    // vienna_params.Vripple = vienna_params.Vout*0.01;
    // vienna_params.C = (vienna_params.Iout*0.005)*0.98*vienna_params.Tac/vienna_params.Vripple

    vienna_params.Vac_ph_rms = vienna_params.Vac_ll_rms/SQRT_3; //rms
    vienna_params.Vac_ph_pk = vienna_params.Vac_ph_rms*SQRT_2;
    vienna_params.Vref = vienna_params.Vout;
    // vienna_params.Rload = vienna_params.Vref ^2/vienna_params.Pout;

    //Current control params
    vienna_params.cur_con_upper_lmt = vienna_params.Vout/2.0f;
    vienna_params.cur_con_lower_lmt = -vienna_params.cur_con_upper_lmt;
    vienna_params.cur_con_kp = 50.0f ;
    vienna_params.cur_con_ki = 300.0f ;
    vienna_params.cur_con_out_scaler = 2.0f/vienna_params.Vout *0.98f;
    vienna_params.cur_con_sogi_k = 0.06366198f;
    vienna_params.cur_con_sogi_w = vienna_params.Wac;

    //SOGI params
    vienna_params.sogi_k = 0.5f;
    vienna_params.sogi_upper_lmt = 500.0f;
    vienna_params.sogi_lower_lmt = -500.0f;
 
    // PLL params
    vienna_params.pll_kp = 3.0f ;
    vienna_params.pll_ki = 50.0f;
    vienna_params.pll_pi_upper_lmt =  TWO_PI * vienna_params.Fac*1.2f;;
    vienna_params.pll_pi_lower_lmt = -TWO_PI * vienna_params.Fac*1.2f;

    //Vbus control params
    vienna_params.vbus_ref_init = vienna_params.Vac_ph_pk *SQRT_3;
    vienna_params.vbus_kp = 0.5f*400.0f *(1.0f/70000.0f)/vienna_params.Tvolt_loop;
    vienna_params.vbus_ki = 100.0f*400.0f *(1.0f/70000.0f)/vienna_params.Tvolt_loop;

    vienna_params.vbus_con_upper_lmt =  vienna_params.Pin_max;
    vienna_params.vbus_con_lower_lmt = 0;

    //-------- Individual modules parameters initialization ------//
    pll_params.Fac = &vienna_params.Fac;

    //----------- PLL ------------------//
	// pll_in.Vabc  = &vienna_io.Vabc;
    pll_state.sogi_alpha_io  = &vienna_io.sogi_alpha_io;
    pll_state.sogi_beta_io  = &vienna_io.sogi_beta_io; 
    pll_state.pi_io  = &vienna_io.pll_pi_io;
    pll_state.DQ = &vienna_io.DQ;
    pll_state.ValphaBeta = &vienna_io.ValphaBeta;
    pll_state.ValphaBetaSeq = &vienna_io.ValphaBetaSeq;

    pll_params.Fac = &vienna_params.Fac;
    pll_params.sogi_k = &vienna_params.sogi_k;
    pll_params.sogi_lower_lmt = &vienna_params.sogi_lower_lmt;
    pll_params.sogi_upper_lmt = &vienna_params.sogi_upper_lmt;
    pll_params.Ts = &vienna_params.Tvolt_loop;

    pll_params.pll_pi_upper_lmt = &vienna_params.pll_pi_upper_lmt;
    pll_params.pll_pi_lower_lmt = &vienna_params.pll_pi_lower_lmt;
    pll_params.pll_kp = &vienna_params.pll_kp;
    pll_params.pll_ki = &vienna_params.pll_ki;

    Pll_initialize(&pll_state, &pll_params);


    //----------- VBUS CONTROLLER ------------------//

    vbus_con_state.pi_io = &vienna_io.vbus_pi_io;
    vbus_con_state.vbus_ref = &vienna_io.vbus_ref;

    vbus_con_params.vbus_con_upper_lmt = &vienna_params.vbus_con_upper_lmt;
    vbus_con_params.vbus_con_lower_lmt = &vienna_params.vbus_con_lower_lmt;
    vbus_con_params.vbus_kp = &vienna_params.vbus_kp;
    vbus_con_params.vbus_ki = &vienna_params.vbus_ki;
    vbus_con_params.Ts = &vienna_params.Tvolt_loop;

    vbus_con_params.vbus_target = &vienna_params.Vref;
    vbus_con_params.vbus_ref_init = &vienna_params.vbus_ref_init;

    VbusController_initialize(&vbus_con_state, &vbus_con_params);

    //----------- CURRENT REF GEN------------------//

    //----------- CURRENT CONTROLLER---------------//
    cur_con_state.pr_ia_io = &vienna_io.pr_ia_io;
    cur_con_state.pr_ib_io = &vienna_io.pr_ib_io;
    cur_con_state.pr_ic_io = &vienna_io.pr_ic_io;
 

    cur_con_params.cur_con_upper_lmt =  &vienna_params.cur_con_upper_lmt;
    cur_con_params.cur_con_lower_lmt =  &vienna_params.cur_con_lower_lmt;
    cur_con_params.cur_kp =  &vienna_params.cur_con_kp;
    cur_con_params.cur_ki =  &vienna_params.cur_con_ki;
    cur_con_params.Ts = &vienna_params.Tcur_loop;

    cur_con_params.scaler = &vienna_params.cur_con_out_scaler;
    cur_con_params.cur_con_sogi_k = &vienna_params.cur_con_sogi_k;
    cur_con_params.cur_con_sogi_w = &vienna_params.cur_con_sogi_w;

    // cur_con_state.w_est = &pll_out.w_est;

    CurController_initialize(&cur_con_state, &cur_con_params);

}

void vienna_calc()
{

    // cur_ref_gen_in.seq_comps.v_al_pos = 300.0f;
    // cur_ref_gen_in.seq_comps.v_al_neg = 100.0f;
    // cur_ref_gen_in.seq_comps.v_be_pos = 0.0f;
    // cur_ref_gen_in.seq_comps.v_be_neg = 0.0f;
    // cur_ref_gen_in.vbus_con_out = 3000.0f;

#ifdef COMPILE_FOR_SIMULATION

    sim_pll_calc(&pll_in, &pll_out);
    sim_VbusController_calc(&vbus_con_in, &vbus_con_out);
    sim_CurRefGen_calc(&cur_ref_gen_in, &cur_ref_gen_out);
    sim_CurController_calc(&cur_con_in, &cur_con_out);

#else

    ReadADC();

    Pll_calc(&pll_in, &pll_state, &pll_params, &pll_out);
    VbusController_calc(&vbus_con_in,&vbus_con_state, &vbus_con_params, &vbus_con_out);
    CurRefGen_calc(&cur_ref_gen_in, &cur_ref_gen_out);
    CurController_calc(&cur_con_in, &cur_con_state, &cur_con_params,&cur_con_out);

    GeneratePWMs();
#endif
}

void sim_pll_calc(PLL_IN_TYPE *in, PLL_OUT_TYPE *out )
{
    Pll_calc(in, &pll_state, &pll_params, out);
}

void sim_VbusController_calc(VBUSCONTROLLER_IN_TYPE *in, VBUSCONTROLLER_OUT_TYPE *out)
{
    VbusController_calc(in, &vbus_con_state, &vbus_con_params, out);
}

void sim_CurRefGen_calc(CURREFGEN_IN_TYPE *in, CURREFGEN_OUT_TYPE *out)
{
    CurRefGen_calc(in, out);
}

void sim_CurController_calc(CURCONTROLLER_IN_TYPE *in, CURCONTROLLER_OUT_TYPE *out)
{
    CurController_calc(in, &cur_con_state, &cur_con_params, out);
}