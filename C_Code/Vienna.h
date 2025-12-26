
#ifndef VIENNA_H_
#define VIENNA_H_

#include"generic/ViennaBasicTypes.h"

typedef struct
{
    //PLL related
    ABC_TYPE Vabc;
    ALPHA_BETA_TYPE ValphaBeta;
    SOGI_IO_TYPE sogi_alpha_io;
    SOGI_IO_TYPE sogi_beta_io;
    SEQ_COMP_TYPE ValphaBetaSeq;
    PI_IO_TYPE  pll_pi_io;
    DQ_TYPE DQ;

    //Vbus control related
    PI_IO_TYPE  vbus_pi_io;
    float32 vbus_ref;


    //Current control related
    PR_IO_TYPE pr_ia_io;
    PR_IO_TYPE pr_ib_io;
    PR_IO_TYPE pr_ic_io;

    

} VIENNA_TYPE;   

typedef struct
{

    float32	Pout ;
    float32	Vac_ll_rms ;
    float32	Fac ;
    float32	Wac ;
    float32	Tac ;
    float32	Vout ;
    float32	Iout ;
    float32	Eff ;
    float32	Fs ;
    float32	Tsw ;
    float32	Tcur_loop ;
    float32	Tvolt_loop ;
    float32	Pin_max ;
    float32	Pin ;
    float32	Igrid_ph_pk ;
    float32	cur_ripple ;
    float32	L ;
    float32	L_ESR ;
    float32	Vripple ;
    float32	C ;
    float32	Vac_ph_rms ;
    float32	Vac_ph_pk ;
    float32	Vref ;
    float32	Rload ;
        
        
    float32 cur_con_kp;
    float32 cur_con_ki;
    float32	cur_con_upper_lmt;
    float32	cur_con_lower_lmt;
    float32 cur_con_sogi_k;
    float32 cur_con_sogi_w;
    float32 cur_con_out_scaler;
        
    float32	sogi_k;
    float32	sogi_upper_lmt;
    float32	sogi_lower_lmt;
        
    float32	pll_kp;
    float32	pll_ki;
    float32	pll_pi_upper_lmt;
    float32	pll_pi_lower_lmt;

    float32	vbus_kp;
    float32	vbus_ki;
    float32	vbus_con_upper_lmt;
    float32	vbus_con_lower_lmt;
    float32 vbus_ref_init;
    
} VIENNA_PARAM_TYPE;  

void vienna_calc();
void vienna_initialize();


#endif //end of VIENNA_H_