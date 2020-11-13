#include "FrameGrabber.h"
#include "Stage.h"
#include "Objective.h"

#include <direct.h>
#include <stdio.h>
#include <math.h>


void MovieMaker(IStage* iSt, IFrameGrabber* iFG, IObjective* iObj, int nstep = 30 , float zstep = -2.0)
{

   for ( int i=0; i<nstep; i++ )
   {
      float z = 0 ;
      iSt->GetPos( 2, &z);
      
      BYTE* pImage ;
      iFG->FreezeFrame( &pImage ) ;

 	  _mkdir("c:\\images") ;
      char filename[256];
      sprintf( filename, "c:\\images\\im%02d_%08.1f.bmp", i, z );
      
      FILE *out = fopen( filename, "wb" );  // binary needed otherwise 0x0A becomes 0x0D0A
      if(!out) 
         return ;

	  CameraSpec CSP;
      iObj->GetSpecs((CameraSpec *)&CSP);
	  int width  = CSP.Width  ; //1280 ;
	  int height = CSP.Height ; //1024 ;

      // microsoft windows and ibm os/2 picture bitmap (*.bmp) 8-bit greyscale
      // GS 
      typedef struct {
         unsigned short int type;			// Magic identifier            
         unsigned int size;					// Complete file size in bytes          
         unsigned int reserved;
         unsigned int offset;					// Offset from the beginning of file to bitmap data, bytes 
      } HEADER;

      typedef struct {
         unsigned int size;               // Header size in bytes      
         int width;						      // Width of image
         int height;						      // Height of image 
         unsigned short int planes;       // Number of colour planes   
         unsigned short int bits;         // Bits per pixel (1,4,8,16,24,32)         
         unsigned int compression;        // Compression type  (0=none)        
         unsigned int imagesize;          // Size of bitmap data in bytes (rounded to the next 4 byte boundary)       
         int xresolution, yresolution;    // Pixels per meter          
         unsigned int ncolours;           // Number of colours  (for 8-bit is 0x100)       
         unsigned int importantcolours;   // Important colours (=number of colors id every color is important)      
      } INFOHEADER;

      HEADER hdr ;
      hdr.reserved = 0 ;
      INFOHEADER ihdr ;
      hdr.type    = 19778 ;							        
      ihdr.width  = width  ;						
      ihdr.height = height ;					
      ihdr.size   = 40 ;							
      ihdr.bits   = 8  ;								        
	  ihdr.ncolours  = pow( 2. , ihdr.bits ) ;
      hdr.offset     = 14 + ihdr.size + 4 * ihdr.ncolours ;	
      ihdr.imagesize = ihdr.width*ihdr.height*ihdr.bits/8 ;   //should be rounded to next 4 byte boudary
      hdr.size       = hdr.offset + ihdr.imagesize ;	
      ihdr.planes = 1 ;
      ihdr.compression = 0 ;
      ihdr.xresolution = 655360000 ;
      ihdr.yresolution = 655360000 ;
      ihdr.importantcolours = ihdr.ncolours ;

      int ibyte=0;

#     define writebmp(var)   printf("\n%04X\t",ibyte); for(int i=0;i<sizeof(var);i++) { printf("%02X ",(int)(char)var); ibyte += fprintf(out,"%c",var); var>>=8; }
      writebmp(hdr.type);			
      writebmp(hdr.size);			
      writebmp(hdr.reserved);		
      writebmp(hdr.offset);			
      writebmp(ihdr.size);			
      writebmp(ihdr.width);			
      writebmp(ihdr.height);		
      writebmp(ihdr.planes);
      writebmp(ihdr.bits);
      writebmp(ihdr.compression);
      writebmp(ihdr.imagesize);
      writebmp(ihdr.xresolution);
      writebmp(ihdr.yresolution);
      writebmp(ihdr.ncolours);
      writebmp(ihdr.importantcolours);
      for(int i=0;i<256;i++) 
         ibyte += fprintf( out, "%c%c%c%c", i, i, i, 0 ); 

	   fwrite( pImage, width * height, 1, out);
   	
      fclose( out );

      float znew = z + zstep ;

      iSt->PosMove(2, znew, 100, 10000);
      Sleep(100);
   }
}


