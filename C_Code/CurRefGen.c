#include<stdio.h>
#include"generic/GenericBlocks.h"
#include "Vienna.h"
#include "CurRefGen.h"



void CurRefGen_initialize()
{
   
}


void CurRefGen_calc(CURREFGEN_IN_TYPE *in, CURREFGEN_OUT_TYPE *out)
{
   
    float32 fact,p_ref;
    float32 v_al_p,v_be_p,v_al_n,v_be_n;
    float32 i_al_p,i_be_p,i_al_n,i_be_n;
    float32 i_al,i_be;
    ALPHA_BETA_TYPE i_alpha_beta;

    p_ref = in->vbus_con_out;
    v_al_p = in->seq_comps.v_al_pos;
    v_be_p = in->seq_comps.v_be_pos;
    v_al_n = in->seq_comps.v_al_neg;
    v_be_n = in->seq_comps.v_be_neg;


    fact = (p_ref*2/3)/(v_al_p*v_al_p+ v_be_p * v_be_p - v_al_n*v_al_n - v_be_n*v_be_n);

    i_al_p  = v_al_p*fact;
    i_be_p  = v_be_p*fact;
    i_al_n  = -v_al_n*fact;
    i_be_n  = -v_be_n*fact;

    i_al = i_al_p + i_al_n;
    i_be = i_be_p + i_be_n;

    i_alpha_beta.Alpha = i_al;
    i_alpha_beta.Beta = i_be;

    GenericBlocks_InvClarke(&i_alpha_beta,&out->iabc);

    out->debug1 = i_al_p;
    out->debug2 =  i_alpha_beta.Alpha;


   
}
