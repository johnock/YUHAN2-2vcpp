#include <windows.h>
#include <cmath>

// 박스를 나타내는 변수
bool rectwrite = false;
bool Circle = false;
bool Bonobono = false;
bool Ryan = false;
bool Cube = false;
bool isSpacePressed = false;
const wchar_t* text = L"드로잉 영역";

// 드로잉 영역을 나타내는 RECT
RECT drawRect = { 35,90,770,450 }; // 드로잉 영역의 좌표

// 파란색 테두리 안의 드로잉 영역을 나타내는 RECT
RECT borderRect;

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            // Box 버튼 클릭
            rectwrite = true;
            Circle = false;
            Bonobono = false;
            Ryan = false;
            Cube = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (LOWORD(wParam) == 2) {
            // Circle 버튼 클릭
            rectwrite = false;
            Circle = true;
            Bonobono = false;
            Ryan = false;
            Cube = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (LOWORD(wParam) == 3) {
            // Bonobono 버튼 클릭
            rectwrite = false;
            Circle = false;
            Bonobono = true;
            Ryan = false;
            Cube = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (LOWORD(wParam) == 4) {
            // Ryan
            rectwrite = false;
            Circle = false;
            Bonobono = false;
            Ryan = true;
            Cube = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (LOWORD(wParam) == 5) {
            // Cube
            rectwrite = false;
            Circle = false;
            Bonobono = false;
            Ryan = false;
            Cube = true;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;

    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            isSpacePressed = true;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;

    case WM_KEYUP:
        if (wParam == VK_SPACE) {
            isSpacePressed = false;
            InvalidateRect(hWnd, NULL, FALSE);
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

        // Box의 좌표와 크기 계산
        RECT outerRect = { margin, margin, 800 - margin, 480 - margin }; // Margin 적용
        RECT innerRect = { outerRect.left + padding, outerRect.top + padding,
                           outerRect.right - padding, outerRect.bottom - padding }; // Padding 적용
        RECT outdrawRect = { 35 - 4,90 - 4 ,770 + 4,450 + 4 };

        // Box 그리기
        HBRUSH hOuterBrush = CreateSolidBrush(RGB(0, 0, 0)); // 바깥쪽 테두리의 색상
        HBRUSH hInnerBrush = CreateSolidBrush(RGB(255, 240, 200));     // 안쪽 테두리의 색상
        HBRUSH hOutBrush = CreateSolidBrush(RGB(80, 188, 223));

        FillRect(hdc, &outerRect, hOuterBrush);
        FillRect(hdc, &innerRect, hInnerBrush);
        FillRect(hdc, &outdrawRect, hOutBrush);
        FillRect(hdc, &drawRect, hInnerBrush);

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

        // 드로잉 영역을 제외한 파란색 테두리 부분 계산
        borderRect.left = clientRect.left + drawRect.left;
        borderRect.top = clientRect.top + drawRect.top;
        borderRect.right = clientRect.left + drawRect.right;
        borderRect.bottom = clientRect.top + drawRect.bottom;

        if (Bonobono) {
            // 피부 그리기
            HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255));
            HBRUSH eyeBrush = CreateSolidBrush(RGB(0, 0, 0)); // 눈 색상 (검정)
            HBRUSH ineyeBrush = CreateSolidBrush(RGB(255, 255, 255)); // 눈동자 색상 (하양)
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 200, 100, 580, 450);

            // 입 그리기 
            HBRUSH mouseBrush = CreateSolidBrush(RGB(255, 150, 255)); // 입 색상 (핑크)
            SelectObject(hdc, mouseBrush);
            Chord(hdc, 365, 260, 405, 350, 0, 0, 0, 0);

            //하얀볼 그리기
            HBRUSH ballBrush = CreateSolidBrush(RGB(255, 255, 255)); // 눈 색상 (하양)
            SelectObject(hdc, ballBrush);
            Ellipse(hdc, 325, 275, 385, 320); // 왼쪽 볼
            Ellipse(hdc, 390, 275, 450, 320); // 오른쪽 볼

            // 코 그리기 (작은 동그라미)
            HBRUSH noseBrush = CreateSolidBrush(RGB(0, 0, 0)); // 코 색상 (검정)
            SelectObject(hdc, noseBrush);
            Ellipse(hdc, 365, 260, 405, 300); // 코

            if (isSpacePressed) {
                // ㅡ ㅡ 그리기
                HPEN eyePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
                SelectObject(hdc, eyePen);
                MoveToEx(hdc, 230, 230, NULL);
                LineTo(hdc, 250, 230);
                MoveToEx(hdc, 530, 230, NULL);
                LineTo(hdc, 550, 230);
                DeleteObject(eyePen);
            }
            else {
                // 눈 그리기
                SelectObject(hdc, eyeBrush);
                Ellipse(hdc, 230, 220, 250, 240); // 왼쪽 눈
                Ellipse(hdc, 530, 220, 550, 240); // 오른쪽 눈

                // 눈동자 그리기
                SelectObject(hdc, ineyeBrush);
                Ellipse(hdc, 232, 222, 248, 238); // 왼쪽 눈동자
                Ellipse(hdc, 532, 222, 548, 238); // 오른쪽 
            }

            // 수염 그리기 (선)
            HPEN beardPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // 수염 색상 (검정)
            SelectObject(hdc, beardPen);
            MoveToEx(hdc, 350, 290, NULL);
            LineTo(hdc, 300, 265);
            MoveToEx(hdc, 430, 290, NULL);
            LineTo(hdc, 470, 265);

            MoveToEx(hdc, 350, 305, NULL);
            LineTo(hdc, 300, 305);
            MoveToEx(hdc, 430, 305, NULL);
            LineTo(hdc, 470, 305);

            // 리소스 해제
            DeleteObject(hBrush);
            DeleteObject(eyeBrush);
            DeleteObject(ballBrush);
            DeleteObject(noseBrush);
            DeleteObject(ineyeBrush);
            DeleteObject(mouseBrush);
            DeleteObject(beardPen);
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

            if (PtInRect(&borderRect, mousePos)) {
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
