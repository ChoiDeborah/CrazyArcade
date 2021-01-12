// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

#include <io.h>

#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")

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
