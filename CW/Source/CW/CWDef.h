//----------------------------------------------------------------------//
//	"CWDef.h"															//
//----------------------------------------------------------------------//
//	Copyright (c) 2024 BeeTribe Co.,Ltd. All Rights Reserved.			//
//																		//
//			24/01/25(��)		Programming by Satoshi Nishimura		//
//----------------------------------------------------------------------//

#ifndef	_CWDef_h_
#define	_CWDef_h_

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	// �f�o�b�O�r���h�ł̒�`
	#define CW_DEBUG (1)
	#define CW_DEMO (0)
#else  // UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	// �����[�X�r���h�ł̒�`
	#define CW_DEBUG (0)
	#define CW_DEMO (0)
#endif // UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT


#if !NO_LOGGING
	#if !CW_DEMO
		#define CW_ENABLE_DEBUGOUTPUT	(1)
	#else	// CW_DEMO
		#define CW_ENABLE_DEBUGOUTPUT	(0)
	#endif // CW_DEMO
#else // NO_LOGGING
	#define CW_ENABLE_DEBUGOUTPUT	(0)
#endif // NO_LOGGING

#if CW_ENABLE_DEBUGOUTPUT
	#define CW_ASSERT(__EXPRESSION__, ...)					checkf(__EXPRESSION__, ##__VA_ARGS__)
	#define CW_ERROR(__FORMAT__, ...)						UE_LOG(LogTemp, Error, __FORMAT__, ##__VA_ARGS__)
	#define CW_WARNING(__FORMAT__, ...)						UE_LOG(LogTemp, Warning, __FORMAT__, ##__VA_ARGS__)
	#define CW_LOG(__FORMAT__, ...)							UE_LOG(LogTemp, Log, __FORMAT__, ##__VA_ARGS__)
#else // CW_ENABLE_DEBUGOUTPUT
	#define CW_ASSERT(__EXPRESSION__, ...)
	#define CW_ERROR(__FORMAT__, ...)
	#define CW_WARNING(__FORMAT__, ...)
	#define CW_LOG(__FORMAT__, ...)
#endif// CW_ENABLE_DEBUGOUTPUT



namespace CW{
void DebugPrintScreen(const FString& text, const FLinearColor& textColor, float screenX, float screenY, float duration, float scale);
}

#if CW_DEBUG
	#define CW_DEBUG_DISPLAY(text, color, x, y, duration, scale) CW::DebugPrintScreen(text, color, x, y, duration, scale)
#else
	#define CW_DEBUG_DISPLAY(text, color, x, y, duration, scale)
#endif

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
class UCWGameInstance;
class ACWPlayerController;

UCWGameInstance* GetCWGameInstance();
ACWPlayerController* GetCWPlayerController();

#endif	//	_CWDef_h_
//----------------------------------------------------------------------//
//	"CWDef.h"	[ END OF FILE ]											//
//----------------------------------------------------------------------//
