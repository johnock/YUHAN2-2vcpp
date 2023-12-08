#include <windows.h>
#include <cmath>

// 박스를 나타내는 변수
bool RT = false;
bool CC = false;
bool BB = false;
bool Ryan = false;
bool Cube = false;
bool isSpacePressed = false;
const wchar_t* text = L"그리는 부분";

// 드로잉 영역을 나타내는 RECT
RECT DR = { 35, 90, 770, 450 }; // 드로잉 영역의 좌표

// 테두리 안의 드로잉 영역을 나타내는 RECT
RECT BR;

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            // Box 버튼 클릭
            RT = true;
            CC = false;
            BB = false;
            Ryan = false;
            Cube = false;
        }
        else if (LOWORD(wParam) == 2) {
            // Circle 버튼 클릭
            RT = false;
            CC = true;
            BB = false;
            Ryan = false;
            Cube = false;
        }
        else if (LOWORD(wParam) == 3) {
            // Bonobono 버튼 클릭
            RT = false;
            CC = false;
            BB = true;
            Ryan = false;
            Cube = false;
        }
        else if (LOWORD(wParam) == 4) {
            // Ryan
            RT = false;
            CC = false;
            BB = false;
            Ryan = true;
            Cube = false;
        }
        else if (LOWORD(wParam) == 5) {
            // Cube
            RT = false;
            CC = false;
            BB = false;
            Ryan = false;
            Cube = true;
        }

        InvalidateRect(hWnd, NULL, FALSE);
        break;

    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            isSpacePressed = true;
        }
        break;

    case WM_KEYUP:
        if (wParam == VK_SPACE) {
            isSpacePressed = false;
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        HBRUSH bgBrush = CreateSolidBrush(RGB(255, 240, 200));
        FillRect(hdc, &clientRect, bgBrush);
        DeleteObject(bgBrush);

        int margin = 8;
        int padding = 8;

        //테두리의 좌표와 크기 계산
        RECT outerRect = { margin, margin, 800 - margin, 480 - margin }; // Margin 적용
        RECT innerRect = { outerRect.left + padding, outerRect.top + padding,
                           outerRect.right - padding, outerRect.bottom - padding }; // Padding 적용
        RECT outdrawRect = { 35 - 4, 90 - 4 ,770 + 4,450 + 4 };

        // 테두리 그리기
        HBRUSH hOuterBrush = CreateSolidBrush(RGB(0, 0, 0)); // 바깥쪽 테두리의 색상
        HBRUSH hInnerBrush = CreateSolidBrush(RGB(255, 240, 200));     // 안쪽 테두리의 색상
        HBRUSH hOutBrush = CreateSolidBrush(RGB(0, 0, 0));

        FillRect(hdc, &outerRect, hOuterBrush);
        FillRect(hdc, &innerRect, hInnerBrush);
        FillRect(hdc, &outdrawRect, hOutBrush);
        FillRect(hdc, &DR, hInnerBrush);

        DeleteObject(hOuterBrush);
        DeleteObject(hInnerBrush);

        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(0, 0, 0)); // 텍스트 색상을 검정색으로 설정
        int textLength = lstrlen(text);
        SIZE textSize;
        GetTextExtentPoint32(hdc, text, textLength, &textSize);
        int textX = (clientRect.right - clientRect.left - textSize.cx) / 2; // 텍스트의 가로 중앙 위치 계산
        int textY = (clientRect.bottom - clientRect.top - textSize.cy) / 2; // 텍스트의 세로 중앙 위치 계산
        TextOut(hdc, textX, textY, text, textLength);

        // 드로잉 영역을 제외한 테두리 부분 계산
        BR.left = clientRect.left + DR.left;
        BR.top = clientRect.top + DR.top;
        BR.right = clientRect.left + DR.right;
        BR.bottom = clientRect.top + DR.bottom;

        // 여기서 사각형 그리는 코드 추가
        if (RT) {
            Rectangle(hdc, 100, 100, 300, 300);
        }

        EndPaint(hWnd, &ps);
    }
    break;

    case WM_SETCURSOR:
    {
        if (LOWORD(lParam) == HTCLIENT) {
            POINT mousePos;
            GetCursorPos(&mousePos);
            ScreenToClient(hWnd, &mousePos);

            if (PtInRect(&BR, mousePos)) {
                SetCursor(LoadCursor(NULL, IDC_CROSS)); // 십자가 모양의 커서로 설정합니다.
                return TRUE;
            }
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;

    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return S_OK;
}

// 프로그램 진입점
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    HWND hWnd;
    HWND hButton3, hButton1, hButton2, hButton4, hButton5;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(255, 240, 200)); // 배경색을 r:255 g:240 b:200으로 설정
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"MidtermExam";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    hWnd = CreateWindow(
        L"MidtermExam", L"MidtermExam", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
        CW_USEDEFAULT, 0, 816, 510, NULL, NULL, hInstance, NULL); // 크기를 800x480으로 설정

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 20, 150, 64, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        172, 20, 150, 64, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        324, 20, 150, 64, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        476, 20, 150, 64, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        628, 20, 150, 64, hWnd, (HMENU)5, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        if (msg.message == WM_KEYDOWN && msg.wParam == VK_SPACE) {
            isSpacePressed = true;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (msg.message == WM_KEYUP && msg.wParam == VK_SPACE) {
            isSpacePressed = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else {
            DispatchMessage(&msg);
        }
    }

    // 배경 브러시 해제
    DeleteObject(wcex.hbrBackground);

    return (int)msg.wParam;
}
