#define _CRT_SECURE_NO_DEPRECATE

#pragma once

#include "includes.h"
#include "typedef.h"

namespace fw
{

	const uint minID = 100;

	class newwin
	{
		static std::map<uint, bool> buttons;
		static uint ChildID;

		WNDCLASSEX wc;
		HWND mainWH;

		static bool notmine(const uint childID){ return childID < minID || childID >= ChildID; }

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam){
			static HBRUSH aquaBrsh = NULL;
			uint childID = static_cast<uint>(GetWindowLongPtr(reinterpret_cast<HWND>(lParam), GWLP_ID));

			switch (uiMsg)
			{

			case WM_COMMAND:

				if (notmine(childID)) break;

				buttons[childID - 100] = true;
				break;

			case WM_CTLCOLORSTATIC:

				if (notmine(childID)) break;

				if (childID % 2){
					// îwåiêFÇîíêFÇ…ê›íË
					SetBkColor(reinterpret_cast<HDC>(wParam), 0xffffff);
					return reinterpret_cast<LRESULT>(GetStockObject(WHITE_BRUSH));
				}
				else{
					// îwåiêFÇêÖêFÇ…ê›íË
					SetBkColor(reinterpret_cast<HDC>(wParam), RGB(200, 255, 255));
					if (aquaBrsh == NULL) aquaBrsh = CreateSolidBrush(RGB(200, 255, 255));
					return reinterpret_cast<LRESULT>(aquaBrsh);
				}
				break;

			case WM_DESTROY:

				if (aquaBrsh != NULL){
					DeleteObject(aquaBrsh);
					aquaBrsh = NULL;
				}

				PostQuitMessage(0);
				break;
			}

			return DefWindowProc(hwnd, uiMsg, wParam, lParam);
		}

		static void InitIndex(uint index){ buttons[index] = false; }
		static bool clicked(uint index){
			bool res = buttons[index];
			InitIndex(index);
			return res;
		}

		static HMENU childID(){ return reinterpret_cast<HMENU>(ChildID++); }

	public:

		class checkbox{
			HWND handle;
			WORD id;

		public:

			checkbox(){ handle = NULL; }
			checkbox & create(const HWND windle, const std::string & str, int x, int y, int width, int height){
				if (handle != NULL) del();

				handle = CreateWindow(
					"BUTTON",
					str.c_str(),
					WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
					x, y,
					width, height,
					windle,
					newwin::childID(),
					GetModuleHandle(NULL),
					NULL
					);

				return *this;
			}
			checkbox & create(const newwin & w, const std::string & str, int x, int y, int width, int height){
				return create(w.handle(), str, x, y, width, height);
			}
			checkbox(const newwin & w, const std::string & str, int x, int y, int width, int height){ create(w, str, x, y, width, height); }

			void check(){ SendMessage(handle, BM_SETCHECK, BST_CHECKED, 0); }
			void uncheck(){ SendMessage(handle, BM_SETCHECK, BST_UNCHECKED, 0); }
			bool ifcheck(){ return BST_CHECKED == SendMessage(handle, BM_GETCHECK, 0, 0); }

			checkbox & del(){
				DestroyWindow(handle);
				return *this;
			}
			~checkbox(){ del(); }
		};

		class input{
			HWND handle;

		public:

			input(){ handle = NULL; }
			input & create(const HWND windle, const std::string & str, int x, int y, int width, int height){
				if (handle != NULL) del();

				handle = CreateWindow(
					"EDIT",
					str.c_str(),
					WS_CHILD | WS_VISIBLE,
					x, y,
					width, height,
					windle,
					newwin::childID(),
					GetModuleHandle(NULL),
					NULL
					);

				return *this;
			}
			input & create(const newwin & w, const std::string & str, int x, int y, int width, int height){
				return create(w.handle(), str, x, y, width, height);
			}
			input(const newwin & w, const std::string & str, int x, int y, int width, int height){ create(w, str, x, y, width, height); }

			std::string gets(){
				char content[257];
				GetWindowText(handle, content, 256);
				return content;
			}

			input & sets(const std::string & output){
				SetWindowText(handle, output.c_str());
				return *this;
			}

			input & del(){
				DestroyWindow(handle);
				return *this;
			}
			~input(){ del(); }
		};

		class text{
			HWND handle;

		public:

			text(){ handle = NULL; }
			text & create(const HWND windle, const std::string & str, int x, int y, int width, int height){
				if (handle != NULL) del();

				handle = CreateWindow(
					"STATIC",
					str.c_str(),
					WS_CHILD | WS_VISIBLE,
					x, y,
					width, height,
					windle,
					newwin::childID(),
					GetModuleHandle(NULL),
					NULL
					);

				return *this;
			}
			text & create(const newwin & w, const std::string & str, int x, int y, int width, int height){
				return create(w.handle(), str, x, y, width, height);
			}
			text(const newwin & w, const std::string & str, int x, int y, int width, int height){ create(w, str, x, y, width, height); }

			std::string gets(){
				char content[257];
				GetWindowText(handle, content, 256);
				return content;
			}

			text & sets(const std::string & output){
				SetWindowText(handle, output.c_str());
				return *this;
			}

			text & del(){
				DestroyWindow(handle);
				return *this;
			}
			~text(){ del(); }
		};

		class button{
			HWND handle;
			uint index;

		public:

			button(){ handle = NULL; }
			button & create(const newwin & w, const std::string & str, int x, int y, int width, int height, bool defbutton = false){
				if (handle != NULL) del();

				int attribute = WS_CHILD | WS_VISIBLE;
				if (defbutton) attribute = attribute | BS_DEFPUSHBUTTON;
				else attribute = attribute | BS_PUSHBUTTON;

				HMENU id = newwin::childID();
				index = reinterpret_cast<uint>(id);
				index -= 100;

				newwin::InitIndex(index);

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
			button(const newwin & w, const std::string & str, int x, int y, int width, int height, bool defbutton = false){ create(w, str, x, y, width, height, defbutton); }

			bool clicked() const { return newwin::clicked(index); }

			button & del(){
				DestroyWindow(handle);
				return *this;
			}
			~button(){ del(); }
		};

		newwin(){}
		void init(const std::string &title, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT){
			wc.cbClsExtra = 0;
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.cbWndExtra = 0;
			wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_APPWORKSPACE + 1);
			wc.hCursor = LoadCursor(GetModuleHandle(NULL), IDC_ARROW);
			wc.hIcon = NULL;
			wc.hIconSm = NULL;
			wc.hInstance = GetModuleHandle(NULL);
			wc.lpfnWndProc = WindowProc;
			wc.lpszClassName = "myClass";
			wc.lpszMenuName = NULL;
			wc.style = CS_DBLCLKS;

			RegisterClassEx(&wc);

			mainWH = CreateWindowEx(
				WS_EX_TOOLWINDOW,
				"myClass",
				title.c_str(),
				WS_BORDER | WS_SYSMENU,
				CW_USEDEFAULT, CW_USEDEFAULT,
				width, height,
				NULL, NULL, GetModuleHandle(NULL), NULL
				);

			ShowWindow(mainWH, SW_SHOWDEFAULT);
			UpdateWindow(mainWH);
		}
		newwin(const std::string &title, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT){ init(title, width, height); }

		HWND handle() const { return mainWH; }

		newwin & del(){
			for (uint i = minID; i < ChildID; ++i) DestroyWindow(reinterpret_cast<HWND>(i));
			DestroyWindow(mainWH);
			return *this;
		}
		~newwin(){ del(); }
	};

}