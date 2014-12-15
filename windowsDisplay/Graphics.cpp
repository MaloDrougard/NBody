
#include "Graphics.h"
#include "Adapter.h"


using namespace std;

Graphics::Graphics() 
{
	pBrush = NULL;
	pFactory = NULL;
	pGrayBrush = NULL;
	pRenderTarget = NULL;
	adapter = NULL;
}


Graphics::~Graphics()
{
	SafeRelease(&pFactory);
	SafeRelease(&pRenderTarget);
	SafeRelease(&pGrayBrush);
	SafeRelease(&pBrush);
	delete adapter;
}

bool Graphics::Initialize(HWND windowHandle)
{	
	hwnd = windowHandle;

	// Create a Direcr2D factory
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
	if (hr != S_OK) return false;
	
	// Create a Direct2D render target.
	RECT rc;
	GetClientRect(hwnd, &rc); // now we have the rectangle size for ever?

	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top
		);




	hr = pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, size),
		&pRenderTarget
		);
	if (hr != S_OK) return false;

	// Create a gray brush.
	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::LightSlateGray),
		&pGrayBrush
		);
	if (hr != S_OK) return false;

	// Create a blue brush.
	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
		&pBrush
		);
	if (hr != S_OK) return false;

	adapter = new Adapter();


	return true;

}
void Graphics::SetBrushColor(float r, float b, float c)
{
	pBrush->SetColor(D2D1::ColorF(r, b, c));
}


void Graphics::ClearScreen()
{
	pRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.5f));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float b, float c, float a)
{
	pBrush->SetColor(D2D1::ColorF(r, b, c));
	pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), pBrush, a);
}

void Graphics::DrawSet(vector<Particle> * particlesSet)
{
	vector<Particle>::iterator it = particlesSet->begin();
	while (it != particlesSet->end()){
		DrawParticule(*it);
		++it;
	}
}

void Graphics::DrawPoint(float x, float y, float r)
{
	pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), r, r), pGrayBrush);
}

void Graphics::DrawParticule(Particle p)
{
	pRenderTarget->FillEllipse(adapter->getPoint(p), pBrush);
}

void Graphics::SetAdapter(Adapter newAdapter)
{
	*adapter = newAdapter;
}