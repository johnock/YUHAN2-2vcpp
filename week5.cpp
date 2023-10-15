#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:windows")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>
#include<stdio.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;
RECT rect = { 0 };


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	{
		startPoint.x = LOWORD(lParam);
		startPoint.y = HIWORD(lParam);
		isMouseLButtonPressed = 1;
		rect = { 0 };
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;

	case WM_MOUSEMOVE:
	{
		if (isMouseLButtonPressed)
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);
			rect.left = min(startPoint.x, endPoint.x);
			rect.top = min(startPoint.y, endPoint.y);
			rect.right = max(startPoint.x, endPoint.x);
			rect.bottom = max(startPoint.y, endPoint.y);
			InvalidateRect(hwnd, NULL, TRUE);
		}

		if (isMouseRButtonPressed && !IsRectEmpty(&rect)) {
			rect.left += LOWORD(lParam) - startPoint.x;
			rect.top += HIWORD(lParam) - startPoint.y;
			rect.right += LOWORD(lParam) - startPoint.x;
			rect.bottom += HIWORD(lParam) - startPoint.y;
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);
		isMouseLButtonPressed = 0;
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;

	case WM_RBUTTONDOWN:
	{
		POINT mousePos;
		mousePos.x = LOWORD(lParam);
		mousePos.y = HIWORD(lParam);

		if (PtInRect(&rect, mousePos)) {
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
			isMouseRButtonPressed = 1;
		}
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;

	case WM_RBUTTONUP:
	{
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);
		isMouseRButtonPressed = 0;
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		if (!IsRectEmpty(&rect))
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
			FillRect(hdc, &rect, hBrush);
			DeleteObject(hBrush);
		}

		EndPaint(hwnd, &ps);

	}
	break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return S_OK;
}

#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	
	}

	// Window viewport 영역 조정
	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("202007065 옥진서"),
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,	// 창의 크기를 변경할 수 있는 테두리 삭제
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); 



	// 메시지 처리 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (GetMessage(&msg, NULL, 0, 0))

		{

			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);

		}
		

	
	return (int)msg.wParam;

}

