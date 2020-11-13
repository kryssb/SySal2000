
TGraph *gr, *gr2 , *gr3, *gr4 ;
TGraph2D *g ;

TF2 f2("dist","sqrt(x*x+y*y)",-10,10,-10,10) ;

const int stepx [] = { 0,0,1} ;

spiral ()
{
   int ngiri = 9 ;
   int* n = new int[ngiri] ;

   n[0] =  1 ;
   n[1] =  8 ;
   n[2] = 12 ;
   n[3] = 16 ;
   n[4] = 32 ;
   n[5] = 28 ;
   n[6] = 52 ;
   n[7] = 48 ;
   n[8] = 72 ;

   N = n[0]+n[1]+n[2]+n[3]+n[4]+n[5]+n[6]+n[7]+n[8] ;

   Int_t* x  = new Int_t[N];
	Int_t* y  = new Int_t[N];

   i= 0 ;
//0
   x[i] =  0 ; y[i++] =  0 ;
//1
   x[i] = -1 ; y[i++] =  0 ;
   x[i] = -1 ; y[i++] = -1 ;
   x[i] =  0 ; y[i++] = -1 ;
   x[i] =  1 ; y[i++] = -1 ;
   x[i] =  1 ; y[i++] =  0 ;   
   x[i] =  1 ; y[i++] =  1 ;
   x[i] =  0 ; y[i++] =  1 ;
   x[i] = -1 ; y[i++] =  1 ;
//2
   x[i] = -2 ; y[i++] =  1 ;
   x[i] = -2 ; y[i++] =  0 ;
   x[i] = -2 ; y[i++] = -1 ;
   x[i] = -1 ; y[i++] = -2 ;
   x[i] =  0 ; y[i++] = -2 ;   
   x[i] =  1 ; y[i++] = -2 ;
   x[i] =  2 ; y[i++] = -1 ;
   x[i] =  2 ; y[i++] =  0 ;
   x[i] =  2 ; y[i++] =  1 ;
   x[i] =  1 ; y[i++] =  2 ;
   x[i] =  0 ; y[i++] =  2 ;   
   x[i] = -1 ; y[i++] =  2 ;
//3
   x[i] = -2 ; y[i++] =  2 ;
   x[i] = -3 ; y[i++] =  1 ;
   x[i] = -3 ; y[i++] =  0 ;
   x[i] = -3 ; y[i++] = -1 ;
   x[i] = -2 ; y[i++] = -2 ;   
   x[i] = -1 ; y[i++] = -3 ;
   x[i] =  0 ; y[i++] = -3 ;
   x[i] =  1 ; y[i++] = -3 ;
   x[i] =  2 ; y[i++] = -2 ;
   x[i] =  3 ; y[i++] = -1 ;
   x[i] =  3 ; y[i++] =  0 ;   
   x[i] =  3 ; y[i++] =  1 ;
   x[i] =  2 ; y[i++] =  2 ;
   x[i] =  1 ; y[i++] =  3 ;
   x[i] =  0 ; y[i++] =  3 ;
   x[i] = -1 ; y[i++] =  3 ;
//4
   x[i] = -2 ; y[i++] =  3 ;
   x[i] = -3 ; y[i++] =  3 ;
   x[i] = -3 ; y[i++] =  2 ;
   x[i] = -4 ; y[i++] =  2 ;
   x[i] = -4 ; y[i++] =  1 ;   
   x[i] = -4 ; y[i++] =  0 ;
   x[i] = -4 ; y[i++] = -1 ;
   x[i] = -4 ; y[i++] = -2 ;
   x[i] = -3 ; y[i++] = -2 ;
   x[i] = -3 ; y[i++] = -3 ;
   x[i] = -2 ; y[i++] = -3 ;
   x[i] = -2 ; y[i++] = -4 ;
   x[i] = -1 ; y[i++] = -4 ;
   x[i] =  0 ; y[i++] = -4 ;
   x[i] =  1 ; y[i++] = -4 ;
   x[i] =  2 ; y[i++] = -4 ;
   x[i] =  2 ; y[i++] = -3 ;
   x[i] =  3 ; y[i++] = -3 ;
   x[i] =  3 ; y[i++] = -2 ;
   x[i] =  4 ; y[i++] = -2 ;
   x[i] =  4 ; y[i++] = -1 ;
   x[i] =  4 ; y[i++] =  0 ;
   x[i] =  4 ; y[i++] =  1 ;
   x[i] =  4 ; y[i++] =  2 ;
   x[i] =  3 ; y[i++] =  2 ;
   x[i] =  3 ; y[i++] =  3 ;
   x[i] =  2 ; y[i++] =  3 ;
   x[i] =  2 ; y[i++] =  4 ;
   x[i] =  1 ; y[i++] =  4 ;
   x[i] =  0 ; y[i++] =  4 ;
   x[i] = -1 ; y[i++] =  4 ;
   x[i] = -2 ; y[i++] =  4 ;
//5
   x[i] = -3 ; y[i++] =  4 ;
   x[i] = -4 ; y[i++] =  3 ;
   x[i] = -5 ; y[i++] =  2 ;
   x[i] = -5 ; y[i++] =  1 ;
   x[i] = -5 ; y[i++] =  0 ;
   x[i] = -5 ; y[i++] = -1 ;
   x[i] = -5 ; y[i++] = -2 ;
   x[i] = -4 ; y[i++] = -3 ;
   x[i] = -3 ; y[i++] = -4 ;
   x[i] = -2 ; y[i++] = -5 ;
   x[i] = -1 ; y[i++] = -5 ;
   x[i] =  0 ; y[i++] = -5 ;
   x[i] =  1 ; y[i++] = -5 ;
   x[i] =  2 ; y[i++] = -5 ;
   x[i] =  3 ; y[i++] = -4 ;
   x[i] =  4 ; y[i++] = -3 ;
   x[i] =  5 ; y[i++] = -2 ;
   x[i] =  5 ; y[i++] = -1 ;
   x[i] =  5 ; y[i++] =  0 ;
   x[i] =  5 ; y[i++] =  1 ;
   x[i] =  5 ; y[i++] =  2 ;
   x[i] =  4 ; y[i++] =  3 ;
   x[i] =  3 ; y[i++] =  4 ;
   x[i] =  2 ; y[i++] =  5 ;
   x[i] =  1 ; y[i++] =  5 ;
   x[i] =  0 ; y[i++] =  5 ;
   x[i] = -1 ; y[i++] =  5 ;
   x[i] = -2 ; y[i++] =  5 ;
//6
   x[i] = -3 ; y[i++] =  5 ;
   x[i] = -4 ; y[i++] =  5 ;
   x[i] = -4 ; y[i++] =  4 ;
   x[i] = -5 ; y[i++] =  4 ;
   x[i] = -5 ; y[i++] =  3 ;
   x[i] = -6 ; y[i++] =  3 ;
   x[i] = -6 ; y[i++] =  2 ;
   x[i] = -6 ; y[i++] =  1 ;
   x[i] = -6 ; y[i++] =  0 ;
   x[i] = -7 ; y[i++] =  0 ;
   x[i] = -6 ; y[i++] = -1 ;
   x[i] = -6 ; y[i++] = -2 ;
   x[i] = -6 ; y[i++] = -3 ;
   x[i] = -5 ; y[i++] = -3 ;
   x[i] = -5 ; y[i++] = -4 ;
   x[i] = -4 ; y[i++] = -4 ;
   x[i] = -4 ; y[i++] = -5 ;
   x[i] = -3 ; y[i++] = -5 ;
   x[i] = -3 ; y[i++] = -6 ;
   x[i] = -2 ; y[i++] = -6 ;
   x[i] = -1 ; y[i++] = -6 ;
   x[i] =  0 ; y[i++] = -6 ;
   x[i] =  0 ; y[i++] = -7 ;
   x[i] =  1 ; y[i++] = -6 ;
   x[i] =  2 ; y[i++] = -6 ;
   x[i] =  3 ; y[i++] = -6 ;
   x[i] =  3 ; y[i++] = -5 ;
   x[i] =  4 ; y[i++] = -5 ;
   x[i] =  4 ; y[i++] = -4 ;
   x[i] =  5 ; y[i++] = -4 ;
   x[i] =  5 ; y[i++] = -3 ;
   x[i] =  6 ; y[i++] = -3 ;
   x[i] =  6 ; y[i++] = -2 ;
   x[i] =  6 ; y[i++] = -1 ;
   x[i] =  6 ; y[i++] =  0 ;
   x[i] =  7 ; y[i++] =  0 ;
   x[i] =  6 ; y[i++] =  1 ;
   x[i] =  6 ; y[i++] =  2 ;
   x[i] =  6 ; y[i++] =  3 ;
   x[i] =  5 ; y[i++] =  3 ;
   x[i] =  5 ; y[i++] =  4 ;
   x[i] =  4 ; y[i++] =  4 ;
   x[i] =  4 ; y[i++] =  5 ;
   x[i] =  3 ; y[i++] =  5 ;
   x[i] =  3 ; y[i++] =  6 ;
   x[i] =  2 ; y[i++] =  6 ;
   x[i] =  1 ; y[i++] =  6 ;
   x[i] =  0 ; y[i++] =  6 ;
   x[i] =  0 ; y[i++] =  7 ;
   x[i] = -1 ; y[i++] =  6 ;
   x[i] = -2 ; y[i++] =  6 ;
   x[i] = -3 ; y[i++] =  6 ;
//7
   x[i] = -4 ; y[i++] =  6 ;
   x[i] = -5 ; y[i++] =  5 ;
   x[i] = -6 ; y[i++] =  4 ;
   x[i] = -7 ; y[i++] =  3 ;
   x[i] = -7 ; y[i++] =  2 ;
   x[i] = -7 ; y[i++] =  1 ;
   x[i] = -8 ; y[i++] =  1 ;
   x[i] = -8 ; y[i++] =  0 ;
   x[i] = -8 ; y[i++] = -1 ;
   x[i] = -7 ; y[i++] = -1 ;
   x[i] = -7 ; y[i++] = -2 ;
   x[i] = -7 ; y[i++] = -3 ;
   x[i] = -6 ; y[i++] = -4 ;
   x[i] = -5 ; y[i++] = -5 ;
   x[i] = -4 ; y[i++] = -6 ;
   x[i] = -3 ; y[i++] = -7 ;
   x[i] = -2 ; y[i++] = -7 ;
   x[i] = -1 ; y[i++] = -7 ;
   x[i] = -1 ; y[i++] = -8 ;
   x[i] =  0 ; y[i++] = -8 ;
   x[i] =  1 ; y[i++] = -8 ;
   x[i] =  1 ; y[i++] = -7 ;
   x[i] =  2 ; y[i++] = -7 ;
   x[i] =  3 ; y[i++] = -7 ;
   x[i] =  4 ; y[i++] = -6 ;
   x[i] =  5 ; y[i++] = -5 ;
   x[i] =  6 ; y[i++] = -4 ;
   x[i] =  7 ; y[i++] = -3 ;
   x[i] =  7 ; y[i++] = -2 ;
   x[i] =  7 ; y[i++] = -1 ;
   x[i] =  8 ; y[i++] = -1 ;
   x[i] =  8 ; y[i++] =  0 ;
   x[i] =  8 ; y[i++] =  1 ;
   x[i] =  7 ; y[i++] =  1 ;
   x[i] =  7 ; y[i++] =  2 ;
   x[i] =  7 ; y[i++] =  3 ;
   x[i] =  6 ; y[i++] =  4 ;
   x[i] =  5 ; y[i++] =  5 ;
   x[i] =  4 ; y[i++] =  6 ;
   x[i] =  3 ; y[i++] =  7 ;
   x[i] =  2 ; y[i++] =  7 ;
   x[i] =  1 ; y[i++] =  7 ;
   x[i] =  1 ; y[i++] =  8 ;
   x[i] =  0 ; y[i++] =  8 ;
   x[i] = -1 ; y[i++] =  8 ;
   x[i] = -1 ; y[i++] =  7 ;
   x[i] = -2 ; y[i++] =  7 ;
   x[i] = -3 ; y[i++] =  7 ;
//8
   x[i] = -4 ; y[i++] =  7 ;
   x[i] = -5 ; y[i++] =  7 ;
   x[i] = -5 ; y[i++] =  6 ;
   x[i] = -6 ; y[i++] =  6 ;
   x[i] = -6 ; y[i++] =  5 ;
   x[i] = -7 ; y[i++] =  5 ;
   x[i] = -7 ; y[i++] =  4 ;
   x[i] = -8 ; y[i++] =  4 ;
   x[i] = -8 ; y[i++] =  3 ;
   x[i] = -8 ; y[i++] =  2 ;

   x[i] = -9 ; y[i++] =  2 ;
   x[i] = -9 ; y[i++] =  1 ;
   x[i] = -9 ; y[i++] =  0 ;
   x[i] = -9 ; y[i++] = -1 ;
   x[i] = -9 ; y[i++] = -2 ;
   x[i] = -8 ; y[i++] = -2 ;
   x[i] = -8 ; y[i++] = -3 ;
   x[i] = -8 ; y[i++] = -4 ;
   x[i] = -7 ; y[i++] = -4 ;
   x[i] = -7 ; y[i++] = -5 ;

   x[i] = -6 ; y[i++] = -5 ;
   x[i] = -6 ; y[i++] = -6 ;
   x[i] = -5 ; y[i++] = -6 ;
   x[i] = -5 ; y[i++] = -7 ;
   x[i] = -4 ; y[i++] = -7 ;
   x[i] = -4 ; y[i++] = -8 ;
   x[i] = -3 ; y[i++] = -8 ;
   x[i] = -2 ; y[i++] = -8 ;
   x[i] = -2 ; y[i++] = -9 ;
   x[i] = -1 ; y[i++] = -9 ;
   x[i] =  0 ; y[i++] = -9 ;
   x[i] =  1 ; y[i++] = -9 ;
   x[i] =  2 ; y[i++] = -9 ;
   x[i] =  2 ; y[i++] = -8 ;
   x[i] =  3 ; y[i++] = -8 ;
   x[i] =  4 ; y[i++] = -8 ;
   x[i] =  4 ; y[i++] = -7 ;
   x[i] =  5 ; y[i++] = -7 ;
   x[i] =  5 ; y[i++] = -6 ;
   x[i] =  6 ; y[i++] = -6 ;
   x[i] =  6 ; y[i++] = -5 ;
   x[i] =  7 ; y[i++] = -5 ;
   x[i] =  7 ; y[i++] = -4 ;
   x[i] =  8 ; y[i++] = -4 ;
   x[i] =  8 ; y[i++] = -3 ;
   x[i] =  8 ; y[i++] = -2 ;
   x[i] =  9 ; y[i++] = -2 ;
   x[i] =  9 ; y[i++] = -1 ;
   x[i] =  9 ; y[i++] =  0 ;
   x[i] =  9 ; y[i++] =  1 ;
   x[i] =  9 ; y[i++] =  2 ;
   x[i] =  8 ; y[i++] =  2 ;
   x[i] =  8 ; y[i++] =  3 ;
   x[i] =  8 ; y[i++] =  4 ;
   x[i] =  7 ; y[i++] =  4 ;
   x[i] =  7 ; y[i++] =  5 ;
   x[i] =  6 ; y[i++] =  5 ;
   x[i] =  6 ; y[i++] =  6 ;
   x[i] =  5 ; y[i++] =  6 ;
   x[i] =  5 ; y[i++] =  7 ;
   x[i] =  4 ; y[i++] =  7 ;
   x[i] =  4 ; y[i++] =  8 ;
   x[i] =  3 ; y[i++] =  8 ;
   x[i] =  2 ; y[i++] =  8 ;
   x[i] =  2 ; y[i++] =  9 ;
   x[i] =  1 ; y[i++] =  9 ;
   x[i] =  0 ; y[i++] =  9 ;
   x[i] = -1 ; y[i++] =  9 ;
   x[i] = -2 ; y[i++] =  9 ;
   x[i] = -2 ; y[i++] =  8 ;
   x[i] = -3 ; y[i++] =  8 ;
   x[i] = -4 ; y[i++] =  8 ;


//--
//   gStyle->SetPalette(0) ;
//   f2->Draw("colZ4");

   gr = new TGraph(N, x, y) ;
   gr->SetMarkerStyle(20);
   gr->SetMarkerSize(1);
   gr->Draw("apl");
//   gr->Draw("same pl");

   printf("x = %2d,", x[0]);
   for (int i=1;i<N;i++)
   {
      int nsum = 0;
      for (int j=0;j<ngiri;j++) {
         nsum += n[j] ;
         if( i == nsum )
            printf("\n    ");
      }
      printf("%2d,", x[i]);
   }
   printf("\ny = %2d,", y[0]);
   for (int i=1;i<N;i++)
   {
      int nsum = 0;
      for (int j=0;j<ngiri;j++) {
         nsum += n[j] ;
         if( i == nsum )
           printf("\n    ");
      }
      printf("%2d,", y[i]);
   }
   printf("\n");

//---

   Float_t* id       = new Float_t[N];
	Float_t* dist     = new Float_t[N];
	Int_t* intdist    = new Int_t[N];

   for (int i=0;i<N;i++)
   {
      id[i] = i;
      dist[i] = sqrt( pow( x[i],2) + pow( y[i],2) ) ;
      intdist[i] = (int) ( 0.5 + dist[i]) ;
   }
   gr2 = new TGraph(N, id, dist) ;
   gr2->SetMarkerStyle(20);
   gr2->SetMarkerSize(0);
   new TCanvas() ;
   gr2->Draw("apl");


   //******************************

//NEW ORDER

   int nn=0;

   Int_t* xx  = new Int_t[N];
	Int_t* yy  = new Int_t[N];

   for( float dd=0; dd<20; dd+= 1 )
   {

      for( int j=0; j<N; j++ )
      {
         if( dist[j] >= dd && dist[j] <  dd+1 ) {
            printf("%f %f %d %d %f\n", dd, dist[j], x[j], y[j], dd-dist[j] ) ;
            xx[nn] = x[j];
            yy[nn] = y[j];
            nn++;
         }
      }
   }

   cout << nn << endl ;

   gr3 = new TGraph(N,xx,yy) ;
   gr3->SetMarkerStyle(20);
   gr3->SetMarkerSize(0);
   new TCanvas() ;
   gr3->Draw("apl");

   Float_t* id4       = new Float_t[N];
	Float_t* dist4     = new Float_t[N];

   for (int i=0;i<N;i++)
   {
      id4[i] = i;
      dist4[i] = sqrt( pow( xx[i],2) + pow( yy[i],2) ) ;
   }
   gr4 = new TGraph(N, id4, dist4) ;
   gr4->SetMarkerStyle(20);
   gr4->SetMarkerSize(0);
   new TCanvas() ;
   gr4->Draw("apl");


}
