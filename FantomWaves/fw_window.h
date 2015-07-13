#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include "fw_includes.h"
#include "fw_popup.h"

namespace fw
{
	/***
	ウィンドウを管理するクラス。
	古い実装。
	*/
	class Window
	{
	private:
		class Exstyle
		{
		private:
			DWORD style;

		public:
			Exstyle(){ defstyle(); }

			Exstyle & defstyle()
			{
				style = WS_EX_LEFT;
				return *this;
			}
#define macro(NAME, STYLE) Exstyle & NAME (){ style = style | STYLE ; return *this; }
			macro(rightscroll, WS_EX_RIGHTSCROLLBAR)
				macro(DandD, WS_EX_ACCEPTFILES)
				macro(appwin, WS_EX_APPWINDOW)
				macro(clientedge, WS_EX_CLIENTEDGE)
				macro(help, WS_EX_CONTEXTHELP)
				macro(dualframe, WS_EX_DLGMODALFRAME)
				macro(left, WS_EX_LEFT)
				macro(leftscroll, WS_EX_LEFTSCROLLBAR)
				macro(right, WS_EX_RIGHT)
				macro(LtoR, WS_EX_LTRREADING)
				macro(RtoL, WS_EX_RTLREADING)
				macro(staticedge, WS_EX_STATICEDGE)
				macro(tool, WS_EX_TOOLWINDOW)
				macro(top, WS_EX_TOPMOST)
				macro(trans, WS_EX_TRANSPARENT)
				macro(raised, WS_EX_WINDOWEDGE)
#undef macro

				DWORD output() const { return style; }
		};

		class Style
		{
		private:
			DWORD style;

		public:
			Style(){ defstyle(); }

			Style & defstyle()
			{
				style = WS_OVERLAPPEDWINDOW;
				return *this;
			}
			Style & invisible(){ style = style & ~WS_VISIBLE; return *this; }
#define macro(NAME, STYLE) Style & NAME (){ style = style | STYLE ; return *this; }
			macro(border, WS_BORDER)
				macro(titlebar, WS_CAPTION)
				macro(ClipChildlen, WS_CLIPCHILDREN)
				macro(disable, WS_DISABLED)
				macro(dialog, WS_DLGFRAME)
				macro(HScroll, WS_HSCROLL)
				macro(maxshow, WS_MAXIMIZE)
				macro(maxbutton, WS_MAXIMIZEBOX)
				macro(minishow, WS_MINIMIZE)
				macro(minibutton, WS_MINIMIZEBOX)
				macro(overlap, WS_OVERLAPPED)
				macro(popup, WS_POPUP)
				macro(menu, WS_SYSMENU)
				macro(thickframe, WS_THICKFRAME)
				macro(visible, WS_VISIBLE)
				macro(VScroll, WS_VSCROLL)
#undef macro

				DWORD output() const { return style; }
		};

	public:
		Exstyle exstyle;
		Style style;

		Window(bool CreateFlag = false)
		{
			ClientSizeMode = true;
			VisibleFlag = true;
			Title = "NewWindow";
			Winproc = DefaultWinproc;
			X = CW_USEDEFAULT;
			Y = CW_USEDEFAULT;
			Width = CW_USEDEFAULT;
			Height = CW_USEDEFAULT;

			if (CreateFlag) create();
		}
		Window(const std::string & title, WNDPROC winproc, int width, int height, bool CreateFlag = false)
		{
			VisibleFlag = true;
			Title = title;
			Winproc = winproc;
			Width = width;
			Height = height;
			X = CW_USEDEFAULT;
			Y = CW_USEDEFAULT;

			if (CreateFlag) create();
		}

		Window & invisible()
		{
			style.invisible();
			VisibleFlag = false;

			return *this;
		}

		Window & ClientSize()
		{
			ClientSizeMode = true;
			return *this;
		}
		Window & WindowSize()
		{
			ClientSizeMode = false;
			return *this;
		}

		Window & create()
		{
			wc.cbClsExtra = 0;
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.cbWndExtra = 0;
			wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_APPWORKSPACE + 1);
			wc.hCursor = reinterpret_cast<HCURSOR>(LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
			wc.hIcon = NULL;
			wc.hIconSm = NULL;
			wc.hInstance = GetModuleHandle(NULL);
			wc.lpfnWndProc = Winproc;
			wc.lpszClassName = "myClass";
			wc.lpszMenuName = NULL;
			wc.style = CS_DBLCLKS;

			RegisterClassEx(&wc);

			int w = width();
			int h = height();
			if (ClientSizeMode && VisibleFlag == true)
			{
				RECT rect;
				rect.left = 1;
				rect.top = 1;
				rect.right = w;
				rect.bottom = h;

				BOOL result = AdjustWindowRectEx(&rect, style.output(), false, exstyle.output());
				if (result == 0)
				{
					fw::popup("ウィンドウを正しく作成することができませんでした。");
				}

				w = rect.right - rect.left;
				h = rect.bottom - rect.top;
			}

			handle = CreateWindowEx(
				exstyle.output(),
				"myClass",
				Title.c_str(),
				style.output(),
				X, Y,
				w, h,
				NULL, NULL, GetModuleHandle(NULL), NULL
				);

			if (VisibleFlag == true)
			{
				ShowWindow(handle, SW_SHOWDEFAULT);
				UpdateWindow(handle);
			}

			return *this;
		}

		int x() const { return X; }
		Window & x(const int x)
		{
			X = x;
			return *this;
		}

		int y() const { return Y; }
		Window & y(const int y)
		{
			Y = y;
			return *this;
		}

		const std::string & title() const { return Title; }
		Window & title(const std::string & title)
		{
			Title = title;
			return *this;
		}

		int width() const { return Width; }
		Window & width(const int width)
		{
			Width = width;
			return *this;
		}

		int height() const { return Height; }
		Window & height(const int height)
		{
			Height = height;
			return *this;
		}

		Window & winproc(WNDPROC winproc)
		{
			Winproc = winproc;
			return *this;
		}

		HWND myhandle() const { return handle; }

		static bool processage()
		{
			MSG msg;
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == 0) return true;
			if (msg.message == WM_QUIT)
			{
				PostQuitMessage(0);
				return false;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			return true;
		}
		static bool processage_win()
		{
			MSG msg;
			BOOL result = GetMessage(&msg, NULL, 0, 0);
			if (result == 0 || result == -1) return false;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			return true;
		}


	private:
		bool VisibleFlag;
		std::string Title;
		WNDPROC Winproc;
		int X, Y, Width, Height;
		bool ClientSizeMode;
		WNDCLASSEX wc;
		HWND handle;

		static LRESULT CALLBACK DefaultWinproc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
		{
			switch (uiMsg){
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			}

			return DefWindowProc(hwnd, uiMsg, wParam, lParam);
		}

	};

}