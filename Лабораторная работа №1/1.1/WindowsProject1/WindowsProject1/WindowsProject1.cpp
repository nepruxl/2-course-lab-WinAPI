#include <Windows.h>
#include <tchar.h>
#include "stdafx.h"
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");


int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	HBRUSH DARKBLUE = CreateSolidBrush(RGB(0, 0, 139));


	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(DARKBLUE); 	// Заполнение окна  


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Лабораторная работа №1 Базанова ИУ5-42"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HBRUSH DARKBLUE = CreateSolidBrush(RGB(0, 0, 139));
	HBRUSH MBLUE = CreateSolidBrush(RGB(0, 0, 205));
	HBRUSH	BLUE = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH	RBLUE = CreateSolidBrush(RGB(65, 105, 225));
	HBRUSH	LBLUE = CreateSolidBrush(RGB(100, 149, 237));

	static int x = 260, y = 20;
	static int i = 0;
	static int knopka = 0;
	HDC hdc; //создаём контекст устройства
	PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода
	static HRGN hRgn;
	HBRUSH hBR;
	RECT rect;
	switch (message) // Обработчик сообщений
	{

	case WM_RBUTTONDOWN:
	{
		if (knopka != 2) knopka = 2;

		InvalidateRgn(hWnd, hRgn, true);
	}
	break;
	case WM_LBUTTONDOWN:
	{	if (i > 5) i = 0;
	i++;
	if (knopka != 1) knopka = 1;
	//InvalidateRgn(hWnd, hRgn, true);
	InvalidateRgn(hWnd, hRgn, true);
	} break;

	case WM_PAINT:

	{			HPEN hPen; //создаём перо
	hdc = BeginPaint(hWnd, &ps);
	GetClientRect(hWnd, &rect);
	
	if (knopka == 1)
	{
		int wx = 400;
		int wy = 400;
		x = ((rect.right - rect.left) / 2) - (wx / 2);
		y = ((rect.bottom - rect.top) / 2) - (wy / 2);
		switch (i)
		{
		case 1:FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(DARKBLUE));
			hBR = CreateSolidBrush(RGB(225, 225, 0));
			SelectObject(hdc, hBR);
			Ellipse(hdc, x, y, x + 400, y + 400);
			break;
		case 2:FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(MBLUE));
			hBR = CreateSolidBrush(RGB(225, 225, 0));
			SelectObject(hdc, hBR);
			Ellipse(hdc, x, y, x + 400, y + 400);

			hBR = CreateSolidBrush(RGB(0, 0, 205));
			SelectObject(hdc, hBR);
			Ellipse(hdc, x + 300, y, x + 700, y + 400);
			hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 205));
			SelectObject(hdc, hPen);
			Ellipse(hdc, x + 300, y, x + 700, y + 400);

			break;
		case 3: FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(BLUE));
			hBR = CreateSolidBrush(RGB(225, 225, 0));
			SelectObject(hdc, hBR);
			Ellipse(hdc, x, y, x + 400, y + 400);

			hBR = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBR);
			Ellipse(hdc, x + 200, y, x + 600, y + 400);
			hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
			SelectObject(hdc, hPen);
			Ellipse(hdc, x + 200, y, x + 600, y + 400);
			break;
		case 4: FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(RBLUE));
			hBR = CreateSolidBrush(RGB(225, 225, 0));
			SelectObject(hdc, hBR);
			Ellipse(hdc, x, y, x + 400, y + 400);

			hBR = CreateSolidBrush(RGB(65, 105, 225));
			SelectObject(hdc, hBR);
			Ellipse(hdc, x + 100, y, x + 500, y + 400);
			hPen = CreatePen(PS_SOLID, 3, RGB(65, 105, 225));
			SelectObject(hdc, hPen);
			Ellipse(hdc, x + 100, y, x + 500, y + 400);
			break;
		case 5:FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(LBLUE));
			hBR = CreateSolidBrush(RGB(225, 225, 0));
			SelectObject(hdc, hBR);
			Ellipse(hdc, x, y, x + 400, y + 400);

			hBR = CreateSolidBrush(RGB(100, 149, 237));
			SelectObject(hdc, hBR);
			Ellipse(hdc, x, y, x + 400, y + 400);
			hPen = CreatePen(PS_SOLID, 3, RGB(100, 149, 237));
			SelectObject(hdc, hPen);
			Ellipse(hdc, x, y, x + 400, y + 400);

			break;
		}

		ValidateRect(hWnd, NULL);

		EndPaint(hWnd, &ps);
	}

	if (knopka == 2)
	{
		SetTimer(hWnd, 1, 3000, NULL);
		FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(LBLUE));
		RECT r;
		GetClientRect(hWnd, &r);
		int wx = 157, wy = 41;
		x = ((r.right - r.left) / 2) - (wx / 2);
		y = ((r.bottom - r.top) / 2) - (wy / 2);
		r.right = x + wx;
		r.left = x;
		r.top = y;
		r.bottom = y + wy;
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		SelectObject(hdc, hPen);
		RoundRect(hdc, x, y, x + wx, y + wy, 3, 3);
		FillRect(ps.hdc, &r, (HBRUSH)(LBLUE));




		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 0, 0));
		DrawText(hdc, TEXT("Базанова ИУ5-42Б"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		
		ValidateRect(hWnd, NULL);
		EndPaint(hWnd, &ps);


	}

	}
	break;

	case WM_TIMER:
	{




	case WM_DESTROY:
	{		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
		return 0;
	}
	}
	break;

	}
}