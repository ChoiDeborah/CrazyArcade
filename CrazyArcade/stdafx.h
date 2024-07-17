// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

#pragma comment(lib, "vfw32.lib")
#include <Vfw.h>

#include <io.h>

#pragma comment(lib, "fmod_vc.lib")
#include "fmod.h"

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <list>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <time.h>

using namespace std;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "Extern.h"
#include "Define.h"
#include "Struct.h"
#include "Enum.h"
#include "Typedef.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Function.h"
