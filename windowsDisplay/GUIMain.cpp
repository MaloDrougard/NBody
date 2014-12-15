// graphics
#include <windows.h>
#include "Graphics.h"

// cores
#include <omp.h>
#include <vector>
#include "Particle.h"
#include "NBodysFunction.h"
#include "Generator.h"


const char    MAIN_WINDOW_TITLE[] = "NBodySimulation",
MAIN_WINDOW_CLASS_NAME[] = "myWindowClass";

const int    MAIN_WINDOW_WIDTH = 1000,
MAIN_WINDOW_HEIGHT = 1000;

// graphics 
double INTERVALX[2] = { -600000000.0, 600000000.0 }; // the range of the word that we will display in meter
double INTERVALY[2] = { -600000000.0, 600000000.0 };
double MASSPONDERATION = 100000000000000000000000.0;
bool compute = true;
Graphics * graphic;

// cores
char GENERATORFILE[100] = "terre-lune.txt";
int COUNTPARTICLE = 10000;
double DELTATIME = 120;
int NUMTHREADS = 1;

vector<Particle>  set;
vector<vector<Particle>> subSet;



int initCore();
int motion(); //update all the particle of the set


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_PAINT:

		// call of graphic 
		graphic->BeginDraw();
		if (compute){
			motion();
		}
		graphic->ClearScreen();
		graphic->DrawSet(&set);
		graphic->EndDraw();
		break;

	case WM_KEYDOWN:

		switch (wParam){
		case VK_SPACE:
			compute = !compute;
			break;
		case VK_UP:
			DELTATIME = 1.2 * DELTATIME;
			break;
			
		case VK_DOWN:
			DELTATIME = 0.83 * DELTATIME;
			break;
		
		case 0x47: //g
			setG(2 * getG());
			break;


		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX w;
	HWND hwnd;
	MSG msg;
	graphic = new Graphics(); // not initialize

	//Register window class
	w.cbSize = sizeof(WNDCLASSEX);
	w.style = 0;
	w.lpfnWndProc = WndProc;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;
	w.hInstance = hInstance;
	w.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon (Alt+Tab)
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszMenuName = NULL;
	w.lpszClassName = MAIN_WINDOW_CLASS_NAME;
	w.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // small icon (title bar)

	if (!RegisterClassEx(&w)){
		MessageBox(NULL, "RegisterClassEx() failed", "System error",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Create window
	hwnd = CreateWindowEx(
		NULL,
		MAIN_WINDOW_CLASS_NAME,
		MAIN_WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL){
		MessageBox(NULL, "CreateWindowEx() failed", "System error",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	// Initialize my display objects
	graphic->Initialize(hwnd);
	graphic->SetAdapter(Adapter(INTERVALX[0], INTERVALX[1], INTERVALY[0], INTERVALY[1], MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, MASSPONDERATION));
	
	// Initialize nbody
	initCore();


	// Show window
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Message loop
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


int initCore()
{
	set = GenerateSet(GENERATORFILE, COUNTPARTICLE);
	/* preparing the parallel section */
	int subSetSize = set.size() / NUMTHREADS;
	vector<Particle>::iterator it = set.begin();
	for (int i = 0; i < NUMTHREADS; ++i) {
		vector<Particle> temp(it, it + subSetSize);
		subSet.push_back(temp);
		it = it + subSetSize;
	}
	vector<Particle> remainder(it, set.end());
	for (int i = 0; i < remainder.size(); ++i){
		subSet.at(i).push_back(remainder.at(i));
	}
	return 1;
}

int motion(){

	int tid = 0;
#pragma omp parallel private(tid) shared(set,subSet) num_threads(NUMTHREADS)
	{
		tid = omp_get_thread_num();
		NBodysAttraction(&set, &(subSet.at(tid)));
		NBodysTravel(&(subSet.at(tid)), DELTATIME);
#pragma omp barrier
	}// end of parallel section
	
	set.clear();
	for (int i = 0; i < NUMTHREADS; ++i) {
		set.insert(set.end(), subSet.at(i).begin(), subSet.at(i).end());
	}
	
	return  1;
}