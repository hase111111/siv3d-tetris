#include"DxLib.h"
#include"SystemMain.h"
#include"Define.h"
#include"Looper.h"
#include"Font.h"

//DXライブラリやゲームの初期処理
bool SystemMain::initialize() const
{
    SetAlwaysRunFlag(TRUE);                                     //ウィンドウがノンアクティブでも実行
    SetWindowSizeChangeEnableFlag(FALSE);                        //ウィンドウサイズを自由に変更できるようにする
    SetOutApplicationLogValidFlag(FALSE);                       //ログ出力しない
    SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);   //フルスクリーン時に縦横比を維持する
    SetWindowText("Tetris");                                          //ウィンドウタイトルを付ける
    ChangeWindowMode(TRUE);                                     //ウィンドウモードに変更
    SetWindowSizeExtendRate(1.0);                               //ウィンドウサイズを変更したい時はここに倍率を指定する
    const int COLOR_BIT = 32;                                   //色のbit数。通常32で良いが軽くするなら16にする
    SetGraphMode(Define::WIN_SIZEX, Define::WIN_SIZEY, COLOR_BIT);    //ゲーム画面の解像度を設定する
    SetWindowIconID(101);

    if (DxLib_Init()) {                         //DXライブラリ初期化処理
        return false;                           //異常終了したら即座にやめる
    }

    MV1SetLoadModelUsePhysicsMode(DX_LOADMODEL_PHYSICS_REALTIME);
    SetDrawScreen(DX_SCREEN_BACK);              //裏画面処理を設定する
    Font::getIns()->LoadFont();
    return true;
}

//DXライブラリやゲームの終了処理
void SystemMain::finalize() const
{
    Font::getIns()->releaseFont();
    DxLib_End();
}

//メイン処理
void SystemMain::main() const
{
    Looper looper;
    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
        if (!looper.loop()) {
            break;
        }
    }   
}
