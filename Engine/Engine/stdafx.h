// stdafx.h : 標準のシステム インクルード ファイルのインクルード
// ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード
// ファイル を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN  // Windows
                             // ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <tchar.h>

// TODO: プログラムに必要な追加ヘッダーをここで参照してください
#if 1
#define SCREEN_SIZE_W 1280
#define SCREEN_SIZE_H 760
#else
#define SCREEN_SIZE_W 40
#define SCREEN_SIZE_H 40
#endif
#define SCREEN_PIXELS (SCREEN_SIZE_W * SCREEN_SIZE_H)
