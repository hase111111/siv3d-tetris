#include"DxLib.h"
#include"SystemMain.h"
#include"Define.h"
#include"Looper.h"
#include"Font.h"

//DX���C�u������Q�[���̏�������
bool SystemMain::initialize() const
{
    SetAlwaysRunFlag(TRUE);                                     //�E�B���h�E���m���A�N�e�B�u�ł����s
    SetWindowSizeChangeEnableFlag(FALSE);                        //�E�B���h�E�T�C�Y�����R�ɕύX�ł���悤�ɂ���
    SetOutApplicationLogValidFlag(FALSE);                       //���O�o�͂��Ȃ�
    SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);   //�t���X�N���[�����ɏc������ێ�����
    SetWindowText("Tetris");                                          //�E�B���h�E�^�C�g����t����
    ChangeWindowMode(TRUE);                                     //�E�B���h�E���[�h�ɕύX
    SetWindowSizeExtendRate(1.0);                               //�E�B���h�E�T�C�Y��ύX���������͂����ɔ{�����w�肷��
    const int COLOR_BIT = 32;                                   //�F��bit���B�ʏ�32�ŗǂ����y������Ȃ�16�ɂ���
    SetGraphMode(Define::WIN_SIZEX, Define::WIN_SIZEY, COLOR_BIT);    //�Q�[����ʂ̉𑜓x��ݒ肷��
    SetWindowIconID(101);

    if (DxLib_Init()) {                         //DX���C�u��������������
        return false;                           //�ُ�I�������瑦���ɂ�߂�
    }

    MV1SetLoadModelUsePhysicsMode(DX_LOADMODEL_PHYSICS_REALTIME);
    SetDrawScreen(DX_SCREEN_BACK);              //����ʏ�����ݒ肷��
    Font::getIns()->LoadFont();
    return true;
}

//DX���C�u������Q�[���̏I������
void SystemMain::finalize() const
{
    Font::getIns()->releaseFont();
    DxLib_End();
}

//���C������
void SystemMain::main() const
{
    Looper looper;
    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
        if (!looper.loop()) {
            break;
        }
    }   
}
