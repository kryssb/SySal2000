/*************************************************************
 *																		       *
 * 	  Code developed by Salerno Emulsion Group in 1996     *
 *																		       *
 *************************************************************/

#ifndef POLYFIT_H
#define POLYFIT_H

int Linear_Fit(int NPoints, double *X, double *Y, double *C0, double *C1, double *Sigma = 0);

int Parabolic_Fit(int NPoints, double *X, double *Y, double *C0, double *C1, double *C2, double *Sigma = 0);

int MultiLinearFit(int NPoints, int NVars, double *Data, double *Out);

#endif

