#include <Windows.h>
#include <sstream>
// 1. 윈도우 클래스 등록 (주의 C++의 클래스 이야기가 아니다!)(type이라고 보면 됨)
// 2. 윈도우 만들기 (1번의 윈도우 클래스 활용)
// 3. 윈도우 메시지 루프 처리
// 4. 윈도우 프로시져(Procedure) 작성

const wchar_t gClassName[] = L"MyWindowClass";

// 윈도우 프로시져 선언
// LRESULT		 : long result
// CALLBACK		 : 내가 부르는게 아니라 다른 사람이 불러주는 것. 내가 부르는게 아니어서 기다리게 될 수 있음
// HWND			 : 메시지를 받은 윈도우
// UINT			 : message 종류
// WPARAM		 : Word Parameter
// LPARAM		 : Long Parameter
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(						
	_In_ HINSTANCE hInstance,			
	_In_opt_ HINSTANCE hPrevInstance,	
	_In_ LPSTR lpCmdLine,				
	_In_ int nShowCmd					
)
{
	// 윈도우 클래스
	// 초기화에 관련된 코드
	WNDCLASSEX wc; //WNDCLASS + Extra == WNDCLASSEX

	ZeroMemory(&wc, sizeof(WNDCLASSEX)); // 구조체를 0으로 초기화. // uniform 초기화도 ㄱㅊ
	wc.style = CS_HREDRAW | CS_VREDRAW; //CS : class style, H + REDRAW : 가로 + 다시 그리기, V + REDRAW : 세로 다시 그리기
	wc.lpszClassName = gClassName; //longpointerstringzero : 클래스 이름을 지정
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // NULL은 마우스 커서의 위치를 말하는데 NULL이라는 말은 운영체제 기본을 가져오라는 말
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; // 배경색. br은 brush라는 뜻으로 그림판의 채우기랑 비슷하다.
	wc.lpfnWndProc = WindowProc; // window procedure의 함수
	wc.cbSize = sizeof(WNDCLASSEX); // cb : count byte

	// 윈도우 클래스 등록 (OS에)

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed TO Register Window Class", L"Error", MB_OK);
		return 0;
	}

	// 만든 클래스를 활용하여 윈도우 생성
	HWND hwnd;
	hwnd = CreateWindowEx( // microsoft doc에 검색해보기
		0,
		gClassName, // 사용하는 클래스 이름
		L"SimpleWindow App", // 윈도우 제목
		WS_OVERLAPPEDWINDOW, // window 그 겹치기 가능하게 하기
		CW_USEDEFAULT, // 차곡 차곡 쌓겠다. x값
		CW_USEDEFAULT, // 차곡 차곡 쌓겠다  y값
		640, //가로 크기
		480, // 세로 크기
		NULL, // manu 그 위에 있는 작은 클릭할 수 있는 리본들
		NULL,
		hInstance,
		NULL
	); // 윈도우 만들기
	if (!hwnd)
	{
		MessageBox(nullptr, L"Failed To Create Window!", L"Error", MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	// winodw message loop
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) // 닫기 누르면 GeetMessage가 false를 반환
	{
		// 무조건 해야할 것.
		TranslateMessage(&msg); // OS가 app에 명령할 때 하위 언어로 되어 있는 것을 상위 언어로 번역
		DispatchMessageW(&msg); // 번역된 message를 각각 윈도우에 보냄

	}
	return (int)msg.wParam;
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(hwnd, &ps); // 반환값은 hwnd가 됨.

	// Pen
	HPEN bluePen = CreatePen(PS_SOLID, 1,RGB(0,0,255)); // PS : pen style

	HPEN oldPen = (HPEN)SelectObject(hdc, bluePen);// 다형성이랑 비슷하게 HGDIOBJ를 쓸 수 있음

	Rectangle(hdc, 0, 0, 100, 100);

	DeleteObject(bluePen);
	SelectObject(hdc, oldPen); // 예전 pen으로 다시 그리기. 가능한 이유는 selecobject가 이전에 사용하던 그리기 도구를 가지고 있어서


	//Brush
	HBRUSH hatchBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hatchBrush);
	Rectangle(hdc, 100, 100, 200, 200);



	DeleteObject(hatchBrush);
	SelectObject(hdc,oldBrush);


	// TODO
	EndPaint(hwnd, &ps); // 그리기가 끝났다라는 것을 알려주는 것. 필수로 들어가야한다. window 내부는 다 C로 되어있기 때문에 소멸자 같은 역할을 하는 게 필요함.

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
//	배경 새로 그리지 않기
//	case WM_ERASEBKGND :
//		break;

	// window 그리기 표준 가이드
	case WM_PAINT :
	{
		OnPaint(hwnd);
	}
		break;

	case WM_KEYDOWN :
		{
			std::stringstream ss;
			if (wParam == VK_SPACE) // 특정 key가 눌렸을 때만 뜨기 // VK 뭐뭐 있는지 공부하기
			{
				ss << "Virtual Key : " << wParam << ", Extra : " << lParam << std::endl;
				OutputDebugStringA(ss.str().c_str());
			}
			
			break;
		}
	case WM_LBUTTONDOWN :
		{
			HDC hdc;

			hdc = GetDC(hwnd);

			Rectangle(hdc, 0, 0, 100, 100);
			
			ReleaseDC(hwnd, hdc);
			break;
		}
	case WM_CLOSE :
		DestroyWindow(hwnd);
		break; // 닫기 버튼을 눌러도 안 끝날 수 있다. 닫기와 앱을 종료하는 것은 다른 이야기이다.

	case WM_DESTROY :
		PostQuitMessage(0); // 이걸로 끝내줘야 한다.
		break;

	default :
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
