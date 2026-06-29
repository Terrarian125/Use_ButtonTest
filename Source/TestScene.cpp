#include "TestScene.h"
#include <DxLib.h>
#include "../Library/Input.h"
#include "../Library/SceneManager.h"
#include "../Library/GuiButton.h"

TestScene::TestScene()
{
    //背景画像のロード
    bgImage = LoadGraph("data/BG_Ti_00.png");

    //メインメニューのボタン配置設定
    int bx = 50;  //ボタンのX座標
    int by = 200; //Y座標
    int bw = 400; //ボタンの幅
    int bh = 90;  //ボタンの高さ
    int bi = 100; //ボタン間隔

    //ボタン画像のロード
    int btnImg_b00 = LoadGraph("data/UI_Ti_00.png");
    int btnImg_b01 = LoadGraph("data/UI_Ti_01.png");
    int btnImg_b02 = LoadGraph("data/UI_Ti_02.png");
    int btnImg_b03 = LoadGraph("data/UI_Ti_03.png");

    //NewGameボタン
    auto b00 = new GuiButton(bx, by, bw, bh, "NewGame");
    b00->SetImage(btnImg_b00);
    b00->onClick = []() {};
    buttons.push_back(b00);

    //Continueボタン
    auto b01 = new GuiButton(bx, by + bi, bw, bh, "Continue");
    b01->SetImage(btnImg_b01);
    b01->onClick = []() {  };
    buttons.push_back(b01);

    //Optionボタン
    auto b02 = new GuiButton(bx, by + bi * 2, bw, bh, "Option");
    b02->SetImage(btnImg_b02);
    b02->onClick = []() {};
    buttons.push_back(b02);

    //Exitボタン
    auto b03 = new GuiButton(bx, by + bi * 3, bw, bh, "Exit");
    b03->SetImage(btnImg_b03);
    b03->onClick = []() {};
    buttons.push_back(b03);
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
    //ボタンの更新処理
    for (auto b : buttons) {
        b->Update();
    }
}


void TestScene::Draw()
{
    //背景描画
    DrawExtendGraph(0, 0, 1280, 720, bgImage, FALSE);

    //メインメニューボタン
    for (auto b : buttons) b->Draw();
}