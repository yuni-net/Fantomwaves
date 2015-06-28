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
*wav �l��Ԃ��Ȃ��R���g���[���p�X���������̂��C��

[0.3.1]
*wav �T�|�[�g���Ă��Ȃ��`�����N�������Ă����܂����Ɠǂݔ�΂��悤�ɏC��

[0.3.0]
*xy2radian ������

[0.2.0]
*Binfile as_string(), head(), byte(), finished() ��ǉ�

[0.1.4]
* wav �ꕔ�́A�܂��������t�H�[�}�b�g�ɑΉ�

[0.1.3]
* Binfile ��x�ǂݍ��ނƊJ�����ςȂ��ɂȂ�o�O���C��

[0.1.2]
* delfile�֐��̖߂�l���t�������̂��C��

[0.1.1]
* vector reqsize�̃o�O���C��

[0.1.0]
* xrandom��ǉ�

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


