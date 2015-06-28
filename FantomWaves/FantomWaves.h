/*
 * WELCOME TO FantomWaves !!
 *
 * this library contains utility class and function and etc...
 *
 * Version: 0.3.2
 * FinalUpdate: 23th Feb 2015
 * Author: yuni.net.liberty
 *
 */

// release note **************************************

#if 0

[0.3.2]
*wav 値を返さないコントロールパスがあったのを修正

[0.3.1]
*wav サポートしていないチャンクがあってもうまいこと読み飛ばすように修正

[0.3.0]
*xy2radian を実装

[0.2.0]
*Binfile as_string(), head(), byte(), finished() を追加

[0.1.4]
* wav 一部の、まちがったフォーマットに対応

[0.1.3]
* Binfile 一度読み込むと開きっぱなしになるバグを修正

[0.1.2]
* delfile関数の戻り値が逆だったのを修正

[0.1.1]
* vector reqsizeのバグを修正

[0.1.0]
* xrandomを追加

#endif


#ifdef FW_STD_DEF_
#define FW_TYPEDEF_
#define FW_CAST_
#define FW_POP_UP_
#endif

#ifdef FW_DX_DEF_
#define FW_USE_DXLIB_
#endif

#ifdef FW_STD_PROGRAMABLE_DEF_
#define FW_PROGRAMABLE_POP_UP_
#endif

#ifdef FW_DX_PROGRAMABLE_DEF_
#define FW_GRAPHIC_DRAG_
#endif


#ifdef FW_ALL_POP_UP_
#define FW_POP_UP_
#define FW_PROGRAMABLE_POP_UP_
#endif

#ifdef FW_POP_UP_
#define FW_VECTOR_POP_UP_
#define FW_DD_POP_UP_
#define FW_BFILE_POP_UP_
#define FW_THREAD_POP_UP_
#endif

#ifdef FW_PROGRAMABLE_POP_UP_
#define FW_GRAPHIC_POP_UP_
#define FW_EACHFRAME_POP_UP_
#endif

#ifdef FW_DD_POP_UP_
#define FW_DDPATH_POP_UP_
#define FW_DDFILE_POP_UP_
#define FW_DDDIRE_POP_UP_
#endif

#include "includes.h"

#include "typedef.h"
#include "eps.h"
#include "cast.h"
#include "cnct.h"
#include "popup.h"
#include "newwin.h"
#include "window.h"
#include "view.h"
#include "trade.h"
#include "vector.h"
#include "vtypedef.h"

#ifdef FW_TYPEDEF_
#include "publicdef.h"
#endif

#include "newshortcut.h"
#include "delete.h"
#include "zeromemory.h"
#include "exerror.h"
#include "nullice.h"
#include "slice.h"
#include "thread.h"
#include "exeexe.h"
#include "filesize.h"
#include "path.h"
#include "newdire.h"
#include "bfile.h"
#include "ring.h"
#include "stdrandom.h"
#include "wav.h"
#include "xrandom.h"
#include "xy2radian.h"

#ifndef FantomWaves_developing_
	#ifdef _DEBUG
	#pragma comment(lib, "FantomWavesd.lib")
	#else
	#pragma comment(lib, "FantomWavesr.lib")
	#endif
#endif


