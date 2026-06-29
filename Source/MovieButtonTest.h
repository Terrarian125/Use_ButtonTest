#pragma once
#include "../Library/SceneBase.h"
#include "../Library/GuiButton.h"
#include <vector>
#include <string>

class MovieButtonTest : public SceneBase
{
public:
    MovieButtonTest();
    ~MovieButtonTest();

    void Update() override;
    void Draw() override;

private:
    int bgImage;          // 背景画像のグラフィックハンドル
    // 各ボタンに対応する動画ハンドル
    GuiButton* b01;
    GuiButton* b02;

    // 切り替え用に控えておく動画ハンドル
    int movie_05;
    int movie_07;

    int currentSelect;    // 現在選択されているボタンのインデックス (0~3)
};