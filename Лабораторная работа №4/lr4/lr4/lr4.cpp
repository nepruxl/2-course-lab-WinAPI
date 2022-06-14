// lr4.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lr4.h"
//#include <math.h>
//#include <stdlib.h>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <wchar.h>
#include <sysinfoapi.h >
#include <iostream>
#include <atltime.h>
using namespace std;

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND hWnd;

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
    LoadStringW(hInstance, IDC_LR4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LR4));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LR4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LR4);
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

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW|WM_SETFONT,
       300,				// x 
       70, 				// y	 Размеры окна 
       900, 				// width 
       600, nullptr, nullptr, hInstance, nullptr);

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
//z
//



HANDLE hThread2;
HANDLE hThread1;
DWORD WINAPI Thread2(LPVOID t);
DWORD WINAPI Thread1(LPVOID t);
int a = 0;
BOOL bFin = true;
BOOL gfin = true;
static int flag1 = 0, flag2 = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect, rect1 = { 450,0, 450, 600 }, rect2 = { 0,0, 450, 600 };
    static int dr = 0;

    switch (message)
    {
        
    case WM_CREATE:
    {

        if (a == 0)
        {

            rect1 = {450,0, 450, 600};

        }
        else
            if (a == 1)
            {
                rect2 = {0, 0, 450, 600};
            }
       
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {

        case 1001:
        {
            gfin = true;
            hThread2 = CreateThread(NULL, 0, Thread2, hWnd, 0, NULL);
            break;
        }
        case 1002:
        {
            TerminateThread(Thread2, 0);
            InvalidateRect(hWnd, NULL, TRUE);
            gfin = FALSE;
            break;
        }
        case 1003:
        {
            bFin = TRUE;
            hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
            break;
        }
        case 1004:
        {
            TerminateThread(Thread1, 0);
            InvalidateRect(hWnd, NULL, TRUE);
            bFin = FALSE;
            break;
        }


        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

DWORD WINAPI Thread2(LPVOID t)
{
    SYSTEMTIME sm;
    TCHAR buff[100];
    PAINTSTRUCT ps;
    RECT rect1 = { 450,0, 450, 600 };

    while (gfin)
    {
        GetLocalTime(&sm);
        swprintf_s(buff, TEXT("The local time is: %02d:%02d:%02d\n"), sm.wHour, sm.wMinute, sm.wSecond);
        HDC hdc1 = GetDC(hWnd);
        LOGFONT lf;
        memset(&lf, 0, sizeof(LOGFONT));
        lstrcpy(lf.lfFaceName, _T("Calibri")); // Имя шрифта.
        lf.lfHeight = 40; // По высоте.
        HFONT hFont = CreateFontIndirect(&lf);
        SelectObject(hdc1, hFont);
        SetTextColor(hdc1, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOut(hdc1, (rect1.right - rect1.left) / 2 + 500, (rect1.bottom - rect1.top) / 2, buff, _tcslen(buff));
        EndPaint(hWnd, &ps);
        flag1 = 1;
        Sleep(150);
    }
    a = 0;
    return 0;
}

DWORD WINAPI Thread1(LPVOID t)
{
    PAINTSTRUCT ps;
    RECT  rect2 = { 0,0, 450, 600 };
    while (bFin)
    {
        int x = ((rect2.right - rect2.left) / 2) - 200;
        int y = ((rect2.bottom - rect2.top) / 2) - 200;
        HDC hdc = GetDC(hWnd);
        HBRUSH hBrush;
        hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        HBRUSH old = (HBRUSH)SelectObject(hdc, hBrush);
        Ellipse(hdc, x, y, x + 400, y + 400);
        DeleteObject(SelectObject(hdc, hBrush));
        Sleep(150);
        ReleaseDC(hWnd, hdc);
    }
    a = 1;
    return (0);
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
