#define MAXPOINTS 64

EdbAffine2D aff;

affine(int BR, int flag=0)
{
     // if flag==2 : do not permit scaling of patterns

// This is the matrix formulation for the transformation that involves scaling
// by r in the x-direction, by s in the y-direction, rotations by theta and phi,
// and translations by e and f.
//
// | x |     | r cos(theta)   -s sin(phi) | | x |   | e |
// |   | --> |                            | |   | + |   |
// | y |     | r sin(theta)    s cos(phi) | | y |   | f |
//
//   The output is in the IFS formalism:
//
//    * r - scaling/reflection in the x direction
//    * s - scaling/reflection in the y direction
//    * theta - rotation of horizontal lines
//    * phi - rotation of vertical lines
//    * e - horizontal translation
//    * f - vertical translation
//

   switch ( BR )
   {
      case 32 :
         int npoints = 2 ;
         char* str_src ="LATERAL MARKS LNGS PL3" ;
         Float_t src_x[MAXPOINTS] = { 141932.1, 141695.0 };
         Float_t src_y[MAXPOINTS] = {  47352.1, 142213.7 };
         char* str_tgt ="LATERAL MARKS LNGS PL2" ; 
         Float_t tgt_x[MAXPOINTS] = { 140725.0, 140690.6 };
         Float_t tgt_y[MAXPOINTS] = {  47477.4, 142315.6 };
         break;

      case 21 :
         int npoints = 2 ;
         char* str_src ="LATERAL MARKS LNGS PL2" ; 
         Float_t src_x[MAXPOINTS] = { 140725.0, 140690.6 };
         Float_t src_y[MAXPOINTS] = {  47477.4, 142315.6 };
         char* str_tgt ="LATERAL MARKS LNGS PL1 REFERENCE"; 
         Float_t tgt_x[MAXPOINTS] = { 122168, 121853 } ;
         Float_t tgt_y[MAXPOINTS] = {   2020,  96828 };
         break;

      case 31 :
         int npoints = 2 ;
         char* str_src ="LATERAL MARKS LNGS PL3" ;
         Float_t src_x[MAXPOINTS] = { 141932.1, 141695.0 };
         Float_t src_y[MAXPOINTS] = {  47352.1, 142213.7 };
         char* str_tgt ="LATERAL MARKS LNGS PL1 REFERENCE"; 
         Float_t tgt_x[MAXPOINTS] = { 122168, 121853 } ;
         Float_t tgt_y[MAXPOINTS] = {   2020,  96828 };
         break;

  }

   printf(" %s  -> %s \n", str_src, str_tgt );
   for (int i=0; i<npoints; i++) 
      printf(" src X[%i] %9.1f Y[%i] %9.1f\t tgt X[%i] %9.1f Y[%i] %9.1f\n",
               i, src_x[i], i, src_y[i], i, tgt_x[i], i, tgt_y[i] );
   aff.Calculate( npoints, src_x, src_y, tgt_x, tgt_y ,flag ) ;
   PrintAffine(aff);
}

PrintAffine(EdbAffine2D aff) 
{
   double a = aff.A11() ;
   double b = aff.A12() ;
   double c = aff.A21() ;
   double d = aff.A22() ;
   double e = aff.B1() ;
   double f = aff.B2() ;

   double theta = atan( c/a ) ;
   double phi   = atan( -b/d );
   double r = a / cos(theta);
   double s = d / cos(phi);

   printf("r: %f   s: %f   theta: %f   phi: %f   e: %.1f   f: %.1f\n",
          r, s, theta, phi, e, f );
//   printf("r: %f   s: %f   theta: %f   phi: %f   e: %.1f   f: %.1f\n",
//         r, s, 180/3.141592*theta, 180/3.141592*phi, e, f );
}
/*
   TPolyLine *pline = new TPolyLine(MAXPOINTS,x0,y0);
   pline->SetFillColor(38);
   pline->SetLineColor(2);
   pline->SetLineWidth(4);
   pline->Draw("f");
   pline->Draw();

   TPolyLine *pline2 = new TPolyLine(MAXPOINTS,x1,y1);
   pline2->SetFillColor(37);
   pline2->SetLineColor(3);
   pline2->SetLineWidth(4);
   pline2->Draw("f");
   pline2->Draw("same");
*/
