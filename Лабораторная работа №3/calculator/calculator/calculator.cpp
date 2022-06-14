// calculator.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "calculator.h"
#include <tchar.h>
#include <string>
#include <atlstr.h>
using namespace std;
#define MAX_LOADSTRING 100

#define windowWidth 400
#define windowHeight 650
#define buttonWidth 78
#define buttonHeight 50

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CALCULATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CALCULATOR));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CALCULATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CALCULATOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, windowWidth, windowHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT rect;

    static HWND Edit, Edit2;
    static TCHAR buf[256];
    static TCHAR ttt[256];
    static bool refresh = false;
    static int operation[2] = { 0 };
    static double leftOperand = NULL;
    switch (message)
    {
    case WM_CREATE:
    {   GetClientRect(hWnd, &rect);
    HWND plus = CreateWindow(_T("button"), _T(" + "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 100,
        rect.bottom - 80,
        100,
        80,
        hWnd, (HMENU)001, NULL, NULL);
    HWND equally = CreateWindow(_T("button"), _T(" = "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 200,
        rect.bottom - 100,
        100,
        100,
        hWnd, (HMENU)002, NULL, NULL);
    HWND point = CreateWindow(_T("button"), _T(" . "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 300,
        rect.bottom - 100,
        100,
        100,
        hWnd, (HMENU)003, NULL, NULL);
    HWND zero = CreateWindow(_T("button"), _T(" 0 "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 400,
        rect.bottom - 100,
        100,
        100,
        hWnd, (HMENU)004, NULL, NULL);
    HWND minus = CreateWindow(_T("button"), _T(" - "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 100,
        rect.bottom - 160,
        100,
        80,
        hWnd, (HMENU)005, NULL, NULL);
    HWND three = CreateWindow(_T("button"), _T(" 3 "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 200,
        rect.bottom - 200,
        100,
        100,
        hWnd, (HMENU)006, NULL, NULL);
    HWND two = CreateWindow(_T("button"), _T(" 2 "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 300,
        rect.bottom - 200,
        100,
        100,
        hWnd, (HMENU)007, NULL, NULL);
    HWND one = CreateWindow(_T("button"), _T(" 1 "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 400,
        rect.bottom - 200,
        100,
        100,
        hWnd, (HMENU)011, NULL, NULL);
    HWND mult = CreateWindow(_T("button"), _T(" * "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 100,
        rect.bottom - 240,
        100,
        80,
        hWnd, (HMENU)012, NULL, NULL);
    HWND six = CreateWindow(_T("button"), _T(" 6 "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 200,
        rect.bottom - 300,
        100,
        100,
        hWnd, (HMENU)013, NULL, NULL);
    HWND five = CreateWindow(_T("button"), _T(" 5 "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 300,
        rect.bottom - 300,
        100,
        100,
        hWnd, (HMENU)014, NULL, NULL);
    HWND four = CreateWindow(_T("button"), _T(" 4 "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 400,
        rect.bottom - 300,
        100,
        100,
        hWnd, (HMENU)015, NULL, NULL);
    HWND divie = CreateWindow(_T("button"), _T(" / "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 100,
        rect.bottom - 320,
        100,
        80,
        hWnd, (HMENU)016, NULL, NULL);
    HWND nine = CreateWindow(_T("button"), _T(" 9 "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 200,
        rect.bottom - 400,
        100,
        100,
        hWnd, (HMENU)017, NULL, NULL);
    HWND eight = CreateWindow(_T("button"), _T(" 8 "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 300,
        rect.bottom - 400,
        100,
        100,
        hWnd, (HMENU)111, NULL, NULL);
    HWND seven = CreateWindow(_T("button"), _T(" 7 "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 400,
        rect.bottom - 400,
        100,
        100,
        hWnd, (HMENU)112, NULL, NULL);
    HWND clear = CreateWindow(_T("button"), _T(" clear "),
        WS_CHILDWINDOW | WS_VISIBLE,
        rect.right - 100,
        rect.bottom - 400,
        100,
        80,
        hWnd, (HMENU)113, hInst, NULL);
    Edit = CreateWindow(_T("edit"), _T(""),
        WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER | ES_NOHIDESEL,
        rect.right - 400,
        rect.bottom - 542,
        400,
        150,
        hWnd, 0, NULL, NULL);
    SendMessage(Edit, EM_SETLIMITTEXT, 10, 0);


    Edit2 = CreateWindow(_T("edit"), _T(""),
        WS_CHILD | WS_VISIBLE | ES_RIGHT,
        rect.right - 400,
        rect.bottom - 575,
        400,
        50,
        hWnd, 0, NULL, NULL);

    HMENU hMenu1 = CreateMenu();
    HMENU hMenubar1 = CreateMenu();
    AppendMenu(hMenu1, MF_STRING, 211, L"About Calculator");
    AppendMenuW(hMenubar1, MF_POPUP, (UINT_PTR)hMenu1, L"Help");
    SetMenu(hWnd, hMenubar1);


    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));
    lstrcpy(lf.lfFaceName, _T("Calibri")); // Имя шрифта.
    lf.lfHeight = 80; // По высоте.
    HFONT hFont = CreateFontIndirect(&lf);
    SendMessage(Edit, WM_SETFONT, (WPARAM)hFont, 0L);
    }
    break;


    case WM_COMMAND:
    {   bool flag = false;
    int wmId = LOWORD(wParam);
    // Разобрать выбор в меню:
    switch (wmId)
    {
    case 001: //+
    {
        operation[0] = operation[1];
        operation[1] = 2;
        refresh = true;
        if (operation[0] == 0) leftOperand = _wtof(buf);
        StrCat(ttt, buf);
        StrCat(ttt, TEXT(" + "));
        SetWindowText(Edit2, ttt);

    }
    break;
    case 002: //=
    {
        operation[0] = operation[1];
        operation[1] = 1;
        refresh = true;
        if (operation[0] == 0) leftOperand = _wtof(buf);
        StrCat(ttt, buf);
        StrCat(ttt, TEXT(" = "));
        SetWindowText(Edit2, ttt);
        memset(&ttt, 0, lstrlen(buf));
    }
    break;
    case 003: //.
    {
        GetWindowText(Edit, buf, sizeof(buf));
        if (StrChr(buf, ',') == NULL) {
            StrCat(buf, TEXT(","));
            SetWindowText(Edit, buf);
        }
    }
    break;
    case 004: //0
    {
        GetWindowText(Edit, buf, sizeof(buf));
        if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
        if (lstrlen(buf) <= 7) {
            StrCat(buf, TEXT("0"));
            SetWindowText(Edit, buf);
        }
    }
    break;
    case 005: //-
    {
        operation[0] = operation[1];
        operation[1] = 3;
        refresh = true;
        if (operation[0] == 0) leftOperand = _wtof(buf);
        StrCat(ttt, buf);
        StrCat(ttt, TEXT(" - "));
        SetWindowText(Edit2, ttt);

    }
    break;
    case 006: //3
    {
        GetWindowText(Edit, buf, sizeof(buf));
        if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
        if (lstrlen(buf) <= 7) {
            StrCat(buf, TEXT("3"));
            SetWindowText(Edit, buf);

        }
    }
    break;
    case 007: //2
    {
        GetWindowText(Edit, buf, sizeof(buf));
        if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
        if (lstrlen(buf) <= 7) {
            StrCat(buf, TEXT("2"));
            SetWindowText(Edit, buf);
        }
    }
    break;
    case 011: //1
    {
        GetWindowText(Edit, buf, sizeof(buf));
        if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
        if (lstrlen(buf) <= 7) {
            StrCat(buf, TEXT("1"));
            SetWindowText(Edit, buf);
        }
    }
    break;
    case 012: //*
    {
        operation[0] = operation[1];
        operation[1] = 4;
        refresh = true;
        if (operation[0] == 0) leftOperand = _wtof(buf);
        StrCat(ttt, buf);
        StrCat(ttt, TEXT(" * "));
        SetWindowText(Edit2, ttt);
    }
    break;
    case 013: //6
    {
        GetWindowText(Edit, buf, sizeof(buf));
        if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
        if (lstrlen(buf) <= 7) {
            StrCat(buf, TEXT("6"));
            SetWindowText(Edit, buf);
        }
    }
    break;
    case 014: //5
    {
        GetWindowText(Edit, buf, sizeof(buf));
        if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
        if (lstrlen(buf) <= 7) {
            StrCat(buf, TEXT("5"));
            SetWindowText(Edit, buf);
        }
    }
    break;
    case 015: //4
    {
        GetWindowText(Edit, buf, sizeof(buf));
        if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
        if (lstrlen(buf) <= 7) {
            StrCat(buf, TEXT("4"));
            SetWindowText(Edit, buf);
        }

    }
    break;
    case 016: ///
    {
        operation[0] = operation[1];
        operation[1] = 5;
        refresh = true;
        if (operation[0] == 0) leftOperand = _wtof(buf);
        StrCat(ttt, buf);
        StrCat(ttt, TEXT(" / "));
        SetWindowText(Edit2, ttt);
    }
    break;
    case 017: //9
    {
        GetWindowText(Edit, buf, sizeof(buf));
        if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
        if (lstrlen(buf) <= 7) {
            StrCat(buf, TEXT("9"));
            SetWindowText(Edit, buf);
        }

    }
    break;
    case 111: //8
    {
        GetWindowText(Edit, buf, sizeof(buf));
        if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
        if (lstrlen(buf) <= 7) {
            StrCat(buf, TEXT("8"));
            SetWindowText(Edit, buf);
        }
    }
    break;
    case 112: //7 
    {
        GetWindowText(Edit, buf, sizeof(buf));
        if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
        if (lstrlen(buf) <= 7) {
            StrCat(buf, TEXT("7"));
            SetWindowText(Edit, buf);
        }
    }
    break;
    case 113: //clear
    {
        refresh = false;
        operation[0] = 0;
        operation[1] = 0;
        leftOperand = NULL;
        memset(&buf[1], 0, lstrlen(buf));
        buf[0] = ' ';
        SetWindowText(Edit, buf);
        SetWindowText(Edit2, buf);
    }
    break;


    case 211:
    {
        MessageBox(hWnd, TEXT("bazanova IU5-42"), TEXT("info"), MB_OK);
    }
    break;

    case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        break;
    case IDM_EXIT:
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;

    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    switch (operation[0]) {
    case 0:
        break;
    case 1:
    {
        operation[0] = 0;
        string klj = to_string(leftOperand);
        copy(klj.begin(), klj.begin() + 8, buf);
        SetWindowText(Edit, buf);
    }
    break;
    case 2:
    {

        operation[0] = 0;
        PWSTR qwe = StrChr(buf, ',');
        if (qwe != NULL) {
            *qwe = '.';
        }
        leftOperand = leftOperand + _wtof(buf);
        string klj = to_string(leftOperand);
        copy(klj.begin(), klj.begin() + 8, buf);
        SetWindowText(Edit, buf);
    }
    break;
    case 3:
    {
        operation[0] = 0;
        PWSTR qwe = StrChr(buf, ',');
        if (qwe != NULL) {
            *qwe = '.';
        }
        leftOperand = leftOperand - _wtof(buf);
        string klj = to_string(leftOperand);
        copy(klj.begin(), klj.begin() + 8, buf);
        SetWindowText(Edit, buf);
    }
    break;

    case 4:
    {
        operation[0] = 0;
        PWSTR qwe = StrChr(buf, ',');
        if (qwe != NULL) {
            *qwe = '.';
        }
        leftOperand = leftOperand * _wtof(buf);
        string klj = to_string(leftOperand);
        copy(klj.begin(), klj.begin() + 8, buf);
        SetWindowText(Edit, buf);
    }
    break;

    case 5:
    {
        operation[0] = 0;
        PWSTR qwe = StrChr(buf, ',');
        if (qwe != NULL) {
            *qwe = '.';
        }
        leftOperand = leftOperand / _wtof(buf);
        string klj = to_string(leftOperand);
        string::iterator it = klj.end();
        copy(klj.begin(), klj.begin() + 8, buf);
        SetWindowText(Edit, buf);
    }
    break;
    }

    return 0;
}


// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
