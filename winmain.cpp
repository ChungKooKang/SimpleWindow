#include <Windows.h>
// HISTANCE : Handle of INSTANCE : intance�� ���� �ڵ�(= pointer ������)
// LPTR : Long Pointer(�Ϲ� pointer ���� �� ���� ����ų �� ����.) to(Null-Terminated�� ������) STRing : ���ڿ��� ����Ű�� ������
int WINAPI WinMain(						// WINAPI�� �Լ� ȣ�� ��Ģ�ε� RAM�� ����� parameter�� �θ��� �������� ȣ���ϰڴٴ� ��
	_In_ HINSTANCE hInstance,			// �� ���� �� pointer
	_In_opt_ HINSTANCE hPrevInstance,	// ���� �� pointer. ���� ���� �ְ� ���� ���� ����.
	_In_ LPSTR lpCmdLine,				// Command line : �������� �� �� �ְ� ������ �ϴ� ��.
	_In_ int nShowCmd					// n : integer ��� ��. showcmd : show Command : command�� ������. ȭ�鿡 �� �� ��üȭ������ �� ������ �ƴϸ� ���� â���� ����� ��� ����.
)
{
	MessageBox(							// �� �˸�â ���ϴ� ��..
		nullptr,
		L"Hello World!",				// L ���ξ�� �����ڵ��� ���� ���ξ� // �˸�â ����
		L"SimpleWindow",				// �˸�â ����
		MB_ICONEXCLAMATION | MB_OK		// �� ����� �ﰢ���� ����ǥ ������ �ֱ� | Ȯ�� Ŭ�� �ڽ� �ֱ�
	);
}