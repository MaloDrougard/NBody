#pragma once
#include <d2d1.h>
#include "Particle.h"
#include "Adapter.h"

template<class Interface>
inline void SafeRelease(
	Interface **ppInterfaceToRelease
	)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

class Graphics
{
public:
	Graphics();
	~Graphics();
	bool Initialize(HWND windowHandle);
	void SetAdapter(Adapter adapter);

	void BeginDraw() { pRenderTarget->BeginDraw(); }
	void EndDraw() { pRenderTarget->EndDraw(); }

	void ClearScreen();
	void DrawCircle(float x, float y, float radius, float r, float b, float c, float a);
	void DrawPoint(float x, float y, float r);
	void DrawParticule(Particle p);
	void DrawSet(vector<Particle> * particlesSet);

	void SetBrushColor(float r, float b, float c);


private:
	HWND hwnd;
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pGrayBrush;
	ID2D1SolidColorBrush* pBrush; 

	Adapter * adapter;

};

