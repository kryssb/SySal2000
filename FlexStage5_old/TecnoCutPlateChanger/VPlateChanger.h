#ifndef __VPLATECHANGERCLASS_H_
#define __VPLATECHANGERCLASS_H_

#include "id.h"

class VPlateChanger
{
	public:
	
		virtual HRESULT _stdcall LoadPlate(Identifier id, BYTE *pppp) = 0;
		virtual HRESULT _stdcall UnloadPlate() = 0;
		/*
			Only methods used also by the COM object should be declared HRESULT _stdcall.
			Other methods need not use this modifier.
			Example:

			virtual int get_Brick() = 0;
		*/
		virtual int GetStatusBits() = 0;
		virtual bool GoToLoadingPosition() = 0;

		/* qui vanno le versioni virtuali di tutte le funzioni che rispondono ai bottoni del Monitor, come GetStatusBits */
};

#endif