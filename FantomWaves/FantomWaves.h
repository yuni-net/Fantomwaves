/*
 * WELCOME TO FantomWaves !!
 *
 * this library contains utility class and function and etc...
 *
 * Version: 5.2.0
 * FinalUpdate: 21st Sep 2015
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

#include "fw_includes.h"

#include "fw_typedef.h"
#include "fw_eps.h"
#include "fw_cast.h"
#include "fw_cnct.h"
#include "fw_popup.h"
#include "fw_WindowEx.h"
#include "fw_window.h"
#include "fw_view.h"
#include "fw_trade.h"
#include "fw_Array.h"
#include "fw_vtypedef.h"

#ifdef FW_TYPEDEF_
#include "fw_publicdef.h"
#endif

#include "fw_newshortcut.h"
#include "fw_delete.h"
#include "fw_zeromemory.h"
#include "fw_exerror.h"
#include "fw_nullice.h"
#include "fw_slice.h"
#include "fw_thread.h"
#include "fw_exeexe.h"
#include "fw_filesize.h"
#include "fw_path.h"
#include "fw_newdire.h"
#include "fw_Binfile.h"
#include "fw_ring.h"
#include "fw_stdrandom.h"
#include "fw_wav.h"
#include "fw_xrandom.h"
#include "fw_xy2radian.h"
#include "fw_NetWork.h"
#include "fw_P2P.h"
#include "fw_UDP_cliant.h"

#ifndef FantomWaves_developing_
	#ifdef _DEBUG
	#pragma comment(lib, "FantomWavesd.lib")
	#else
	#pragma comment(lib, "FantomWavesr.lib")
	#endif
#endif


