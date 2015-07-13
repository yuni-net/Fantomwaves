#define _CRT_SECURE_NO_DEPRECATE

#pragma once

#include "fw_includes.h"
#include "fw_typedef.h"

namespace fw
{

	const uint min_ID = 100;

	/***
	@brief [Windows限定]ウィンドウの作成・管理を司る。
	*/
	class WindowEx
	{
	public:
		/***
		チェックボックス子ウィンドウ管理クラス。
		*/
		class Checkbox{
			HWND handle;
			WORD id;

		public:

			Checkbox(){ handle = NULL; }
			Checkbox & create(const HWND windle, const std::string & str, int x, int y, int width, int height){
				if (handle != NULL) del();

				handle = CreateWindow(
					"BUTTON",
					str.c_str(),
					WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
					x, y,
					width, height,
					windle,
					WindowEx::get_child_ID(),
					GetModuleHandle(NULL),
					NULL
					);

				return *this;
			}
			Checkbox & create(const WindowEx & w, const std::string & str, int x, int y, int width, int height){
				return create(w.handle(), str, x, y, width, height);
			}
			Checkbox(const WindowEx & w, const std::string & str, int x, int y, int width, int height){ create(w, str, x, y, width, height); }

			void check(){ SendMessage(handle, BM_SETCHECK, BST_CHECKED, 0); }
			void uncheck(){ SendMessage(handle, BM_SETCHECK, BST_UNCHECKED, 0); }
			bool ifcheck(){ return BST_CHECKED == SendMessage(handle, BM_GETCHECK, 0, 0); }

			Checkbox & del(){
				DestroyWindow(handle);
				return *this;
			}
			~Checkbox(){ del(); }
		};

		/***
		エディットボックス子ウィンドウ管理クラス。
		*/
		class Input{
			HWND handle;

		public:

			Input(){ handle = NULL; }
			Input & create(const HWND windle, const std::string & str, int x, int y, int width, int height){
				if (handle != NULL) del();

				handle = CreateWindow(
					"EDIT",
					str.c_str(),
					WS_CHILD | WS_VISIBLE,
					x, y,
					width, height,
					windle,
					WindowEx::get_child_ID(),
					GetModuleHandle(NULL),
					NULL
					);

				return *this;
			}
			Input & create(const WindowEx & w, const std::string & str, int x, int y, int width, int height){
				return create(w.handle(), str, x, y, width, height);
			}
			Input(const WindowEx & w, const std::string & str, int x, int y, int width, int height){ create(w, str, x, y, width, height); }

			std::string gets(){
				char content[257];
				GetWindowText(handle, content, 256);
				return content;
			}

			Input & sets(const std::string & output){
				SetWindowText(handle, output.c_str());
				return *this;
			}

			Input & del(){
				DestroyWindow(handle);
				return *this;
			}
			~Input(){ del(); }
		};

		/***
		STATIC子ウィンドウ管理クラス。
		*/
		class TextField{
			HWND handle;

		public:

			TextField(){ handle = NULL; }
			TextField & create(const HWND windle, const std::string & str, int x, int y, int width, int height){
				if (handle != NULL) del();

				handle = CreateWindow(
					"STATIC",
					str.c_str(),
					WS_CHILD | WS_VISIBLE,
					x, y,
					width, height,
					windle,
					WindowEx::get_child_ID(),
					GetModuleHandle(NULL),
					NULL
					);

				return *this;
			}
			TextField & create(const WindowEx & w, const std::string & str, int x, int y, int width, int height){
				return create(w.handle(), str, x, y, width, height);
			}
			TextField(const WindowEx & w, const std::string & str, int x, int y, int width, int height){ create(w, str, x, y, width, height); }

			std::string gets(){
				char content[257];
				GetWindowText(handle, content, 256);
				return content;
			}

			TextField & sets(const std::string & output){
				SetWindowText(handle, output.c_str());
				return *this;
			}

			TextField & del(){
				DestroyWindow(handle);
				return *this;
			}
			~TextField(){ del(); }
		};

		/***
		ボタン子ウィンドウ管理クラス。
		*/
		class Button{
			HWND handle;
			uint index;

		public:

			Button(){ handle = NULL; }
			Button & create(const WindowEx & w, const std::string & str, int x, int y, int width, int height, bool defbutton = false){
				if (handle != NULL) del();

				int attribute = WS_CHILD | WS_VISIBLE;
				if (defbutton) attribute = attribute | BS_DEFPUSHBUTTON;
				else attribute = attribute | BS_PUSHBUTTON;

				HMENU id = WindowEx::get_child_ID();
				index = reinterpret_cast<uint>(id);
				index -= 100;

				WindowEx::init_index(index);

				handle = CreateWindow(
					"BUTTON",
					str.c_str(),
					attribute,
					x, y,
					width, height,
					w.handle(),
					id,
					GetModuleHandle(NULL),
					NULL
					);

				return *this;
			}
			Button(const WindowEx & w, const std::string & str, int x, int y, int width, int height, bool defbutton = false){ create(w, str, x, y, width, height, defbutton); }

			bool clicked() const { return WindowEx::clicked(index); }

			Button & del(){
				DestroyWindow(handle);
				return *this;
			}
			~Button(){ del(); }
		};

		WindowEx(){}
		void init(const std::string &title, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT){
			wc.cbClsExtra = 0;
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.cbWndExtra = 0;
			wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_APPWORKSPACE + 1);
			wc.hCursor = LoadCursor(GetModuleHandle(NULL), IDC_ARROW);
			wc.hIcon = NULL;
			wc.hIconSm = NULL;
			wc.hInstance = GetModuleHandle(NULL);
			wc.lpfnWndProc = win_proc;
			wc.lpszClassName = "myClass";
			wc.lpszMenuName = NULL;
			wc.style = CS_DBLCLKS;

			RegisterClassEx(&wc);

			main_winhand = CreateWindowEx(
				WS_EX_TOOLWINDOW,
				"myClass",
				title.c_str(),
				WS_BORDER | WS_SYSMENU,
				CW_USEDEFAULT, CW_USEDEFAULT,
				width, height,
				NULL, NULL, GetModuleHandle(NULL), NULL
				);

			ShowWindow(main_winhand, SW_SHOWDEFAULT);
			UpdateWindow(main_winhand);
		}
		WindowEx(const std::string &title, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT){ init(title, width, height); }

		HWND handle() const { return main_winhand; }

		/***
		@brief このウィンドウを消します。
		*/
		WindowEx & del(){
			for (uint i = min_ID; i < child_ID; ++i) DestroyWindow(reinterpret_cast<HWND>(i));
			DestroyWindow(main_winhand);
			return *this;
		}
		~WindowEx(){ del(); }



	private:
		static std::map<uint, bool> buttons;
		static uint child_ID;

		WNDCLASSEX wc;
		HWND main_winhand;

		/***
		@brief 子ウィンドウハンドルが、このクラスが管理している子ウィンドウなのかを調べる。
		@param 調べたい子ウィンドウハンドルを指定します。
		@return true...管理している子ウィンドウ false...知らないウィンドウ
		*/
		static bool notmine(const uint ID){ return ID < min_ID || ID >= child_ID; }

		/***
		@brief デフォルトのウィンドウプロシージャです。
		*/
		static LRESULT CALLBACK win_proc(HWND hwnd, UINT message, WPARAM polym_param, LPARAM sub_param){
			static HBRUSH aqua_brsh = NULL;
			uint mychild_ID = static_cast<uint>(GetWindowLongPtr(reinterpret_cast<HWND>(sub_param), GWLP_ID));

			switch (message)
			{

			case WM_COMMAND:

				if (notmine(mychild_ID)) break;

				buttons[mychild_ID - 100] = true;
				break;

			case WM_CTLCOLORSTATIC:

				if (notmine(mychild_ID)) break;

				if (mychild_ID % 2){
					// 背景色を白色に設定
					SetBkColor(reinterpret_cast<HDC>(polym_param), 0xffffff);
					return reinterpret_cast<LRESULT>(GetStockObject(WHITE_BRUSH));
				}
				else{
					// 背景色を水色に設定
					SetBkColor(reinterpret_cast<HDC>(polym_param), RGB(200, 255, 255));
					if (aqua_brsh == NULL) aqua_brsh = CreateSolidBrush(RGB(200, 255, 255));
					return reinterpret_cast<LRESULT>(aqua_brsh);
				}
				break;

			case WM_DESTROY:

				if (aqua_brsh != NULL){
					DeleteObject(aqua_brsh);
					aqua_brsh = NULL;
				}

				PostQuitMessage(0);
				break;
			}

			return DefWindowProc(hwnd, message, polym_param, sub_param);
		}

		static void init_index(uint index){ buttons[index] = false; }
		static bool clicked(uint index){
			bool res = buttons[index];
			init_index(index);
			return res;
		}

		static HMENU get_child_ID(){ return reinterpret_cast<HMENU>(child_ID++); }

	};

}