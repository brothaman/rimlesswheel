/*
Generated 20-Jul-2007 21:06:48 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041


ROADMAP (rowdy.sd)

Bodies          Inb
No  Name        body Joint type  Coords q         Multipliers
--- ----------- ---- ----------- ---------------- -----------------------
 -1 $ground                                      |
  0 main_body    -1  Sixdof        0   1   2     |
                     ...           3   4   5   8 |
  1 left_wheel    0  Pin           6?            |  0p
  2 right_wheel   0  Pin           7?            |  1p

User Constraints

  0 user_0                                       |  2
  1 user_1                                       |  3
  2 user_2                                       |  4
  3 user_3                                       |  5
  4 user_4                                       |  6
  5 user_5                                       |  7
  6 user_6                                       |  8
  7 user_7                                       |  9
  8 user_8                                       | 10

*/
#include <math.h>
#include <stdio.h>

typedef struct {
    int ground_,nbod_,ndof_,ncons_,nloop_,nldof_,nloopc_,nball_,nlball_,npres_,
      nuser_;
    int jtype_[3],inb_[3],outb_[3],njntdof_[3],njntc_[3],njntp_[3],firstq_[3],
      ballq_[3],firstm_[3],firstp_[3];
    int trans_[8],firstu_[9];
} sdgtopo_t;
#define ground (sdgtopo.ground_)
#define nbod (sdgtopo.nbod_)
#define ndof (sdgtopo.ndof_)
#define ncons (sdgtopo.ncons_)
#define nloop (sdgtopo.nloop_)
#define nldof (sdgtopo.nldof_)
#define nloopc (sdgtopo.nloopc_)
#define nball (sdgtopo.nball_)
#define nlball (sdgtopo.nlball_)
#define npres (sdgtopo.npres_)
#define nuser (sdgtopo.nuser_)
#define jtype (sdgtopo.jtype_)
#define inb (sdgtopo.inb_)
#define outb (sdgtopo.outb_)
#define njntdof (sdgtopo.njntdof_)
#define njntc (sdgtopo.njntc_)
#define njntp (sdgtopo.njntp_)
#define firstq (sdgtopo.firstq_)
#define ballq (sdgtopo.ballq_)
#define firstm (sdgtopo.firstm_)
#define firstp (sdgtopo.firstp_)
#define trans (sdgtopo.trans_)
#define firstu (sdgtopo.firstu_)

typedef struct {
    double grav_[3],mk_[3],ik_[3][3][3],pin_[8][3];
    double rk_[3][3],ri_[3][3],pres_[8],stabvel_,stabpos_;
    int mfrcflg_,roustate_,vpkflg_,inerflg_,mmflg_,mmlduflg_,wwflg_,ltauflg_,
      fs0flg_,ii_,mmap_[8];
    int gravq_[3],mkq_[3],ikq_[3][3][3],pinq_[8][3],rkq_[3][3],riq_[3][3],presq_
      [8],stabvelq_,stabposq_;
    double mtot_,psmkg_,rhead_[3][3],rcom_[3][3],mkrcomt_[3][3][3],psikg_[3][3],
      psrcomg_[3],psrkg_[3],psrig_[3],psmk_[8],psik_[8][3][3],psrcom_[8][3],
      psrk_[8][3],psri_[8][3];
} sdginput_t;
#define grav (sdginput.grav_)
#define mk (sdginput.mk_)
#define ik (sdginput.ik_)
#define pin (sdginput.pin_)
#define rk (sdginput.rk_)
#define ri (sdginput.ri_)
#define pres (sdginput.pres_)
#define stabvel (sdginput.stabvel_)
#define stabpos (sdginput.stabpos_)
#define rhead (sdginput.rhead_)
#define rcom (sdginput.rcom_)
#define psrcomg (sdginput.psrcomg_)
#define psrcom (sdginput.psrcom_)
#define mkrcomt (sdginput.mkrcomt_)
#define psmk (sdginput.psmk_)
#define psik (sdginput.psik_)
#define psrk (sdginput.psrk_)
#define psri (sdginput.psri_)
#define psmkg (sdginput.psmkg_)
#define psikg (sdginput.psikg_)
#define psrkg (sdginput.psrkg_)
#define psrig (sdginput.psrig_)
#define mtot (sdginput.mtot_)
#define mfrcflg (sdginput.mfrcflg_)
#define roustate (sdginput.roustate_)
#define vpkflg (sdginput.vpkflg_)
#define inerflg (sdginput.inerflg_)
#define mmflg (sdginput.mmflg_)
#define mmlduflg (sdginput.mmlduflg_)
#define wwflg (sdginput.wwflg_)
#define ltauflg (sdginput.ltauflg_)
#define fs0flg (sdginput.fs0flg_)
#define ii (sdginput.ii_)
#define mmap (sdginput.mmap_)
#define gravq (sdginput.gravq_)
#define mkq (sdginput.mkq_)
#define ikq (sdginput.ikq_)
#define pinq (sdginput.pinq_)
#define rkq (sdginput.rkq_)
#define riq (sdginput.riq_)
#define presq (sdginput.presq_)
#define stabvelq (sdginput.stabvelq_)
#define stabposq (sdginput.stabposq_)

typedef struct {
    double curtim_,q_[9],qn_[9],u_[8],cnk_[8][3][3],cnb_[3][3][3];
    double rnk_[8][3],vnk_[8][3],wk_[8][3],rnb_[3][3],vnb_[3][3],wb_[3][3],
      wbrcom_[3][3],com_[3],rnkg_[3];
    double Cik_[8][3][3],rikt_[8][3][3],Iko_[8][3][3],mkrk_[8][3][3],Cib_[3][3][
      3];
    double Wkk_[8][3],Vkk_[8][3],dik_[8][3],rpp_[8][3],rpk_[8][3],rik_[8][3],
      rik2_[8][3];
    double rpri_[8][3],Wik_[8][3],Vik_[8][3],Wirk_[8][3],rkWkk_[8][3],Wkrpk_[8][
      3],VikWkr_[8][3];
    double perr_[11],verr_[11],aerr_[11],mult_[11],ufk_[3][3],utk_[3][3],mfk_[3
      ][3],mtk_[3][3];
    double utau_[8],mtau_[8],uacc_[8],uvel_[8],upos_[9];
    double s6_,c6_,s7_,c7_;
} sdgstate_t;
#define curtim (sdgstate.curtim_)
#define q (sdgstate.q_)
#define qn (sdgstate.qn_)
#define u (sdgstate.u_)
#define cnk (sdgstate.cnk_)
#define cnb (sdgstate.cnb_)
#define rnkg (sdgstate.rnkg_)
#define rnk (sdgstate.rnk_)
#define rnb (sdgstate.rnb_)
#define vnk (sdgstate.vnk_)
#define vnb (sdgstate.vnb_)
#define wk (sdgstate.wk_)
#define wb (sdgstate.wb_)
#define com (sdgstate.com_)
#define Cik (sdgstate.Cik_)
#define Cib (sdgstate.Cib_)
#define rikt (sdgstate.rikt_)
#define Iko (sdgstate.Iko_)
#define mkrk (sdgstate.mkrk_)
#define Wkk (sdgstate.Wkk_)
#define Vkk (sdgstate.Vkk_)
#define dik (sdgstate.dik_)
#define rpp (sdgstate.rpp_)
#define rpk (sdgstate.rpk_)
#define rik (sdgstate.rik_)
#define rik2 (sdgstate.rik2_)
#define rpri (sdgstate.rpri_)
#define Wik (sdgstate.Wik_)
#define Vik (sdgstate.Vik_)
#define Wirk (sdgstate.Wirk_)
#define rkWkk (sdgstate.rkWkk_)
#define Wkrpk (sdgstate.Wkrpk_)
#define VikWkr (sdgstate.VikWkr_)
#define wbrcom (sdgstate.wbrcom_)
#define perr (sdgstate.perr_)
#define verr (sdgstate.verr_)
#define aerr (sdgstate.aerr_)
#define mult (sdgstate.mult_)
#define ufk (sdgstate.ufk_)
#define utk (sdgstate.utk_)
#define utau (sdgstate.utau_)
#define mfk (sdgstate.mfk_)
#define mtk (sdgstate.mtk_)
#define mtau (sdgstate.mtau_)
#define uacc (sdgstate.uacc_)
#define uvel (sdgstate.uvel_)
#define upos (sdgstate.upos_)
#define s6 (sdgstate.s6_)
#define c6 (sdgstate.c6_)
#define s7 (sdgstate.s7_)
#define c7 (sdgstate.c7_)

typedef struct {
    double fs0_[8],qdot_[9],Otk_[8][3],Atk_[8][3],AiOiWi_[8][3],Fstar_[8][3];
    double Tstar_[8][3],Fstark_[8][3],Tstark_[8][3],IkWk_[8][3],WkIkWk_[8][3],
      gk_[8][3],IkbWk_[3][3],WkIkbWk_[3][3];
    double w0w0_[3],w1w1_[3],w2w2_[3],w0w1_[3],w0w2_[3],w1w2_[3];
    double w00w11_[3],w00w22_[3],w11w22_[3],ww_[11][11],qraux_[11];
    double mm_[8][8],mlo_[8][8],mdi_[8],IkWpk_[8][8][3],works_[8],workss_[8][8];
    double Wpk_[8][8][3],Vpk_[8][8][3],VWri_[8][8][3];
    int wmap_[11],multmap_[11],jpvt_[11],wsiz_,wrank_;
} sdglhs_t;
#define qdot (sdglhs.qdot_)
#define Otk (sdglhs.Otk_)
#define Atk (sdglhs.Atk_)
#define AiOiWi (sdglhs.AiOiWi_)
#define Fstar (sdglhs.Fstar_)
#define Tstar (sdglhs.Tstar_)
#define fs0 (sdglhs.fs0_)
#define Fstark (sdglhs.Fstark_)
#define Tstark (sdglhs.Tstark_)
#define IkWk (sdglhs.IkWk_)
#define IkbWk (sdglhs.IkbWk_)
#define WkIkWk (sdglhs.WkIkWk_)
#define WkIkbWk (sdglhs.WkIkbWk_)
#define gk (sdglhs.gk_)
#define w0w0 (sdglhs.w0w0_)
#define w1w1 (sdglhs.w1w1_)
#define w2w2 (sdglhs.w2w2_)
#define w0w1 (sdglhs.w0w1_)
#define w0w2 (sdglhs.w0w2_)
#define w1w2 (sdglhs.w1w2_)
#define w00w11 (sdglhs.w00w11_)
#define w00w22 (sdglhs.w00w22_)
#define w11w22 (sdglhs.w11w22_)
#define ww (sdglhs.ww_)
#define qraux (sdglhs.qraux_)
#define mm (sdglhs.mm_)
#define mlo (sdglhs.mlo_)
#define mdi (sdglhs.mdi_)
#define IkWpk (sdglhs.IkWpk_)
#define works (sdglhs.works_)
#define workss (sdglhs.workss_)
#define Wpk (sdglhs.Wpk_)
#define Vpk (sdglhs.Vpk_)
#define VWri (sdglhs.VWri_)
#define wmap (sdglhs.wmap_)
#define multmap (sdglhs.multmap_)
#define jpvt (sdglhs.jpvt_)
#define wsiz (sdglhs.wsiz_)
#define wrank (sdglhs.wrank_)

typedef struct {
    double fs_[8],udot_[8],tauc_[8],dyad_[3][3][3],fc_[8][3],tc_[8][3];
    double ank_[8][3],onk_[8][3],Onkb_[8][3],AOnkri_[8][3],Ankb_[8][3],AnkAtk_[8
      ][3],anb_[3][3],onb_[3][3],dyrcom_[3][3];
    double ffk_[8][3],ttk_[8][3],fccikt_[8][3],ffkb_[3][3],ttkb_[3][3];
} sdgrhs_t;
#define fs (sdgrhs.fs_)
#define udot (sdgrhs.udot_)
#define ank (sdgrhs.ank_)
#define anb (sdgrhs.anb_)
#define onk (sdgrhs.onk_)
#define onb (sdgrhs.onb_)
#define Onkb (sdgrhs.Onkb_)
#define AOnkri (sdgrhs.AOnkri_)
#define Ankb (sdgrhs.Ankb_)
#define AnkAtk (sdgrhs.AnkAtk_)
#define dyrcom (sdgrhs.dyrcom_)
#define ffk (sdgrhs.ffk_)
#define ttk (sdgrhs.ttk_)
#define fccikt (sdgrhs.fccikt_)
#define ffkb (sdgrhs.ffkb_)
#define ttkb (sdgrhs.ttkb_)
#define dyad (sdgrhs.dyad_)
#define fc (sdgrhs.fc_)
#define tc (sdgrhs.tc_)
#define tauc (sdgrhs.tauc_)

typedef struct {
    double temp_[3000],tmat1_[3][3],tmat2_[3][3],tvec1_[3],tvec2_[3],tvec3_[3],
      tvec4_[3],tvec5_[3];
    double tsc1_,tsc2_,tsc3_;
} sdgtemp_t;
#define temp (sdgtemp.temp_)
#define tmat1 (sdgtemp.tmat1_)
#define tmat2 (sdgtemp.tmat2_)
#define tvec1 (sdgtemp.tvec1_)
#define tvec2 (sdgtemp.tvec2_)
#define tvec3 (sdgtemp.tvec3_)
#define tvec4 (sdgtemp.tvec4_)
#define tvec5 (sdgtemp.tvec5_)
#define tsc1 (sdgtemp.tsc1_)
#define tsc2 (sdgtemp.tsc2_)
#define tsc3 (sdgtemp.tsc3_)

sdgtopo_t sdgtopo = {
/*  Topological information
*/
    /* ground */ 1,
    /* nbod */ 3,
    /* ndof */ 8,
    /* ncons */ 11,
    /* nloop */ 0,
    /* nldof */ 0,
    /* nloopc */ 0,
    /* nball */ 1,
    /* nlball */ 0,
    /* npres */ 2,
    /* nuser */ 9,
    /* jtype[0] */ 6,
    /* jtype[1] */ 1,
    /* jtype[2] */ 1,
    /* inb[0] */ -1,
    /* inb[1] */ 0,
    /* inb[2] */ 0,
    /* outb[0] */ 0,
    /* outb[1] */ 1,
    /* outb[2] */ 2,
    /* njntdof[0] */ 6,
    /* njntdof[1] */ 1,
    /* njntdof[2] */ 1,
    /* njntc[0] */ 0,
    /* njntc[1] */ 0,
    /* njntc[2] */ 0,
    /* njntp[0] */ 0,
    /* njntp[1] */ 1,
    /* njntp[2] */ 1,
    /* firstq[0] */ 0,
    /* firstq[1] */ 6,
    /* firstq[2] */ 7,
    /* ballq[0] */ 8,
    /* ballq[1] */ -104,
    /* ballq[2] */ -104,
    /* firstm[0] */ -1,
    /* firstm[1] */ -1,
    /* firstm[2] */ -1,
    /* firstp[0] */ -1,
    /* firstp[1] */ 0,
    /* firstp[2] */ 1,
    /* trans[0] */ 1,
    /* trans[1] */ 1,
    /* trans[2] */ 1,
    /* trans[3] */ 0,
    /* trans[4] */ 0,
    /* trans[5] */ 0,
    /* trans[6] */ 0,
    /* trans[7] */ 0,
    /* firstu[0] */ 2,
    /* firstu[1] */ 3,
    /* firstu[2] */ 4,
    /* firstu[3] */ 5,
    /* firstu[4] */ 6,
    /* firstu[5] */ 7,
    /* firstu[6] */ 8,
    /* firstu[7] */ 9,
    /* firstu[8] */ 10,
};
sdginput_t sdginput = {
/* Model parameters from the input file */

/* gravity */
    /* grav[0] */ 0.,
    /* grav[1] */ 0.,
    /* grav[2] */ -9.81,

/* mass */
    /* mk[0] */ .5,
    /* mk[1] */ .1,
    /* mk[2] */ .1,

/* inertia */
    /* ik[0][0][0] */ 1.,
    /* ik[0][0][1] */ 0.,
    /* ik[0][0][2] */ 0.,
    /* ik[0][1][0] */ 0.,
    /* ik[0][1][1] */ 1.,
    /* ik[0][1][2] */ 0.,
    /* ik[0][2][0] */ 0.,
    /* ik[0][2][1] */ 0.,
    /* ik[0][2][2] */ 1.,
    /* ik[1][0][0] */ 1.,
    /* ik[1][0][1] */ 0.,
    /* ik[1][0][2] */ 0.,
    /* ik[1][1][0] */ 0.,
    /* ik[1][1][1] */ 1.,
    /* ik[1][1][2] */ 0.,
    /* ik[1][2][0] */ 0.,
    /* ik[1][2][1] */ 0.,
    /* ik[1][2][2] */ 1.,
    /* ik[2][0][0] */ 1.,
    /* ik[2][0][1] */ 0.,
    /* ik[2][0][2] */ 0.,
    /* ik[2][1][0] */ 0.,
    /* ik[2][1][1] */ 1.,
    /* ik[2][1][2] */ 0.,
    /* ik[2][2][0] */ 0.,
    /* ik[2][2][1] */ 0.,
    /* ik[2][2][2] */ 1.,

/* tree hinge axis vectors */
    /* pin[0][0] */ 1.,
    /* pin[0][1] */ 0.,
    /* pin[0][2] */ 0.,
    /* pin[1][0] */ 0.,
    /* pin[1][1] */ 1.,
    /* pin[1][2] */ 0.,
    /* pin[2][0] */ 0.,
    /* pin[2][1] */ 0.,
    /* pin[2][2] */ 1.,
    /* pin[3][0] */ 0.,
    /* pin[3][1] */ 0.,
    /* pin[3][2] */ 0.,
    /* pin[4][0] */ 0.,
    /* pin[4][1] */ 0.,
    /* pin[4][2] */ 0.,
    /* pin[5][0] */ 0.,
    /* pin[5][1] */ 0.,
    /* pin[5][2] */ 0.,
    /* pin[6][0] */ 1.,
    /* pin[6][1] */ 0.,
    /* pin[6][2] */ 0.,
    /* pin[7][0] */ 1.,
    /* pin[7][1] */ 0.,
    /* pin[7][2] */ 0.,

/* tree bodytojoint vectors */
    /* rk[0][0] */ 0.,
    /* rk[0][1] */ 0.,
    /* rk[0][2] */ 0.,
    /* rk[1][0] */ 0.,
    /* rk[1][1] */ 0.,
    /* rk[1][2] */ 0.,
    /* rk[2][0] */ 0.,
    /* rk[2][1] */ 0.,
    /* rk[2][2] */ 0.,

/* tree inbtojoint vectors */
    /* ri[0][0] */ 0.,
    /* ri[0][1] */ 0.,
    /* ri[0][2] */ 0.,
    /* ri[1][0] */ 0.,
    /* ri[1][1] */ 0.,
    /* ri[1][2] */ 0.,
    /* ri[2][0] */ 0.,
    /* ri[2][1] */ 0.,
    /* ri[2][2] */ 0.,

/* tree prescribed motion */
    /* pres[0] */ 0.,
    /* pres[1] */ 0.,
    /* pres[2] */ 0.,
    /* pres[3] */ 0.,
    /* pres[4] */ 0.,
    /* pres[5] */ 0.,
    /* pres[6] */ 0.,
    /* pres[7] */ 0.,

/* stabilization parameters */
    /* stabvel */ 0.,
    /* stabpos */ 0.,

/* miscellaneous */
    /* mfrcflg */ 0,
    /* roustate */ 0,
    /* vpkflg */ 0,
    /* inerflg */ 0,
    /* mmflg */ 0,
    /* mmlduflg */ 0,
    /* wwflg */ 0,
    /* ltauflg */ 0,
    /* fs0flg */ 0,
    /* ii */ 0,
    /* mmap[0] */ 0,
    /* mmap[1] */ 1,
    /* mmap[2] */ 2,
    /* mmap[3] */ 3,
    /* mmap[4] */ 4,
    /* mmap[5] */ 5,
    /* mmap[6] */ 6,
    /* mmap[7] */ 7,

/* Which parameters were "?" (1) or "<nominal>?" (3) */
    /* gravq[0] */ 0,
    /* gravq[1] */ 0,
    /* gravq[2] */ 0,
    /* mkq[0] */ 3,
    /* mkq[1] */ 3,
    /* mkq[2] */ 3,
    /* ikq[0][0][0] */ 3,
    /* ikq[0][0][1] */ 3,
    /* ikq[0][0][2] */ 3,
    /* ikq[0][1][0] */ 3,
    /* ikq[0][1][1] */ 3,
    /* ikq[0][1][2] */ 3,
    /* ikq[0][2][0] */ 3,
    /* ikq[0][2][1] */ 3,
    /* ikq[0][2][2] */ 3,
    /* ikq[1][0][0] */ 3,
    /* ikq[1][0][1] */ 3,
    /* ikq[1][0][2] */ 3,
    /* ikq[1][1][0] */ 3,
    /* ikq[1][1][1] */ 3,
    /* ikq[1][1][2] */ 3,
    /* ikq[1][2][0] */ 3,
    /* ikq[1][2][1] */ 3,
    /* ikq[1][2][2] */ 3,
    /* ikq[2][0][0] */ 3,
    /* ikq[2][0][1] */ 3,
    /* ikq[2][0][2] */ 3,
    /* ikq[2][1][0] */ 3,
    /* ikq[2][1][1] */ 3,
    /* ikq[2][1][2] */ 3,
    /* ikq[2][2][0] */ 3,
    /* ikq[2][2][1] */ 3,
    /* ikq[2][2][2] */ 3,
    /* pinq[0][0] */ 3,
    /* pinq[0][1] */ 3,
    /* pinq[0][2] */ 3,
    /* pinq[1][0] */ 3,
    /* pinq[1][1] */ 3,
    /* pinq[1][2] */ 3,
    /* pinq[2][0] */ 3,
    /* pinq[2][1] */ 3,
    /* pinq[2][2] */ 3,
    /* pinq[3][0] */ 0,
    /* pinq[3][1] */ 0,
    /* pinq[3][2] */ 0,
    /* pinq[4][0] */ 0,
    /* pinq[4][1] */ 0,
    /* pinq[4][2] */ 0,
    /* pinq[5][0] */ 0,
    /* pinq[5][1] */ 0,
    /* pinq[5][2] */ 0,
    /* pinq[6][0] */ 3,
    /* pinq[6][1] */ 3,
    /* pinq[6][2] */ 3,
    /* pinq[7][0] */ 3,
    /* pinq[7][1] */ 3,
    /* pinq[7][2] */ 3,
    /* rkq[0][0] */ 3,
    /* rkq[0][1] */ 3,
    /* rkq[0][2] */ 3,
    /* rkq[1][0] */ 3,
    /* rkq[1][1] */ 3,
    /* rkq[1][2] */ 3,
    /* rkq[2][0] */ 3,
    /* rkq[2][1] */ 3,
    /* rkq[2][2] */ 3,
    /* riq[0][0] */ 3,
    /* riq[0][1] */ 3,
    /* riq[0][2] */ 3,
    /* riq[1][0] */ 3,
    /* riq[1][1] */ 3,
    /* riq[1][2] */ 3,
    /* riq[2][0] */ 3,
    /* riq[2][1] */ 3,
    /* riq[2][2] */ 3,
    /* presq[0] */ 0,
    /* presq[1] */ 0,
    /* presq[2] */ 0,
    /* presq[3] */ 0,
    /* presq[4] */ 0,
    /* presq[5] */ 0,
    /* presq[6] */ 3,
    /* presq[7] */ 3,
    /* stabvelq */ 3,
    /* stabposq */ 3,

/* End of values from input file */

};
sdgstate_t sdgstate;
sdglhs_t sdglhs;
sdgrhs_t sdgrhs;
sdgtemp_t sdgtemp;


void sdinit(void)
{
/*
Initialization routine


 This routine must be called before the first call to sdstate(), after
 supplying values for any `?' parameters in the input.
*/
    double sumsq,norminv;
    int i,j,k;


/* Check that all `?' parameters have been assigned values */

    for (k = 0; k < 3; k++) {
        if (gravq[k] == 1) {
            sdseterr(7,25);
        }
    }
    for (k = 0; k < 3; k++) {
        if (mkq[k] == 1) {
            sdseterr(7,26);
        }
        for (i = 0; i < 3; i++) {
            if (rkq[k][i] == 1) {
                sdseterr(7,29);
            }
            if (riq[k][i] == 1) {
                sdseterr(7,30);
            }
            for (j = 0; j < 3; j++) {
                if (ikq[k][i][j] == 1) {
                    sdseterr(7,27);
                }
            }
        }
    }
    for (k = 0; k < 8; k++) {
        for (i = 0; i < 3; i++) {
            if (pinq[k][i] == 1) {
                sdseterr(7,28);
            }
        }
    }

/* Normalize pin vectors if necessary */

    sumsq = ((pin[0][2]*pin[0][2])+((pin[0][0]*pin[0][0])+(pin[0][1]*pin[0][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[0][0] = (norminv*pin[0][0]);
    pin[0][1] = (norminv*pin[0][1]);
    pin[0][2] = (norminv*pin[0][2]);
    sumsq = ((pin[1][2]*pin[1][2])+((pin[1][0]*pin[1][0])+(pin[1][1]*pin[1][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[1][0] = (norminv*pin[1][0]);
    pin[1][1] = (norminv*pin[1][1]);
    pin[1][2] = (norminv*pin[1][2]);
    sumsq = ((pin[2][2]*pin[2][2])+((pin[2][0]*pin[2][0])+(pin[2][1]*pin[2][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[2][0] = (norminv*pin[2][0]);
    pin[2][1] = (norminv*pin[2][1]);
    pin[2][2] = (norminv*pin[2][2]);
    sumsq = ((pin[6][2]*pin[6][2])+((pin[6][0]*pin[6][0])+(pin[6][1]*pin[6][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[6][0] = (norminv*pin[6][0]);
    pin[6][1] = (norminv*pin[6][1]);
    pin[6][2] = (norminv*pin[6][2]);
    sumsq = ((pin[7][2]*pin[7][2])+((pin[7][0]*pin[7][0])+(pin[7][1]*pin[7][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[7][0] = (norminv*pin[7][0]);
    pin[7][1] = (norminv*pin[7][1]);
    pin[7][2] = (norminv*pin[7][2]);

/* Zero out Vpk and Wpk */

    for (i = 0; i < 8; i++) {
        for (j = i; j <= 7; j++) {
            for (k = 0; k < 3; k++) {
                Vpk[i][j][k] = 0.;
                Wpk[i][j][k] = 0.;
            }
        }
    }

/* Compute pseudobody-related constants */

    rcom[0][0] = 0.;
    rcom[0][1] = 0.;
    rcom[0][2] = 0.;
    rcom[1][0] = 0.;
    rcom[1][1] = 0.;
    rcom[1][2] = 0.;
    rcom[2][0] = 0.;
    rcom[2][1] = 0.;
    rcom[2][2] = 0.;
    rkWkk[6][0] = ((pin[6][2]*rk[1][1])-(pin[6][1]*rk[1][2]));
    rkWkk[6][1] = ((pin[6][0]*rk[1][2])-(pin[6][2]*rk[1][0]));
    rkWkk[6][2] = ((pin[6][1]*rk[1][0])-(pin[6][0]*rk[1][1]));
    rkWkk[7][0] = ((pin[7][2]*rk[2][1])-(pin[7][1]*rk[2][2]));
    rkWkk[7][1] = ((pin[7][0]*rk[2][2])-(pin[7][2]*rk[2][0]));
    rkWkk[7][2] = ((pin[7][1]*rk[2][0])-(pin[7][0]*rk[2][1]));
    dik[6][0] = (ri[1][0]-rk[0][0]);
    dik[6][1] = (ri[1][1]-rk[0][1]);
    dik[6][2] = (ri[1][2]-rk[0][2]);
    dik[7][0] = (ri[2][0]-rk[0][0]);
    dik[7][1] = (ri[2][1]-rk[0][1]);
    dik[7][2] = (ri[2][2]-rk[0][2]);

/* Compute mass properties-related constants */

    mtot = (mk[2]+(mk[0]+mk[1]));
    mkrk[5][0][1] = -(mk[0]*rk[0][2]);
    mkrk[5][0][2] = (mk[0]*rk[0][1]);
    mkrk[5][1][0] = (mk[0]*rk[0][2]);
    mkrk[5][1][2] = -(mk[0]*rk[0][0]);
    mkrk[5][2][0] = -(mk[0]*rk[0][1]);
    mkrk[5][2][1] = (mk[0]*rk[0][0]);
    mkrk[6][0][1] = -(mk[1]*rk[1][2]);
    mkrk[6][0][2] = (mk[1]*rk[1][1]);
    mkrk[6][1][0] = (mk[1]*rk[1][2]);
    mkrk[6][1][2] = -(mk[1]*rk[1][0]);
    mkrk[6][2][0] = -(mk[1]*rk[1][1]);
    mkrk[6][2][1] = (mk[1]*rk[1][0]);
    mkrk[7][0][1] = -(mk[2]*rk[2][2]);
    mkrk[7][0][2] = (mk[2]*rk[2][1]);
    mkrk[7][1][0] = (mk[2]*rk[2][2]);
    mkrk[7][1][2] = -(mk[2]*rk[2][0]);
    mkrk[7][2][0] = -(mk[2]*rk[2][1]);
    mkrk[7][2][1] = (mk[2]*rk[2][0]);
    Iko[5][0][0] = (ik[0][0][0]-((mkrk[5][0][1]*rk[0][2])-(mkrk[5][0][2]*
      rk[0][1])));
    Iko[5][0][1] = (ik[0][0][1]-(mkrk[5][0][2]*rk[0][0]));
    Iko[5][0][2] = (ik[0][0][2]+(mkrk[5][0][1]*rk[0][0]));
    Iko[5][1][0] = (ik[0][1][0]+(mkrk[5][1][2]*rk[0][1]));
    Iko[5][1][1] = (ik[0][1][1]-((mkrk[5][1][2]*rk[0][0])-(mkrk[5][1][0]*
      rk[0][2])));
    Iko[5][1][2] = (ik[0][1][2]-(mkrk[5][1][0]*rk[0][1]));
    Iko[5][2][0] = (ik[0][2][0]-(mkrk[5][2][1]*rk[0][2]));
    Iko[5][2][1] = (ik[0][2][1]+(mkrk[5][2][0]*rk[0][2]));
    Iko[5][2][2] = (ik[0][2][2]-((mkrk[5][2][0]*rk[0][1])-(mkrk[5][2][1]*
      rk[0][0])));
    Iko[6][0][0] = (ik[1][0][0]-((mkrk[6][0][1]*rk[1][2])-(mkrk[6][0][2]*
      rk[1][1])));
    Iko[6][0][1] = (ik[1][0][1]-(mkrk[6][0][2]*rk[1][0]));
    Iko[6][0][2] = (ik[1][0][2]+(mkrk[6][0][1]*rk[1][0]));
    Iko[6][1][0] = (ik[1][1][0]+(mkrk[6][1][2]*rk[1][1]));
    Iko[6][1][1] = (ik[1][1][1]-((mkrk[6][1][2]*rk[1][0])-(mkrk[6][1][0]*
      rk[1][2])));
    Iko[6][1][2] = (ik[1][1][2]-(mkrk[6][1][0]*rk[1][1]));
    Iko[6][2][0] = (ik[1][2][0]-(mkrk[6][2][1]*rk[1][2]));
    Iko[6][2][1] = (ik[1][2][1]+(mkrk[6][2][0]*rk[1][2]));
    Iko[6][2][2] = (ik[1][2][2]-((mkrk[6][2][0]*rk[1][1])-(mkrk[6][2][1]*
      rk[1][0])));
    Iko[7][0][0] = (ik[2][0][0]-((mkrk[7][0][1]*rk[2][2])-(mkrk[7][0][2]*
      rk[2][1])));
    Iko[7][0][1] = (ik[2][0][1]-(mkrk[7][0][2]*rk[2][0]));
    Iko[7][0][2] = (ik[2][0][2]+(mkrk[7][0][1]*rk[2][0]));
    Iko[7][1][0] = (ik[2][1][0]+(mkrk[7][1][2]*rk[2][1]));
    Iko[7][1][1] = (ik[2][1][1]-((mkrk[7][1][2]*rk[2][0])-(mkrk[7][1][0]*
      rk[2][2])));
    Iko[7][1][2] = (ik[2][1][2]-(mkrk[7][1][0]*rk[2][1]));
    Iko[7][2][0] = (ik[2][2][0]-(mkrk[7][2][1]*rk[2][2]));
    Iko[7][2][1] = (ik[2][2][1]+(mkrk[7][2][0]*rk[2][2]));
    Iko[7][2][2] = (ik[2][2][2]-((mkrk[7][2][0]*rk[2][1])-(mkrk[7][2][1]*
      rk[2][0])));
    sdserialno(&i);
    if (i != 30123) {
        sdseterr(7,41);
    }
    roustate = 1;
}

/* Convert state to form using 1-2-3 Euler angles for ball joints. */

void sdst2ang(double st[9],
    double stang[8])
{
    int i;
    double dc[3][3];

    for (i = 0; i < 8; i++) {
        stang[i] = st[i];
    }
    sdquat2dc(st[3],st[4],st[5],st[8],dc);
    sddc2ang(dc,&stang[3],&stang[4],&stang[5]);
}

/* Convert 1-2-3 form of state back to Euler parameters for ball joints. */

void sdang2st(double stang[8],
    double st[9])
{
    int i;
    double dc[3][3];

    for (i = 0; i < 8; i++) {
        st[i] = stang[i];
    }
    sdang2dc(stang[3],stang[4],stang[5],dc);
    sddc2quat(dc,&st[3],&st[4],&st[5],&st[8]);
}

/* Normalize Euler parameters in state. */

void sdnrmsterr(double st[9],
    double normst[9],
    int routine)
{
    int i;
    double norm;

    for (i = 0; i < 9; i++) {
        normst[i] = st[i];
    }
    norm = sqrt(st[3]*st[3]+st[4]*st[4]+st[5]*st[5]+st[8]*st[8]);
    if (routine != 0) {
        if ((norm < .9) || (norm > 1.1)) {
            sdseterr(routine,14);
        }
    }
    if (norm == 0.) {
        normst[8] = 1.;
        norm = 1.;
    }
    norm = 1./norm;
    normst[3] = normst[3]*norm;
    normst[4] = normst[4]*norm;
    normst[5] = normst[5]*norm;
    normst[8] = normst[8]*norm;
}

void sdnormst(double st[9],
    double normst[9])
{

    sdnrmsterr(st,normst,0);
}

void sdstate(double timein,
    double qin[9],
    double uin[8])
{
/*
Compute kinematic information and store it in sdgstate.

Generated 20-Jul-2007 21:06:48 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    int i,j,qchg,uchg;
    double ee,stab;

    if ((roustate != 1) && (roustate != 2) && (roustate != 3)) {
        sdseterr(8,22);
        return;
    }
    if (roustate == 1) {
        for (i = 0; i < 8; i++) {
            if (presq[i] == 1) {
                sdseterr(8,31);
            }
        }
    }
/*
See if time or any qs have changed since last call
*/
    if ((roustate != 1) && (timein == curtim)) {
        qchg = 0;
        for (i = 0; i < 9; i++) {
            if (qin[i] != q[i]) {
                qchg = 1;
                break;
            }
        }
    } else {
        qchg = 1;
    }
/*
If time and qs are unchanged, check us
*/
    if (qchg == 0) {
        uchg = 0;
        for (i = 0; i < 8; i++) {
            if (uin[i] != u[i]) {
                uchg = 1;
                break;
            }
        }
    } else {
        uchg = 1;
    }
    curtim = timein;
    roustate = 2;
    if (qchg == 0) {
        goto skipqs;
    }
/*
Position-related variables need to be computed
*/
    vpkflg = 0;
    mmflg = 0;
    mmlduflg = 0;
    wwflg = 0;
    for (i = 0; i < 9; i++) {
        q[i] = qin[i];
    }
/*
Normalize Euler parameters in state
*/
    sdnrmsterr(q,qn,8);
/*
Compute sines and cosines of q
*/
    s6 = sin(q[6]);
    c6 = cos(q[6]);
    s7 = sin(q[7]);
    c7 = cos(q[7]);
/*
Compute across-axis direction cosines Cik
*/
    Cik[3][0][0] = (1.-(2.*((qn[4]*qn[4])+(qn[5]*qn[5]))));
    Cik[3][0][1] = (2.*((qn[3]*qn[4])-(qn[5]*qn[8])));
    Cik[3][0][2] = (2.*((qn[3]*qn[5])+(qn[4]*qn[8])));
    Cik[3][1][0] = (2.*((qn[3]*qn[4])+(qn[5]*qn[8])));
    Cik[3][1][1] = (1.-(2.*((qn[3]*qn[3])+(qn[5]*qn[5]))));
    Cik[3][1][2] = (2.*((qn[4]*qn[5])-(qn[3]*qn[8])));
    Cik[3][2][0] = (2.*((qn[3]*qn[5])-(qn[4]*qn[8])));
    Cik[3][2][1] = (2.*((qn[3]*qn[8])+(qn[4]*qn[5])));
    Cik[3][2][2] = (1.-(2.*((qn[3]*qn[3])+(qn[4]*qn[4]))));
    Cik[6][0][0] = ((pin[6][0]*pin[6][0])+(c6*(1.-(pin[6][0]*pin[6][0]))));
    Cik[6][0][1] = (((pin[6][0]*pin[6][1])-(pin[6][2]*s6))-(c6*(pin[6][0]*
      pin[6][1])));
    Cik[6][0][2] = (((pin[6][0]*pin[6][2])+(pin[6][1]*s6))-(c6*(pin[6][0]*
      pin[6][2])));
    Cik[6][1][0] = (((pin[6][0]*pin[6][1])+(pin[6][2]*s6))-(c6*(pin[6][0]*
      pin[6][1])));
    Cik[6][1][1] = ((pin[6][1]*pin[6][1])+(c6*(1.-(pin[6][1]*pin[6][1]))));
    Cik[6][1][2] = (((pin[6][1]*pin[6][2])-(pin[6][0]*s6))-(c6*(pin[6][1]*
      pin[6][2])));
    Cik[6][2][0] = (((pin[6][0]*pin[6][2])-(pin[6][1]*s6))-(c6*(pin[6][0]*
      pin[6][2])));
    Cik[6][2][1] = (((pin[6][0]*s6)+(pin[6][1]*pin[6][2]))-(c6*(pin[6][1]*
      pin[6][2])));
    Cik[6][2][2] = ((pin[6][2]*pin[6][2])+(c6*(1.-(pin[6][2]*pin[6][2]))));
    Cik[7][0][0] = ((pin[7][0]*pin[7][0])+(c7*(1.-(pin[7][0]*pin[7][0]))));
    Cik[7][0][1] = (((pin[7][0]*pin[7][1])-(pin[7][2]*s7))-(c7*(pin[7][0]*
      pin[7][1])));
    Cik[7][0][2] = (((pin[7][0]*pin[7][2])+(pin[7][1]*s7))-(c7*(pin[7][0]*
      pin[7][2])));
    Cik[7][1][0] = (((pin[7][0]*pin[7][1])+(pin[7][2]*s7))-(c7*(pin[7][0]*
      pin[7][1])));
    Cik[7][1][1] = ((pin[7][1]*pin[7][1])+(c7*(1.-(pin[7][1]*pin[7][1]))));
    Cik[7][1][2] = (((pin[7][1]*pin[7][2])-(pin[7][0]*s7))-(c7*(pin[7][1]*
      pin[7][2])));
    Cik[7][2][0] = (((pin[7][0]*pin[7][2])-(pin[7][1]*s7))-(c7*(pin[7][0]*
      pin[7][2])));
    Cik[7][2][1] = (((pin[7][0]*s7)+(pin[7][1]*pin[7][2]))-(c7*(pin[7][1]*
      pin[7][2])));
    Cik[7][2][2] = ((pin[7][2]*pin[7][2])+(c7*(1.-(pin[7][2]*pin[7][2]))));
/*
Compute across-joint direction cosines Cib
*/
/*
Compute gravity
*/
    gk[6][0] = -(9.81*((Cik[3][2][2]*Cik[6][2][0])+((Cik[3][2][0]*Cik[6][0][0])+
      (Cik[3][2][1]*Cik[6][1][0]))));
    gk[6][1] = -(9.81*((Cik[3][2][2]*Cik[6][2][1])+((Cik[3][2][0]*Cik[6][0][1])+
      (Cik[3][2][1]*Cik[6][1][1]))));
    gk[6][2] = -(9.81*((Cik[3][2][2]*Cik[6][2][2])+((Cik[3][2][0]*Cik[6][0][2])+
      (Cik[3][2][1]*Cik[6][1][2]))));
    gk[7][0] = -(9.81*((Cik[3][2][2]*Cik[7][2][0])+((Cik[3][2][0]*Cik[7][0][0])+
      (Cik[3][2][1]*Cik[7][1][0]))));
    gk[7][1] = -(9.81*((Cik[3][2][2]*Cik[7][2][1])+((Cik[3][2][0]*Cik[7][0][1])+
      (Cik[3][2][1]*Cik[7][1][1]))));
    gk[7][2] = -(9.81*((Cik[3][2][2]*Cik[7][2][2])+((Cik[3][2][0]*Cik[7][0][2])+
      (Cik[3][2][1]*Cik[7][1][2]))));
/*
Compute cnk & cnb (direction cosines in N)
*/
    cnk[6][0][0] = ((Cik[3][0][2]*Cik[6][2][0])+((Cik[3][0][0]*Cik[6][0][0])+(
      Cik[3][0][1]*Cik[6][1][0])));
    cnk[6][0][1] = ((Cik[3][0][2]*Cik[6][2][1])+((Cik[3][0][0]*Cik[6][0][1])+(
      Cik[3][0][1]*Cik[6][1][1])));
    cnk[6][0][2] = ((Cik[3][0][2]*Cik[6][2][2])+((Cik[3][0][0]*Cik[6][0][2])+(
      Cik[3][0][1]*Cik[6][1][2])));
    cnk[6][1][0] = ((Cik[3][1][2]*Cik[6][2][0])+((Cik[3][1][0]*Cik[6][0][0])+(
      Cik[3][1][1]*Cik[6][1][0])));
    cnk[6][1][1] = ((Cik[3][1][2]*Cik[6][2][1])+((Cik[3][1][0]*Cik[6][0][1])+(
      Cik[3][1][1]*Cik[6][1][1])));
    cnk[6][1][2] = ((Cik[3][1][2]*Cik[6][2][2])+((Cik[3][1][0]*Cik[6][0][2])+(
      Cik[3][1][1]*Cik[6][1][2])));
    cnk[6][2][0] = ((Cik[3][2][2]*Cik[6][2][0])+((Cik[3][2][0]*Cik[6][0][0])+(
      Cik[3][2][1]*Cik[6][1][0])));
    cnk[6][2][1] = ((Cik[3][2][2]*Cik[6][2][1])+((Cik[3][2][0]*Cik[6][0][1])+(
      Cik[3][2][1]*Cik[6][1][1])));
    cnk[6][2][2] = ((Cik[3][2][2]*Cik[6][2][2])+((Cik[3][2][0]*Cik[6][0][2])+(
      Cik[3][2][1]*Cik[6][1][2])));
    cnk[7][0][0] = ((Cik[3][0][2]*Cik[7][2][0])+((Cik[3][0][0]*Cik[7][0][0])+(
      Cik[3][0][1]*Cik[7][1][0])));
    cnk[7][0][1] = ((Cik[3][0][2]*Cik[7][2][1])+((Cik[3][0][0]*Cik[7][0][1])+(
      Cik[3][0][1]*Cik[7][1][1])));
    cnk[7][0][2] = ((Cik[3][0][2]*Cik[7][2][2])+((Cik[3][0][0]*Cik[7][0][2])+(
      Cik[3][0][1]*Cik[7][1][2])));
    cnk[7][1][0] = ((Cik[3][1][2]*Cik[7][2][0])+((Cik[3][1][0]*Cik[7][0][0])+(
      Cik[3][1][1]*Cik[7][1][0])));
    cnk[7][1][1] = ((Cik[3][1][2]*Cik[7][2][1])+((Cik[3][1][0]*Cik[7][0][1])+(
      Cik[3][1][1]*Cik[7][1][1])));
    cnk[7][1][2] = ((Cik[3][1][2]*Cik[7][2][2])+((Cik[3][1][0]*Cik[7][0][2])+(
      Cik[3][1][1]*Cik[7][1][2])));
    cnk[7][2][0] = ((Cik[3][2][2]*Cik[7][2][0])+((Cik[3][2][0]*Cik[7][0][0])+(
      Cik[3][2][1]*Cik[7][1][0])));
    cnk[7][2][1] = ((Cik[3][2][2]*Cik[7][2][1])+((Cik[3][2][0]*Cik[7][0][1])+(
      Cik[3][2][1]*Cik[7][1][1])));
    cnk[7][2][2] = ((Cik[3][2][2]*Cik[7][2][2])+((Cik[3][2][0]*Cik[7][0][2])+(
      Cik[3][2][1]*Cik[7][1][2])));
    cnb[0][0][0] = Cik[3][0][0];
    cnb[0][0][1] = Cik[3][0][1];
    cnb[0][0][2] = Cik[3][0][2];
    cnb[0][1][0] = Cik[3][1][0];
    cnb[0][1][1] = Cik[3][1][1];
    cnb[0][1][2] = Cik[3][1][2];
    cnb[0][2][0] = Cik[3][2][0];
    cnb[0][2][1] = Cik[3][2][1];
    cnb[0][2][2] = Cik[3][2][2];
    cnb[1][0][0] = cnk[6][0][0];
    cnb[1][0][1] = cnk[6][0][1];
    cnb[1][0][2] = cnk[6][0][2];
    cnb[1][1][0] = cnk[6][1][0];
    cnb[1][1][1] = cnk[6][1][1];
    cnb[1][1][2] = cnk[6][1][2];
    cnb[1][2][0] = cnk[6][2][0];
    cnb[1][2][1] = cnk[6][2][1];
    cnb[1][2][2] = cnk[6][2][2];
    cnb[2][0][0] = cnk[7][0][0];
    cnb[2][0][1] = cnk[7][0][1];
    cnb[2][0][2] = cnk[7][0][2];
    cnb[2][1][0] = cnk[7][1][0];
    cnb[2][1][1] = cnk[7][1][1];
    cnb[2][1][2] = cnk[7][1][2];
    cnb[2][2][0] = cnk[7][2][0];
    cnb[2][2][1] = cnk[7][2][1];
    cnb[2][2][2] = cnk[7][2][2];
/*
Compute q-related auxiliary variables
*/
    rpp[0][0] = (pin[0][0]*q[0]);
    rpp[0][1] = (pin[0][1]*q[0]);
    rpp[0][2] = (pin[0][2]*q[0]);
    rpp[1][0] = (pin[1][0]*q[1]);
    rpp[1][1] = (pin[1][1]*q[1]);
    rpp[1][2] = (pin[1][2]*q[1]);
    rpp[2][0] = (pin[2][0]*q[2]);
    rpp[2][1] = (pin[2][1]*q[2]);
    rpp[2][2] = (pin[2][2]*q[2]);
    rpri[0][0] = (ri[0][0]+rpp[0][0]);
    rpri[0][1] = (ri[0][1]+rpp[0][1]);
    rpri[0][2] = (ri[0][2]+rpp[0][2]);
    rik[0][0] = (ri[0][0]+rpp[0][0]);
    rik[0][1] = (ri[0][1]+rpp[0][1]);
    rik[0][2] = (ri[0][2]+rpp[0][2]);
    rik[6][0] = (((Cik[6][2][0]*ri[1][2])+((Cik[6][0][0]*ri[1][0])+(Cik[6][1][0]
      *ri[1][1])))-rk[1][0]);
    rik[6][1] = (((Cik[6][2][1]*ri[1][2])+((Cik[6][0][1]*ri[1][0])+(Cik[6][1][1]
      *ri[1][1])))-rk[1][1]);
    rik[6][2] = (((Cik[6][2][2]*ri[1][2])+((Cik[6][0][2]*ri[1][0])+(Cik[6][1][2]
      *ri[1][1])))-rk[1][2]);
    rik[7][0] = (((Cik[7][2][0]*ri[2][2])+((Cik[7][0][0]*ri[2][0])+(Cik[7][1][0]
      *ri[2][1])))-rk[2][0]);
    rik[7][1] = (((Cik[7][2][1]*ri[2][2])+((Cik[7][0][1]*ri[2][0])+(Cik[7][1][1]
      *ri[2][1])))-rk[2][1]);
    rik[7][2] = (((Cik[7][2][2]*ri[2][2])+((Cik[7][0][2]*ri[2][0])+(Cik[7][1][2]
      *ri[2][1])))-rk[2][2]);
/*
Compute rnk & rnb (mass center locations in N)
*/
    rnk[0][0] = (ri[0][0]+rpp[0][0]);
    rnk[0][1] = (ri[0][1]+rpp[0][1]);
    rnk[0][2] = (ri[0][2]+rpp[0][2]);
    rnk[1][0] = (rnk[0][0]+rpp[1][0]);
    rnk[1][1] = (rnk[0][1]+rpp[1][1]);
    rnk[1][2] = (rnk[0][2]+rpp[1][2]);
    rnk[2][0] = (rnk[1][0]+rpp[2][0]);
    rnk[2][1] = (rnk[1][1]+rpp[2][1]);
    rnk[2][2] = (rnk[1][2]+rpp[2][2]);
    rnk[5][0] = (rnk[2][0]-((Cik[3][0][2]*rk[0][2])+((Cik[3][0][0]*rk[0][0])+(
      Cik[3][0][1]*rk[0][1]))));
    rnk[5][1] = (rnk[2][1]-((Cik[3][1][2]*rk[0][2])+((Cik[3][1][0]*rk[0][0])+(
      Cik[3][1][1]*rk[0][1]))));
    rnk[5][2] = (rnk[2][2]-((Cik[3][2][2]*rk[0][2])+((Cik[3][2][0]*rk[0][0])+(
      Cik[3][2][1]*rk[0][1]))));
    rnk[6][0] = ((rnk[5][0]+((Cik[3][0][2]*ri[1][2])+((Cik[3][0][0]*ri[1][0])+(
      Cik[3][0][1]*ri[1][1]))))-((cnk[6][0][2]*rk[1][2])+((cnk[6][0][0]*rk[1][0]
      )+(cnk[6][0][1]*rk[1][1]))));
    rnk[6][1] = ((rnk[5][1]+((Cik[3][1][2]*ri[1][2])+((Cik[3][1][0]*ri[1][0])+(
      Cik[3][1][1]*ri[1][1]))))-((cnk[6][1][2]*rk[1][2])+((cnk[6][1][0]*rk[1][0]
      )+(cnk[6][1][1]*rk[1][1]))));
    rnk[6][2] = ((rnk[5][2]+((Cik[3][2][2]*ri[1][2])+((Cik[3][2][0]*ri[1][0])+(
      Cik[3][2][1]*ri[1][1]))))-((cnk[6][2][2]*rk[1][2])+((cnk[6][2][0]*rk[1][0]
      )+(cnk[6][2][1]*rk[1][1]))));
    rnk[7][0] = ((rnk[5][0]+((Cik[3][0][2]*ri[2][2])+((Cik[3][0][0]*ri[2][0])+(
      Cik[3][0][1]*ri[2][1]))))-((cnk[7][0][2]*rk[2][2])+((cnk[7][0][0]*rk[2][0]
      )+(cnk[7][0][1]*rk[2][1]))));
    rnk[7][1] = ((rnk[5][1]+((Cik[3][1][2]*ri[2][2])+((Cik[3][1][0]*ri[2][0])+(
      Cik[3][1][1]*ri[2][1]))))-((cnk[7][1][2]*rk[2][2])+((cnk[7][1][0]*rk[2][0]
      )+(cnk[7][1][1]*rk[2][1]))));
    rnk[7][2] = ((rnk[5][2]+((Cik[3][2][2]*ri[2][2])+((Cik[3][2][0]*ri[2][0])+(
      Cik[3][2][1]*ri[2][1]))))-((cnk[7][2][2]*rk[2][2])+((cnk[7][2][0]*rk[2][0]
      )+(cnk[7][2][1]*rk[2][1]))));
    rnb[0][0] = rnk[5][0];
    rnb[0][1] = rnk[5][1];
    rnb[0][2] = rnk[5][2];
    rnb[1][0] = rnk[6][0];
    rnb[1][1] = rnk[6][1];
    rnb[1][2] = rnk[6][2];
    rnb[2][0] = rnk[7][0];
    rnb[2][1] = rnk[7][1];
    rnb[2][2] = rnk[7][2];
/*
Compute com (system mass center location in N)
*/
    com[0] = ((1./mtot)*((mk[2]*rnk[7][0])+((mk[0]*rnk[5][0])+(mk[1]*rnk[6][0]))
      ));
    com[1] = ((1./mtot)*((mk[2]*rnk[7][1])+((mk[0]*rnk[5][1])+(mk[1]*rnk[6][1]))
      ));
    com[2] = ((1./mtot)*((mk[2]*rnk[7][2])+((mk[0]*rnk[5][2])+(mk[1]*rnk[6][2]))
      ));
/*
Compute constraint position errors
*/
    skipqs: ;
    sduperr(curtim,q,&perr[2]);
    if (uchg == 0) {
        goto skipus;
    }
/*
Velocity-related variables need to be computed
*/
    inerflg = 0;
    for (i = 0; i < 8; i++) {
        u[i] = uin[i];
    }
/*
Compute u-related auxiliary variables
*/
    Wik[6][0] = (pin[6][0]*u[6]);
    Wik[6][1] = (pin[6][1]*u[6]);
    Wik[6][2] = (pin[6][2]*u[6]);
    Wik[7][0] = (pin[7][0]*u[7]);
    Wik[7][1] = (pin[7][1]*u[7]);
    Wik[7][2] = (pin[7][2]*u[7]);
    Vik[0][0] = (pin[0][0]*u[0]);
    Vik[0][1] = (pin[0][1]*u[0]);
    Vik[0][2] = (pin[0][2]*u[0]);
    Vik[1][0] = (pin[1][0]*u[1]);
    Vik[1][1] = (pin[1][1]*u[1]);
    Vik[1][2] = (pin[1][2]*u[1]);
    Vik[2][0] = (pin[2][0]*u[2]);
    Vik[2][1] = (pin[2][1]*u[2]);
    Vik[2][2] = (pin[2][2]*u[2]);
/*
Compute wk & wb (angular velocities)
*/
    wk[6][0] = (Wik[6][0]+((Cik[6][2][0]*u[5])+((Cik[6][0][0]*u[3])+(
      Cik[6][1][0]*u[4]))));
    wk[6][1] = (Wik[6][1]+((Cik[6][2][1]*u[5])+((Cik[6][0][1]*u[3])+(
      Cik[6][1][1]*u[4]))));
    wk[6][2] = (Wik[6][2]+((Cik[6][2][2]*u[5])+((Cik[6][0][2]*u[3])+(
      Cik[6][1][2]*u[4]))));
    wk[7][0] = (Wik[7][0]+((Cik[7][2][0]*u[5])+((Cik[7][0][0]*u[3])+(
      Cik[7][1][0]*u[4]))));
    wk[7][1] = (Wik[7][1]+((Cik[7][2][1]*u[5])+((Cik[7][0][1]*u[3])+(
      Cik[7][1][1]*u[4]))));
    wk[7][2] = (Wik[7][2]+((Cik[7][2][2]*u[5])+((Cik[7][0][2]*u[3])+(
      Cik[7][1][2]*u[4]))));
    wb[0][0] = u[3];
    wb[0][1] = u[4];
    wb[0][2] = u[5];
    wb[1][0] = wk[6][0];
    wb[1][1] = wk[6][1];
    wb[1][2] = wk[6][2];
    wb[2][0] = wk[7][0];
    wb[2][1] = wk[7][1];
    wb[2][2] = wk[7][2];
/*
Compute auxiliary variables involving wk
*/
    Wirk[6][0] = ((ri[1][2]*u[4])-(ri[1][1]*u[5]));
    Wirk[6][1] = ((ri[1][0]*u[5])-(ri[1][2]*u[3]));
    Wirk[6][2] = ((ri[1][1]*u[3])-(ri[1][0]*u[4]));
    Wirk[7][0] = ((ri[2][2]*u[4])-(ri[2][1]*u[5]));
    Wirk[7][1] = ((ri[2][0]*u[5])-(ri[2][2]*u[3]));
    Wirk[7][2] = ((ri[2][1]*u[3])-(ri[2][0]*u[4]));
    Wkrpk[5][0] = ((rk[0][1]*u[5])-(rk[0][2]*u[4]));
    Wkrpk[5][1] = ((rk[0][2]*u[3])-(rk[0][0]*u[5]));
    Wkrpk[5][2] = ((rk[0][0]*u[4])-(rk[0][1]*u[3]));
    Wkrpk[6][0] = ((rk[1][1]*wk[6][2])-(rk[1][2]*wk[6][1]));
    Wkrpk[6][1] = ((rk[1][2]*wk[6][0])-(rk[1][0]*wk[6][2]));
    Wkrpk[6][2] = ((rk[1][0]*wk[6][1])-(rk[1][1]*wk[6][0]));
    Wkrpk[7][0] = ((rk[2][1]*wk[7][2])-(rk[2][2]*wk[7][1]));
    Wkrpk[7][1] = ((rk[2][2]*wk[7][0])-(rk[2][0]*wk[7][2]));
    Wkrpk[7][2] = ((rk[2][0]*wk[7][1])-(rk[2][1]*wk[7][0]));
    IkWk[5][0] = ((ik[0][0][2]*u[5])+((ik[0][0][0]*u[3])+(ik[0][0][1]*u[4])));
    IkWk[5][1] = ((ik[0][1][2]*u[5])+((ik[0][1][0]*u[3])+(ik[0][1][1]*u[4])));
    IkWk[5][2] = ((ik[0][2][2]*u[5])+((ik[0][2][0]*u[3])+(ik[0][2][1]*u[4])));
    WkIkWk[5][0] = ((IkWk[5][2]*u[4])-(IkWk[5][1]*u[5]));
    WkIkWk[5][1] = ((IkWk[5][0]*u[5])-(IkWk[5][2]*u[3]));
    WkIkWk[5][2] = ((IkWk[5][1]*u[3])-(IkWk[5][0]*u[4]));
    IkWk[6][0] = ((ik[1][0][2]*wk[6][2])+((ik[1][0][0]*wk[6][0])+(ik[1][0][1]*
      wk[6][1])));
    IkWk[6][1] = ((ik[1][1][2]*wk[6][2])+((ik[1][1][0]*wk[6][0])+(ik[1][1][1]*
      wk[6][1])));
    IkWk[6][2] = ((ik[1][2][2]*wk[6][2])+((ik[1][2][0]*wk[6][0])+(ik[1][2][1]*
      wk[6][1])));
    WkIkWk[6][0] = ((IkWk[6][2]*wk[6][1])-(IkWk[6][1]*wk[6][2]));
    WkIkWk[6][1] = ((IkWk[6][0]*wk[6][2])-(IkWk[6][2]*wk[6][0]));
    WkIkWk[6][2] = ((IkWk[6][1]*wk[6][0])-(IkWk[6][0]*wk[6][1]));
    IkWk[7][0] = ((ik[2][0][2]*wk[7][2])+((ik[2][0][0]*wk[7][0])+(ik[2][0][1]*
      wk[7][1])));
    IkWk[7][1] = ((ik[2][1][2]*wk[7][2])+((ik[2][1][0]*wk[7][0])+(ik[2][1][1]*
      wk[7][1])));
    IkWk[7][2] = ((ik[2][2][2]*wk[7][2])+((ik[2][2][0]*wk[7][0])+(ik[2][2][1]*
      wk[7][1])));
    WkIkWk[7][0] = ((IkWk[7][2]*wk[7][1])-(IkWk[7][1]*wk[7][2]));
    WkIkWk[7][1] = ((IkWk[7][0]*wk[7][2])-(IkWk[7][2]*wk[7][0]));
    WkIkWk[7][2] = ((IkWk[7][1]*wk[7][0])-(IkWk[7][0]*wk[7][1]));
/*
Compute temporaries for use in SDRHS
*/
    w0w0[0] = (u[3]*u[3]);
    w0w0[1] = (wk[6][0]*wk[6][0]);
    w0w0[2] = (wk[7][0]*wk[7][0]);
    w1w1[0] = (u[4]*u[4]);
    w1w1[1] = (wk[6][1]*wk[6][1]);
    w1w1[2] = (wk[7][1]*wk[7][1]);
    w2w2[0] = (u[5]*u[5]);
    w2w2[1] = (wk[6][2]*wk[6][2]);
    w2w2[2] = (wk[7][2]*wk[7][2]);
    w0w1[0] = (u[3]*u[4]);
    w0w1[1] = (wk[6][0]*wk[6][1]);
    w0w1[2] = (wk[7][0]*wk[7][1]);
    w0w2[0] = (u[3]*u[5]);
    w0w2[1] = (wk[6][0]*wk[6][2]);
    w0w2[2] = (wk[7][0]*wk[7][2]);
    w1w2[0] = (u[4]*u[5]);
    w1w2[1] = (wk[6][1]*wk[6][2]);
    w1w2[2] = (wk[7][1]*wk[7][2]);
    w00w11[0] = -(w0w0[0]+w1w1[0]);
    w00w11[1] = -(w0w0[1]+w1w1[1]);
    w00w11[2] = -(w0w0[2]+w1w1[2]);
    w00w22[0] = -(w0w0[0]+w2w2[0]);
    w00w22[1] = -(w0w0[1]+w2w2[1]);
    w00w22[2] = -(w0w0[2]+w2w2[2]);
    w11w22[0] = -(w1w1[0]+w2w2[0]);
    w11w22[1] = -(w1w1[1]+w2w2[1]);
    w11w22[2] = -(w1w1[2]+w2w2[2]);
/*
Compute vnk & vnb (mass center linear velocities in N)
*/
    vnk[1][0] = (Vik[0][0]+Vik[1][0]);
    vnk[1][1] = (Vik[0][1]+Vik[1][1]);
    vnk[1][2] = (Vik[0][2]+Vik[1][2]);
    vnk[2][0] = (Vik[2][0]+vnk[1][0]);
    vnk[2][1] = (Vik[2][1]+vnk[1][1]);
    vnk[2][2] = (Vik[2][2]+vnk[1][2]);
    vnk[5][0] = (vnk[2][0]+((Cik[3][0][2]*Wkrpk[5][2])+((Cik[3][0][0]*
      Wkrpk[5][0])+(Cik[3][0][1]*Wkrpk[5][1]))));
    vnk[5][1] = (vnk[2][1]+((Cik[3][1][2]*Wkrpk[5][2])+((Cik[3][1][0]*
      Wkrpk[5][0])+(Cik[3][1][1]*Wkrpk[5][1]))));
    vnk[5][2] = (vnk[2][2]+((Cik[3][2][2]*Wkrpk[5][2])+((Cik[3][2][0]*
      Wkrpk[5][0])+(Cik[3][2][1]*Wkrpk[5][1]))));
    vnk[6][0] = ((vnk[5][0]+((Cik[3][0][2]*Wirk[6][2])+((Cik[3][0][0]*Wirk[6][0]
      )+(Cik[3][0][1]*Wirk[6][1]))))+((cnk[6][0][2]*Wkrpk[6][2])+((cnk[6][0][0]*
      Wkrpk[6][0])+(cnk[6][0][1]*Wkrpk[6][1]))));
    vnk[6][1] = ((vnk[5][1]+((Cik[3][1][2]*Wirk[6][2])+((Cik[3][1][0]*Wirk[6][0]
      )+(Cik[3][1][1]*Wirk[6][1]))))+((cnk[6][1][2]*Wkrpk[6][2])+((cnk[6][1][0]*
      Wkrpk[6][0])+(cnk[6][1][1]*Wkrpk[6][1]))));
    vnk[6][2] = ((vnk[5][2]+((Cik[3][2][2]*Wirk[6][2])+((Cik[3][2][0]*Wirk[6][0]
      )+(Cik[3][2][1]*Wirk[6][1]))))+((cnk[6][2][2]*Wkrpk[6][2])+((cnk[6][2][0]*
      Wkrpk[6][0])+(cnk[6][2][1]*Wkrpk[6][1]))));
    vnk[7][0] = ((vnk[5][0]+((Cik[3][0][2]*Wirk[7][2])+((Cik[3][0][0]*Wirk[7][0]
      )+(Cik[3][0][1]*Wirk[7][1]))))+((cnk[7][0][2]*Wkrpk[7][2])+((cnk[7][0][0]*
      Wkrpk[7][0])+(cnk[7][0][1]*Wkrpk[7][1]))));
    vnk[7][1] = ((vnk[5][1]+((Cik[3][1][2]*Wirk[7][2])+((Cik[3][1][0]*Wirk[7][0]
      )+(Cik[3][1][1]*Wirk[7][1]))))+((cnk[7][1][2]*Wkrpk[7][2])+((cnk[7][1][0]*
      Wkrpk[7][0])+(cnk[7][1][1]*Wkrpk[7][1]))));
    vnk[7][2] = ((vnk[5][2]+((Cik[3][2][2]*Wirk[7][2])+((Cik[3][2][0]*Wirk[7][0]
      )+(Cik[3][2][1]*Wirk[7][1]))))+((cnk[7][2][2]*Wkrpk[7][2])+((cnk[7][2][0]*
      Wkrpk[7][0])+(cnk[7][2][1]*Wkrpk[7][1]))));
    vnb[0][0] = vnk[5][0];
    vnb[0][1] = vnk[5][1];
    vnb[0][2] = vnk[5][2];
    vnb[1][0] = vnk[6][0];
    vnb[1][1] = vnk[6][1];
    vnb[1][2] = vnk[6][2];
    vnb[2][0] = vnk[7][0];
    vnb[2][1] = vnk[7][1];
    vnb[2][2] = vnk[7][2];
/*
Compute qdot (kinematical equations)
*/
    qdot[0] = u[0];
    qdot[1] = u[1];
    qdot[2] = u[2];
    qdot[3] = (.5*((q[8]*u[3])+((q[4]*u[5])-(q[5]*u[4]))));
    qdot[4] = (.5*((q[5]*u[3])+((q[8]*u[4])-(q[3]*u[5]))));
    qdot[5] = (.5*(((q[3]*u[4])+(q[8]*u[5]))-(q[4]*u[3])));
    qdot[8] = -(.5*((q[3]*u[3])+((q[4]*u[4])+(q[5]*u[5]))));
    if (stabvel  !=  0.) {
        ee = ((q[8]*q[8])+((q[5]*q[5])+((q[3]*q[3])+(q[4]*q[4]))));
        stab = ((stabvel*(1.-ee))/ee);
        qdot[3] = (qdot[3]+(q[3]*stab));
        qdot[4] = (qdot[4]+(q[4]*stab));
        qdot[5] = (qdot[5]+(q[5]*stab));
        qdot[8] = (qdot[8]+(q[8]*stab));
    }
    qdot[6] = u[6];
    qdot[7] = u[7];
/*
Compute constraint velocity errors
*/
    skipus: ;
    sduverr(curtim,q,u,&verr[2]);
/*
Initialize applied forces and torques to zero
*/
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            ufk[i][j] = 0.;
            utk[i][j] = 0.;
        }
    }
    for (i = 0; i < 8; i++) {
        utau[i] = 0.;
    }
    ltauflg = 0;
    fs0flg = 0;
/*
Initialize prescribed motions
*/
    uacc[6] = 0.;
    uvel[6] = u[6];
    upos[6] = q[6];
    uacc[7] = 0.;
    uvel[7] = u[7];
    upos[7] = q[7];
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  332 adds/subtracts/negates
                    451 multiplies
                      4 divides
                    307 assignments
*/
}

void sdqdot(double oqdot[9])
{
/*
Return position coordinate derivatives for tree joints.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(63,23);
        return;
    }
    for (i = 0; i <= 8; i++) {
        oqdot[i] = qdot[i];
    }
}

void sdu2qdot(double uin[8],
    double oqdot[9])
{
/*
Convert velocities to qdots.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(64,23);
        return;
    }
    for (i = 0; i <= 7; i++) {
        oqdot[i] = uin[i];
    }
    oqdot[3] = (.5*((q[8]*uin[3])+((q[4]*uin[5])-(q[5]*uin[4]))));
    oqdot[4] = (.5*((q[5]*uin[3])+((q[8]*uin[4])-(q[3]*uin[5]))));
    oqdot[5] = (.5*(((q[3]*uin[4])+(q[8]*uin[5]))-(q[4]*uin[3])));
    oqdot[8] = -(.5*((q[3]*uin[3])+((q[4]*uin[4])+(q[5]*uin[5]))));
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    9 adds/subtracts/negates
                     16 multiplies
                      0 divides
                     12 assignments
*/
}

void sdpsstate(double lqin[1])
{

    if (roustate != 2) {
        sdseterr(9,23);
        return;
    }
}

void sddovpk(void)
{

    if (vpkflg == 0) {
/*
Compute Wpk (partial angular velocities)
*/
        Wpk[3][3][0] = 1.;
        Wpk[3][4][0] = 1.;
        Wpk[3][5][0] = 1.;
        Wpk[3][6][0] = Cik[6][0][0];
        Wpk[3][6][1] = Cik[6][0][1];
        Wpk[3][6][2] = Cik[6][0][2];
        Wpk[3][7][0] = Cik[7][0][0];
        Wpk[3][7][1] = Cik[7][0][1];
        Wpk[3][7][2] = Cik[7][0][2];
        Wpk[4][4][1] = 1.;
        Wpk[4][5][1] = 1.;
        Wpk[4][6][0] = Cik[6][1][0];
        Wpk[4][6][1] = Cik[6][1][1];
        Wpk[4][6][2] = Cik[6][1][2];
        Wpk[4][7][0] = Cik[7][1][0];
        Wpk[4][7][1] = Cik[7][1][1];
        Wpk[4][7][2] = Cik[7][1][2];
        Wpk[5][5][2] = 1.;
        Wpk[5][6][0] = Cik[6][2][0];
        Wpk[5][6][1] = Cik[6][2][1];
        Wpk[5][6][2] = Cik[6][2][2];
        Wpk[5][7][0] = Cik[7][2][0];
        Wpk[5][7][1] = Cik[7][2][1];
        Wpk[5][7][2] = Cik[7][2][2];
        Wpk[6][6][0] = pin[6][0];
        Wpk[6][6][1] = pin[6][1];
        Wpk[6][6][2] = pin[6][2];
        Wpk[7][7][0] = pin[7][0];
        Wpk[7][7][1] = pin[7][1];
        Wpk[7][7][2] = pin[7][2];
/*
Compute Vpk (partial velocities)
*/
        Vpk[0][0][0] = pin[0][0];
        Vpk[0][0][1] = pin[0][1];
        Vpk[0][0][2] = pin[0][2];
        Vpk[0][1][0] = pin[0][0];
        Vpk[0][1][1] = pin[0][1];
        Vpk[0][1][2] = pin[0][2];
        Vpk[0][2][0] = pin[0][0];
        Vpk[0][2][1] = pin[0][1];
        Vpk[0][2][2] = pin[0][2];
        Vpk[0][3][0] = ((Cik[3][2][0]*pin[0][2])+((Cik[3][0][0]*pin[0][0])+(
          Cik[3][1][0]*pin[0][1])));
        Vpk[0][3][1] = ((Cik[3][2][1]*pin[0][2])+((Cik[3][0][1]*pin[0][0])+(
          Cik[3][1][1]*pin[0][1])));
        Vpk[0][3][2] = ((Cik[3][2][2]*pin[0][2])+((Cik[3][0][2]*pin[0][0])+(
          Cik[3][1][2]*pin[0][1])));
        Vpk[0][4][0] = Vpk[0][3][0];
        Vpk[0][4][1] = Vpk[0][3][1];
        Vpk[0][4][2] = Vpk[0][3][2];
        Vpk[0][5][0] = Vpk[0][3][0];
        Vpk[0][5][1] = Vpk[0][3][1];
        Vpk[0][5][2] = Vpk[0][3][2];
        Vpk[0][6][0] = ((Cik[6][2][0]*Vpk[0][3][2])+((Cik[6][0][0]*Vpk[0][3][0])
          +(Cik[6][1][0]*Vpk[0][3][1])));
        Vpk[0][6][1] = ((Cik[6][2][1]*Vpk[0][3][2])+((Cik[6][0][1]*Vpk[0][3][0])
          +(Cik[6][1][1]*Vpk[0][3][1])));
        Vpk[0][6][2] = ((Cik[6][2][2]*Vpk[0][3][2])+((Cik[6][0][2]*Vpk[0][3][0])
          +(Cik[6][1][2]*Vpk[0][3][1])));
        Vpk[0][7][0] = ((Cik[7][2][0]*Vpk[0][3][2])+((Cik[7][0][0]*Vpk[0][3][0])
          +(Cik[7][1][0]*Vpk[0][3][1])));
        Vpk[0][7][1] = ((Cik[7][2][1]*Vpk[0][3][2])+((Cik[7][0][1]*Vpk[0][3][0])
          +(Cik[7][1][1]*Vpk[0][3][1])));
        Vpk[0][7][2] = ((Cik[7][2][2]*Vpk[0][3][2])+((Cik[7][0][2]*Vpk[0][3][0])
          +(Cik[7][1][2]*Vpk[0][3][1])));
        Vpk[1][1][0] = pin[1][0];
        Vpk[1][1][1] = pin[1][1];
        Vpk[1][1][2] = pin[1][2];
        Vpk[1][2][0] = pin[1][0];
        Vpk[1][2][1] = pin[1][1];
        Vpk[1][2][2] = pin[1][2];
        Vpk[1][3][0] = ((Cik[3][2][0]*pin[1][2])+((Cik[3][0][0]*pin[1][0])+(
          Cik[3][1][0]*pin[1][1])));
        Vpk[1][3][1] = ((Cik[3][2][1]*pin[1][2])+((Cik[3][0][1]*pin[1][0])+(
          Cik[3][1][1]*pin[1][1])));
        Vpk[1][3][2] = ((Cik[3][2][2]*pin[1][2])+((Cik[3][0][2]*pin[1][0])+(
          Cik[3][1][2]*pin[1][1])));
        Vpk[1][4][0] = Vpk[1][3][0];
        Vpk[1][4][1] = Vpk[1][3][1];
        Vpk[1][4][2] = Vpk[1][3][2];
        Vpk[1][5][0] = Vpk[1][3][0];
        Vpk[1][5][1] = Vpk[1][3][1];
        Vpk[1][5][2] = Vpk[1][3][2];
        Vpk[1][6][0] = ((Cik[6][2][0]*Vpk[1][3][2])+((Cik[6][0][0]*Vpk[1][3][0])
          +(Cik[6][1][0]*Vpk[1][3][1])));
        Vpk[1][6][1] = ((Cik[6][2][1]*Vpk[1][3][2])+((Cik[6][0][1]*Vpk[1][3][0])
          +(Cik[6][1][1]*Vpk[1][3][1])));
        Vpk[1][6][2] = ((Cik[6][2][2]*Vpk[1][3][2])+((Cik[6][0][2]*Vpk[1][3][0])
          +(Cik[6][1][2]*Vpk[1][3][1])));
        Vpk[1][7][0] = ((Cik[7][2][0]*Vpk[1][3][2])+((Cik[7][0][0]*Vpk[1][3][0])
          +(Cik[7][1][0]*Vpk[1][3][1])));
        Vpk[1][7][1] = ((Cik[7][2][1]*Vpk[1][3][2])+((Cik[7][0][1]*Vpk[1][3][0])
          +(Cik[7][1][1]*Vpk[1][3][1])));
        Vpk[1][7][2] = ((Cik[7][2][2]*Vpk[1][3][2])+((Cik[7][0][2]*Vpk[1][3][0])
          +(Cik[7][1][2]*Vpk[1][3][1])));
        Vpk[2][2][0] = pin[2][0];
        Vpk[2][2][1] = pin[2][1];
        Vpk[2][2][2] = pin[2][2];
        Vpk[2][3][0] = ((Cik[3][2][0]*pin[2][2])+((Cik[3][0][0]*pin[2][0])+(
          Cik[3][1][0]*pin[2][1])));
        Vpk[2][3][1] = ((Cik[3][2][1]*pin[2][2])+((Cik[3][0][1]*pin[2][0])+(
          Cik[3][1][1]*pin[2][1])));
        Vpk[2][3][2] = ((Cik[3][2][2]*pin[2][2])+((Cik[3][0][2]*pin[2][0])+(
          Cik[3][1][2]*pin[2][1])));
        Vpk[2][4][0] = Vpk[2][3][0];
        Vpk[2][4][1] = Vpk[2][3][1];
        Vpk[2][4][2] = Vpk[2][3][2];
        Vpk[2][5][0] = Vpk[2][3][0];
        Vpk[2][5][1] = Vpk[2][3][1];
        Vpk[2][5][2] = Vpk[2][3][2];
        Vpk[2][6][0] = ((Cik[6][2][0]*Vpk[2][3][2])+((Cik[6][0][0]*Vpk[2][3][0])
          +(Cik[6][1][0]*Vpk[2][3][1])));
        Vpk[2][6][1] = ((Cik[6][2][1]*Vpk[2][3][2])+((Cik[6][0][1]*Vpk[2][3][0])
          +(Cik[6][1][1]*Vpk[2][3][1])));
        Vpk[2][6][2] = ((Cik[6][2][2]*Vpk[2][3][2])+((Cik[6][0][2]*Vpk[2][3][0])
          +(Cik[6][1][2]*Vpk[2][3][1])));
        Vpk[2][7][0] = ((Cik[7][2][0]*Vpk[2][3][2])+((Cik[7][0][0]*Vpk[2][3][0])
          +(Cik[7][1][0]*Vpk[2][3][1])));
        Vpk[2][7][1] = ((Cik[7][2][1]*Vpk[2][3][2])+((Cik[7][0][1]*Vpk[2][3][0])
          +(Cik[7][1][1]*Vpk[2][3][1])));
        Vpk[2][7][2] = ((Cik[7][2][2]*Vpk[2][3][2])+((Cik[7][0][2]*Vpk[2][3][0])
          +(Cik[7][1][2]*Vpk[2][3][1])));
        Vpk[3][5][1] = rk[0][2];
        Vpk[3][5][2] = -rk[0][1];
        VWri[3][6][1] = (rk[0][2]-ri[1][2]);
        VWri[3][6][2] = (ri[1][1]-rk[0][1]);
        Vpk[3][6][0] = (((Cik[6][0][2]*rk[1][1])-(Cik[6][0][1]*rk[1][2]))+((
          Cik[6][1][0]*VWri[3][6][1])+(Cik[6][2][0]*VWri[3][6][2])));
        Vpk[3][6][1] = (((Cik[6][0][0]*rk[1][2])-(Cik[6][0][2]*rk[1][0]))+((
          Cik[6][1][1]*VWri[3][6][1])+(Cik[6][2][1]*VWri[3][6][2])));
        Vpk[3][6][2] = (((Cik[6][0][1]*rk[1][0])-(Cik[6][0][0]*rk[1][1]))+((
          Cik[6][1][2]*VWri[3][6][1])+(Cik[6][2][2]*VWri[3][6][2])));
        VWri[3][7][1] = (rk[0][2]-ri[2][2]);
        VWri[3][7][2] = (ri[2][1]-rk[0][1]);
        Vpk[3][7][0] = (((Cik[7][0][2]*rk[2][1])-(Cik[7][0][1]*rk[2][2]))+((
          Cik[7][1][0]*VWri[3][7][1])+(Cik[7][2][0]*VWri[3][7][2])));
        Vpk[3][7][1] = (((Cik[7][0][0]*rk[2][2])-(Cik[7][0][2]*rk[2][0]))+((
          Cik[7][1][1]*VWri[3][7][1])+(Cik[7][2][1]*VWri[3][7][2])));
        Vpk[3][7][2] = (((Cik[7][0][1]*rk[2][0])-(Cik[7][0][0]*rk[2][1]))+((
          Cik[7][1][2]*VWri[3][7][1])+(Cik[7][2][2]*VWri[3][7][2])));
        Vpk[4][5][0] = -rk[0][2];
        Vpk[4][5][2] = rk[0][0];
        VWri[4][6][0] = (ri[1][2]-rk[0][2]);
        VWri[4][6][2] = (rk[0][0]-ri[1][0]);
        Vpk[4][6][0] = (((Cik[6][0][0]*VWri[4][6][0])+(Cik[6][2][0]*
          VWri[4][6][2]))+((Cik[6][1][2]*rk[1][1])-(Cik[6][1][1]*rk[1][2])));
        Vpk[4][6][1] = (((Cik[6][0][1]*VWri[4][6][0])+(Cik[6][2][1]*
          VWri[4][6][2]))+((Cik[6][1][0]*rk[1][2])-(Cik[6][1][2]*rk[1][0])));
        Vpk[4][6][2] = (((Cik[6][0][2]*VWri[4][6][0])+(Cik[6][2][2]*
          VWri[4][6][2]))+((Cik[6][1][1]*rk[1][0])-(Cik[6][1][0]*rk[1][1])));
        VWri[4][7][0] = (ri[2][2]-rk[0][2]);
        VWri[4][7][2] = (rk[0][0]-ri[2][0]);
        Vpk[4][7][0] = (((Cik[7][0][0]*VWri[4][7][0])+(Cik[7][2][0]*
          VWri[4][7][2]))+((Cik[7][1][2]*rk[2][1])-(Cik[7][1][1]*rk[2][2])));
        Vpk[4][7][1] = (((Cik[7][0][1]*VWri[4][7][0])+(Cik[7][2][1]*
          VWri[4][7][2]))+((Cik[7][1][0]*rk[2][2])-(Cik[7][1][2]*rk[2][0])));
        Vpk[4][7][2] = (((Cik[7][0][2]*VWri[4][7][0])+(Cik[7][2][2]*
          VWri[4][7][2]))+((Cik[7][1][1]*rk[2][0])-(Cik[7][1][0]*rk[2][1])));
        Vpk[5][5][0] = rk[0][1];
        Vpk[5][5][1] = -rk[0][0];
        VWri[5][6][0] = (rk[0][1]-ri[1][1]);
        VWri[5][6][1] = (ri[1][0]-rk[0][0]);
        Vpk[5][6][0] = (((Cik[6][0][0]*VWri[5][6][0])+(Cik[6][1][0]*
          VWri[5][6][1]))+((Cik[6][2][2]*rk[1][1])-(Cik[6][2][1]*rk[1][2])));
        Vpk[5][6][1] = (((Cik[6][0][1]*VWri[5][6][0])+(Cik[6][1][1]*
          VWri[5][6][1]))+((Cik[6][2][0]*rk[1][2])-(Cik[6][2][2]*rk[1][0])));
        Vpk[5][6][2] = (((Cik[6][0][2]*VWri[5][6][0])+(Cik[6][1][2]*
          VWri[5][6][1]))+((Cik[6][2][1]*rk[1][0])-(Cik[6][2][0]*rk[1][1])));
        VWri[5][7][0] = (rk[0][1]-ri[2][1]);
        VWri[5][7][1] = (ri[2][0]-rk[0][0]);
        Vpk[5][7][0] = (((Cik[7][0][0]*VWri[5][7][0])+(Cik[7][1][0]*
          VWri[5][7][1]))+((Cik[7][2][2]*rk[2][1])-(Cik[7][2][1]*rk[2][2])));
        Vpk[5][7][1] = (((Cik[7][0][1]*VWri[5][7][0])+(Cik[7][1][1]*
          VWri[5][7][1]))+((Cik[7][2][0]*rk[2][2])-(Cik[7][2][2]*rk[2][0])));
        Vpk[5][7][2] = (((Cik[7][0][2]*VWri[5][7][0])+(Cik[7][1][2]*
          VWri[5][7][1]))+((Cik[7][2][1]*rk[2][0])-(Cik[7][2][0]*rk[2][1])));
        Vpk[6][6][0] = ((pin[6][2]*rk[1][1])-(pin[6][1]*rk[1][2]));
        Vpk[6][6][1] = ((pin[6][0]*rk[1][2])-(pin[6][2]*rk[1][0]));
        Vpk[6][6][2] = ((pin[6][1]*rk[1][0])-(pin[6][0]*rk[1][1]));
        Vpk[7][7][0] = ((pin[7][2]*rk[2][1])-(pin[7][1]*rk[2][2]));
        Vpk[7][7][1] = ((pin[7][0]*rk[2][2])-(pin[7][2]*rk[2][0]));
        Vpk[7][7][2] = ((pin[7][1]*rk[2][0])-(pin[7][0]*rk[2][1]));
        vpkflg = 1;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  129 adds/subtracts/negates
                    165 multiplies
                      0 divides
                    135 assignments
*/
}

void sddoltau(void)
{

/*
Compute effect of loop hinge torques
*/
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      0 assignments
*/
}

void sddoiner(void)
{

/*
Compute inertial accelerations and related temps
*/
    if (inerflg == 0) {
/*
Compute Otk (inertial angular acceleration)
*/
        Otk[6][0] = ((Wik[6][2]*wk[6][1])-(Wik[6][1]*wk[6][2]));
        Otk[6][1] = ((Wik[6][0]*wk[6][2])-(Wik[6][2]*wk[6][0]));
        Otk[6][2] = ((Wik[6][1]*wk[6][0])-(Wik[6][0]*wk[6][1]));
        Otk[7][0] = ((Wik[7][2]*wk[7][1])-(Wik[7][1]*wk[7][2]));
        Otk[7][1] = ((Wik[7][0]*wk[7][2])-(Wik[7][2]*wk[7][0]));
        Otk[7][2] = ((Wik[7][1]*wk[7][0])-(Wik[7][0]*wk[7][1]));
/*
Compute Atk (inertial linear acceleration)
*/
        Atk[5][0] = ((u[4]*Wkrpk[5][2])-(u[5]*Wkrpk[5][1]));
        Atk[5][1] = ((u[5]*Wkrpk[5][0])-(u[3]*Wkrpk[5][2]));
        Atk[5][2] = ((u[3]*Wkrpk[5][1])-(u[4]*Wkrpk[5][0]));
        AiOiWi[6][0] = (Atk[5][0]+((u[4]*Wirk[6][2])-(u[5]*Wirk[6][1])));
        AiOiWi[6][1] = (Atk[5][1]+((u[5]*Wirk[6][0])-(u[3]*Wirk[6][2])));
        AiOiWi[6][2] = (Atk[5][2]+((u[3]*Wirk[6][1])-(u[4]*Wirk[6][0])));
        Atk[6][0] = (((AiOiWi[6][2]*Cik[6][2][0])+((AiOiWi[6][0]*Cik[6][0][0])+(
          AiOiWi[6][1]*Cik[6][1][0])))+(((Otk[6][2]*rk[1][1])-(Otk[6][1]*
          rk[1][2]))+((wk[6][1]*Wkrpk[6][2])-(wk[6][2]*Wkrpk[6][1]))));
        Atk[6][1] = (((AiOiWi[6][2]*Cik[6][2][1])+((AiOiWi[6][0]*Cik[6][0][1])+(
          AiOiWi[6][1]*Cik[6][1][1])))+(((Otk[6][0]*rk[1][2])-(Otk[6][2]*
          rk[1][0]))+((wk[6][2]*Wkrpk[6][0])-(wk[6][0]*Wkrpk[6][2]))));
        Atk[6][2] = (((AiOiWi[6][2]*Cik[6][2][2])+((AiOiWi[6][0]*Cik[6][0][2])+(
          AiOiWi[6][1]*Cik[6][1][2])))+(((Otk[6][1]*rk[1][0])-(Otk[6][0]*
          rk[1][1]))+((wk[6][0]*Wkrpk[6][1])-(wk[6][1]*Wkrpk[6][0]))));
        AiOiWi[7][0] = (Atk[5][0]+((u[4]*Wirk[7][2])-(u[5]*Wirk[7][1])));
        AiOiWi[7][1] = (Atk[5][1]+((u[5]*Wirk[7][0])-(u[3]*Wirk[7][2])));
        AiOiWi[7][2] = (Atk[5][2]+((u[3]*Wirk[7][1])-(u[4]*Wirk[7][0])));
        Atk[7][0] = (((AiOiWi[7][2]*Cik[7][2][0])+((AiOiWi[7][0]*Cik[7][0][0])+(
          AiOiWi[7][1]*Cik[7][1][0])))+(((Otk[7][2]*rk[2][1])-(Otk[7][1]*
          rk[2][2]))+((wk[7][1]*Wkrpk[7][2])-(wk[7][2]*Wkrpk[7][1]))));
        Atk[7][1] = (((AiOiWi[7][2]*Cik[7][2][1])+((AiOiWi[7][0]*Cik[7][0][1])+(
          AiOiWi[7][1]*Cik[7][1][1])))+(((Otk[7][0]*rk[2][2])-(Otk[7][2]*
          rk[2][0]))+((wk[7][2]*Wkrpk[7][0])-(wk[7][0]*Wkrpk[7][2]))));
        Atk[7][2] = (((AiOiWi[7][2]*Cik[7][2][2])+((AiOiWi[7][0]*Cik[7][0][2])+(
          AiOiWi[7][1]*Cik[7][1][2])))+(((Otk[7][1]*rk[2][0])-(Otk[7][0]*
          rk[2][1]))+((wk[7][0]*Wkrpk[7][1])-(wk[7][1]*Wkrpk[7][0]))));
        inerflg = 1;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   57 adds/subtracts/negates
                     72 multiplies
                      0 divides
                     21 assignments
*/
}

void sddofs0(void)
{

/*
Compute effect of all applied loads
*/
    if (fs0flg == 0) {
        sddoltau();
        sddoiner();
/*
Compute Fstar (forces)
*/
        Fstar[5][0] = ((mk[0]*(Atk[5][0]+(9.81*Cik[3][2][0])))-ufk[0][0]);
        Fstar[5][1] = ((mk[0]*(Atk[5][1]+(9.81*Cik[3][2][1])))-ufk[0][1]);
        Fstar[5][2] = ((mk[0]*(Atk[5][2]+(9.81*Cik[3][2][2])))-ufk[0][2]);
        Fstar[6][0] = ((mk[1]*(Atk[6][0]-gk[6][0]))-ufk[1][0]);
        Fstar[6][1] = ((mk[1]*(Atk[6][1]-gk[6][1]))-ufk[1][1]);
        Fstar[6][2] = ((mk[1]*(Atk[6][2]-gk[6][2]))-ufk[1][2]);
        Fstar[7][0] = ((mk[2]*(Atk[7][0]-gk[7][0]))-ufk[2][0]);
        Fstar[7][1] = ((mk[2]*(Atk[7][1]-gk[7][1]))-ufk[2][1]);
        Fstar[7][2] = ((mk[2]*(Atk[7][2]-gk[7][2]))-ufk[2][2]);
/*
Compute Tstar (torques)
*/
        Tstar[5][0] = (WkIkWk[5][0]-utk[0][0]);
        Tstar[5][1] = (WkIkWk[5][1]-utk[0][1]);
        Tstar[5][2] = (WkIkWk[5][2]-utk[0][2]);
        Tstar[6][0] = ((WkIkWk[6][0]+((ik[1][0][2]*Otk[6][2])+((ik[1][0][0]*
          Otk[6][0])+(ik[1][0][1]*Otk[6][1]))))-utk[1][0]);
        Tstar[6][1] = ((WkIkWk[6][1]+((ik[1][1][2]*Otk[6][2])+((ik[1][1][0]*
          Otk[6][0])+(ik[1][1][1]*Otk[6][1]))))-utk[1][1]);
        Tstar[6][2] = ((WkIkWk[6][2]+((ik[1][2][2]*Otk[6][2])+((ik[1][2][0]*
          Otk[6][0])+(ik[1][2][1]*Otk[6][1]))))-utk[1][2]);
        Tstar[7][0] = ((WkIkWk[7][0]+((ik[2][0][2]*Otk[7][2])+((ik[2][0][0]*
          Otk[7][0])+(ik[2][0][1]*Otk[7][1]))))-utk[2][0]);
        Tstar[7][1] = ((WkIkWk[7][1]+((ik[2][1][2]*Otk[7][2])+((ik[2][1][0]*
          Otk[7][0])+(ik[2][1][1]*Otk[7][1]))))-utk[2][1]);
        Tstar[7][2] = ((WkIkWk[7][2]+((ik[2][2][2]*Otk[7][2])+((ik[2][2][0]*
          Otk[7][0])+(ik[2][2][1]*Otk[7][1]))))-utk[2][2]);
/*
Compute fs0 (RHS ignoring constraints)
*/
        sddovpk();
        fs0[0] = (utau[0]-(((Fstar[7][2]*Vpk[0][7][2])+((Fstar[7][0]*
          Vpk[0][7][0])+(Fstar[7][1]*Vpk[0][7][1])))+(((Fstar[5][2]*Vpk[0][3][2]
          )+((Fstar[5][0]*Vpk[0][3][0])+(Fstar[5][1]*Vpk[0][3][1])))+((
          Fstar[6][2]*Vpk[0][6][2])+((Fstar[6][0]*Vpk[0][6][0])+(Fstar[6][1]*
          Vpk[0][6][1]))))));
        fs0[1] = (utau[1]-(((Fstar[7][2]*Vpk[1][7][2])+((Fstar[7][0]*
          Vpk[1][7][0])+(Fstar[7][1]*Vpk[1][7][1])))+(((Fstar[5][2]*Vpk[1][3][2]
          )+((Fstar[5][0]*Vpk[1][3][0])+(Fstar[5][1]*Vpk[1][3][1])))+((
          Fstar[6][2]*Vpk[1][6][2])+((Fstar[6][0]*Vpk[1][6][0])+(Fstar[6][1]*
          Vpk[1][6][1]))))));
        fs0[2] = (utau[2]-(((Fstar[7][2]*Vpk[2][7][2])+((Fstar[7][0]*
          Vpk[2][7][0])+(Fstar[7][1]*Vpk[2][7][1])))+(((Fstar[5][2]*Vpk[2][3][2]
          )+((Fstar[5][0]*Vpk[2][3][0])+(Fstar[5][1]*Vpk[2][3][1])))+((
          Fstar[6][2]*Vpk[2][6][2])+((Fstar[6][0]*Vpk[2][6][0])+(Fstar[6][1]*
          Vpk[2][6][1]))))));
        temp[0] = (((Tstar[5][0]+((Fstar[5][1]*rk[0][2])-(Fstar[5][2]*rk[0][1]))
          )+(((Cik[6][0][2]*Tstar[6][2])+((Cik[6][0][0]*Tstar[6][0])+(
          Cik[6][0][1]*Tstar[6][1])))+((Fstar[6][2]*Vpk[3][6][2])+((Fstar[6][0]*
          Vpk[3][6][0])+(Fstar[6][1]*Vpk[3][6][1])))))+(((Cik[7][0][2]*
          Tstar[7][2])+((Cik[7][0][0]*Tstar[7][0])+(Cik[7][0][1]*Tstar[7][1])))+
          ((Fstar[7][2]*Vpk[3][7][2])+((Fstar[7][0]*Vpk[3][7][0])+(Fstar[7][1]*
          Vpk[3][7][1])))));
        fs0[3] = (utau[3]-temp[0]);
        temp[0] = (((Tstar[5][1]+((Fstar[5][2]*rk[0][0])-(Fstar[5][0]*rk[0][2]))
          )+(((Cik[6][1][2]*Tstar[6][2])+((Cik[6][1][0]*Tstar[6][0])+(
          Cik[6][1][1]*Tstar[6][1])))+((Fstar[6][2]*Vpk[4][6][2])+((Fstar[6][0]*
          Vpk[4][6][0])+(Fstar[6][1]*Vpk[4][6][1])))))+(((Cik[7][1][2]*
          Tstar[7][2])+((Cik[7][1][0]*Tstar[7][0])+(Cik[7][1][1]*Tstar[7][1])))+
          ((Fstar[7][2]*Vpk[4][7][2])+((Fstar[7][0]*Vpk[4][7][0])+(Fstar[7][1]*
          Vpk[4][7][1])))));
        fs0[4] = (utau[4]-temp[0]);
        temp[0] = (((Tstar[5][2]+((Fstar[5][0]*rk[0][1])-(Fstar[5][1]*rk[0][0]))
          )+(((Cik[6][2][2]*Tstar[6][2])+((Cik[6][2][0]*Tstar[6][0])+(
          Cik[6][2][1]*Tstar[6][1])))+((Fstar[6][2]*Vpk[5][6][2])+((Fstar[6][0]*
          Vpk[5][6][0])+(Fstar[6][1]*Vpk[5][6][1])))))+(((Cik[7][2][2]*
          Tstar[7][2])+((Cik[7][2][0]*Tstar[7][0])+(Cik[7][2][1]*Tstar[7][1])))+
          ((Fstar[7][2]*Vpk[5][7][2])+((Fstar[7][0]*Vpk[5][7][0])+(Fstar[7][1]*
          Vpk[5][7][1])))));
        fs0[5] = (utau[5]-temp[0]);
        fs0[6] = (utau[6]-(((Fstar[6][2]*Vpk[6][6][2])+((Fstar[6][0]*
          Vpk[6][6][0])+(Fstar[6][1]*Vpk[6][6][1])))+((pin[6][2]*Tstar[6][2])+((
          pin[6][0]*Tstar[6][0])+(pin[6][1]*Tstar[6][1])))));
        fs0[7] = (utau[7]-(((Fstar[7][2]*Vpk[7][7][2])+((Fstar[7][0]*
          Vpk[7][7][0])+(Fstar[7][1]*Vpk[7][7][1])))+((pin[7][2]*Tstar[7][2])+((
          pin[7][0]*Tstar[7][0])+(pin[7][1]*Tstar[7][1])))));
        fs0flg = 1;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  129 adds/subtracts/negates
                    111 multiplies
                      0 divides
                     29 assignments
*/
}

void sddomm(int routine)
{
    int dumroutine,errnum;
    int i;

    if (mmflg == 0) {
/*
Compute mass matrix (MM)
*/
        sddovpk();
        IkWpk[3][6][0] = ((Cik[6][0][2]*ik[1][0][2])+((Cik[6][0][0]*ik[1][0][0])
          +(Cik[6][0][1]*ik[1][0][1])));
        IkWpk[3][6][1] = ((Cik[6][0][2]*ik[1][1][2])+((Cik[6][0][0]*ik[1][1][0])
          +(Cik[6][0][1]*ik[1][1][1])));
        IkWpk[3][6][2] = ((Cik[6][0][2]*ik[1][2][2])+((Cik[6][0][0]*ik[1][2][0])
          +(Cik[6][0][1]*ik[1][2][1])));
        IkWpk[3][7][0] = ((Cik[7][0][2]*ik[2][0][2])+((Cik[7][0][0]*ik[2][0][0])
          +(Cik[7][0][1]*ik[2][0][1])));
        IkWpk[3][7][1] = ((Cik[7][0][2]*ik[2][1][2])+((Cik[7][0][0]*ik[2][1][0])
          +(Cik[7][0][1]*ik[2][1][1])));
        IkWpk[3][7][2] = ((Cik[7][0][2]*ik[2][2][2])+((Cik[7][0][0]*ik[2][2][0])
          +(Cik[7][0][1]*ik[2][2][1])));
        IkWpk[4][6][0] = ((Cik[6][1][2]*ik[1][0][2])+((Cik[6][1][0]*ik[1][0][0])
          +(Cik[6][1][1]*ik[1][0][1])));
        IkWpk[4][6][1] = ((Cik[6][1][2]*ik[1][1][2])+((Cik[6][1][0]*ik[1][1][0])
          +(Cik[6][1][1]*ik[1][1][1])));
        IkWpk[4][6][2] = ((Cik[6][1][2]*ik[1][2][2])+((Cik[6][1][0]*ik[1][2][0])
          +(Cik[6][1][1]*ik[1][2][1])));
        IkWpk[4][7][0] = ((Cik[7][1][2]*ik[2][0][2])+((Cik[7][1][0]*ik[2][0][0])
          +(Cik[7][1][1]*ik[2][0][1])));
        IkWpk[4][7][1] = ((Cik[7][1][2]*ik[2][1][2])+((Cik[7][1][0]*ik[2][1][0])
          +(Cik[7][1][1]*ik[2][1][1])));
        IkWpk[4][7][2] = ((Cik[7][1][2]*ik[2][2][2])+((Cik[7][1][0]*ik[2][2][0])
          +(Cik[7][1][1]*ik[2][2][1])));
        IkWpk[5][6][0] = ((Cik[6][2][2]*ik[1][0][2])+((Cik[6][2][0]*ik[1][0][0])
          +(Cik[6][2][1]*ik[1][0][1])));
        IkWpk[5][6][1] = ((Cik[6][2][2]*ik[1][1][2])+((Cik[6][2][0]*ik[1][1][0])
          +(Cik[6][2][1]*ik[1][1][1])));
        IkWpk[5][6][2] = ((Cik[6][2][2]*ik[1][2][2])+((Cik[6][2][0]*ik[1][2][0])
          +(Cik[6][2][1]*ik[1][2][1])));
        IkWpk[5][7][0] = ((Cik[7][2][2]*ik[2][0][2])+((Cik[7][2][0]*ik[2][0][0])
          +(Cik[7][2][1]*ik[2][0][1])));
        IkWpk[5][7][1] = ((Cik[7][2][2]*ik[2][1][2])+((Cik[7][2][0]*ik[2][1][0])
          +(Cik[7][2][1]*ik[2][1][1])));
        IkWpk[5][7][2] = ((Cik[7][2][2]*ik[2][2][2])+((Cik[7][2][0]*ik[2][2][0])
          +(Cik[7][2][1]*ik[2][2][1])));
        IkWpk[6][6][0] = ((ik[1][0][2]*pin[6][2])+((ik[1][0][0]*pin[6][0])+(
          ik[1][0][1]*pin[6][1])));
        IkWpk[6][6][1] = ((ik[1][1][2]*pin[6][2])+((ik[1][1][0]*pin[6][0])+(
          ik[1][1][1]*pin[6][1])));
        IkWpk[6][6][2] = ((ik[1][2][2]*pin[6][2])+((ik[1][2][0]*pin[6][0])+(
          ik[1][2][1]*pin[6][1])));
        IkWpk[7][7][0] = ((ik[2][0][2]*pin[7][2])+((ik[2][0][0]*pin[7][0])+(
          ik[2][0][1]*pin[7][1])));
        IkWpk[7][7][1] = ((ik[2][1][2]*pin[7][2])+((ik[2][1][0]*pin[7][0])+(
          ik[2][1][1]*pin[7][1])));
        IkWpk[7][7][2] = ((ik[2][2][2]*pin[7][2])+((ik[2][2][0]*pin[7][0])+(
          ik[2][2][1]*pin[7][1])));
        mm[0][0] = ((mk[2]*((Vpk[0][7][2]*Vpk[0][7][2])+((Vpk[0][7][0]*
          Vpk[0][7][0])+(Vpk[0][7][1]*Vpk[0][7][1]))))+((mk[0]*((Vpk[0][3][2]*
          Vpk[0][3][2])+((Vpk[0][3][0]*Vpk[0][3][0])+(Vpk[0][3][1]*Vpk[0][3][1])
          )))+(mk[1]*((Vpk[0][6][2]*Vpk[0][6][2])+((Vpk[0][6][0]*Vpk[0][6][0])+(
          Vpk[0][6][1]*Vpk[0][6][1]))))));
        mm[0][1] = ((mk[2]*((Vpk[0][7][2]*Vpk[1][7][2])+((Vpk[0][7][0]*
          Vpk[1][7][0])+(Vpk[0][7][1]*Vpk[1][7][1]))))+((mk[0]*((Vpk[0][3][2]*
          Vpk[1][3][2])+((Vpk[0][3][0]*Vpk[1][3][0])+(Vpk[0][3][1]*Vpk[1][3][1])
          )))+(mk[1]*((Vpk[0][6][2]*Vpk[1][6][2])+((Vpk[0][6][0]*Vpk[1][6][0])+(
          Vpk[0][6][1]*Vpk[1][6][1]))))));
        mm[0][2] = ((mk[2]*((Vpk[0][7][2]*Vpk[2][7][2])+((Vpk[0][7][0]*
          Vpk[2][7][0])+(Vpk[0][7][1]*Vpk[2][7][1]))))+((mk[0]*((Vpk[0][3][2]*
          Vpk[2][3][2])+((Vpk[0][3][0]*Vpk[2][3][0])+(Vpk[0][3][1]*Vpk[2][3][1])
          )))+(mk[1]*((Vpk[0][6][2]*Vpk[2][6][2])+((Vpk[0][6][0]*Vpk[2][6][0])+(
          Vpk[0][6][1]*Vpk[2][6][1]))))));
        mm[0][3] = ((mk[2]*((Vpk[0][7][2]*Vpk[3][7][2])+((Vpk[0][7][0]*
          Vpk[3][7][0])+(Vpk[0][7][1]*Vpk[3][7][1]))))+((mk[0]*((rk[0][2]*
          Vpk[0][3][1])-(rk[0][1]*Vpk[0][3][2])))+(mk[1]*((Vpk[0][6][2]*
          Vpk[3][6][2])+((Vpk[0][6][0]*Vpk[3][6][0])+(Vpk[0][6][1]*Vpk[3][6][1])
          )))));
        mm[0][4] = ((mk[2]*((Vpk[0][7][2]*Vpk[4][7][2])+((Vpk[0][7][0]*
          Vpk[4][7][0])+(Vpk[0][7][1]*Vpk[4][7][1]))))+((mk[0]*((rk[0][0]*
          Vpk[0][3][2])-(rk[0][2]*Vpk[0][3][0])))+(mk[1]*((Vpk[0][6][2]*
          Vpk[4][6][2])+((Vpk[0][6][0]*Vpk[4][6][0])+(Vpk[0][6][1]*Vpk[4][6][1])
          )))));
        mm[0][5] = ((mk[2]*((Vpk[0][7][2]*Vpk[5][7][2])+((Vpk[0][7][0]*
          Vpk[5][7][0])+(Vpk[0][7][1]*Vpk[5][7][1]))))+((mk[0]*((rk[0][1]*
          Vpk[0][3][0])-(rk[0][0]*Vpk[0][3][1])))+(mk[1]*((Vpk[0][6][2]*
          Vpk[5][6][2])+((Vpk[0][6][0]*Vpk[5][6][0])+(Vpk[0][6][1]*Vpk[5][6][1])
          )))));
        mm[0][6] = (mk[1]*((Vpk[0][6][2]*Vpk[6][6][2])+((Vpk[0][6][0]*
          Vpk[6][6][0])+(Vpk[0][6][1]*Vpk[6][6][1]))));
        mm[0][7] = (mk[2]*((Vpk[0][7][2]*Vpk[7][7][2])+((Vpk[0][7][0]*
          Vpk[7][7][0])+(Vpk[0][7][1]*Vpk[7][7][1]))));
        mm[1][1] = ((mk[2]*((Vpk[1][7][2]*Vpk[1][7][2])+((Vpk[1][7][0]*
          Vpk[1][7][0])+(Vpk[1][7][1]*Vpk[1][7][1]))))+((mk[0]*((Vpk[1][3][2]*
          Vpk[1][3][2])+((Vpk[1][3][0]*Vpk[1][3][0])+(Vpk[1][3][1]*Vpk[1][3][1])
          )))+(mk[1]*((Vpk[1][6][2]*Vpk[1][6][2])+((Vpk[1][6][0]*Vpk[1][6][0])+(
          Vpk[1][6][1]*Vpk[1][6][1]))))));
        mm[1][2] = ((mk[2]*((Vpk[1][7][2]*Vpk[2][7][2])+((Vpk[1][7][0]*
          Vpk[2][7][0])+(Vpk[1][7][1]*Vpk[2][7][1]))))+((mk[0]*((Vpk[1][3][2]*
          Vpk[2][3][2])+((Vpk[1][3][0]*Vpk[2][3][0])+(Vpk[1][3][1]*Vpk[2][3][1])
          )))+(mk[1]*((Vpk[1][6][2]*Vpk[2][6][2])+((Vpk[1][6][0]*Vpk[2][6][0])+(
          Vpk[1][6][1]*Vpk[2][6][1]))))));
        mm[1][3] = ((mk[2]*((Vpk[1][7][2]*Vpk[3][7][2])+((Vpk[1][7][0]*
          Vpk[3][7][0])+(Vpk[1][7][1]*Vpk[3][7][1]))))+((mk[0]*((rk[0][2]*
          Vpk[1][3][1])-(rk[0][1]*Vpk[1][3][2])))+(mk[1]*((Vpk[1][6][2]*
          Vpk[3][6][2])+((Vpk[1][6][0]*Vpk[3][6][0])+(Vpk[1][6][1]*Vpk[3][6][1])
          )))));
        mm[1][4] = ((mk[2]*((Vpk[1][7][2]*Vpk[4][7][2])+((Vpk[1][7][0]*
          Vpk[4][7][0])+(Vpk[1][7][1]*Vpk[4][7][1]))))+((mk[0]*((rk[0][0]*
          Vpk[1][3][2])-(rk[0][2]*Vpk[1][3][0])))+(mk[1]*((Vpk[1][6][2]*
          Vpk[4][6][2])+((Vpk[1][6][0]*Vpk[4][6][0])+(Vpk[1][6][1]*Vpk[4][6][1])
          )))));
        mm[1][5] = ((mk[2]*((Vpk[1][7][2]*Vpk[5][7][2])+((Vpk[1][7][0]*
          Vpk[5][7][0])+(Vpk[1][7][1]*Vpk[5][7][1]))))+((mk[0]*((rk[0][1]*
          Vpk[1][3][0])-(rk[0][0]*Vpk[1][3][1])))+(mk[1]*((Vpk[1][6][2]*
          Vpk[5][6][2])+((Vpk[1][6][0]*Vpk[5][6][0])+(Vpk[1][6][1]*Vpk[5][6][1])
          )))));
        mm[1][6] = (mk[1]*((Vpk[1][6][2]*Vpk[6][6][2])+((Vpk[1][6][0]*
          Vpk[6][6][0])+(Vpk[1][6][1]*Vpk[6][6][1]))));
        mm[1][7] = (mk[2]*((Vpk[1][7][2]*Vpk[7][7][2])+((Vpk[1][7][0]*
          Vpk[7][7][0])+(Vpk[1][7][1]*Vpk[7][7][1]))));
        mm[2][2] = ((mk[2]*((Vpk[2][7][2]*Vpk[2][7][2])+((Vpk[2][7][0]*
          Vpk[2][7][0])+(Vpk[2][7][1]*Vpk[2][7][1]))))+((mk[0]*((Vpk[2][3][2]*
          Vpk[2][3][2])+((Vpk[2][3][0]*Vpk[2][3][0])+(Vpk[2][3][1]*Vpk[2][3][1])
          )))+(mk[1]*((Vpk[2][6][2]*Vpk[2][6][2])+((Vpk[2][6][0]*Vpk[2][6][0])+(
          Vpk[2][6][1]*Vpk[2][6][1]))))));
        mm[2][3] = ((mk[2]*((Vpk[2][7][2]*Vpk[3][7][2])+((Vpk[2][7][0]*
          Vpk[3][7][0])+(Vpk[2][7][1]*Vpk[3][7][1]))))+((mk[0]*((rk[0][2]*
          Vpk[2][3][1])-(rk[0][1]*Vpk[2][3][2])))+(mk[1]*((Vpk[2][6][2]*
          Vpk[3][6][2])+((Vpk[2][6][0]*Vpk[3][6][0])+(Vpk[2][6][1]*Vpk[3][6][1])
          )))));
        mm[2][4] = ((mk[2]*((Vpk[2][7][2]*Vpk[4][7][2])+((Vpk[2][7][0]*
          Vpk[4][7][0])+(Vpk[2][7][1]*Vpk[4][7][1]))))+((mk[0]*((rk[0][0]*
          Vpk[2][3][2])-(rk[0][2]*Vpk[2][3][0])))+(mk[1]*((Vpk[2][6][2]*
          Vpk[4][6][2])+((Vpk[2][6][0]*Vpk[4][6][0])+(Vpk[2][6][1]*Vpk[4][6][1])
          )))));
        mm[2][5] = ((mk[2]*((Vpk[2][7][2]*Vpk[5][7][2])+((Vpk[2][7][0]*
          Vpk[5][7][0])+(Vpk[2][7][1]*Vpk[5][7][1]))))+((mk[0]*((rk[0][1]*
          Vpk[2][3][0])-(rk[0][0]*Vpk[2][3][1])))+(mk[1]*((Vpk[2][6][2]*
          Vpk[5][6][2])+((Vpk[2][6][0]*Vpk[5][6][0])+(Vpk[2][6][1]*Vpk[5][6][1])
          )))));
        mm[2][6] = (mk[1]*((Vpk[2][6][2]*Vpk[6][6][2])+((Vpk[2][6][0]*
          Vpk[6][6][0])+(Vpk[2][6][1]*Vpk[6][6][1]))));
        mm[2][7] = (mk[2]*((Vpk[2][7][2]*Vpk[7][7][2])+((Vpk[2][7][0]*
          Vpk[7][7][0])+(Vpk[2][7][1]*Vpk[7][7][1]))));
        temp[0] = ((ik[0][0][0]+(mk[0]*((rk[0][1]*rk[0][1])+(rk[0][2]*rk[0][2]))
          ))+((mk[1]*((Vpk[3][6][2]*Vpk[3][6][2])+((Vpk[3][6][0]*Vpk[3][6][0])+(
          Vpk[3][6][1]*Vpk[3][6][1]))))+((Cik[6][0][2]*IkWpk[3][6][2])+((
          Cik[6][0][0]*IkWpk[3][6][0])+(Cik[6][0][1]*IkWpk[3][6][1])))));
        mm[3][3] = (temp[0]+((mk[2]*((Vpk[3][7][2]*Vpk[3][7][2])+((Vpk[3][7][0]*
          Vpk[3][7][0])+(Vpk[3][7][1]*Vpk[3][7][1]))))+((Cik[7][0][2]*
          IkWpk[3][7][2])+((Cik[7][0][0]*IkWpk[3][7][0])+(Cik[7][0][1]*
          IkWpk[3][7][1])))));
        temp[0] = ((ik[0][0][1]-(mk[0]*(rk[0][0]*rk[0][1])))+((mk[1]*((
          Vpk[3][6][2]*Vpk[4][6][2])+((Vpk[3][6][0]*Vpk[4][6][0])+(Vpk[3][6][1]*
          Vpk[4][6][1]))))+((Cik[6][0][2]*IkWpk[4][6][2])+((Cik[6][0][0]*
          IkWpk[4][6][0])+(Cik[6][0][1]*IkWpk[4][6][1])))));
        mm[3][4] = (temp[0]+((mk[2]*((Vpk[3][7][2]*Vpk[4][7][2])+((Vpk[3][7][0]*
          Vpk[4][7][0])+(Vpk[3][7][1]*Vpk[4][7][1]))))+((Cik[7][0][2]*
          IkWpk[4][7][2])+((Cik[7][0][0]*IkWpk[4][7][0])+(Cik[7][0][1]*
          IkWpk[4][7][1])))));
        temp[0] = ((ik[0][0][2]-(mk[0]*(rk[0][0]*rk[0][2])))+((mk[1]*((
          Vpk[3][6][2]*Vpk[5][6][2])+((Vpk[3][6][0]*Vpk[5][6][0])+(Vpk[3][6][1]*
          Vpk[5][6][1]))))+((Cik[6][0][2]*IkWpk[5][6][2])+((Cik[6][0][0]*
          IkWpk[5][6][0])+(Cik[6][0][1]*IkWpk[5][6][1])))));
        mm[3][5] = (temp[0]+((mk[2]*((Vpk[3][7][2]*Vpk[5][7][2])+((Vpk[3][7][0]*
          Vpk[5][7][0])+(Vpk[3][7][1]*Vpk[5][7][1]))))+((Cik[7][0][2]*
          IkWpk[5][7][2])+((Cik[7][0][0]*IkWpk[5][7][0])+(Cik[7][0][1]*
          IkWpk[5][7][1])))));
        mm[3][6] = ((mk[1]*((Vpk[3][6][2]*Vpk[6][6][2])+((Vpk[3][6][0]*
          Vpk[6][6][0])+(Vpk[3][6][1]*Vpk[6][6][1]))))+((Cik[6][0][2]*
          IkWpk[6][6][2])+((Cik[6][0][0]*IkWpk[6][6][0])+(Cik[6][0][1]*
          IkWpk[6][6][1]))));
        mm[3][7] = ((mk[2]*((Vpk[3][7][2]*Vpk[7][7][2])+((Vpk[3][7][0]*
          Vpk[7][7][0])+(Vpk[3][7][1]*Vpk[7][7][1]))))+((Cik[7][0][2]*
          IkWpk[7][7][2])+((Cik[7][0][0]*IkWpk[7][7][0])+(Cik[7][0][1]*
          IkWpk[7][7][1]))));
        temp[0] = ((ik[0][1][1]+(mk[0]*((rk[0][0]*rk[0][0])+(rk[0][2]*rk[0][2]))
          ))+((mk[1]*((Vpk[4][6][2]*Vpk[4][6][2])+((Vpk[4][6][0]*Vpk[4][6][0])+(
          Vpk[4][6][1]*Vpk[4][6][1]))))+((Cik[6][1][2]*IkWpk[4][6][2])+((
          Cik[6][1][0]*IkWpk[4][6][0])+(Cik[6][1][1]*IkWpk[4][6][1])))));
        mm[4][4] = (temp[0]+((mk[2]*((Vpk[4][7][2]*Vpk[4][7][2])+((Vpk[4][7][0]*
          Vpk[4][7][0])+(Vpk[4][7][1]*Vpk[4][7][1]))))+((Cik[7][1][2]*
          IkWpk[4][7][2])+((Cik[7][1][0]*IkWpk[4][7][0])+(Cik[7][1][1]*
          IkWpk[4][7][1])))));
        temp[0] = ((ik[0][1][2]-(mk[0]*(rk[0][1]*rk[0][2])))+((mk[1]*((
          Vpk[4][6][2]*Vpk[5][6][2])+((Vpk[4][6][0]*Vpk[5][6][0])+(Vpk[4][6][1]*
          Vpk[5][6][1]))))+((Cik[6][1][2]*IkWpk[5][6][2])+((Cik[6][1][0]*
          IkWpk[5][6][0])+(Cik[6][1][1]*IkWpk[5][6][1])))));
        mm[4][5] = (temp[0]+((mk[2]*((Vpk[4][7][2]*Vpk[5][7][2])+((Vpk[4][7][0]*
          Vpk[5][7][0])+(Vpk[4][7][1]*Vpk[5][7][1]))))+((Cik[7][1][2]*
          IkWpk[5][7][2])+((Cik[7][1][0]*IkWpk[5][7][0])+(Cik[7][1][1]*
          IkWpk[5][7][1])))));
        mm[4][6] = ((mk[1]*((Vpk[4][6][2]*Vpk[6][6][2])+((Vpk[4][6][0]*
          Vpk[6][6][0])+(Vpk[4][6][1]*Vpk[6][6][1]))))+((Cik[6][1][2]*
          IkWpk[6][6][2])+((Cik[6][1][0]*IkWpk[6][6][0])+(Cik[6][1][1]*
          IkWpk[6][6][1]))));
        mm[4][7] = ((mk[2]*((Vpk[4][7][2]*Vpk[7][7][2])+((Vpk[4][7][0]*
          Vpk[7][7][0])+(Vpk[4][7][1]*Vpk[7][7][1]))))+((Cik[7][1][2]*
          IkWpk[7][7][2])+((Cik[7][1][0]*IkWpk[7][7][0])+(Cik[7][1][1]*
          IkWpk[7][7][1]))));
        temp[0] = ((ik[0][2][2]+(mk[0]*((rk[0][0]*rk[0][0])+(rk[0][1]*rk[0][1]))
          ))+((mk[1]*((Vpk[5][6][2]*Vpk[5][6][2])+((Vpk[5][6][0]*Vpk[5][6][0])+(
          Vpk[5][6][1]*Vpk[5][6][1]))))+((Cik[6][2][2]*IkWpk[5][6][2])+((
          Cik[6][2][0]*IkWpk[5][6][0])+(Cik[6][2][1]*IkWpk[5][6][1])))));
        mm[5][5] = (temp[0]+((mk[2]*((Vpk[5][7][2]*Vpk[5][7][2])+((Vpk[5][7][0]*
          Vpk[5][7][0])+(Vpk[5][7][1]*Vpk[5][7][1]))))+((Cik[7][2][2]*
          IkWpk[5][7][2])+((Cik[7][2][0]*IkWpk[5][7][0])+(Cik[7][2][1]*
          IkWpk[5][7][1])))));
        mm[5][6] = ((mk[1]*((Vpk[5][6][2]*Vpk[6][6][2])+((Vpk[5][6][0]*
          Vpk[6][6][0])+(Vpk[5][6][1]*Vpk[6][6][1]))))+((Cik[6][2][2]*
          IkWpk[6][6][2])+((Cik[6][2][0]*IkWpk[6][6][0])+(Cik[6][2][1]*
          IkWpk[6][6][1]))));
        mm[5][7] = ((mk[2]*((Vpk[5][7][2]*Vpk[7][7][2])+((Vpk[5][7][0]*
          Vpk[7][7][0])+(Vpk[5][7][1]*Vpk[7][7][1]))))+((Cik[7][2][2]*
          IkWpk[7][7][2])+((Cik[7][2][0]*IkWpk[7][7][0])+(Cik[7][2][1]*
          IkWpk[7][7][1]))));
        mm[6][6] = ((mk[1]*((Vpk[6][6][2]*Vpk[6][6][2])+((Vpk[6][6][0]*
          Vpk[6][6][0])+(Vpk[6][6][1]*Vpk[6][6][1]))))+((IkWpk[6][6][2]*
          pin[6][2])+((IkWpk[6][6][0]*pin[6][0])+(IkWpk[6][6][1]*pin[6][1]))));
        mm[6][7] = 0.;
        mm[7][7] = ((mk[2]*((Vpk[7][7][2]*Vpk[7][7][2])+((Vpk[7][7][0]*
          Vpk[7][7][0])+(Vpk[7][7][1]*Vpk[7][7][1]))))+((IkWpk[7][7][2]*
          pin[7][2])+((IkWpk[7][7][0]*pin[7][0])+(IkWpk[7][7][1]*pin[7][1]))));
/*
Check for singular mass matrix
*/
        for (i = 0; i < 8; i++) {
            if (mm[i][i] < 1e-13) {
                sdseterr(routine,47);
            }
        }
        sderror(&dumroutine,&errnum);
        if (errnum == 0) {
            mmflg = 1;
        }
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  292 adds/subtracts/negates
                    422 multiplies
                      0 divides
                     66 assignments
*/
}

void sddommldu(int routine)
{
    int i;
    int dumroutine,errnum;

    if (mmlduflg == 0) {
        sddomm(routine);
/*
Numerically decompose the mass matrix
*/
        sdldudcomp(8,8,mmap,1e-13,workss,works,mm,mlo,mdi);
/*
Check for singular mass matrix
*/
        for (i = 0; i < 8; i++) {
            if (mdi[i] <= 1e-13) {
                sdseterr(routine,47);
            }
        }
        sderror(&dumroutine,&errnum);
        if (errnum == 0) {
            mmlduflg = 1;
        }
    }
}

void sdlhs(int routine)
{
/* Compute all remaining state- and force-dependent quantities
*/

    roustate = 2;
    sddommldu(routine);
    sddofs0();
}

void sdmfrc(double imult[11])
{
/*
Calculate forces due to constraint multipliers.

*/
    int i,j;
    double umult[9];

/*
Initialize all multiplier forces to zero.
*/
    for (i = 0; i <= 2; i++) {
        for (j = 0; j <= 2; j++) {
            mfk[i][j] = 0.;
            mtk[i][j] = 0.;
        }
    }
    for (i = 0; i <= 7; i++) {
        mtau[i] = 0.;
    }
/*
Compute user-generated multiplier forces
*/
    umult[0] = imult[2];
    umult[1] = imult[3];
    umult[2] = imult[4];
    umult[3] = imult[5];
    umult[4] = imult[6];
    umult[5] = imult[7];
    umult[6] = imult[8];
    umult[7] = imult[9];
    umult[8] = imult[10];
    mfrcflg = 1;
    sduconsfrc(curtim,q,u,umult);
    mfrcflg = 0;
    if (pres[6]  !=  0.) {
        mtau[6] = (imult[0]+mtau[6]);
    }
    if (pres[7]  !=  0.) {
        mtau[7] = (imult[1]+mtau[7]);
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    2 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     37 assignments
*/
}

void sdequivht(double tau[8])
{
/* Compute tree hinge torques to match effect of applied loads
*/
    double fstareq[8][3],tstareq[8][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(56,23);
        return;
    }
/*
Compute fstareq (forces)
*/
    fstareq[5][0] = ((9.81*(Cik[3][2][0]*mk[0]))-ufk[0][0]);
    fstareq[5][1] = ((9.81*(Cik[3][2][1]*mk[0]))-ufk[0][1]);
    fstareq[5][2] = ((9.81*(Cik[3][2][2]*mk[0]))-ufk[0][2]);
    fstareq[6][0] = -(ufk[1][0]+(gk[6][0]*mk[1]));
    fstareq[6][1] = -(ufk[1][1]+(gk[6][1]*mk[1]));
    fstareq[6][2] = -(ufk[1][2]+(gk[6][2]*mk[1]));
    fstareq[7][0] = -(ufk[2][0]+(gk[7][0]*mk[2]));
    fstareq[7][1] = -(ufk[2][1]+(gk[7][1]*mk[2]));
    fstareq[7][2] = -(ufk[2][2]+(gk[7][2]*mk[2]));
/*
Compute tstareq (torques)
*/
/*
Compute taus (RHS ignoring constraints and inertial forces)
*/
    sddovpk();
    tau[0] = (utau[0]-(((fstareq[7][2]*Vpk[0][7][2])+((fstareq[7][0]*
      Vpk[0][7][0])+(fstareq[7][1]*Vpk[0][7][1])))+(((fstareq[5][2]*Vpk[0][3][2]
      )+((fstareq[5][0]*Vpk[0][3][0])+(fstareq[5][1]*Vpk[0][3][1])))+((
      fstareq[6][2]*Vpk[0][6][2])+((fstareq[6][0]*Vpk[0][6][0])+(fstareq[6][1]*
      Vpk[0][6][1]))))));
    tau[1] = (utau[1]-(((fstareq[7][2]*Vpk[1][7][2])+((fstareq[7][0]*
      Vpk[1][7][0])+(fstareq[7][1]*Vpk[1][7][1])))+(((fstareq[5][2]*Vpk[1][3][2]
      )+((fstareq[5][0]*Vpk[1][3][0])+(fstareq[5][1]*Vpk[1][3][1])))+((
      fstareq[6][2]*Vpk[1][6][2])+((fstareq[6][0]*Vpk[1][6][0])+(fstareq[6][1]*
      Vpk[1][6][1]))))));
    tau[2] = (utau[2]-(((fstareq[7][2]*Vpk[2][7][2])+((fstareq[7][0]*
      Vpk[2][7][0])+(fstareq[7][1]*Vpk[2][7][1])))+(((fstareq[5][2]*Vpk[2][3][2]
      )+((fstareq[5][0]*Vpk[2][3][0])+(fstareq[5][1]*Vpk[2][3][1])))+((
      fstareq[6][2]*Vpk[2][6][2])+((fstareq[6][0]*Vpk[2][6][0])+(fstareq[6][1]*
      Vpk[2][6][1]))))));
    temp[0] = ((((fstareq[7][2]*Vpk[3][7][2])+((fstareq[7][0]*Vpk[3][7][0])+(
      fstareq[7][1]*Vpk[3][7][1])))-((Cik[7][0][2]*utk[2][2])+((Cik[7][0][0]*
      utk[2][0])+(Cik[7][0][1]*utk[2][1]))))+((((fstareq[5][1]*rk[0][2])-(
      fstareq[5][2]*rk[0][1]))-utk[0][0])+(((fstareq[6][2]*Vpk[3][6][2])+((
      fstareq[6][0]*Vpk[3][6][0])+(fstareq[6][1]*Vpk[3][6][1])))-((Cik[6][0][2]*
      utk[1][2])+((Cik[6][0][0]*utk[1][0])+(Cik[6][0][1]*utk[1][1]))))));
    tau[3] = (utau[3]-temp[0]);
    temp[0] = ((((fstareq[7][2]*Vpk[4][7][2])+((fstareq[7][0]*Vpk[4][7][0])+(
      fstareq[7][1]*Vpk[4][7][1])))-((Cik[7][1][2]*utk[2][2])+((Cik[7][1][0]*
      utk[2][0])+(Cik[7][1][1]*utk[2][1]))))+((((fstareq[5][2]*rk[0][0])-(
      fstareq[5][0]*rk[0][2]))-utk[0][1])+(((fstareq[6][2]*Vpk[4][6][2])+((
      fstareq[6][0]*Vpk[4][6][0])+(fstareq[6][1]*Vpk[4][6][1])))-((Cik[6][1][2]*
      utk[1][2])+((Cik[6][1][0]*utk[1][0])+(Cik[6][1][1]*utk[1][1]))))));
    tau[4] = (utau[4]-temp[0]);
    temp[0] = ((((fstareq[7][2]*Vpk[5][7][2])+((fstareq[7][0]*Vpk[5][7][0])+(
      fstareq[7][1]*Vpk[5][7][1])))-((Cik[7][2][2]*utk[2][2])+((Cik[7][2][0]*
      utk[2][0])+(Cik[7][2][1]*utk[2][1]))))+((((fstareq[5][0]*rk[0][1])-(
      fstareq[5][1]*rk[0][0]))-utk[0][2])+(((fstareq[6][2]*Vpk[5][6][2])+((
      fstareq[6][0]*Vpk[5][6][0])+(fstareq[6][1]*Vpk[5][6][1])))-((Cik[6][2][2]*
      utk[1][2])+((Cik[6][2][0]*utk[1][0])+(Cik[6][2][1]*utk[1][1]))))));
    tau[5] = (utau[5]-temp[0]);
    tau[6] = (utau[6]-(((fstareq[6][2]*Vpk[6][6][2])+((fstareq[6][0]*
      Vpk[6][6][0])+(fstareq[6][1]*Vpk[6][6][1])))-((pin[6][2]*utk[1][2])+((
      pin[6][0]*utk[1][0])+(pin[6][1]*utk[1][1])))));
    tau[7] = (utau[7]-(((fstareq[7][2]*Vpk[7][7][2])+((fstareq[7][0]*
      Vpk[7][7][0])+(fstareq[7][1]*Vpk[7][7][1])))-((pin[7][2]*utk[2][2])+((
      pin[7][0]*utk[2][0])+(pin[7][1]*utk[2][1])))));
/*
Op counts below do not include called subroutines
*/
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   99 adds/subtracts/negates
                     93 multiplies
                      0 divides
                     20 assignments
*/
}

void sdfs0(void)
{

/*
Compute Fs (ignoring multiplier forces)
*/
    fs[0] = fs0[0];
    fs[1] = fs0[1];
    fs[2] = fs0[2];
    fs[3] = fs0[3];
    fs[4] = fs0[4];
    fs[5] = fs0[5];
    fs[6] = fs0[6];
    fs[7] = fs0[7];
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      8 assignments
*/
}

void sdfsmult(void)
{

/*
Compute Fs (multiplier-generated forces only)
*/
    sddovpk();
    fs[0] = (mtau[0]+(((mfk[2][2]*Vpk[0][7][2])+((mfk[2][0]*Vpk[0][7][0])+(
      mfk[2][1]*Vpk[0][7][1])))+(((mfk[0][2]*Vpk[0][3][2])+((mfk[0][0]*
      Vpk[0][3][0])+(mfk[0][1]*Vpk[0][3][1])))+((mfk[1][2]*Vpk[0][6][2])+((
      mfk[1][0]*Vpk[0][6][0])+(mfk[1][1]*Vpk[0][6][1]))))));
    fs[1] = (mtau[1]+(((mfk[2][2]*Vpk[1][7][2])+((mfk[2][0]*Vpk[1][7][0])+(
      mfk[2][1]*Vpk[1][7][1])))+(((mfk[0][2]*Vpk[1][3][2])+((mfk[0][0]*
      Vpk[1][3][0])+(mfk[0][1]*Vpk[1][3][1])))+((mfk[1][2]*Vpk[1][6][2])+((
      mfk[1][0]*Vpk[1][6][0])+(mfk[1][1]*Vpk[1][6][1]))))));
    fs[2] = (mtau[2]+(((mfk[2][2]*Vpk[2][7][2])+((mfk[2][0]*Vpk[2][7][0])+(
      mfk[2][1]*Vpk[2][7][1])))+(((mfk[0][2]*Vpk[2][3][2])+((mfk[0][0]*
      Vpk[2][3][0])+(mfk[0][1]*Vpk[2][3][1])))+((mfk[1][2]*Vpk[2][6][2])+((
      mfk[1][0]*Vpk[2][6][0])+(mfk[1][1]*Vpk[2][6][1]))))));
    temp[0] = (((((mfk[0][2]*rk[0][1])-(mfk[0][1]*rk[0][2]))-mtk[0][0])-(((
      Cik[6][0][2]*mtk[1][2])+((Cik[6][0][0]*mtk[1][0])+(Cik[6][0][1]*mtk[1][1])
      ))+((mfk[1][2]*Vpk[3][6][2])+((mfk[1][0]*Vpk[3][6][0])+(mfk[1][1]*
      Vpk[3][6][1])))))-(((Cik[7][0][2]*mtk[2][2])+((Cik[7][0][0]*mtk[2][0])+(
      Cik[7][0][1]*mtk[2][1])))+((mfk[2][2]*Vpk[3][7][2])+((mfk[2][0]*
      Vpk[3][7][0])+(mfk[2][1]*Vpk[3][7][1])))));
    fs[3] = (mtau[3]-temp[0]);
    temp[0] = (((((mfk[0][0]*rk[0][2])-(mfk[0][2]*rk[0][0]))-mtk[0][1])-(((
      Cik[6][1][2]*mtk[1][2])+((Cik[6][1][0]*mtk[1][0])+(Cik[6][1][1]*mtk[1][1])
      ))+((mfk[1][2]*Vpk[4][6][2])+((mfk[1][0]*Vpk[4][6][0])+(mfk[1][1]*
      Vpk[4][6][1])))))-(((Cik[7][1][2]*mtk[2][2])+((Cik[7][1][0]*mtk[2][0])+(
      Cik[7][1][1]*mtk[2][1])))+((mfk[2][2]*Vpk[4][7][2])+((mfk[2][0]*
      Vpk[4][7][0])+(mfk[2][1]*Vpk[4][7][1])))));
    fs[4] = (mtau[4]-temp[0]);
    temp[0] = (((((mfk[0][1]*rk[0][0])-(mfk[0][0]*rk[0][1]))-mtk[0][2])-(((
      Cik[6][2][2]*mtk[1][2])+((Cik[6][2][0]*mtk[1][0])+(Cik[6][2][1]*mtk[1][1])
      ))+((mfk[1][2]*Vpk[5][6][2])+((mfk[1][0]*Vpk[5][6][0])+(mfk[1][1]*
      Vpk[5][6][1])))))-(((Cik[7][2][2]*mtk[2][2])+((Cik[7][2][0]*mtk[2][0])+(
      Cik[7][2][1]*mtk[2][1])))+((mfk[2][2]*Vpk[5][7][2])+((mfk[2][0]*
      Vpk[5][7][0])+(mfk[2][1]*Vpk[5][7][1])))));
    fs[5] = (mtau[5]-temp[0]);
    fs[6] = (mtau[6]+(((mfk[1][2]*Vpk[6][6][2])+((mfk[1][0]*Vpk[6][6][0])+(
      mfk[1][1]*Vpk[6][6][1])))+((mtk[1][2]*pin[6][2])+((mtk[1][0]*pin[6][0])+(
      mtk[1][1]*pin[6][1])))));
    fs[7] = (mtau[7]+(((mfk[2][2]*Vpk[7][7][2])+((mfk[2][0]*Vpk[7][7][0])+(
      mfk[2][1]*Vpk[7][7][1])))+((mtk[2][2]*pin[7][2])+((mtk[2][0]*pin[7][0])+(
      mtk[2][1]*pin[7][1])))));
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   84 adds/subtracts/negates
                     81 multiplies
                      0 divides
                     11 assignments
*/
}

void sdfsfull(void)
{

/*
Compute Fs (including all forces)
*/
    sdfsmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
    fs[2] = (fs[2]+fs0[2]);
    fs[3] = (fs[3]+fs0[3]);
    fs[4] = (fs[4]+fs0[4]);
    fs[5] = (fs[5]+fs0[5]);
    fs[6] = (fs[6]+fs0[6]);
    fs[7] = (fs[7]+fs0[7]);
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    8 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      8 assignments
*/
}

void sdfsgenmult(void)
{

/*
Compute Fs (generic multiplier-generated forces)
*/
    sddovpk();
    fs[0] = (mtau[0]+(((mfk[2][2]*Vpk[0][7][2])+((mfk[2][0]*Vpk[0][7][0])+(
      mfk[2][1]*Vpk[0][7][1])))+(((mfk[0][2]*Vpk[0][3][2])+((mfk[0][0]*
      Vpk[0][3][0])+(mfk[0][1]*Vpk[0][3][1])))+((mfk[1][2]*Vpk[0][6][2])+((
      mfk[1][0]*Vpk[0][6][0])+(mfk[1][1]*Vpk[0][6][1]))))));
    fs[1] = (mtau[1]+(((mfk[2][2]*Vpk[1][7][2])+((mfk[2][0]*Vpk[1][7][0])+(
      mfk[2][1]*Vpk[1][7][1])))+(((mfk[0][2]*Vpk[1][3][2])+((mfk[0][0]*
      Vpk[1][3][0])+(mfk[0][1]*Vpk[1][3][1])))+((mfk[1][2]*Vpk[1][6][2])+((
      mfk[1][0]*Vpk[1][6][0])+(mfk[1][1]*Vpk[1][6][1]))))));
    fs[2] = (mtau[2]+(((mfk[2][2]*Vpk[2][7][2])+((mfk[2][0]*Vpk[2][7][0])+(
      mfk[2][1]*Vpk[2][7][1])))+(((mfk[0][2]*Vpk[2][3][2])+((mfk[0][0]*
      Vpk[2][3][0])+(mfk[0][1]*Vpk[2][3][1])))+((mfk[1][2]*Vpk[2][6][2])+((
      mfk[1][0]*Vpk[2][6][0])+(mfk[1][1]*Vpk[2][6][1]))))));
    temp[0] = (((((mfk[0][2]*rk[0][1])-(mfk[0][1]*rk[0][2]))-mtk[0][0])-(((
      Cik[6][0][2]*mtk[1][2])+((Cik[6][0][0]*mtk[1][0])+(Cik[6][0][1]*mtk[1][1])
      ))+((mfk[1][2]*Vpk[3][6][2])+((mfk[1][0]*Vpk[3][6][0])+(mfk[1][1]*
      Vpk[3][6][1])))))-(((Cik[7][0][2]*mtk[2][2])+((Cik[7][0][0]*mtk[2][0])+(
      Cik[7][0][1]*mtk[2][1])))+((mfk[2][2]*Vpk[3][7][2])+((mfk[2][0]*
      Vpk[3][7][0])+(mfk[2][1]*Vpk[3][7][1])))));
    fs[3] = (mtau[3]-temp[0]);
    temp[0] = (((((mfk[0][0]*rk[0][2])-(mfk[0][2]*rk[0][0]))-mtk[0][1])-(((
      Cik[6][1][2]*mtk[1][2])+((Cik[6][1][0]*mtk[1][0])+(Cik[6][1][1]*mtk[1][1])
      ))+((mfk[1][2]*Vpk[4][6][2])+((mfk[1][0]*Vpk[4][6][0])+(mfk[1][1]*
      Vpk[4][6][1])))))-(((Cik[7][1][2]*mtk[2][2])+((Cik[7][1][0]*mtk[2][0])+(
      Cik[7][1][1]*mtk[2][1])))+((mfk[2][2]*Vpk[4][7][2])+((mfk[2][0]*
      Vpk[4][7][0])+(mfk[2][1]*Vpk[4][7][1])))));
    fs[4] = (mtau[4]-temp[0]);
    temp[0] = (((((mfk[0][1]*rk[0][0])-(mfk[0][0]*rk[0][1]))-mtk[0][2])-(((
      Cik[6][2][2]*mtk[1][2])+((Cik[6][2][0]*mtk[1][0])+(Cik[6][2][1]*mtk[1][1])
      ))+((mfk[1][2]*Vpk[5][6][2])+((mfk[1][0]*Vpk[5][6][0])+(mfk[1][1]*
      Vpk[5][6][1])))))-(((Cik[7][2][2]*mtk[2][2])+((Cik[7][2][0]*mtk[2][0])+(
      Cik[7][2][1]*mtk[2][1])))+((mfk[2][2]*Vpk[5][7][2])+((mfk[2][0]*
      Vpk[5][7][0])+(mfk[2][1]*Vpk[5][7][1])))));
    fs[5] = (mtau[5]-temp[0]);
    fs[6] = (mtau[6]+(((mfk[1][2]*Vpk[6][6][2])+((mfk[1][0]*Vpk[6][6][0])+(
      mfk[1][1]*Vpk[6][6][1])))+((mtk[1][2]*pin[6][2])+((mtk[1][0]*pin[6][0])+(
      mtk[1][1]*pin[6][1])))));
    fs[7] = (mtau[7]+(((mfk[2][2]*Vpk[7][7][2])+((mfk[2][0]*Vpk[7][7][0])+(
      mfk[2][1]*Vpk[7][7][1])))+((mtk[2][2]*pin[7][2])+((mtk[2][0]*pin[7][0])+(
      mtk[2][1]*pin[7][1])))));
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   84 adds/subtracts/negates
                     81 multiplies
                      0 divides
                     11 assignments
*/
}

void sdfsgenfull(void)
{

/*
Compute Fs (incl generic mult & other forces)
*/
    sdfsgenmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
    fs[2] = (fs[2]+fs0[2]);
    fs[3] = (fs[3]+fs0[3]);
    fs[4] = (fs[4]+fs0[4]);
    fs[5] = (fs[5]+fs0[5]);
    fs[6] = (fs[6]+fs0[6]);
    fs[7] = (fs[7]+fs0[7]);
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    8 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      8 assignments
*/
}

void sdfulltrq(double udotin[8],
    double multin[11],
    double trqout[8])
{
/* Compute hinge torques which would produce indicated udots
*/
    double fstarr[8][3],tstarr[8][3],Otkr[8][3],Atir[8][3],Atkr[8][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(61,23);
        return;
    }
/*
Compute multiplier-generated forces
*/
    sdmfrc(multin);
/*
Account for inertial accelerations and supplied udots
*/
    Otkr[6][0] = (((Cik[6][2][0]*udotin[5])+((Cik[6][0][0]*udotin[3])+(
      Cik[6][1][0]*udotin[4])))+((pin[6][0]*udotin[6])+((Wik[6][2]*wk[6][1])-(
      Wik[6][1]*wk[6][2]))));
    Otkr[6][1] = (((Cik[6][2][1]*udotin[5])+((Cik[6][0][1]*udotin[3])+(
      Cik[6][1][1]*udotin[4])))+((pin[6][1]*udotin[6])+((Wik[6][0]*wk[6][2])-(
      Wik[6][2]*wk[6][0]))));
    Otkr[6][2] = (((Cik[6][2][2]*udotin[5])+((Cik[6][0][2]*udotin[3])+(
      Cik[6][1][2]*udotin[4])))+((pin[6][2]*udotin[6])+((Wik[6][1]*wk[6][0])-(
      Wik[6][0]*wk[6][1]))));
    Otkr[7][0] = (((Cik[7][2][0]*udotin[5])+((Cik[7][0][0]*udotin[3])+(
      Cik[7][1][0]*udotin[4])))+((pin[7][0]*udotin[7])+((Wik[7][2]*wk[7][1])-(
      Wik[7][1]*wk[7][2]))));
    Otkr[7][1] = (((Cik[7][2][1]*udotin[5])+((Cik[7][0][1]*udotin[3])+(
      Cik[7][1][1]*udotin[4])))+((pin[7][1]*udotin[7])+((Wik[7][0]*wk[7][2])-(
      Wik[7][2]*wk[7][0]))));
    Otkr[7][2] = (((Cik[7][2][2]*udotin[5])+((Cik[7][0][2]*udotin[3])+(
      Cik[7][1][2]*udotin[4])))+((pin[7][2]*udotin[7])+((Wik[7][1]*wk[7][0])-(
      Wik[7][0]*wk[7][1]))));
    Atkr[0][0] = (pin[0][0]*udotin[0]);
    Atkr[0][1] = (pin[0][1]*udotin[0]);
    Atkr[0][2] = (pin[0][2]*udotin[0]);
    Atkr[1][0] = (Atkr[0][0]+(pin[1][0]*udotin[1]));
    Atkr[1][1] = (Atkr[0][1]+(pin[1][1]*udotin[1]));
    Atkr[1][2] = (Atkr[0][2]+(pin[1][2]*udotin[1]));
    Atkr[2][0] = (Atkr[1][0]+(pin[2][0]*udotin[2]));
    Atkr[2][1] = (Atkr[1][1]+(pin[2][1]*udotin[2]));
    Atkr[2][2] = (Atkr[1][2]+(pin[2][2]*udotin[2]));
    Atkr[3][0] = ((Atkr[2][2]*Cik[3][2][0])+((Atkr[2][0]*Cik[3][0][0])+(
      Atkr[2][1]*Cik[3][1][0])));
    Atkr[3][1] = ((Atkr[2][2]*Cik[3][2][1])+((Atkr[2][0]*Cik[3][0][1])+(
      Atkr[2][1]*Cik[3][1][1])));
    Atkr[3][2] = ((Atkr[2][2]*Cik[3][2][2])+((Atkr[2][0]*Cik[3][0][2])+(
      Atkr[2][1]*Cik[3][1][2])));
    Atkr[5][0] = (Atkr[3][0]+(((rk[0][1]*udotin[5])-(rk[0][2]*udotin[4]))+((u[4]
      *Wkrpk[5][2])-(u[5]*Wkrpk[5][1]))));
    Atkr[5][1] = (Atkr[3][1]+(((rk[0][2]*udotin[3])-(rk[0][0]*udotin[5]))+((u[5]
      *Wkrpk[5][0])-(u[3]*Wkrpk[5][2]))));
    Atkr[5][2] = (Atkr[3][2]+(((rk[0][0]*udotin[4])-(rk[0][1]*udotin[3]))+((u[3]
      *Wkrpk[5][1])-(u[4]*Wkrpk[5][0]))));
    Atir[6][0] = (Atkr[5][0]+(((ri[1][2]*udotin[4])-(ri[1][1]*udotin[5]))+((u[4]
      *Wirk[6][2])-(u[5]*Wirk[6][1]))));
    Atir[6][1] = (Atkr[5][1]+(((ri[1][0]*udotin[5])-(ri[1][2]*udotin[3]))+((u[5]
      *Wirk[6][0])-(u[3]*Wirk[6][2]))));
    Atir[6][2] = (Atkr[5][2]+(((ri[1][1]*udotin[3])-(ri[1][0]*udotin[4]))+((u[3]
      *Wirk[6][1])-(u[4]*Wirk[6][0]))));
    Atkr[6][0] = (((Atir[6][2]*Cik[6][2][0])+((Atir[6][0]*Cik[6][0][0])+(
      Atir[6][1]*Cik[6][1][0])))+(((Otkr[6][2]*rk[1][1])-(Otkr[6][1]*rk[1][2]))+
      ((wk[6][1]*Wkrpk[6][2])-(wk[6][2]*Wkrpk[6][1]))));
    Atkr[6][1] = (((Atir[6][2]*Cik[6][2][1])+((Atir[6][0]*Cik[6][0][1])+(
      Atir[6][1]*Cik[6][1][1])))+(((Otkr[6][0]*rk[1][2])-(Otkr[6][2]*rk[1][0]))+
      ((wk[6][2]*Wkrpk[6][0])-(wk[6][0]*Wkrpk[6][2]))));
    Atkr[6][2] = (((Atir[6][2]*Cik[6][2][2])+((Atir[6][0]*Cik[6][0][2])+(
      Atir[6][1]*Cik[6][1][2])))+(((Otkr[6][1]*rk[1][0])-(Otkr[6][0]*rk[1][1]))+
      ((wk[6][0]*Wkrpk[6][1])-(wk[6][1]*Wkrpk[6][0]))));
    Atir[7][0] = (Atkr[5][0]+(((ri[2][2]*udotin[4])-(ri[2][1]*udotin[5]))+((u[4]
      *Wirk[7][2])-(u[5]*Wirk[7][1]))));
    Atir[7][1] = (Atkr[5][1]+(((ri[2][0]*udotin[5])-(ri[2][2]*udotin[3]))+((u[5]
      *Wirk[7][0])-(u[3]*Wirk[7][2]))));
    Atir[7][2] = (Atkr[5][2]+(((ri[2][1]*udotin[3])-(ri[2][0]*udotin[4]))+((u[3]
      *Wirk[7][1])-(u[4]*Wirk[7][0]))));
    Atkr[7][0] = (((Atir[7][2]*Cik[7][2][0])+((Atir[7][0]*Cik[7][0][0])+(
      Atir[7][1]*Cik[7][1][0])))+(((Otkr[7][2]*rk[2][1])-(Otkr[7][1]*rk[2][2]))+
      ((wk[7][1]*Wkrpk[7][2])-(wk[7][2]*Wkrpk[7][1]))));
    Atkr[7][1] = (((Atir[7][2]*Cik[7][2][1])+((Atir[7][0]*Cik[7][0][1])+(
      Atir[7][1]*Cik[7][1][1])))+(((Otkr[7][0]*rk[2][2])-(Otkr[7][2]*rk[2][0]))+
      ((wk[7][2]*Wkrpk[7][0])-(wk[7][0]*Wkrpk[7][2]))));
    Atkr[7][2] = (((Atir[7][2]*Cik[7][2][2])+((Atir[7][0]*Cik[7][0][2])+(
      Atir[7][1]*Cik[7][1][2])))+(((Otkr[7][1]*rk[2][0])-(Otkr[7][0]*rk[2][1]))+
      ((wk[7][0]*Wkrpk[7][1])-(wk[7][1]*Wkrpk[7][0]))));
/*
Accumulate all forces and torques
*/
    fstarr[5][0] = ((mfk[0][0]+ufk[0][0])-(mk[0]*(Atkr[5][0]+(9.81*Cik[3][2][0])
      )));
    fstarr[5][1] = ((mfk[0][1]+ufk[0][1])-(mk[0]*(Atkr[5][1]+(9.81*Cik[3][2][1])
      )));
    fstarr[5][2] = ((mfk[0][2]+ufk[0][2])-(mk[0]*(Atkr[5][2]+(9.81*Cik[3][2][2])
      )));
    fstarr[6][0] = ((mfk[1][0]+ufk[1][0])+(mk[1]*(gk[6][0]-Atkr[6][0])));
    fstarr[6][1] = ((mfk[1][1]+ufk[1][1])+(mk[1]*(gk[6][1]-Atkr[6][1])));
    fstarr[6][2] = ((mfk[1][2]+ufk[1][2])+(mk[1]*(gk[6][2]-Atkr[6][2])));
    fstarr[7][0] = ((mfk[2][0]+ufk[2][0])+(mk[2]*(gk[7][0]-Atkr[7][0])));
    fstarr[7][1] = ((mfk[2][1]+ufk[2][1])+(mk[2]*(gk[7][1]-Atkr[7][1])));
    fstarr[7][2] = ((mfk[2][2]+ufk[2][2])+(mk[2]*(gk[7][2]-Atkr[7][2])));
    tstarr[5][0] = ((mtk[0][0]+utk[0][0])-(WkIkWk[5][0]+((ik[0][0][2]*udotin[5])
      +((ik[0][0][0]*udotin[3])+(ik[0][0][1]*udotin[4])))));
    tstarr[5][1] = ((mtk[0][1]+utk[0][1])-(WkIkWk[5][1]+((ik[0][1][2]*udotin[5])
      +((ik[0][1][0]*udotin[3])+(ik[0][1][1]*udotin[4])))));
    tstarr[5][2] = ((mtk[0][2]+utk[0][2])-(WkIkWk[5][2]+((ik[0][2][2]*udotin[5])
      +((ik[0][2][0]*udotin[3])+(ik[0][2][1]*udotin[4])))));
    tstarr[6][0] = ((mtk[1][0]+utk[1][0])-(WkIkWk[6][0]+((ik[1][0][2]*Otkr[6][2]
      )+((ik[1][0][0]*Otkr[6][0])+(ik[1][0][1]*Otkr[6][1])))));
    tstarr[6][1] = ((mtk[1][1]+utk[1][1])-(WkIkWk[6][1]+((ik[1][1][2]*Otkr[6][2]
      )+((ik[1][1][0]*Otkr[6][0])+(ik[1][1][1]*Otkr[6][1])))));
    tstarr[6][2] = ((mtk[1][2]+utk[1][2])-(WkIkWk[6][2]+((ik[1][2][2]*Otkr[6][2]
      )+((ik[1][2][0]*Otkr[6][0])+(ik[1][2][1]*Otkr[6][1])))));
    tstarr[7][0] = ((mtk[2][0]+utk[2][0])-(WkIkWk[7][0]+((ik[2][0][2]*Otkr[7][2]
      )+((ik[2][0][0]*Otkr[7][0])+(ik[2][0][1]*Otkr[7][1])))));
    tstarr[7][1] = ((mtk[2][1]+utk[2][1])-(WkIkWk[7][1]+((ik[2][1][2]*Otkr[7][2]
      )+((ik[2][1][0]*Otkr[7][0])+(ik[2][1][1]*Otkr[7][1])))));
    tstarr[7][2] = ((mtk[2][2]+utk[2][2])-(WkIkWk[7][2]+((ik[2][2][2]*Otkr[7][2]
      )+((ik[2][2][0]*Otkr[7][0])+(ik[2][2][1]*Otkr[7][1])))));
/*
Now calculate the torques
*/
    sddovpk();
    trqout[0] = -((mtau[0]+utau[0])+(((fstarr[7][2]*Vpk[0][7][2])+((fstarr[7][0]
      *Vpk[0][7][0])+(fstarr[7][1]*Vpk[0][7][1])))+(((fstarr[5][2]*Vpk[0][3][2])
      +((fstarr[5][0]*Vpk[0][3][0])+(fstarr[5][1]*Vpk[0][3][1])))+((fstarr[6][2]
      *Vpk[0][6][2])+((fstarr[6][0]*Vpk[0][6][0])+(fstarr[6][1]*Vpk[0][6][1]))))
      ));
    trqout[1] = -((mtau[1]+utau[1])+(((fstarr[7][2]*Vpk[1][7][2])+((fstarr[7][0]
      *Vpk[1][7][0])+(fstarr[7][1]*Vpk[1][7][1])))+(((fstarr[5][2]*Vpk[1][3][2])
      +((fstarr[5][0]*Vpk[1][3][0])+(fstarr[5][1]*Vpk[1][3][1])))+((fstarr[6][2]
      *Vpk[1][6][2])+((fstarr[6][0]*Vpk[1][6][0])+(fstarr[6][1]*Vpk[1][6][1]))))
      ));
    trqout[2] = -((mtau[2]+utau[2])+(((fstarr[7][2]*Vpk[2][7][2])+((fstarr[7][0]
      *Vpk[2][7][0])+(fstarr[7][1]*Vpk[2][7][1])))+(((fstarr[5][2]*Vpk[2][3][2])
      +((fstarr[5][0]*Vpk[2][3][0])+(fstarr[5][1]*Vpk[2][3][1])))+((fstarr[6][2]
      *Vpk[2][6][2])+((fstarr[6][0]*Vpk[2][6][0])+(fstarr[6][1]*Vpk[2][6][1]))))
      ));
    temp[0] = (((tstarr[5][0]+((fstarr[5][1]*rk[0][2])-(fstarr[5][2]*rk[0][1])))
      +(((Cik[6][0][2]*tstarr[6][2])+((Cik[6][0][0]*tstarr[6][0])+(Cik[6][0][1]*
      tstarr[6][1])))+((fstarr[6][2]*Vpk[3][6][2])+((fstarr[6][0]*Vpk[3][6][0])+
      (fstarr[6][1]*Vpk[3][6][1])))))+(((Cik[7][0][2]*tstarr[7][2])+((
      Cik[7][0][0]*tstarr[7][0])+(Cik[7][0][1]*tstarr[7][1])))+((fstarr[7][2]*
      Vpk[3][7][2])+((fstarr[7][0]*Vpk[3][7][0])+(fstarr[7][1]*Vpk[3][7][1])))))
      ;
    trqout[3] = -((mtau[3]+utau[3])+temp[0]);
    temp[0] = (((tstarr[5][1]+((fstarr[5][2]*rk[0][0])-(fstarr[5][0]*rk[0][2])))
      +(((Cik[6][1][2]*tstarr[6][2])+((Cik[6][1][0]*tstarr[6][0])+(Cik[6][1][1]*
      tstarr[6][1])))+((fstarr[6][2]*Vpk[4][6][2])+((fstarr[6][0]*Vpk[4][6][0])+
      (fstarr[6][1]*Vpk[4][6][1])))))+(((Cik[7][1][2]*tstarr[7][2])+((
      Cik[7][1][0]*tstarr[7][0])+(Cik[7][1][1]*tstarr[7][1])))+((fstarr[7][2]*
      Vpk[4][7][2])+((fstarr[7][0]*Vpk[4][7][0])+(fstarr[7][1]*Vpk[4][7][1])))))
      ;
    trqout[4] = -((mtau[4]+utau[4])+temp[0]);
    temp[0] = (((tstarr[5][2]+((fstarr[5][0]*rk[0][1])-(fstarr[5][1]*rk[0][0])))
      +(((Cik[6][2][2]*tstarr[6][2])+((Cik[6][2][0]*tstarr[6][0])+(Cik[6][2][1]*
      tstarr[6][1])))+((fstarr[6][2]*Vpk[5][6][2])+((fstarr[6][0]*Vpk[5][6][0])+
      (fstarr[6][1]*Vpk[5][6][1])))))+(((Cik[7][2][2]*tstarr[7][2])+((
      Cik[7][2][0]*tstarr[7][0])+(Cik[7][2][1]*tstarr[7][1])))+((fstarr[7][2]*
      Vpk[5][7][2])+((fstarr[7][0]*Vpk[5][7][0])+(fstarr[7][1]*Vpk[5][7][1])))))
      ;
    trqout[5] = -((mtau[5]+utau[5])+temp[0]);
    trqout[6] = -((mtau[6]+utau[6])+(((fstarr[6][2]*Vpk[6][6][2])+((fstarr[6][0]
      *Vpk[6][6][0])+(fstarr[6][1]*Vpk[6][6][1])))+((pin[6][2]*tstarr[6][2])+((
      pin[6][0]*tstarr[6][0])+(pin[6][1]*tstarr[6][1])))));
    trqout[7] = -((mtau[7]+utau[7])+(((fstarr[7][2]*Vpk[7][7][2])+((fstarr[7][0]
      *Vpk[7][7][0])+(fstarr[7][1]*Vpk[7][7][1])))+((pin[7][2]*tstarr[7][2])+((
      pin[7][0]*tstarr[7][0])+(pin[7][1]*tstarr[7][1])))));
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  286 adds/subtracts/negates
                    252 multiplies
                      0 divides
                     62 assignments
*/
}

void sdcomptrq(double udotin[8],
    double trqout[8])
{
/* Compute hinge torques to produce these udots, ignoring constraints
*/
    int i;
    double multin[11];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(60,23);
        return;
    }
    for (i = 0; i < 11; i++) {
        multin[i] = 0.;
    }
    sdfulltrq(udotin,multin,trqout);
}

void sdmulttrq(double multin[11],
    double trqout[8])
{
/* Compute hinge trqs which would be produced by these mults.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(65,23);
        return;
    }
    sdmfrc(multin);
    sdfsmult();
    for (i = 0; i < 8; i++) {
        trqout[i] = fs[i];
    }
}

void sdrhs(void)
{
/*
Generated 20-Jul-2007 21:06:48 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/

/*
Compute hinge torques for tree hinges
*/
    tauc[0] = (mtau[0]+utau[0]);
    tauc[1] = (mtau[1]+utau[1]);
    tauc[2] = (mtau[2]+utau[2]);
    tauc[3] = (mtau[3]+utau[3]);
    tauc[4] = (mtau[4]+utau[4]);
    tauc[5] = (mtau[5]+utau[5]);
    tauc[6] = (mtau[6]+utau[6]);
    tauc[7] = (mtau[7]+utau[7]);
    sddoiner();
/*
Compute onk & onb (angular accels in N)
*/
    Onkb[6][0] = ((pin[6][0]*udot[6])+((Cik[6][2][0]*udot[5])+((Cik[6][0][0]*
      udot[3])+(Cik[6][1][0]*udot[4]))));
    Onkb[6][1] = ((pin[6][1]*udot[6])+((Cik[6][2][1]*udot[5])+((Cik[6][0][1]*
      udot[3])+(Cik[6][1][1]*udot[4]))));
    Onkb[6][2] = ((pin[6][2]*udot[6])+((Cik[6][2][2]*udot[5])+((Cik[6][0][2]*
      udot[3])+(Cik[6][1][2]*udot[4]))));
    Onkb[7][0] = ((pin[7][0]*udot[7])+((Cik[7][2][0]*udot[5])+((Cik[7][0][0]*
      udot[3])+(Cik[7][1][0]*udot[4]))));
    Onkb[7][1] = ((pin[7][1]*udot[7])+((Cik[7][2][1]*udot[5])+((Cik[7][0][1]*
      udot[3])+(Cik[7][1][1]*udot[4]))));
    Onkb[7][2] = ((pin[7][2]*udot[7])+((Cik[7][2][2]*udot[5])+((Cik[7][0][2]*
      udot[3])+(Cik[7][1][2]*udot[4]))));
    onk[6][0] = (Onkb[6][0]+Otk[6][0]);
    onk[6][1] = (Onkb[6][1]+Otk[6][1]);
    onk[6][2] = (Onkb[6][2]+Otk[6][2]);
    onk[7][0] = (Onkb[7][0]+Otk[7][0]);
    onk[7][1] = (Onkb[7][1]+Otk[7][1]);
    onk[7][2] = (Onkb[7][2]+Otk[7][2]);
    onb[0][0] = udot[3];
    onb[0][1] = udot[4];
    onb[0][2] = udot[5];
    onb[1][0] = onk[6][0];
    onb[1][1] = onk[6][1];
    onb[1][2] = onk[6][2];
    onb[2][0] = onk[7][0];
    onb[2][1] = onk[7][1];
    onb[2][2] = onk[7][2];
/*
Compute acceleration dyadics
*/
    dyad[0][0][0] = w11w22[0];
    dyad[0][0][1] = (w0w1[0]-udot[5]);
    dyad[0][0][2] = (udot[4]+w0w2[0]);
    dyad[0][1][0] = (udot[5]+w0w1[0]);
    dyad[0][1][1] = w00w22[0];
    dyad[0][1][2] = (w1w2[0]-udot[3]);
    dyad[0][2][0] = (w0w2[0]-udot[4]);
    dyad[0][2][1] = (udot[3]+w1w2[0]);
    dyad[0][2][2] = w00w11[0];
    dyad[1][0][0] = w11w22[1];
    dyad[1][0][1] = (w0w1[1]-onk[6][2]);
    dyad[1][0][2] = (onk[6][1]+w0w2[1]);
    dyad[1][1][0] = (onk[6][2]+w0w1[1]);
    dyad[1][1][1] = w00w22[1];
    dyad[1][1][2] = (w1w2[1]-onk[6][0]);
    dyad[1][2][0] = (w0w2[1]-onk[6][1]);
    dyad[1][2][1] = (onk[6][0]+w1w2[1]);
    dyad[1][2][2] = w00w11[1];
    dyad[2][0][0] = w11w22[2];
    dyad[2][0][1] = (w0w1[2]-onk[7][2]);
    dyad[2][0][2] = (onk[7][1]+w0w2[2]);
    dyad[2][1][0] = (onk[7][2]+w0w1[2]);
    dyad[2][1][1] = w00w22[2];
    dyad[2][1][2] = (w1w2[2]-onk[7][0]);
    dyad[2][2][0] = (w0w2[2]-onk[7][1]);
    dyad[2][2][1] = (onk[7][0]+w1w2[2]);
    dyad[2][2][2] = w00w11[2];
/*
Compute ank & anb (mass center linear accels in N)
*/
    Ankb[0][0] = (pin[0][0]*udot[0]);
    Ankb[0][1] = (pin[0][1]*udot[0]);
    Ankb[0][2] = (pin[0][2]*udot[0]);
    Ankb[1][0] = (Ankb[0][0]+(pin[1][0]*udot[1]));
    Ankb[1][1] = (Ankb[0][1]+(pin[1][1]*udot[1]));
    Ankb[1][2] = (Ankb[0][2]+(pin[1][2]*udot[1]));
    Ankb[2][0] = (Ankb[1][0]+(pin[2][0]*udot[2]));
    Ankb[2][1] = (Ankb[1][1]+(pin[2][1]*udot[2]));
    Ankb[2][2] = (Ankb[1][2]+(pin[2][2]*udot[2]));
    Ankb[3][0] = ((Ankb[2][2]*Cik[3][2][0])+((Ankb[2][0]*Cik[3][0][0])+(
      Ankb[2][1]*Cik[3][1][0])));
    Ankb[3][1] = ((Ankb[2][2]*Cik[3][2][1])+((Ankb[2][0]*Cik[3][0][1])+(
      Ankb[2][1]*Cik[3][1][1])));
    Ankb[3][2] = ((Ankb[2][2]*Cik[3][2][2])+((Ankb[2][0]*Cik[3][0][2])+(
      Ankb[2][1]*Cik[3][1][2])));
    Ankb[5][0] = (Ankb[3][0]+((rk[0][1]*udot[5])-(rk[0][2]*udot[4])));
    Ankb[5][1] = (Ankb[3][1]+((rk[0][2]*udot[3])-(rk[0][0]*udot[5])));
    Ankb[5][2] = (Ankb[3][2]+((rk[0][0]*udot[4])-(rk[0][1]*udot[3])));
    AOnkri[6][0] = (Ankb[5][0]+((ri[1][2]*udot[4])-(ri[1][1]*udot[5])));
    AOnkri[6][1] = (Ankb[5][1]+((ri[1][0]*udot[5])-(ri[1][2]*udot[3])));
    AOnkri[6][2] = (Ankb[5][2]+((ri[1][1]*udot[3])-(ri[1][0]*udot[4])));
    Ankb[6][0] = (((AOnkri[6][2]*Cik[6][2][0])+((AOnkri[6][0]*Cik[6][0][0])+(
      AOnkri[6][1]*Cik[6][1][0])))+((Onkb[6][2]*rk[1][1])-(Onkb[6][1]*rk[1][2]))
      );
    Ankb[6][1] = (((AOnkri[6][2]*Cik[6][2][1])+((AOnkri[6][0]*Cik[6][0][1])+(
      AOnkri[6][1]*Cik[6][1][1])))+((Onkb[6][0]*rk[1][2])-(Onkb[6][2]*rk[1][0]))
      );
    Ankb[6][2] = (((AOnkri[6][2]*Cik[6][2][2])+((AOnkri[6][0]*Cik[6][0][2])+(
      AOnkri[6][1]*Cik[6][1][2])))+((Onkb[6][1]*rk[1][0])-(Onkb[6][0]*rk[1][1]))
      );
    AOnkri[7][0] = (Ankb[5][0]+((ri[2][2]*udot[4])-(ri[2][1]*udot[5])));
    AOnkri[7][1] = (Ankb[5][1]+((ri[2][0]*udot[5])-(ri[2][2]*udot[3])));
    AOnkri[7][2] = (Ankb[5][2]+((ri[2][1]*udot[3])-(ri[2][0]*udot[4])));
    Ankb[7][0] = (((AOnkri[7][2]*Cik[7][2][0])+((AOnkri[7][0]*Cik[7][0][0])+(
      AOnkri[7][1]*Cik[7][1][0])))+((Onkb[7][2]*rk[2][1])-(Onkb[7][1]*rk[2][2]))
      );
    Ankb[7][1] = (((AOnkri[7][2]*Cik[7][2][1])+((AOnkri[7][0]*Cik[7][0][1])+(
      AOnkri[7][1]*Cik[7][1][1])))+((Onkb[7][0]*rk[2][2])-(Onkb[7][2]*rk[2][0]))
      );
    Ankb[7][2] = (((AOnkri[7][2]*Cik[7][2][2])+((AOnkri[7][0]*Cik[7][0][2])+(
      AOnkri[7][1]*Cik[7][1][2])))+((Onkb[7][1]*rk[2][0])-(Onkb[7][0]*rk[2][1]))
      );
    AnkAtk[5][0] = (Ankb[5][0]+Atk[5][0]);
    AnkAtk[5][1] = (Ankb[5][1]+Atk[5][1]);
    AnkAtk[5][2] = (Ankb[5][2]+Atk[5][2]);
    ank[5][0] = ((AnkAtk[5][2]*Cik[3][0][2])+((AnkAtk[5][0]*Cik[3][0][0])+(
      AnkAtk[5][1]*Cik[3][0][1])));
    ank[5][1] = ((AnkAtk[5][2]*Cik[3][1][2])+((AnkAtk[5][0]*Cik[3][1][0])+(
      AnkAtk[5][1]*Cik[3][1][1])));
    ank[5][2] = ((AnkAtk[5][2]*Cik[3][2][2])+((AnkAtk[5][0]*Cik[3][2][0])+(
      AnkAtk[5][1]*Cik[3][2][1])));
    AnkAtk[6][0] = (Ankb[6][0]+Atk[6][0]);
    AnkAtk[6][1] = (Ankb[6][1]+Atk[6][1]);
    AnkAtk[6][2] = (Ankb[6][2]+Atk[6][2]);
    ank[6][0] = ((AnkAtk[6][2]*cnk[6][0][2])+((AnkAtk[6][0]*cnk[6][0][0])+(
      AnkAtk[6][1]*cnk[6][0][1])));
    ank[6][1] = ((AnkAtk[6][2]*cnk[6][1][2])+((AnkAtk[6][0]*cnk[6][1][0])+(
      AnkAtk[6][1]*cnk[6][1][1])));
    ank[6][2] = ((AnkAtk[6][2]*cnk[6][2][2])+((AnkAtk[6][0]*cnk[6][2][0])+(
      AnkAtk[6][1]*cnk[6][2][1])));
    AnkAtk[7][0] = (Ankb[7][0]+Atk[7][0]);
    AnkAtk[7][1] = (Ankb[7][1]+Atk[7][1]);
    AnkAtk[7][2] = (Ankb[7][2]+Atk[7][2]);
    ank[7][0] = ((AnkAtk[7][2]*cnk[7][0][2])+((AnkAtk[7][0]*cnk[7][0][0])+(
      AnkAtk[7][1]*cnk[7][0][1])));
    ank[7][1] = ((AnkAtk[7][2]*cnk[7][1][2])+((AnkAtk[7][0]*cnk[7][1][0])+(
      AnkAtk[7][1]*cnk[7][1][1])));
    ank[7][2] = ((AnkAtk[7][2]*cnk[7][2][2])+((AnkAtk[7][0]*cnk[7][2][0])+(
      AnkAtk[7][1]*cnk[7][2][1])));
    anb[0][0] = ank[5][0];
    anb[0][1] = ank[5][1];
    anb[0][2] = ank[5][2];
    anb[1][0] = ank[6][0];
    anb[1][1] = ank[6][1];
    anb[1][2] = ank[6][2];
    anb[2][0] = ank[7][0];
    anb[2][1] = ank[7][1];
    anb[2][2] = ank[7][2];
/*
Compute constraint acceleration errors
*/
    roustate = 3;
    sduaerr(curtim,q,u,udot,&aerr[2]);
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  131 adds/subtracts/negates
                    117 multiplies
                      0 divides
                    110 assignments
*/
}

void sdmassmat(double mmat[8][8])
{
/* Return the system mass matrix (LHS)
*/
    int i,j;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(57,23);
        return;
    }
    sddomm(57);
    for (i = 0; i < 8; i++) {
        for (j = i; j <= 7; j++) {
            mmat[i][j] = mm[i][j];
            mmat[j][i] = mm[i][j];
        }
    }
}

void sdfrcmat(double fmat[8])
{
/* Return the system force matrix (RHS), excluding constraints
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(58,23);
        return;
    }
    sddofs0();
    for (i = 0; i < 8; i++) {
        fmat[i] = fs0[i];
    }
}

void sdpseudo(double lqout[1],
    double luout[1])
{
/*
Return pseudo-coordinates for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void sdpsqdot(double lqdout[1])
{
/*
Return pseudo-coordinate derivatives for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void sdpsudot(double ludout[1])
{
/*
Return pseudo-coordinate accelerations for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void sdperr(double errs[11])
{
/*
Return position constraint errors.

*/

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(26,23);
        return;
    }
    if (pres[6]  !=  0.) {
        perr[0] = (q[6]-upos[6]);
    } else {
        perr[0] = 0.;
    }
    if (pres[7]  !=  0.) {
        perr[1] = (q[7]-upos[7]);
    } else {
        perr[1] = 0.;
    }
    errs[0] = perr[0];
    errs[1] = perr[1];
    errs[2] = perr[2];
    errs[3] = perr[3];
    errs[4] = perr[4];
    errs[5] = perr[5];
    errs[6] = perr[6];
    errs[7] = perr[7];
    errs[8] = perr[8];
    errs[9] = perr[9];
    errs[10] = perr[10];
}

void sdverr(double errs[11])
{
/*
Return velocity constraint errors.

*/

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(27,23);
        return;
    }
    if (pres[6]  !=  0.) {
        verr[0] = (u[6]-uvel[6]);
    } else {
        verr[0] = 0.;
    }
    if (pres[7]  !=  0.) {
        verr[1] = (u[7]-uvel[7]);
    } else {
        verr[1] = 0.;
    }
    errs[0] = verr[0];
    errs[1] = verr[1];
    errs[2] = verr[2];
    errs[3] = verr[3];
    errs[4] = verr[4];
    errs[5] = verr[5];
    errs[6] = verr[6];
    errs[7] = verr[7];
    errs[8] = verr[8];
    errs[9] = verr[9];
    errs[10] = verr[10];
}

void sdaerr(double errs[11])
{
/*
Return acceleration constraint errors.

*/

    if (roustate != 3) {
        sdseterr(35,24);
        return;
    }
    if (pres[6]  !=  0.) {
        aerr[0] = (udot[6]-uacc[6]);
    } else {
        aerr[0] = 0.;
    }
    if (pres[7]  !=  0.) {
        aerr[1] = (udot[7]-uacc[7]);
    } else {
        aerr[1] = 0.;
    }
    errs[0] = aerr[0];
    errs[1] = aerr[1];
    errs[2] = aerr[2];
    errs[3] = aerr[3];
    errs[4] = aerr[4];
    errs[5] = aerr[5];
    errs[6] = aerr[6];
    errs[7] = aerr[7];
    errs[8] = aerr[8];
    errs[9] = aerr[9];
    errs[10] = aerr[10];
}
int 
sdchkbnum(int routine,
    int bnum)
{

    if ((bnum < -1) || (bnum > 2)) {
        sdseterr(routine,15);
        return 1;
    }
    return 0;
}
int 
sdchkjnum(int routine,
    int jnum)
{

    if ((jnum < 0) || (jnum > 2)) {
        sdseterr(routine,16);
        return 1;
    }
    return 0;
}
int 
sdchkucnum(int routine,
    int ucnum)
{

    if ((ucnum < 0) || (ucnum > 8)) {
        sdseterr(routine,21);
        return 1;
    }
    return 0;
}
int 
sdchkjaxis(int routine,
    int jnum,
    int axnum)
{
    int maxax;

    if (sdchkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((axnum < 0) || (axnum > 6)) {
        sdseterr(routine,17);
        return 1;
    }
    maxax = njntdof[jnum]-1;
    if ((jtype[jnum] == 4) || (jtype[jnum] == 6) || (jtype[jnum] == 21)) {
        maxax = maxax+1;
    }
    if (axnum > maxax) {
        sdseterr(routine,18);
        return 1;
    }
    return 0;
}
int 
sdchkjpin(int routine,
    int jnum,
    int pinno)
{
    int maxax,pinok;

    if (sdchkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((pinno < 0) || (pinno > 5)) {
        sdseterr(routine,17);
        return 1;
    }
    if (njntdof[jnum] >= 3) {
        maxax = 2;
    } else {
        maxax = njntdof[jnum]-1;
    }
    if (jtype[jnum] == 4) {
        maxax = -1;
    }
    if (jtype[jnum] == 7) {
        maxax = 0;
    }
    pinok = 0;
    if (pinno <= maxax) {
        pinok = 1;
    }
    if (pinok == 0) {
        sdseterr(routine,18);
        return 1;
    }
    return 0;
}
int 
sdindx(int joint,
    int axis)
{
    int offs,gotit;

    if (sdchkjaxis(36,joint,axis) != 0) {
        return 0;
    }
    gotit = 0;
    if (jtype[joint] == 4) {
        if (axis == 3) {
            offs = ballq[joint];
            gotit = 1;
        }
    } else {
        if ((jtype[joint] == 6) || (jtype[joint] == 21)) {
            if (axis == 6) {
                offs = ballq[joint];
                gotit = 1;
            }
        }
    }
    if (gotit == 0) {
        offs = firstq[joint]+axis;
    }
    return offs;
}

void sdpresacc(int joint,
    int axis,
    double prval)
{

    if (sdchkjaxis(13,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(13,23);
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        uacc[sdindx(joint,axis)] = prval;
    }
}

void sdpresvel(int joint,
    int axis,
    double prval)
{

    if (sdchkjaxis(14,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(14,23);
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        uvel[sdindx(joint,axis)] = prval;
    }
}

void sdprespos(int joint,
    int axis,
    double prval)
{

    if (sdchkjaxis(15,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(15,23);
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        upos[sdindx(joint,axis)] = prval;
    }
}

void sdgetht(int joint,
    int axis,
    double *torque)
{

    if (sdchkjaxis(30,joint,axis) != 0) {
        return;
    }
    if (roustate != 3) {
        sdseterr(30,24);
        return;
    }
    *torque = tauc[sdindx(joint,axis)];
}

void sdhinget(int joint,
    int axis,
    double torque)
{

    if (sdchkjaxis(10,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(10,23);
        return;
    }
    if (mfrcflg != 0) {
        mtau[sdindx(joint,axis)] = mtau[sdindx(joint,axis)]+torque;
    } else {
        fs0flg = 0;
        utau[sdindx(joint,axis)] = utau[sdindx(joint,axis)]+torque;
    }
}

void sdpointf(int body,
    double point[3],
    double force[3])
{
    double torque[3];

    if (sdchkbnum(11,body) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(11,23);
        return;
    }
    if (body == -1) {
        return;
    }
    torque[0] = point[1]*force[2]-point[2]*force[1];
    torque[1] = point[2]*force[0]-point[0]*force[2];
    torque[2] = point[0]*force[1]-point[1]*force[0];
    if (mfrcflg != 0) {
        mfk[body][0] = mfk[body][0]+force[0];
        mtk[body][0] = mtk[body][0]+torque[0];
        mfk[body][1] = mfk[body][1]+force[1];
        mtk[body][1] = mtk[body][1]+torque[1];
        mfk[body][2] = mfk[body][2]+force[2];
        mtk[body][2] = mtk[body][2]+torque[2];
    } else {
        fs0flg = 0;
        ufk[body][0] = ufk[body][0]+force[0];
        utk[body][0] = utk[body][0]+torque[0];
        ufk[body][1] = ufk[body][1]+force[1];
        utk[body][1] = utk[body][1]+torque[1];
        ufk[body][2] = ufk[body][2]+force[2];
        utk[body][2] = utk[body][2]+torque[2];
    }
}

void sdbodyt(int body,
    double torque[3])
{

    if (sdchkbnum(12,body) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(12,23);
        return;
    }
    if (body == -1) {
        return;
    }
    if (mfrcflg != 0) {
        mtk[body][0] = mtk[body][0]+torque[0];
        mtk[body][1] = mtk[body][1]+torque[1];
        mtk[body][2] = mtk[body][2]+torque[2];
    } else {
        fs0flg = 0;
        utk[body][0] = utk[body][0]+torque[0];
        utk[body][1] = utk[body][1]+torque[1];
        utk[body][2] = utk[body][2]+torque[2];
    }
}

void sddoww(int routine)
{
    double pp[11][8],dpp[8][11];
    int i,j,c;
    double sum;
    double dfk[3][3],dtk[3][3],dtau[8],dltci[1][3],dltc[1][3],dlfci[1][3],dlfc[1
      ][3];
    double dTinb[1][3],dToutb[1][3],dltaufi[1][3],dltaufo[1][3],dltauti[1][3],
      dltauto[1][3];
    double umult[9];
    double dfs[8],row[8],dinvrow[8];

    roustate = 2;
    if (wwflg == 0) {
/*
Compute constraint effects
*/
        sddovpk();
        sddommldu(routine);
/*
Constraint 0 (prescribed motion)
*/
        if (pres[6]  !=  0.) {
            dtau[6] = 1.;
        } else {
            dtau[6] = 0.;
        }
        dfs[6] = dtau[6];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[7] = 0.;
        sdldubsl(8,8,mmap,mlo,dfs,row);
        sdldubsd(8,8,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 7; i++) {
            pp[0][i] = row[i];
            dpp[i][0] = dinvrow[i];
        }
        wmap[0] = 0;
/*
Constraint 1 (prescribed motion)
*/
        if (pres[7]  !=  0.) {
            dtau[7] = 1.;
        } else {
            dtau[7] = 0.;
        }
        dfs[7] = dtau[7];
        dfs[0] = 0.;
        dfs[1] = 0.;
        dfs[2] = 0.;
        dfs[3] = 0.;
        dfs[4] = 0.;
        dfs[5] = 0.;
        dfs[6] = 0.;
        sdldubsl(8,8,mmap,mlo,dfs,row);
        sdldubsd(8,8,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 7; i++) {
            pp[1][i] = row[i];
            dpp[i][1] = dinvrow[i];
        }
        wmap[1] = 1;
/*
Constraint 2 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 2; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 7; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 1.;
        umult[1] = 0.;
        umult[2] = 0.;
        umult[3] = 0.;
        umult[4] = 0.;
        umult[5] = 0.;
        umult[6] = 0.;
        umult[7] = 0.;
        umult[8] = 0.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(8,8,mmap,mlo,fs,row);
        sdldubsd(8,8,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 7; i++) {
            pp[2][i] = row[i];
            dpp[i][2] = dinvrow[i];
        }
        wmap[2] = 2;
/*
Constraint 3 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 2; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 7; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 0.;
        umult[1] = 1.;
        umult[2] = 0.;
        umult[3] = 0.;
        umult[4] = 0.;
        umult[5] = 0.;
        umult[6] = 0.;
        umult[7] = 0.;
        umult[8] = 0.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(8,8,mmap,mlo,fs,row);
        sdldubsd(8,8,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 7; i++) {
            pp[3][i] = row[i];
            dpp[i][3] = dinvrow[i];
        }
        wmap[3] = 3;
/*
Constraint 4 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 2; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 7; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 0.;
        umult[1] = 0.;
        umult[2] = 1.;
        umult[3] = 0.;
        umult[4] = 0.;
        umult[5] = 0.;
        umult[6] = 0.;
        umult[7] = 0.;
        umult[8] = 0.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(8,8,mmap,mlo,fs,row);
        sdldubsd(8,8,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 7; i++) {
            pp[4][i] = row[i];
            dpp[i][4] = dinvrow[i];
        }
        wmap[4] = 4;
/*
Constraint 5 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 2; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 7; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 0.;
        umult[1] = 0.;
        umult[2] = 0.;
        umult[3] = 1.;
        umult[4] = 0.;
        umult[5] = 0.;
        umult[6] = 0.;
        umult[7] = 0.;
        umult[8] = 0.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(8,8,mmap,mlo,fs,row);
        sdldubsd(8,8,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 7; i++) {
            pp[5][i] = row[i];
            dpp[i][5] = dinvrow[i];
        }
        wmap[5] = 5;
/*
Constraint 6 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 2; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 7; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 0.;
        umult[1] = 0.;
        umult[2] = 0.;
        umult[3] = 0.;
        umult[4] = 1.;
        umult[5] = 0.;
        umult[6] = 0.;
        umult[7] = 0.;
        umult[8] = 0.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(8,8,mmap,mlo,fs,row);
        sdldubsd(8,8,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 7; i++) {
            pp[6][i] = row[i];
            dpp[i][6] = dinvrow[i];
        }
        wmap[6] = 6;
/*
Constraint 7 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 2; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 7; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 0.;
        umult[1] = 0.;
        umult[2] = 0.;
        umult[3] = 0.;
        umult[4] = 0.;
        umult[5] = 1.;
        umult[6] = 0.;
        umult[7] = 0.;
        umult[8] = 0.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(8,8,mmap,mlo,fs,row);
        sdldubsd(8,8,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 7; i++) {
            pp[7][i] = row[i];
            dpp[i][7] = dinvrow[i];
        }
        wmap[7] = 7;
/*
Constraint 8 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 2; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 7; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 0.;
        umult[1] = 0.;
        umult[2] = 0.;
        umult[3] = 0.;
        umult[4] = 0.;
        umult[5] = 0.;
        umult[6] = 1.;
        umult[7] = 0.;
        umult[8] = 0.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(8,8,mmap,mlo,fs,row);
        sdldubsd(8,8,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 7; i++) {
            pp[8][i] = row[i];
            dpp[i][8] = dinvrow[i];
        }
        wmap[8] = 8;
/*
Constraint 9 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 2; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 7; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 0.;
        umult[1] = 0.;
        umult[2] = 0.;
        umult[3] = 0.;
        umult[4] = 0.;
        umult[5] = 0.;
        umult[6] = 0.;
        umult[7] = 1.;
        umult[8] = 0.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(8,8,mmap,mlo,fs,row);
        sdldubsd(8,8,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 7; i++) {
            pp[9][i] = row[i];
            dpp[i][9] = dinvrow[i];
        }
        wmap[9] = 9;
/*
Constraint 10 (user constraint)
*/
/*
Initialize all multiplier forces to zero.
*/
        for (i = 0; i <= 2; i++) {
            for (j = 0; j <= 2; j++) {
                mfk[i][j] = 0.;
                mtk[i][j] = 0.;
            }
        }
        for (i = 0; i <= 7; i++) {
            mtau[i] = 0.;
        }
/*
Compute user-generated multiplier forces
*/
        umult[0] = 0.;
        umult[1] = 0.;
        umult[2] = 0.;
        umult[3] = 0.;
        umult[4] = 0.;
        umult[5] = 0.;
        umult[6] = 0.;
        umult[7] = 0.;
        umult[8] = 1.;
        mfrcflg = 1;
        sduconsfrc(curtim,q,u,umult);
        mfrcflg = 0;
        sdfsmult();
        sdldubsl(8,8,mmap,mlo,fs,row);
        sdldubsd(8,8,mmap,mdi,row,dinvrow);
        for (i = 0; i <= 7; i++) {
            pp[10][i] = row[i];
            dpp[i][10] = dinvrow[i];
        }
        wmap[10] = 10;
/*
Produce constraint coefficient matrix WW
*/
        for (c = 0; c <= 10; c++) {
            for (i = c; i <= 10; i++) {
                sum = 0.;
                for (j = 0; j <= 7; j++) {
                    sum = sum+pp[wmap[c]][j]*dpp[j][wmap[i]];
                }
                ww[wmap[c]][wmap[i]] = sum;
                ww[wmap[i]][wmap[c]] = sum;
            }
        }
/*
Form QR decomposition of WW
*/
        sdqrdcomp(11,11,11,11,wmap,wmap,ww,qraux,jpvt);
        wwflg = 1;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  528 adds/subtracts/negates
                    528 multiplies
                      0 divides
                   1237 assignments
*/
}

void sdxudot0(int routine,
    double oudot0[8])
{
/*
Compute unconstrained equations
*/
    int i;

    sdlhs(routine);
/*
Solve equations ignoring constraints
*/
    sdfs0();
    sdldubslv(8,8,mmap,works,mlo,mdi,fs,udot);
    for (i = 0; i <= 7; i++) {
        oudot0[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      8 assignments
*/
}

void sdudot0(double oudot0[8])
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(66,23);
        return;
    }
    sdxudot0(66,oudot0);
}

void sdsetudot(double iudot[8])
{
/*
Assign udots and advance to stage Dynamics Ready
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(68,23);
        return;
    }
    for (i = 0; i <= 7; i++) {
        udot[i] = iudot[i];
    }
    sdrhs();
}

void sdxudotm(int routine,
    double imult[11],
    double oudotm[8])
{
/*
Compute udots due only to multipliers
*/
    int i;

    sdlhs(routine);
    sdmfrc(imult);
    sdfsmult();
    sdldubslv(8,8,mmap,works,mlo,mdi,fs,udot);
    for (i = 0; i <= 7; i++) {
        oudotm[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      8 assignments
*/
}

void sdudotm(double imult[11],
    double oudotm[8])
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(67,23);
        return;
    }
    sdxudotm(67,imult,oudotm);
}

void sdderiv(double oqdot[9],
    double oudot[8])
{
/*
This is the derivative section for a 3-body ground-based
system with 8 hinge degree(s) of freedom.
2 of the degrees of freedom may follow prescribed motion.
There are 11 constraints.
*/
    double workr[11],bb[11],b0[11],v0[11],p0[11];
    int iwork[11];
    int i,j;
    double udot0[8],udot1[8];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(17,23);
        return;
    }
    if (stabvelq == 1) {
        sdseterr(17,32);
    }
    if (stabposq == 1) {
        sdseterr(17,33);
    }
    wsiz = 11;
/*
Compute unconstrained equations
*/
    sdxudot0(17,udot0);
    sdrhs();
    sdaerr(b0);
    if (stabvel  !=  0.) {
        sdverr(v0);
    }
    if (stabpos  !=  0.) {
        sdperr(p0);
    }
/*
Stabilize constraints using Baumgarte's method
*/
    for (i = 0; i <= 10; i++) {
        bb[i] = -b0[i];
    }
    if (stabvel  !=  0.) {
        for (i = 0; i <= 10; i++) {
            bb[i] = bb[i]-stabvel*v0[i];
        }
    }
    if (stabpos  !=  0.) {
        for (i = 0; i <= 10; i++) {
            bb[i] = bb[i]-stabpos*p0[i];
        }
    }
/*
Compute and decompose constraint matrix WW
*/
    sddoww(17);
/*
Numerically solve for constraint multipliers
*/
    sdqrbslv(11,11,11,11,wmap,wmap,1e-13,workr,iwork,ww,qraux,jpvt,bb,mult,&
      wrank);
    for (i = 0; i <= 10; i++) {
        multmap[i] = 0;
    }
    for (i = 0; i < wrank; i++) {
        multmap[jpvt[i]] = 1;
    }
    j = 0;
    for (i = 0; i <= 10; i++) {
        if (multmap[i] != 0) {
            multmap[j] = wmap[i];
            j = j+1;
        }
    }
/*
Compute final udots
*/
    sdxudotm(17,mult,udot1);
    for (i = 0; i <= 7; i++) {
        udot[i] = udot0[i]+udot1[i];
    }
    sdrhs();
    for (i = 0; i <= 8; i++) {
        oqdot[i] = qdot[i];
    }
    for (i = 0; i <= 7; i++) {
        oudot[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   41 adds/subtracts/negates
                     22 multiplies
                      0 divides
                     58 assignments
*/
}
/*
Compute residuals for use with DAE integrator
*/

void sdresid(double eqdot[9],
    double eudot[8],
    double emults[11],
    double resid[28])
{
    int i;
    double uderrs[8],p0[11];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(16,23);
        return;
    }
    if (stabposq == 1) {
        sdseterr(16,33);
    }
    sdfulltrq(eudot,emults,uderrs);
    for (i = 0; i < 9; i++) {
        resid[i] = eqdot[i]-qdot[i];
    }
    for (i = 0; i < 8; i++) {
        resid[9+i] = uderrs[i];
    }
    sdverr(&resid[17]);
    if (stabpos  !=  0.) {
        sdperr(p0);
        for (i = 0; i < 11; i++) {
            resid[17+i] = resid[17+i]+stabpos*p0[i];
        }
    }
    for (i = 0; i < 8; i++) {
        udot[i] = eudot[i];
    }
    for (i = 0; i < 11; i++) {
        mult[i] = emults[i];
    }
    sdrhs();
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   20 adds/subtracts/negates
                     11 multiplies
                      0 divides
                     47 assignments
*/
}

void sdmult(double omults[11],
    int *owrank,
    int omultmap[11])
{
    int i;

    if (roustate != 3) {
        sdseterr(34,24);
        return;
    }
    for (i = 0; i < 11; i++) {
        omults[i] = mult[i];
        if (i <= wrank-1) {
            omultmap[i] = multmap[i];
        } else {
            omultmap[i] = -1;
        }
    }
    *owrank = wrank;
}

void sdreac(double force[3][3],
    double torque[3][3])
{
/*
Generated 20-Jul-2007 21:06:48 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/

    if (roustate != 3) {
        sdseterr(31,24);
        return;
    }
/*
Compute reaction forces for non-weld tree joints
*/
    ffkb[0][0] = (mfk[0][0]+ufk[0][0]);
    ffkb[0][1] = (mfk[0][1]+ufk[0][1]);
    ffkb[0][2] = (mfk[0][2]+ufk[0][2]);
    ffkb[1][0] = (mfk[1][0]+ufk[1][0]);
    ffkb[1][1] = (mfk[1][1]+ufk[1][1]);
    ffkb[1][2] = (mfk[1][2]+ufk[1][2]);
    ffkb[2][0] = (mfk[2][0]+ufk[2][0]);
    ffkb[2][1] = (mfk[2][1]+ufk[2][1]);
    ffkb[2][2] = (mfk[2][2]+ufk[2][2]);
    ttkb[0][0] = (mtk[0][0]+utk[0][0]);
    ttkb[0][1] = (mtk[0][1]+utk[0][1]);
    ttkb[0][2] = (mtk[0][2]+utk[0][2]);
    ttkb[1][0] = (mtk[1][0]+utk[1][0]);
    ttkb[1][1] = (mtk[1][1]+utk[1][1]);
    ttkb[1][2] = (mtk[1][2]+utk[1][2]);
    ttkb[2][0] = (mtk[2][0]+utk[2][0]);
    ttkb[2][1] = (mtk[2][1]+utk[2][1]);
    ttkb[2][2] = (mtk[2][2]+utk[2][2]);
    fc[7][0] = ((mk[2]*(AnkAtk[7][0]-gk[7][0]))-ffkb[2][0]);
    fc[7][1] = ((mk[2]*(AnkAtk[7][1]-gk[7][1]))-ffkb[2][1]);
    fc[7][2] = ((mk[2]*(AnkAtk[7][2]-gk[7][2]))-ffkb[2][2]);
    tc[7][0] = ((WkIkWk[7][0]+((ik[2][0][2]*onk[7][2])+((ik[2][0][0]*onk[7][0])+
      (ik[2][0][1]*onk[7][1]))))-(ttkb[2][0]+((fc[7][2]*rk[2][1])-(fc[7][1]*
      rk[2][2]))));
    tc[7][1] = ((WkIkWk[7][1]+((ik[2][1][2]*onk[7][2])+((ik[2][1][0]*onk[7][0])+
      (ik[2][1][1]*onk[7][1]))))-(ttkb[2][1]+((fc[7][0]*rk[2][2])-(fc[7][2]*
      rk[2][0]))));
    tc[7][2] = ((WkIkWk[7][2]+((ik[2][2][2]*onk[7][2])+((ik[2][2][0]*onk[7][0])+
      (ik[2][2][1]*onk[7][1]))))-(ttkb[2][2]+((fc[7][1]*rk[2][0])-(fc[7][0]*
      rk[2][1]))));
    fccikt[7][0] = ((Cik[7][0][2]*fc[7][2])+((Cik[7][0][0]*fc[7][0])+(
      Cik[7][0][1]*fc[7][1])));
    fccikt[7][1] = ((Cik[7][1][2]*fc[7][2])+((Cik[7][1][0]*fc[7][0])+(
      Cik[7][1][1]*fc[7][1])));
    fccikt[7][2] = ((Cik[7][2][2]*fc[7][2])+((Cik[7][2][0]*fc[7][0])+(
      Cik[7][2][1]*fc[7][1])));
    ffk[5][0] = (ffkb[0][0]-fccikt[7][0]);
    ffk[5][1] = (ffkb[0][1]-fccikt[7][1]);
    ffk[5][2] = (ffkb[0][2]-fccikt[7][2]);
    ttk[5][0] = (ttkb[0][0]-(((Cik[7][0][2]*tc[7][2])+((Cik[7][0][0]*tc[7][0])+(
      Cik[7][0][1]*tc[7][1])))+((fccikt[7][2]*ri[2][1])-(fccikt[7][1]*ri[2][2]))
      ));
    ttk[5][1] = (ttkb[0][1]-(((Cik[7][1][2]*tc[7][2])+((Cik[7][1][0]*tc[7][0])+(
      Cik[7][1][1]*tc[7][1])))+((fccikt[7][0]*ri[2][2])-(fccikt[7][2]*ri[2][0]))
      ));
    ttk[5][2] = (ttkb[0][2]-(((Cik[7][2][2]*tc[7][2])+((Cik[7][2][0]*tc[7][0])+(
      Cik[7][2][1]*tc[7][1])))+((fccikt[7][1]*ri[2][0])-(fccikt[7][0]*ri[2][1]))
      ));
    fc[6][0] = ((mk[1]*(AnkAtk[6][0]-gk[6][0]))-ffkb[1][0]);
    fc[6][1] = ((mk[1]*(AnkAtk[6][1]-gk[6][1]))-ffkb[1][1]);
    fc[6][2] = ((mk[1]*(AnkAtk[6][2]-gk[6][2]))-ffkb[1][2]);
    tc[6][0] = ((WkIkWk[6][0]+((ik[1][0][2]*onk[6][2])+((ik[1][0][0]*onk[6][0])+
      (ik[1][0][1]*onk[6][1]))))-(ttkb[1][0]+((fc[6][2]*rk[1][1])-(fc[6][1]*
      rk[1][2]))));
    tc[6][1] = ((WkIkWk[6][1]+((ik[1][1][2]*onk[6][2])+((ik[1][1][0]*onk[6][0])+
      (ik[1][1][1]*onk[6][1]))))-(ttkb[1][1]+((fc[6][0]*rk[1][2])-(fc[6][2]*
      rk[1][0]))));
    tc[6][2] = ((WkIkWk[6][2]+((ik[1][2][2]*onk[6][2])+((ik[1][2][0]*onk[6][0])+
      (ik[1][2][1]*onk[6][1]))))-(ttkb[1][2]+((fc[6][1]*rk[1][0])-(fc[6][0]*
      rk[1][1]))));
    fccikt[6][0] = ((Cik[6][0][2]*fc[6][2])+((Cik[6][0][0]*fc[6][0])+(
      Cik[6][0][1]*fc[6][1])));
    fccikt[6][1] = ((Cik[6][1][2]*fc[6][2])+((Cik[6][1][0]*fc[6][0])+(
      Cik[6][1][1]*fc[6][1])));
    fccikt[6][2] = ((Cik[6][2][2]*fc[6][2])+((Cik[6][2][0]*fc[6][0])+(
      Cik[6][2][1]*fc[6][1])));
    ffk[5][0] = (ffk[5][0]-fccikt[6][0]);
    ffk[5][1] = (ffk[5][1]-fccikt[6][1]);
    ffk[5][2] = (ffk[5][2]-fccikt[6][2]);
    ttk[5][0] = (ttk[5][0]-(((Cik[6][0][2]*tc[6][2])+((Cik[6][0][0]*tc[6][0])+(
      Cik[6][0][1]*tc[6][1])))+((fccikt[6][2]*ri[1][1])-(fccikt[6][1]*ri[1][2]))
      ));
    ttk[5][1] = (ttk[5][1]-(((Cik[6][1][2]*tc[6][2])+((Cik[6][1][0]*tc[6][0])+(
      Cik[6][1][1]*tc[6][1])))+((fccikt[6][0]*ri[1][2])-(fccikt[6][2]*ri[1][0]))
      ));
    ttk[5][2] = (ttk[5][2]-(((Cik[6][2][2]*tc[6][2])+((Cik[6][2][0]*tc[6][0])+(
      Cik[6][2][1]*tc[6][1])))+((fccikt[6][1]*ri[1][0])-(fccikt[6][0]*ri[1][1]))
      ));
    fc[5][0] = ((mk[0]*(AnkAtk[5][0]+(9.81*Cik[3][2][0])))-ffk[5][0]);
    fc[5][1] = ((mk[0]*(AnkAtk[5][1]+(9.81*Cik[3][2][1])))-ffk[5][1]);
    fc[5][2] = ((mk[0]*(AnkAtk[5][2]+(9.81*Cik[3][2][2])))-ffk[5][2]);
    tc[5][0] = ((WkIkWk[5][0]+((ik[0][0][2]*udot[5])+((ik[0][0][0]*udot[3])+(
      ik[0][0][1]*udot[4]))))-(ttk[5][0]+((fc[5][2]*rk[0][1])-(fc[5][1]*rk[0][2]
      ))));
    tc[5][1] = ((WkIkWk[5][1]+((ik[0][1][2]*udot[5])+((ik[0][1][0]*udot[3])+(
      ik[0][1][1]*udot[4]))))-(ttk[5][1]+((fc[5][0]*rk[0][2])-(fc[5][2]*rk[0][0]
      ))));
    tc[5][2] = ((WkIkWk[5][2]+((ik[0][2][2]*udot[5])+((ik[0][2][0]*udot[3])+(
      ik[0][2][1]*udot[4]))))-(ttk[5][2]+((fc[5][1]*rk[0][0])-(fc[5][0]*rk[0][1]
      ))));
    fccikt[5][0] = fc[5][0];
    fccikt[5][1] = fc[5][1];
    fccikt[5][2] = fc[5][2];
    ffk[4][0] = -fccikt[5][0];
    ffk[4][1] = -fccikt[5][1];
    ffk[4][2] = -fccikt[5][2];
    ttk[4][0] = -tc[5][0];
    ttk[4][1] = -tc[5][1];
    ttk[4][2] = -tc[5][2];
    fc[4][0] = -ffk[4][0];
    fc[4][1] = -ffk[4][1];
    fc[4][2] = -ffk[4][2];
    tc[4][0] = -ttk[4][0];
    tc[4][1] = -ttk[4][1];
    tc[4][2] = -ttk[4][2];
    fccikt[4][0] = fc[4][0];
    fccikt[4][1] = fc[4][1];
    fccikt[4][2] = fc[4][2];
    ffk[3][0] = -fccikt[4][0];
    ffk[3][1] = -fccikt[4][1];
    ffk[3][2] = -fccikt[4][2];
    ttk[3][0] = -tc[4][0];
    ttk[3][1] = -tc[4][1];
    ttk[3][2] = -tc[4][2];
    fc[3][0] = -ffk[3][0];
    fc[3][1] = -ffk[3][1];
    fc[3][2] = -ffk[3][2];
    tc[3][0] = -ttk[3][0];
    tc[3][1] = -ttk[3][1];
    tc[3][2] = -ttk[3][2];
    fccikt[3][0] = ((Cik[3][0][2]*fc[3][2])+((Cik[3][0][0]*fc[3][0])+(
      Cik[3][0][1]*fc[3][1])));
    fccikt[3][1] = ((Cik[3][1][2]*fc[3][2])+((Cik[3][1][0]*fc[3][0])+(
      Cik[3][1][1]*fc[3][1])));
    fccikt[3][2] = ((Cik[3][2][2]*fc[3][2])+((Cik[3][2][0]*fc[3][0])+(
      Cik[3][2][1]*fc[3][1])));
    ffk[2][0] = -fccikt[3][0];
    ffk[2][1] = -fccikt[3][1];
    ffk[2][2] = -fccikt[3][2];
    ttk[2][0] = -((Cik[3][0][2]*tc[3][2])+((Cik[3][0][0]*tc[3][0])+(Cik[3][0][1]
      *tc[3][1])));
    ttk[2][1] = -((Cik[3][1][2]*tc[3][2])+((Cik[3][1][0]*tc[3][0])+(Cik[3][1][1]
      *tc[3][1])));
    ttk[2][2] = -((Cik[3][2][2]*tc[3][2])+((Cik[3][2][0]*tc[3][0])+(Cik[3][2][1]
      *tc[3][1])));
    fc[2][0] = -ffk[2][0];
    fc[2][1] = -ffk[2][1];
    fc[2][2] = -ffk[2][2];
    tc[2][0] = -ttk[2][0];
    tc[2][1] = -ttk[2][1];
    tc[2][2] = -ttk[2][2];
    fccikt[2][0] = fc[2][0];
    fccikt[2][1] = fc[2][1];
    fccikt[2][2] = fc[2][2];
    ffk[1][0] = -fccikt[2][0];
    ffk[1][1] = -fccikt[2][1];
    ffk[1][2] = -fccikt[2][2];
    ttk[1][0] = -(tc[2][0]+((fccikt[2][2]*rpp[2][1])-(fccikt[2][1]*rpp[2][2])));
    ttk[1][1] = -(tc[2][1]+((fccikt[2][0]*rpp[2][2])-(fccikt[2][2]*rpp[2][0])));
    ttk[1][2] = -(tc[2][2]+((fccikt[2][1]*rpp[2][0])-(fccikt[2][0]*rpp[2][1])));
    fc[1][0] = -ffk[1][0];
    fc[1][1] = -ffk[1][1];
    fc[1][2] = -ffk[1][2];
    tc[1][0] = -ttk[1][0];
    tc[1][1] = -ttk[1][1];
    tc[1][2] = -ttk[1][2];
    fccikt[1][0] = fc[1][0];
    fccikt[1][1] = fc[1][1];
    fccikt[1][2] = fc[1][2];
    ffk[0][0] = -fccikt[1][0];
    ffk[0][1] = -fccikt[1][1];
    ffk[0][2] = -fccikt[1][2];
    ttk[0][0] = -(tc[1][0]+((fccikt[1][2]*rpp[1][1])-(fccikt[1][1]*rpp[1][2])));
    ttk[0][1] = -(tc[1][1]+((fccikt[1][0]*rpp[1][2])-(fccikt[1][2]*rpp[1][0])));
    ttk[0][2] = -(tc[1][2]+((fccikt[1][1]*rpp[1][0])-(fccikt[1][0]*rpp[1][1])));
    fc[0][0] = -ffk[0][0];
    fc[0][1] = -ffk[0][1];
    fc[0][2] = -ffk[0][2];
    tc[0][0] = -ttk[0][0];
    tc[0][1] = -ttk[0][1];
    tc[0][2] = -ttk[0][2];
    force[0][0] = fc[5][0];
    torque[0][0] = tc[5][0];
    force[0][1] = fc[5][1];
    torque[0][1] = tc[5][1];
    force[0][2] = fc[5][2];
    torque[0][2] = tc[5][2];
    force[1][0] = fc[6][0];
    torque[1][0] = tc[6][0];
    force[1][1] = fc[6][1];
    torque[1][1] = tc[6][1];
    force[1][2] = fc[6][2];
    torque[1][2] = tc[6][2];
    force[2][0] = fc[7][0];
    torque[2][0] = tc[7][0];
    force[2][1] = fc[7][1];
    torque[2][1] = tc[7][1];
    force[2][2] = fc[7][2];
    torque[2][2] = tc[7][2];
/*
Compute reaction forces for tree weld joints
*/
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  222 adds/subtracts/negates
                    135 multiplies
                      0 divides
                    147 assignments
*/
}

void sdmom(double lm[3],
    double am[3],
    double *ke)
{
/*
Compute system linear and angular momentum, and kinetic energy.

Generated 20-Jul-2007 21:06:48 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double lk[3][3],hnk[3][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(19,23);
        return;
    }
    lk[0][0] = (mk[0]*vnk[5][0]);
    lk[0][1] = (mk[0]*vnk[5][1]);
    lk[0][2] = (mk[0]*vnk[5][2]);
    lk[1][0] = (mk[1]*vnk[6][0]);
    lk[1][1] = (mk[1]*vnk[6][1]);
    lk[1][2] = (mk[1]*vnk[6][2]);
    lk[2][0] = (mk[2]*vnk[7][0]);
    lk[2][1] = (mk[2]*vnk[7][1]);
    lk[2][2] = (mk[2]*vnk[7][2]);
    hnk[0][0] = ((ik[0][0][2]*u[5])+((ik[0][0][0]*u[3])+(ik[0][0][1]*u[4])));
    hnk[0][1] = ((ik[0][1][2]*u[5])+((ik[0][1][0]*u[3])+(ik[0][1][1]*u[4])));
    hnk[0][2] = ((ik[0][2][2]*u[5])+((ik[0][2][0]*u[3])+(ik[0][2][1]*u[4])));
    hnk[1][0] = ((ik[1][0][2]*wk[6][2])+((ik[1][0][0]*wk[6][0])+(ik[1][0][1]*
      wk[6][1])));
    hnk[1][1] = ((ik[1][1][2]*wk[6][2])+((ik[1][1][0]*wk[6][0])+(ik[1][1][1]*
      wk[6][1])));
    hnk[1][2] = ((ik[1][2][2]*wk[6][2])+((ik[1][2][0]*wk[6][0])+(ik[1][2][1]*
      wk[6][1])));
    hnk[2][0] = ((ik[2][0][2]*wk[7][2])+((ik[2][0][0]*wk[7][0])+(ik[2][0][1]*
      wk[7][1])));
    hnk[2][1] = ((ik[2][1][2]*wk[7][2])+((ik[2][1][0]*wk[7][0])+(ik[2][1][1]*
      wk[7][1])));
    hnk[2][2] = ((ik[2][2][2]*wk[7][2])+((ik[2][2][0]*wk[7][0])+(ik[2][2][1]*
      wk[7][1])));
    lm[0] = (lk[2][0]+(lk[0][0]+lk[1][0]));
    lm[1] = (lk[2][1]+(lk[0][1]+lk[1][1]));
    lm[2] = (lk[2][2]+(lk[0][2]+lk[1][2]));
    temp[0] = ((((cnk[7][0][2]*hnk[2][2])+((cnk[7][0][0]*hnk[2][0])+(
      cnk[7][0][1]*hnk[2][1])))+((lk[2][2]*rnk[7][1])-(lk[2][1]*rnk[7][2])))+(((
      (Cik[3][0][2]*hnk[0][2])+((Cik[3][0][0]*hnk[0][0])+(Cik[3][0][1]*hnk[0][1]
      )))+((lk[0][2]*rnk[5][1])-(lk[0][1]*rnk[5][2])))+(((cnk[6][0][2]*hnk[1][2]
      )+((cnk[6][0][0]*hnk[1][0])+(cnk[6][0][1]*hnk[1][1])))+((lk[1][2]*
      rnk[6][1])-(lk[1][1]*rnk[6][2])))));
    am[0] = (temp[0]-((com[1]*lm[2])-(com[2]*lm[1])));
    temp[0] = ((((cnk[7][1][2]*hnk[2][2])+((cnk[7][1][0]*hnk[2][0])+(
      cnk[7][1][1]*hnk[2][1])))+((lk[2][0]*rnk[7][2])-(lk[2][2]*rnk[7][0])))+(((
      (Cik[3][1][2]*hnk[0][2])+((Cik[3][1][0]*hnk[0][0])+(Cik[3][1][1]*hnk[0][1]
      )))+((lk[0][0]*rnk[5][2])-(lk[0][2]*rnk[5][0])))+(((cnk[6][1][2]*hnk[1][2]
      )+((cnk[6][1][0]*hnk[1][0])+(cnk[6][1][1]*hnk[1][1])))+((lk[1][0]*
      rnk[6][2])-(lk[1][2]*rnk[6][0])))));
    am[1] = (temp[0]-((com[2]*lm[0])-(com[0]*lm[2])));
    temp[0] = ((((cnk[7][2][2]*hnk[2][2])+((cnk[7][2][0]*hnk[2][0])+(
      cnk[7][2][1]*hnk[2][1])))+((lk[2][1]*rnk[7][0])-(lk[2][0]*rnk[7][1])))+(((
      (Cik[3][2][2]*hnk[0][2])+((Cik[3][2][0]*hnk[0][0])+(Cik[3][2][1]*hnk[0][1]
      )))+((lk[0][1]*rnk[5][0])-(lk[0][0]*rnk[5][1])))+(((cnk[6][2][2]*hnk[1][2]
      )+((cnk[6][2][0]*hnk[1][0])+(cnk[6][2][1]*hnk[1][1])))+((lk[1][1]*
      rnk[6][0])-(lk[1][0]*rnk[6][1])))));
    am[2] = (temp[0]-((com[0]*lm[1])-(com[1]*lm[0])));
    temp[0] = ((((hnk[0][2]*u[5])+((hnk[0][0]*u[3])+(hnk[0][1]*u[4])))+((
      lk[0][2]*vnk[5][2])+((lk[0][0]*vnk[5][0])+(lk[0][1]*vnk[5][1]))))+(((
      hnk[1][2]*wk[6][2])+((hnk[1][0]*wk[6][0])+(hnk[1][1]*wk[6][1])))+((
      lk[1][2]*vnk[6][2])+((lk[1][0]*vnk[6][0])+(lk[1][1]*vnk[6][1])))));
    *ke = (.5*((((hnk[2][2]*wk[7][2])+((hnk[2][0]*wk[7][0])+(hnk[2][1]*wk[7][1])
      ))+((lk[2][2]*vnk[7][2])+((lk[2][0]*vnk[7][0])+(lk[2][1]*vnk[7][1]))))+
      temp[0]));
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   89 adds/subtracts/negates
                    106 multiplies
                      0 divides
                     29 assignments
*/
}

void sdsys(double *mtoto,
    double cm[3],
    double icm[3][3])
{
/*
Compute system total mass, and instantaneous center of mass and
inertia matrix.

Generated 20-Jul-2007 21:06:48 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double ikcnkt[8][3][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(20,23);
        return;
    }
    *mtoto = mtot;
    cm[0] = com[0];
    cm[1] = com[1];
    cm[2] = com[2];
    ikcnkt[5][0][0] = ((Cik[3][0][2]*ik[0][0][2])+((Cik[3][0][0]*ik[0][0][0])+(
      Cik[3][0][1]*ik[0][0][1])));
    ikcnkt[5][0][1] = ((Cik[3][1][2]*ik[0][0][2])+((Cik[3][1][0]*ik[0][0][0])+(
      Cik[3][1][1]*ik[0][0][1])));
    ikcnkt[5][0][2] = ((Cik[3][2][2]*ik[0][0][2])+((Cik[3][2][0]*ik[0][0][0])+(
      Cik[3][2][1]*ik[0][0][1])));
    ikcnkt[5][1][0] = ((Cik[3][0][2]*ik[0][1][2])+((Cik[3][0][0]*ik[0][1][0])+(
      Cik[3][0][1]*ik[0][1][1])));
    ikcnkt[5][1][1] = ((Cik[3][1][2]*ik[0][1][2])+((Cik[3][1][0]*ik[0][1][0])+(
      Cik[3][1][1]*ik[0][1][1])));
    ikcnkt[5][1][2] = ((Cik[3][2][2]*ik[0][1][2])+((Cik[3][2][0]*ik[0][1][0])+(
      Cik[3][2][1]*ik[0][1][1])));
    ikcnkt[5][2][0] = ((Cik[3][0][2]*ik[0][2][2])+((Cik[3][0][0]*ik[0][2][0])+(
      Cik[3][0][1]*ik[0][2][1])));
    ikcnkt[5][2][1] = ((Cik[3][1][2]*ik[0][2][2])+((Cik[3][1][0]*ik[0][2][0])+(
      Cik[3][1][1]*ik[0][2][1])));
    ikcnkt[5][2][2] = ((Cik[3][2][2]*ik[0][2][2])+((Cik[3][2][0]*ik[0][2][0])+(
      Cik[3][2][1]*ik[0][2][1])));
    ikcnkt[6][0][0] = ((cnk[6][0][2]*ik[1][0][2])+((cnk[6][0][0]*ik[1][0][0])+(
      cnk[6][0][1]*ik[1][0][1])));
    ikcnkt[6][0][1] = ((cnk[6][1][2]*ik[1][0][2])+((cnk[6][1][0]*ik[1][0][0])+(
      cnk[6][1][1]*ik[1][0][1])));
    ikcnkt[6][0][2] = ((cnk[6][2][2]*ik[1][0][2])+((cnk[6][2][0]*ik[1][0][0])+(
      cnk[6][2][1]*ik[1][0][1])));
    ikcnkt[6][1][0] = ((cnk[6][0][2]*ik[1][1][2])+((cnk[6][0][0]*ik[1][1][0])+(
      cnk[6][0][1]*ik[1][1][1])));
    ikcnkt[6][1][1] = ((cnk[6][1][2]*ik[1][1][2])+((cnk[6][1][0]*ik[1][1][0])+(
      cnk[6][1][1]*ik[1][1][1])));
    ikcnkt[6][1][2] = ((cnk[6][2][2]*ik[1][1][2])+((cnk[6][2][0]*ik[1][1][0])+(
      cnk[6][2][1]*ik[1][1][1])));
    ikcnkt[6][2][0] = ((cnk[6][0][2]*ik[1][2][2])+((cnk[6][0][0]*ik[1][2][0])+(
      cnk[6][0][1]*ik[1][2][1])));
    ikcnkt[6][2][1] = ((cnk[6][1][2]*ik[1][2][2])+((cnk[6][1][0]*ik[1][2][0])+(
      cnk[6][1][1]*ik[1][2][1])));
    ikcnkt[6][2][2] = ((cnk[6][2][2]*ik[1][2][2])+((cnk[6][2][0]*ik[1][2][0])+(
      cnk[6][2][1]*ik[1][2][1])));
    ikcnkt[7][0][0] = ((cnk[7][0][2]*ik[2][0][2])+((cnk[7][0][0]*ik[2][0][0])+(
      cnk[7][0][1]*ik[2][0][1])));
    ikcnkt[7][0][1] = ((cnk[7][1][2]*ik[2][0][2])+((cnk[7][1][0]*ik[2][0][0])+(
      cnk[7][1][1]*ik[2][0][1])));
    ikcnkt[7][0][2] = ((cnk[7][2][2]*ik[2][0][2])+((cnk[7][2][0]*ik[2][0][0])+(
      cnk[7][2][1]*ik[2][0][1])));
    ikcnkt[7][1][0] = ((cnk[7][0][2]*ik[2][1][2])+((cnk[7][0][0]*ik[2][1][0])+(
      cnk[7][0][1]*ik[2][1][1])));
    ikcnkt[7][1][1] = ((cnk[7][1][2]*ik[2][1][2])+((cnk[7][1][0]*ik[2][1][0])+(
      cnk[7][1][1]*ik[2][1][1])));
    ikcnkt[7][1][2] = ((cnk[7][2][2]*ik[2][1][2])+((cnk[7][2][0]*ik[2][1][0])+(
      cnk[7][2][1]*ik[2][1][1])));
    ikcnkt[7][2][0] = ((cnk[7][0][2]*ik[2][2][2])+((cnk[7][0][0]*ik[2][2][0])+(
      cnk[7][0][1]*ik[2][2][1])));
    ikcnkt[7][2][1] = ((cnk[7][1][2]*ik[2][2][2])+((cnk[7][1][0]*ik[2][2][0])+(
      cnk[7][1][1]*ik[2][2][1])));
    ikcnkt[7][2][2] = ((cnk[7][2][2]*ik[2][2][2])+((cnk[7][2][0]*ik[2][2][0])+(
      cnk[7][2][1]*ik[2][2][1])));
    temp[0] = (((mk[0]*((rnk[5][1]*rnk[5][1])+(rnk[5][2]*rnk[5][2])))+((
      Cik[3][0][2]*ikcnkt[5][2][0])+((Cik[3][0][0]*ikcnkt[5][0][0])+(
      Cik[3][0][1]*ikcnkt[5][1][0]))))+((mk[1]*((rnk[6][1]*rnk[6][1])+(rnk[6][2]
      *rnk[6][2])))+((cnk[6][0][2]*ikcnkt[6][2][0])+((cnk[6][0][0]*
      ikcnkt[6][0][0])+(cnk[6][0][1]*ikcnkt[6][1][0])))));
    icm[0][0] = ((((mk[2]*((rnk[7][1]*rnk[7][1])+(rnk[7][2]*rnk[7][2])))+((
      cnk[7][0][2]*ikcnkt[7][2][0])+((cnk[7][0][0]*ikcnkt[7][0][0])+(
      cnk[7][0][1]*ikcnkt[7][1][0]))))+temp[0])-(mtot*((com[1]*com[1])+(com[2]*
      com[2]))));
    temp[0] = ((((cnk[7][0][2]*ikcnkt[7][2][1])+((cnk[7][0][0]*ikcnkt[7][0][1])+
      (cnk[7][0][1]*ikcnkt[7][1][1])))-(mk[2]*(rnk[7][0]*rnk[7][1])))+((((
      Cik[3][0][2]*ikcnkt[5][2][1])+((Cik[3][0][0]*ikcnkt[5][0][1])+(
      Cik[3][0][1]*ikcnkt[5][1][1])))-(mk[0]*(rnk[5][0]*rnk[5][1])))+(((
      cnk[6][0][2]*ikcnkt[6][2][1])+((cnk[6][0][0]*ikcnkt[6][0][1])+(
      cnk[6][0][1]*ikcnkt[6][1][1])))-(mk[1]*(rnk[6][0]*rnk[6][1])))));
    icm[0][1] = ((mtot*(com[0]*com[1]))+temp[0]);
    temp[0] = ((((cnk[7][0][2]*ikcnkt[7][2][2])+((cnk[7][0][0]*ikcnkt[7][0][2])+
      (cnk[7][0][1]*ikcnkt[7][1][2])))-(mk[2]*(rnk[7][0]*rnk[7][2])))+((((
      Cik[3][0][2]*ikcnkt[5][2][2])+((Cik[3][0][0]*ikcnkt[5][0][2])+(
      Cik[3][0][1]*ikcnkt[5][1][2])))-(mk[0]*(rnk[5][0]*rnk[5][2])))+(((
      cnk[6][0][2]*ikcnkt[6][2][2])+((cnk[6][0][0]*ikcnkt[6][0][2])+(
      cnk[6][0][1]*ikcnkt[6][1][2])))-(mk[1]*(rnk[6][0]*rnk[6][2])))));
    icm[0][2] = ((mtot*(com[0]*com[2]))+temp[0]);
    icm[1][0] = icm[0][1];
    temp[0] = (((mk[0]*((rnk[5][0]*rnk[5][0])+(rnk[5][2]*rnk[5][2])))+((
      Cik[3][1][2]*ikcnkt[5][2][1])+((Cik[3][1][0]*ikcnkt[5][0][1])+(
      Cik[3][1][1]*ikcnkt[5][1][1]))))+((mk[1]*((rnk[6][0]*rnk[6][0])+(rnk[6][2]
      *rnk[6][2])))+((cnk[6][1][2]*ikcnkt[6][2][1])+((cnk[6][1][0]*
      ikcnkt[6][0][1])+(cnk[6][1][1]*ikcnkt[6][1][1])))));
    icm[1][1] = ((((mk[2]*((rnk[7][0]*rnk[7][0])+(rnk[7][2]*rnk[7][2])))+((
      cnk[7][1][2]*ikcnkt[7][2][1])+((cnk[7][1][0]*ikcnkt[7][0][1])+(
      cnk[7][1][1]*ikcnkt[7][1][1]))))+temp[0])-(mtot*((com[0]*com[0])+(com[2]*
      com[2]))));
    temp[0] = ((((cnk[7][1][2]*ikcnkt[7][2][2])+((cnk[7][1][0]*ikcnkt[7][0][2])+
      (cnk[7][1][1]*ikcnkt[7][1][2])))-(mk[2]*(rnk[7][1]*rnk[7][2])))+((((
      Cik[3][1][2]*ikcnkt[5][2][2])+((Cik[3][1][0]*ikcnkt[5][0][2])+(
      Cik[3][1][1]*ikcnkt[5][1][2])))-(mk[0]*(rnk[5][1]*rnk[5][2])))+(((
      cnk[6][1][2]*ikcnkt[6][2][2])+((cnk[6][1][0]*ikcnkt[6][0][2])+(
      cnk[6][1][1]*ikcnkt[6][1][2])))-(mk[1]*(rnk[6][1]*rnk[6][2])))));
    icm[1][2] = ((mtot*(com[1]*com[2]))+temp[0]);
    icm[2][0] = icm[0][2];
    icm[2][1] = icm[1][2];
    temp[0] = (((mk[0]*((rnk[5][0]*rnk[5][0])+(rnk[5][1]*rnk[5][1])))+((
      Cik[3][2][2]*ikcnkt[5][2][2])+((Cik[3][2][0]*ikcnkt[5][0][2])+(
      Cik[3][2][1]*ikcnkt[5][1][2]))))+((mk[1]*((rnk[6][0]*rnk[6][0])+(rnk[6][1]
      *rnk[6][1])))+((cnk[6][2][2]*ikcnkt[6][2][2])+((cnk[6][2][0]*
      ikcnkt[6][0][2])+(cnk[6][2][1]*ikcnkt[6][1][2])))));
    icm[2][2] = ((((mk[2]*((rnk[7][0]*rnk[7][0])+(rnk[7][1]*rnk[7][1])))+((
      cnk[7][2][2]*ikcnkt[7][2][2])+((cnk[7][2][0]*ikcnkt[7][0][2])+(
      cnk[7][2][1]*ikcnkt[7][1][2]))))+temp[0])-(mtot*((com[0]*com[0])+(com[1]*
      com[1]))));
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  138 adds/subtracts/negates
                    195 multiplies
                      0 divides
                     46 assignments
*/
}

void sdpos(int body,
    double pt[3],
    double loc[3])
{
/*
Return inertial frame location of a point on a body.

*/
    double pv[3];

    if (sdchkbnum(21,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(21,23);
        return;
    }
    if (body  ==  -1) {
        loc[0] = pt[0];
        loc[1] = pt[1];
        loc[2] = pt[2];
    } else {
        pv[0] = rnb[body][0]+pt[0]*cnb[body][0][0]+pt[1]*cnb[body][0][1]+pt[2]*
          cnb[body][0][2];
        pv[1] = rnb[body][1]+pt[0]*cnb[body][1][0]+pt[1]*cnb[body][1][1]+pt[2]*
          cnb[body][1][2];
        pv[2] = rnb[body][2]+pt[0]*cnb[body][2][0]+pt[1]*cnb[body][2][1]+pt[2]*
          cnb[body][2][2];
        loc[0] = pv[0];
        loc[1] = pv[1];
        loc[2] = pv[2];
    }
}

void sdvel(int body,
    double pt[3],
    double velo[3])
{
/*
Return inertial frame velocity of a point on a body.

*/
    double pv[3];

    if (sdchkbnum(22,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(22,23);
        return;
    }
    if (body  ==  -1) {
        velo[0] = 0.;
        velo[1] = 0.;
        velo[2] = 0.;
    } else {
        pv[0] = wb[body][1]*pt[2]-wb[body][2]*pt[1];
        pv[1] = wb[body][2]*pt[0]-wb[body][0]*pt[2];
        pv[2] = wb[body][0]*pt[1]-wb[body][1]*pt[0];
        velo[0] = vnb[body][0]+pv[0]*cnb[body][0][0]+pv[1]*cnb[body][0][1]+pv[2]
          *cnb[body][0][2];
        velo[1] = vnb[body][1]+pv[0]*cnb[body][1][0]+pv[1]*cnb[body][1][1]+pv[2]
          *cnb[body][1][2];
        velo[2] = vnb[body][2]+pv[0]*cnb[body][2][0]+pv[1]*cnb[body][2][1]+pv[2]
          *cnb[body][2][2];
    }
}

void sdorient(int body,
    double dircos[3][3])
{
/*
Return orientation of body w.r.t. ground frame.

*/

    if (sdchkbnum(23,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(23,23);
        return;
    }
    if (body == -1) {
        dircos[0][0] = 1.;
        dircos[0][1] = 0.;
        dircos[0][2] = 0.;
        dircos[1][0] = 0.;
        dircos[1][1] = 1.;
        dircos[1][2] = 0.;
        dircos[2][0] = 0.;
        dircos[2][1] = 0.;
        dircos[2][2] = 1.;
    } else {
        dircos[0][0] = cnb[body][0][0];
        dircos[0][1] = cnb[body][0][1];
        dircos[0][2] = cnb[body][0][2];
        dircos[1][0] = cnb[body][1][0];
        dircos[1][1] = cnb[body][1][1];
        dircos[1][2] = cnb[body][1][2];
        dircos[2][0] = cnb[body][2][0];
        dircos[2][1] = cnb[body][2][1];
        dircos[2][2] = cnb[body][2][2];
    }
}

void sdangvel(int body,
    double avel[3])
{
/*
Return angular velocity of the body.

*/

    if (sdchkbnum(24,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(24,23);
        return;
    }
    if (body == -1) {
        avel[0] = 0.;
        avel[1] = 0.;
        avel[2] = 0.;
    } else {
        avel[0] = wb[body][0];
        avel[1] = wb[body][1];
        avel[2] = wb[body][2];
    }
}

void sdtrans(int frbod,
    double ivec[3],
    int tobod,
    double ovec[3])
{
/*
Transform ivec from frbod frame to tobod frame.

*/
    double pv[3];

    if (sdchkbnum(25,frbod) != 0) {
        return;
    }
    if (sdchkbnum(25,tobod) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(25,23);
        return;
    }
    if (frbod == tobod) {
        sdvcopy(ivec,ovec);
        return;
    }
    if (frbod == -1) {
        sdvcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod
          ][2][0];
        ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod
          ][2][1];
        ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod
          ][2][2];
        return;
    }
    if (tobod == -1) {
        sdvcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[frbod][0][0]+pv[1]*cnb[frbod][0][1]+pv[2]*cnb[frbod
          ][0][2];
        ovec[1] = pv[0]*cnb[frbod][1][0]+pv[1]*cnb[frbod][1][1]+pv[2]*cnb[frbod
          ][1][2];
        ovec[2] = pv[0]*cnb[frbod][2][0]+pv[1]*cnb[frbod][2][1]+pv[2]*cnb[frbod
          ][2][2];
        return;
    }
    pv[0] = ivec[0]*cnb[frbod][0][0]+ivec[1]*cnb[frbod][0][1]+ivec[2]*cnb[frbod
      ][0][2];
    pv[1] = ivec[0]*cnb[frbod][1][0]+ivec[1]*cnb[frbod][1][1]+ivec[2]*cnb[frbod
      ][1][2];
    pv[2] = ivec[0]*cnb[frbod][2][0]+ivec[1]*cnb[frbod][2][1]+ivec[2]*cnb[frbod
      ][2][2];
    ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod][2][
      0];
    ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod][2][
      1];
    ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod][2][
      2];
}

void sdrel2cart(int coord,
    int body,
    double point[3],
    double linchg[3],
    double rotchg[3])
{
/* Return derivative of pt loc and body orient w.r.t. hinge rate
*/
    int x,i,gnd;
    double lin[3],pv[3];

    if ((coord < 0) || (coord > 7)) {
        sdseterr(59,45);
        return;
    }
    if (sdchkbnum(59,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(59,23);
        return;
    }
    gnd = -1;
    if (body == gnd) {
        x = -1;
    } else {
        x = firstq[body]+njntdof[body]-1;
    }
    if (x < coord) {
        sdvset(0.,0.,0.,linchg);
        sdvset(0.,0.,0.,rotchg);
        return;
    }
    sddovpk();
    for (i = 0; i < 3; i++) {
        rotchg[i] = Wpk[coord][x][i];
        lin[i] = Vpk[coord][x][i];
    }
    if (body == gnd) {
        sdvcopy(point,pv);
    } else {
        pv[0] = rcom[body][0]+point[0];
        pv[1] = rcom[body][1]+point[1];
        pv[2] = rcom[body][2]+point[2];
    }
    sdvcross(rotchg,pv,linchg);
    sdvadd(linchg,lin,linchg);
}

void sdacc(int body,
    double pt[3],
    double accel[3])
{
/*
Return linear acceleration a point of the specified body.

*/
    double pv[3];

    if (sdchkbnum(32,body) != 0) {
        return;
    }
    if (roustate != 3) {
        sdseterr(32,24);
        return;
    }
    if (body  ==  -1) {
        accel[0] = 0.;
        accel[1] = 0.;
        accel[2] = 0.;
    } else {
        pv[0] = pt[0]*dyad[body][0][0]+pt[1]*dyad[body][0][1]+pt[2]*dyad[body][0
          ][2];
        pv[1] = pt[0]*dyad[body][1][0]+pt[1]*dyad[body][1][1]+pt[2]*dyad[body][1
          ][2];
        pv[2] = pt[0]*dyad[body][2][0]+pt[1]*dyad[body][2][1]+pt[2]*dyad[body][2
          ][2];
        accel[0] = anb[body][0]+pv[0]*cnb[body][0][0]+pv[1]*cnb[body][0][1]+pv[2
          ]*cnb[body][0][2];
        accel[1] = anb[body][1]+pv[0]*cnb[body][1][0]+pv[1]*cnb[body][1][1]+pv[2
          ]*cnb[body][1][2];
        accel[2] = anb[body][2]+pv[0]*cnb[body][2][0]+pv[1]*cnb[body][2][1]+pv[2
          ]*cnb[body][2][2];
    }
}

void sdangacc(int body,
    double aacc[3])
{
/*
Return angular acceleration of the body.

*/

    if (sdchkbnum(33,body) != 0) {
        return;
    }
    if (roustate != 3) {
        sdseterr(33,24);
        return;
    }
    if (body == -1) {
        aacc[0] = 0.;
        aacc[1] = 0.;
        aacc[2] = 0.;
    } else {
        aacc[0] = onb[body][0];
        aacc[1] = onb[body][1];
        aacc[2] = onb[body][2];
    }
}

void sdgrav(double gravin[3])
{

    sdseterr(1,19);
    roustate = 0;
}

void sdmass(int body,
    double massin)
{

    if (sdchkbnum(2,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(2,15);
        return;
    }
    if (mkq[body] != 0) {
        mk[body] = massin;
        mkq[body] = 3;
    } else {
        sdseterr(2,19);
    }
    roustate = 0;
}

void sdiner(int body,
    double inerin[3][3])
{
    int anyques;

    if (sdchkbnum(3,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(3,15);
        return;
    }
    anyques = 0;
    if (ikq[body][0][0]  !=  0) {
        ik[body][0][0] = inerin[0][0];
        ikq[body][0][0] = 3;
        anyques = 1;
    }
    if (ikq[body][0][1]  !=  0) {
        ik[body][0][1] = inerin[0][1];
        ikq[body][0][1] = 3;
        ik[body][1][0] = inerin[0][1];
        ikq[body][1][0] = 3;
        anyques = 1;
    }
    if (ikq[body][0][2]  !=  0) {
        ik[body][0][2] = inerin[0][2];
        ikq[body][0][2] = 3;
        ik[body][2][0] = inerin[0][2];
        ikq[body][2][0] = 3;
        anyques = 1;
    }
    if (ikq[body][1][1]  !=  0) {
        ik[body][1][1] = inerin[1][1];
        ikq[body][1][1] = 3;
        anyques = 1;
    }
    if (ikq[body][1][2]  !=  0) {
        ik[body][1][2] = inerin[1][2];
        ikq[body][1][2] = 3;
        ik[body][2][1] = inerin[1][2];
        ikq[body][2][1] = 3;
        anyques = 1;
    }
    if (ikq[body][2][2]  !=  0) {
        ik[body][2][2] = inerin[2][2];
        ikq[body][2][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(3,19);
    }
    roustate = 0;
}

void sdbtj(int joint,
    double btjin[3])
{
    int anyques;

    if (sdchkjnum(4,joint) != 0) {
        return;
    }
    anyques = 0;
    if (rkq[joint][0]  !=  0) {
        rk[joint][0] = btjin[0];
        rkq[joint][0] = 3;
        anyques = 1;
    }
    if (rkq[joint][1]  !=  0) {
        rk[joint][1] = btjin[1];
        rkq[joint][1] = 3;
        anyques = 1;
    }
    if (rkq[joint][2]  !=  0) {
        rk[joint][2] = btjin[2];
        rkq[joint][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(4,19);
    }
    roustate = 0;
}

void sditj(int joint,
    double itjin[3])
{
    int anyques;

    if (sdchkjnum(5,joint) != 0) {
        return;
    }
    anyques = 0;
    if (riq[joint][0]  !=  0) {
        ri[joint][0] = itjin[0];
        riq[joint][0] = 3;
        anyques = 1;
    }
    if (riq[joint][1]  !=  0) {
        ri[joint][1] = itjin[1];
        riq[joint][1] = 3;
        anyques = 1;
    }
    if (riq[joint][2]  !=  0) {
        ri[joint][2] = itjin[2];
        riq[joint][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(5,19);
    }
    roustate = 0;
}

void sdpin(int joint,
    int pinno,
    double pinin[3])
{
    int anyques,offs;

    if (sdchkjpin(6,joint,pinno) != 0) {
        return;
    }
    anyques = 0;
    offs = firstq[joint]+pinno;
    if (jtype[joint] == 21) {
        offs = offs+3;
    }
    if (jtype[joint] == 11) {
        offs = offs+1;
    }
    if (pinq[offs][0]  !=  0) {
        pin[offs][0] = pinin[0];
        pinq[offs][0] = 3;
        anyques = 1;
    }
    if (pinq[offs][1]  !=  0) {
        pin[offs][1] = pinin[1];
        pinq[offs][1] = 3;
        anyques = 1;
    }
    if (pinq[offs][2]  !=  0) {
        pin[offs][2] = pinin[2];
        pinq[offs][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(6,19);
    }
    roustate = 0;
}

void sdpres(int joint,
    int axis,
    int presin)
{
    int anyques;

    if (sdchkjaxis(37,joint,axis) != 0) {
        return;
    }
    if ((presin != 0) && (presin != 1)) {
        sdseterr(37,20);
    }
    anyques = 0;
    if (presq[sdindx(joint,axis)]  !=  0) {
        if (presin  !=  0) {
            pres[sdindx(joint,axis)] = 1.;
        } else {
            pres[sdindx(joint,axis)] = 0.;
        }
        presq[sdindx(joint,axis)] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(37,19);
    }
    wwflg = 0;
}

void sdconschg(void)
{

    wwflg = 0;
}

void sdstab(double velin,
    double posin)
{

    stabvel = velin;
    stabvelq = 3;
    stabpos = posin;
    stabposq = 3;
}

void sdgetgrav(double gravout[3])
{

    gravout[0] = grav[0];
    gravout[1] = grav[1];
    gravout[2] = grav[2];
}

void sdgetmass(int body,
    double *massout)
{

    if (sdchkbnum(40,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(40,15);
        return;
    }
    *massout = mk[body];
}

void sdgetiner(int body,
    double inerout[3][3])
{

    if (sdchkbnum(41,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(41,15);
        return;
    }
    inerout[0][0] = ik[body][0][0];
    inerout[0][1] = ik[body][0][1];
    inerout[0][2] = ik[body][0][2];
    inerout[1][0] = ik[body][1][0];
    inerout[1][1] = ik[body][1][1];
    inerout[1][2] = ik[body][1][2];
    inerout[2][0] = ik[body][2][0];
    inerout[2][1] = ik[body][2][1];
    inerout[2][2] = ik[body][2][2];
}

void sdgetbtj(int joint,
    double btjout[3])
{

    if (sdchkjnum(42,joint) != 0) {
        return;
    }
    btjout[0] = rk[joint][0];
    btjout[1] = rk[joint][1];
    btjout[2] = rk[joint][2];
}

void sdgetitj(int joint,
    double itjout[3])
{

    if (sdchkjnum(43,joint) != 0) {
        return;
    }
    itjout[0] = ri[joint][0];
    itjout[1] = ri[joint][1];
    itjout[2] = ri[joint][2];
}

void sdgetpin(int joint,
    int pinno,
    double pinout[3])
{
    int offs;

    if (sdchkjpin(44,joint,pinno) != 0) {
        return;
    }
    offs = firstq[joint]+pinno;
    if (jtype[joint] == 21) {
        offs = offs+3;
    }
    if (jtype[joint] == 11) {
        offs = offs+1;
    }
    pinout[0] = pin[offs][0];
    pinout[1] = pin[offs][1];
    pinout[2] = pin[offs][2];
}

void sdgetpres(int joint,
    int axis,
    int *presout)
{

    if (sdchkjaxis(45,joint,axis) != 0) {
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        *presout = 1;
    } else {
        *presout = 0;
    }
}

void sdgetstab(double *velout,
    double *posout)
{

    *velout = stabvel;
    *posout = stabpos;
}

void sdinfo(int info[50])
{

    info[0] = ground;
    info[1] = nbod;
    info[2] = ndof;
    info[3] = ncons;
    info[4] = nloop;
    info[5] = nldof;
    info[6] = nloopc;
    info[7] = nball;
    info[8] = nlball;
    info[9] = npres;
    info[10] = nuser;
    info[11] = 11;
/* info entries from 12-49 are reserved */
}

void sdjnt(int joint,
    int info[50],
    int tran[6])
{
    int i,offs;

    if (sdchkjnum(48,joint) != 0) {
        return;
    }
    info[0] = jtype[joint];
    info[1] = 0;
    offs = 0;
    info[2] = inb[joint];
    info[3] = outb[joint];
    info[4] = njntdof[joint];
    info[5] = njntc[joint];
    info[6] = njntp[joint];
    info[7] = firstq[joint];
    info[8] = ballq[joint];
    info[9] = firstm[joint];
    info[10] = firstp[joint];
/* info entries from 11-49 are reserved */

    for (i = 0; i <= 5; i++) {
        if (i  <  njntdof[joint]) {
            tran[i] = trans[offs+firstq[joint]+i];
        } else {
            tran[i] = -1;
        }
    }
}

void sdcons(int consno,
    int info[50])
{

    if (sdchkucnum(49,consno) != 0) {
        return;
    }
    info[0] = 1;
    info[1] = firstu[consno];
/* info entries from 2-49 are reserved */
}

void sdgentime(int *gentm)
{

    *gentm = 210648;
}
/*
Done. CPU seconds used: 0.03  Memory used: 1728512 bytes.
Equation complexity:
  sdstate:   332 adds   451 multiplies     4 divides   307 assignments
  sdderiv:  4609 adds  4840 multiplies   170 divides  5526 assignments
  sdresid:   568 adds   545 multiplies     0 divides   391 assignments
  sdreac:    222 adds   135 multiplies     0 divides   147 assignments
  sdmom:      89 adds   106 multiplies     0 divides    29 assignments
  sdsys:     138 adds   195 multiplies     0 divides    46 assignments
*/
