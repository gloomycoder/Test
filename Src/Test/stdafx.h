// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "CommonInclude.h"


#ifdef _DEBUG
	#ifdef _WIN64
		#pragma comment(lib, "Behavior_x64_Debug")
	#else
		#pragma comment(lib, "Behavior_x86_Debug")
	#endif
#else
	#ifdef _WIN64
		#pragma comment(lib, "Behavior_x64_Release")
	#else
		#pragma comment(lib, "Behavior_x86_Rlelase")
	#endif
#endif