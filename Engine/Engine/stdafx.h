// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h
// �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h
// �t�@�C�� ���L�q���܂��B
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN // Windows
                            // �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>

// C �����^�C�� �w�b�_�[ �t�@�C��
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <tchar.h>

// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă�������
#if 1
#define SCREEN_SIZE_W 1280
#define SCREEN_SIZE_H 760
#else
#define SCREEN_SIZE_W 40
#define SCREEN_SIZE_H 40
#endif
#define SCREEN_PIXELS (SCREEN_SIZE_W * SCREEN_SIZE_H)
