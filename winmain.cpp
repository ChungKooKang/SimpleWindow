#include <Windows.h>
#include <sstream>
// 1. ������ Ŭ���� ��� (���� C++�� Ŭ���� �̾߱Ⱑ �ƴϴ�!)(type�̶�� ���� ��)
// 2. ������ ����� (1���� ������ Ŭ���� Ȱ��)
// 3. ������ �޽��� ���� ó��
// 4. ������ ���ν���(Procedure) �ۼ�

const wchar_t gClassName[] = L"MyWindowClass";

// ������ ���ν��� ����
// LRESULT		 : long result
// CALLBACK		 : ���� �θ��°� �ƴ϶� �ٸ� ����� �ҷ��ִ� ��. ���� �θ��°� �ƴϾ ��ٸ��� �� �� ����
// HWND			 : �޽����� ���� ������
// UINT			 : message ����
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
	// ������ Ŭ����
	// �ʱ�ȭ�� ���õ� �ڵ�
	WNDCLASSEX wc; //WNDCLASS + Extra == WNDCLASSEX

	ZeroMemory(&wc, sizeof(WNDCLASSEX)); // ����ü�� 0���� �ʱ�ȭ. // uniform �ʱ�ȭ�� ����
	wc.style = CS_HREDRAW | CS_VREDRAW; //CS : class style, H + REDRAW : ���� + �ٽ� �׸���, V + REDRAW : ���� �ٽ� �׸���
	wc.lpszClassName = gClassName; //longpointerstringzero : Ŭ���� �̸��� ����
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // NULL�� ���콺 Ŀ���� ��ġ�� ���ϴµ� NULL�̶�� ���� �ü�� �⺻�� ��������� ��
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; // ����. br�� brush��� ������ �׸����� ä���� ����ϴ�.
	wc.lpfnWndProc = WindowProc; // window procedure�� �Լ�
	wc.cbSize = sizeof(WNDCLASSEX); // cb : count byte

	// ������ Ŭ���� ��� (OS��)

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed TO Register Window Class", L"Error", MB_OK);
		return 0;
	}

	// ���� Ŭ������ Ȱ���Ͽ� ������ ����
	HWND hwnd;
	hwnd = CreateWindowEx( // microsoft doc�� �˻��غ���
		0,
		gClassName, // ����ϴ� Ŭ���� �̸�
		L"SimpleWindow App", // ������ ����
		WS_OVERLAPPEDWINDOW, // window �� ��ġ�� �����ϰ� �ϱ�
		CW_USEDEFAULT, // ���� ���� �װڴ�. x��
		CW_USEDEFAULT, // ���� ���� �װڴ�  y��
		640, //���� ũ��
		480, // ���� ũ��
		NULL, // manu �� ���� �ִ� ���� Ŭ���� �� �ִ� ������
		NULL,
		hInstance,
		NULL
	); // ������ �����
	if (!hwnd)
	{
		MessageBox(nullptr, L"Failed To Create Window!", L"Error", MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	// winodw message loop
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) // �ݱ� ������ GeetMessage�� false�� ��ȯ
	{
		// ������ �ؾ��� ��.
		TranslateMessage(&msg); // OS�� app�� ����� �� ���� ���� �Ǿ� �ִ� ���� ���� ���� ����
		DispatchMessageW(&msg); // ������ message�� ���� �����쿡 ����

	}
	return (int)msg.wParam;
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(hwnd, &ps); // ��ȯ���� hwnd�� ��.

	// Pen
	HPEN bluePen = CreatePen(PS_SOLID, 1,RGB(0,0,255)); // PS : pen style

	HPEN oldPen = (HPEN)SelectObject(hdc, bluePen);// �������̶� ����ϰ� HGDIOBJ�� �� �� ����

	Rectangle(hdc, 0, 0, 100, 100);

	DeleteObject(bluePen);
	SelectObject(hdc, oldPen); // ���� pen���� �ٽ� �׸���. ������ ������ selecobject�� ������ ����ϴ� �׸��� ������ ������ �־


	//Brush
	HBRUSH hatchBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hatchBrush);
	Rectangle(hdc, 100, 100, 200, 200);



	DeleteObject(hatchBrush);
	SelectObject(hdc,oldBrush);


	// TODO
	EndPaint(hwnd, &ps); // �׸��Ⱑ �����ٶ�� ���� �˷��ִ� ��. �ʼ��� �����Ѵ�. window ���δ� �� C�� �Ǿ��ֱ� ������ �Ҹ��� ���� ������ �ϴ� �� �ʿ���.

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
//	��� ���� �׸��� �ʱ�
//	case WM_ERASEBKGND :
//		break;

	// window �׸��� ǥ�� ���̵�
	case WM_PAINT :
	{
		OnPaint(hwnd);
	}
		break;

	case WM_KEYDOWN :
		{
			std::stringstream ss;
			if (wParam == VK_SPACE) // Ư�� key�� ������ ���� �߱� // VK ���� �ִ��� �����ϱ�
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
		break; // �ݱ� ��ư�� ������ �� ���� �� �ִ�. �ݱ�� ���� �����ϴ� ���� �ٸ� �̾߱��̴�.

	case WM_DESTROY :
		PostQuitMessage(0); // �̰ɷ� ������� �Ѵ�.
		break;

	default :
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
