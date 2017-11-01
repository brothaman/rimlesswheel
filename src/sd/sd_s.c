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
#include <math.h>

/* These routines are passed to sdroot. */

void sdposfunc(double vars[8],
    double param[1],
    double resid[11])
{
    int i;
    double pos[9],vel[8];

    for (i = 0; i < 8; i++) {
        vel[i] = 0.;
    }
    sdang2st(vars,pos);
    sdstate(param[0],pos,vel);
    sdumotion(param[0],pos,vel);
    sdperr(resid);
}

void sdvelfunc(double vars[8],
    double param[10],
    double resid[11])
{

    sdstate(param[9],param,vars);
    sdumotion(param[9],param,vars);
    sdverr(resid);
}

void sdstatfunc(double vars[8],
    double param[9],
    double resid[19])
{
    double pos[9],qdotdum[9];

    sdang2st(vars,pos);
    sdstate(param[8],pos,param);
    sdumotion(param[8],pos,param);
    sduforce(param[8],pos,param);
    sdperr(resid);
    sdderiv(qdotdum,&resid[11]);
}

void sdstdyfunc(double vars[16],
    double param[1],
    double resid[30])
{
    double pos[9],qdotdum[9];

    sdang2st(vars,pos);
    sdstate(param[0],pos,&vars[8]);
    sdumotion(param[0],pos,&vars[8]);
    sduforce(param[0],pos,&vars[8]);
    sdperr(resid);
    sdverr(&resid[11]);
    sdderiv(qdotdum,&resid[22]);
}

/* This routine is passed to the integrator. */

void sdmotfunc(double time,
    double state[17],
    double dstate[17],
    double param[1],
    int *status)
{
    double err[11];
    int i;

    sdstate(time,state,&state[9]);
    sdumotion(time,state,&state[9]);
    sduforce(time,state,&state[9]);
    sdderiv(dstate,&dstate[9]);
    *status = 1;
    sdverr(err);
    for (i = 0; i < 11; i++) {
        if (fabs(err[i]) > param[0]) {
            return;
        }
    }
    sdperr(err);
    for (i = 0; i < 11; i++) {
        if (fabs(err[i]) > param[0]) {
            return;
        }
    }
    *status = 0;
}

/* This routine performs assembly analysis. */

void sdassemble(double time,
    double state[17],
    int lock[8],
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double perrs[11],param[1];
    int i;
    double jw[88],dw[722],rw[149];
    int iw[76],rooterr;

    sdgentime(&i);
    if (i != 210648) {
        sdseterr(50,42);
    }
    param[0] = time;
    sdst2ang(state,state);
    sdroot(sdposfunc,state,param,11,8,0,lock,tol,tol,maxevals,
      jw,dw,rw,iw,perrs,fcnt,&rooterr);
    sdposfunc(state,param,perrs);
    *fcnt = *fcnt+1;
    sdang2st(state,state);
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs initial velocity analysis. */

void sdinitvel(double time,
    double state[17],
    int lock[8],
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double verrs[11],param[10];
    int i;
    double jw[88],dw[722],rw[149];
    int iw[76],rooterr;

    sdgentime(&i);
    if (i != 210648) {
        sdseterr(51,42);
    }
    for (i = 0; i < 9; i++) {
        param[i] = state[i];
    }
    param[9] = time;
    sdroot(sdvelfunc,&state[9],param,11,8,0,lock,tol,tol,maxevals,
      jw,dw,rw,iw,verrs,fcnt,&rooterr);
    sdvelfunc(&state[9],param,verrs);
    *fcnt = *fcnt+1;
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs static analysis. */

void sdstatic(double time,
    double state[17],
    int lock[8],
    double ctol,
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double resid[19],param[9],jw[152],dw[1458],rw[205];
    int iw[108],rooterr,i;

    sdgentime(&i);
    if (i != 210648) {
        sdseterr(52,42);
    }
    for (i = 0; i < 8; i++) {
        param[i] = state[9+i];
    }
    param[8] = time;
    sdst2ang(state,state);
    sdroot(sdstatfunc,state,param,19,8,8,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    sdstatfunc(state,param,resid);
    *fcnt = *fcnt+1;
    sdang2st(state,state);
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs steady motion analysis. */

void sdsteady(double time,
    double state[17],
    int lock[16],
    double ctol,
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double resid[30],param[1],vars[16];
    double jw[480],dw[4232],rw[354];
    int iw[184],rooterr,i;

    sdgentime(&i);
    if (i != 210648) {
        sdseterr(53,42);
    }
    param[0] = time;
    sdst2ang(state,vars);
    for (i = 0; i < 8; i++) {
        vars[8+i] = state[9+i];
    }
    sdroot(sdstdyfunc,vars,param,30,16,8,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    sdstdyfunc(vars,param,resid);
    *fcnt = *fcnt+1;
    sdang2st(vars,state);
    for (i = 0; i < 8; i++) {
        state[9+i] = vars[8+i];
    }
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs state integration. */

void sdmotion(double *time,
    double state[17],
    double dstate[17],
    double dt,
    double ctol,
    double tol,
    int *flag,
    int *err)
{
    static double step;
    double work[102],ttime,param[1];
    int vintgerr,which,ferr,i;

    sdgentime(&i);
    if (i != 210648) {
        sdseterr(54,42);
    }
    param[0] = ctol;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        step = dt;
        *flag = 0;
    }
    if (step <= 0.) {
        step = dt;
    }
    sdvinteg(sdmotfunc,&ttime,state,dstate,param,dt,&step,17,tol,work,&vintgerr,
      &which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

void sdfmotion(double *time,
    double state[17],
    double dstate[17],
    double dt,
    double ctol,
    int *flag,
    double *errest,
    int *err)
{
    double work[68],ttime,param[1];
    int ferr,i;

    sdgentime(&i);
    if (i != 210648) {
        sdseterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    sdfinteg(sdmotfunc,&ttime,state,dstate,param,dt,17,work,errest,&ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
