#pragma once

namespace Engine
{
	typedef struct tagGraphicDesc
	{	
		enum WINMODE { WINMODE_FULL, WINMODE_WIN, WINMODE_END };

		HWND			hWnd;
		unsigned int	iSizeX, iSizeY;
		WINMODE			eWinMode;		
		
	}GRAPHICDESC;

	// D3DDECLUSAGE


	typedef struct tagVertex_Position_Texcoord
	{
		D3DXVECTOR3			vPosition;
		D3DXVECTOR2			vTexcoord;		
	} VTXPOSTEX;


}
