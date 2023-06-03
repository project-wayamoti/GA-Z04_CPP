#include "DxLib.h"
#include <math.h>
#include <cmath>
#define WIDTH 1280
#define HEIGHT 720

// プログラムの最初はWinMainで始める
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### 初期設定 #####//
    // ウィンドウモード設定
    ChangeWindowMode(TRUE);

    // 画面サイズ設定
    SetGraphMode(WIDTH, HEIGHT, 32);

    // DXライブラリ初期化処理
    if (DxLib_Init() == -1) {
        return -1; // エラーが起きたら直ちに終了
    }



    //## 環境に応じて設定

    // 減衰値
    // ※液晶のフレームレートによって変化することがわかっているため
    // 動きが早すぎる場合やおそすぎる場合はこの数値を調整すること。
    float decay = 0.97; // 60=0.97 300=0.9925 or 0.99

    // キー入力時の移動速度
    int moveSpeed = 15;

    // 除法数値
    // ※液晶のフレームレートによって変化することがわかっているため
    // 動きが早すぎる場合やおそすぎる場合はこの数値を調整すること。
    float divisor = 0.25; // 60=0.25 300=0.01



    //## 固有の設定

    // 色の設定
    unsigned int mainColor = GetColor(0, 0, 255);
    unsigned int subColor = GetColor(255, 0, 0);

    // 移動物体初期座標設定
    float x = WIDTH / 2;
    float y = HEIGHT / 2;
    float x_ = 1;
    float y_ = 1;

    // 固定
    float x1 = 500;
    float y1 = 370;

    // 移動物体の箱サイズ
    int size = 32;

    // 箱のサイズの半分を計算
    int sc = size / 2;

    // メインループ（描画処理）
    while (ProcessMessage() == 0) {
        // 画面の更新
        ClearDrawScreen();


        //##### ここから 中央物体の処理
        //球体移動処理
        DrawCircle(x, y, size, mainColor, TRUE); //TRUE 塗りつぶし / FLASE 塗りつぶさない

        //移動計算
        x += x_;
        //y += y_;
        if (x == 0 + size)      x_ = +1;
        if (x == WIDTH - size)  x_ = -1;
        //if (y == 0 + size)      y_ = +1;
        //if (y == HEIGHT - size) y_ = -1;

        /* 斜め移動
        if (x == 0 + size)      x_ = +1;
        if (x == WIDTH - size)  x_ = -1;
        if (y == 0 + size)      y_ = +1;
        if (y == HEIGHT - size) y_ = -1;
        */

        // 2つの円の中心座標の差分を計算
        float dx = x1 - x;
        float dy = y1 - y;

        // 2つの円の中心座標の距離を計算
        float distance = std::sqrt((dx * dx) + (dy * dy));



        //回転可能範囲
        DrawCircle(500, 370, 16, GetColor(255, 255, 255), FALSE); //TRUE 塗りつぶし / FLASE 塗りつぶさない
        DrawCircle(500, 370, 64, GetColor(255, 255, 255), FALSE); //TRUE 塗りつぶし / FLASE 塗りつぶさない




        //##### ここから 描画処理
        printfDx("x:%f y:%f\n", x, y);
        printfDx("x:%f y:%f\n", x1, y1);
        printfDx("x:%f y:%f\n", dx, dy);
        printfDx("%d\n", distance);


        // 画面の更新（必須）
        ScreenFlip();
        clsDx(); // デバッグログ画面をクリアする処理
    }

    DxLib_End(); // DX Libraryの使用を終了する処理
    return 0;    // ソフトを正常終了
}