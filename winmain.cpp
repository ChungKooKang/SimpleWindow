#include <Windows.h>
// HISTANCE : Handle of INSTANCE : intance에 대한 핸들(= pointer 손잡이)
// LPTR : Long Pointer(일반 pointer 보다 더 많이 가르킬 수 있음.) to(Null-Terminated가 생략됨) STRing : 문자열을 가르키는 포인터
// MessageBox
//		HWND hwnd			 : Handle(pointer) of WND (WiNDow) 부모 윈도우
//		LPCWSTR lpText		 : Long Pointer C(constant)W(wide) STRing : messagebox에 본문 역할
//		LPCWSTR lpCaption	 : 제목
//		UINT uType			 : Unsinged Interger 스타일
int WINAPI WinMain(						// WINAPI는 함수 호출 규칙인데 RAM에 저장된 parameter를 부르는 형식으로 호출하겠다는 말
	_In_ HINSTANCE hInstance,			// 걍 지금 것 pointer
	_In_opt_ HINSTANCE hPrevInstance,	// 이전 것 pointer. 있을 수도 있고 없을 수도 있음.
	_In_ LPSTR lpCmdLine,				// Command line : 명령줄을 줄 수 있게 들어오게 하는 것.
	_In_ int nShowCmd					// n : integer 라는 뜻. showcmd : show Command : command를 보여줌. 화면에 뜰 때 전체화면으로 할 것인지 아니면 작은 창으로 뜰건지 등등 정함.
)
{
	MessageBox(							// 그 알림창 말하는 것..
		nullptr,						// HWND에서 nullptr일 경우 O.S.가 부모 window 이다.
		L"Hello World!",				// L 접두어는 유니코드라는 뜻의 접두어 // 알림창 내용
		L"SimpleWindow",				// 알림창 내용
		MB_ICONEXCLAMATION | MB_OKCANCEL// 그 노란색 삼각형에 느낌표 아이콘 넣기 | 확인 클릭 박스 넣기
	);
}

