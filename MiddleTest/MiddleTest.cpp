#include <windows.h>

// 도형 그리기 옵션을 제어하는 변수들
bool rectwrite = false;
bool Circle = false;
bool Bonobono = false;
bool Ryan = false;
bool Cube = false;
bool isSpacePressed = false;
const wchar_t* text = L"드로잉 영역";  // 화면에 표시될 텍스트

// 초기에 그릴 사각형의 좌표
RECT drawRect = { 35, 90, 770, 450 };
RECT borderRect;  // 커서 모양 변경 영역을 결정하는 사각형

// 윈도우 프로시저 콜백 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        // 버튼 클릭 이벤트 처리
        if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 5) {
            rectwrite = LOWORD(wParam) == 1;
            Circle = LOWORD(wParam) == 2;
            Bonobono = LOWORD(wParam) == 3;
            Ryan = LOWORD(wParam) == 4;
            Cube = LOWORD(wParam) == 5;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;

    case WM_KEYDOWN:
        // 스페이스바 눌림 이벤트 처리
        if (wParam == VK_SPACE) {
            isSpacePressed = true;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;

    case WM_KEYUP:
        // 스페이스바 떼어짐 이벤트 처리
        if (wParam == VK_SPACE) {
            isSpacePressed = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;

    case WM_PAINT:
        // 그림 그리기 이벤트 처리
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 화면 초기화
        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        HBRUSH bgBrush = CreateSolidBrush(RGB(255, 240, 200));
        FillRect(hdc, &clientRect, bgBrush);
        DeleteObject(bgBrush);

        // 그림 영역 표시
        int margin = 8;
        int padding = 8;

        // 내부 및 외부 테두리 사각형 생성
        RECT outerRect = { margin, margin, 800 - margin, 480 - margin };
        RECT innerRect = { outerRect.left + padding, outerRect.top + padding,
                           outerRect.right - padding, outerRect.bottom - padding };
        RECT outdrawRect = { 35 - 4,90 - 4 ,770 + 4,450 + 4 };

        HBRUSH hOuterBrush = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH hInnerBrush = CreateSolidBrush(RGB(255, 240, 200));
        HBRUSH hOutBrush = CreateSolidBrush(RGB(80, 188, 223));

        FillRect(hdc, &outerRect, hOuterBrush);
        FillRect(hdc, &innerRect, hInnerBrush);
        FillRect(hdc, &outdrawRect, hOutBrush);
        FillRect(hdc, &drawRect, hInnerBrush);

        DeleteObject(hOuterBrush);
        DeleteObject(hInnerBrush);

        // 텍스트 표시
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(0, 0, 0));
        int textLength = lstrlen(text);
        SIZE textSize;
        GetTextExtentPoint32(hdc, text, textLength, &textSize);
        int textX = (clientRect.right - clientRect.left - textSize.cx) / 2;
        int textY = (clientRect.bottom - clientRect.top - textSize.cy) / 2;
        TextOut(hdc, textX, textY, text, textLength);

        // 테두리 사각형 좌표 계산
        borderRect.left = clientRect.left + drawRect.left;
        borderRect.top = clientRect.top + drawRect.top;
        borderRect.right = clientRect.left + drawRect.right;
        borderRect.bottom = clientRect.top + drawRect.bottom;

        // Bonobono 옵션일 때 그림 그리기
        if (Bonobono) {
            // 여러 색으로 Bonobono 그리기
            HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255));
            HBRUSH eyeBrush = CreateSolidBrush(RGB(0, 0, 0));
            HBRUSH ineyeBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 200, 100, 580, 450);

            HBRUSH mouseBrush = CreateSolidBrush(RGB(255, 150, 255));
            SelectObject(hdc, mouseBrush);
            Chord(hdc, 365, 260, 405, 350, 0, 0, 0, 0);

            HBRUSH ballBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, ballBrush);
            Ellipse(hdc, 325, 275, 385, 320);
            Ellipse(hdc, 390, 275, 450, 320);

            HBRUSH noseBrush = CreateSolidBrush(RGB(0, 0, 0));
            SelectObject(hdc, noseBrush);
            Ellipse(hdc, 365, 260, 405, 300);

            // 스페이스바가 눌려있을 때 눈 감기
            if (isSpacePressed) {
                HPEN eyePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
                SelectObject(hdc, eyePen);
                MoveToEx(hdc, 230, 230, NULL);
                LineTo(hdc, 250, 230);
                MoveToEx(hdc, 530, 230, NULL);
                LineTo(hdc, 550, 230);
                DeleteObject(eyePen);
            }
            // 스페이스바가 눌려있지 않을 때 눈 그리기
            else {
                SelectObject(hdc, eyeBrush);
                Ellipse(hdc, 230, 220, 250, 240);
                Ellipse(hdc, 530, 220, 550, 240);

                SelectObject(hdc, ineyeBrush);
                Ellipse(hdc, 232, 222, 248, 238);
                Ellipse(hdc, 532, 222, 548, 238);
            }

            // 수염 그리기
            HPEN beardPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            SelectObject(hdc, beardPen);
            MoveToEx(hdc, 350, 290, NULL);
            LineTo(hdc, 300, 265);
            MoveToEx(hdc, 430, 290, NULL);
            LineTo(hdc, 470, 265);

            MoveToEx(hdc, 350, 305, NULL);
            LineTo(hdc, 300, 305);
            MoveToEx(hdc, 430, 305, NULL);
            LineTo(hdc, 470, 305);

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
        // 커서 모양 변경
    {
        if (LOWORD(lParam) == HTCLIENT) {
            POINT mousePos;
            GetCursorPos(&mousePos);
            ScreenToClient(hWnd, &mousePos);

            // 커서가 특정 영역 안에 있으면 십자 모양으로 변경
            if (PtInRect(&borderRect, mousePos)) {
                SetCursor(LoadCursor(NULL, IDC_CROSS));
                return TRUE;
            }
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;

    case WM_CLOSE:
        // 창 닫기
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        // 프로그램 종료
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

    // 윈도우 클래스 정의
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(255, 240, 200));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"MidtermExam";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    // 윈도우 클래스 등록
    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    // 윈도우 생성
    hWnd = CreateWindow(
        L"MidtermExam", L"MidtermExam", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
        CW_USEDEFAULT, 0, 816, 510, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    // 버튼 생성
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

    // 윈도우 화면에 표시
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

    // 배경 브러시 삭제
    DeleteObject(wcex.hbrBackground);

    return (int)msg.wParam;
}
