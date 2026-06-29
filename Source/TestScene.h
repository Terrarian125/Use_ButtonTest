#pragma once
#include "../Library/SceneBase.h"
#include "../Library/GuiButton.h"
#include <vector>

/// <summary>
/// </summary>
class TestScene : public SceneBase
{
public:
    TestScene();
    ~TestScene();

    void Update() override;
    void Draw() override;

private:
    int bgImage;                     // 背景画像のグラフィックハンドル
    int btnImage;                    // ボタン画像のグラフィックハンドル
    std::vector<GuiButton*> buttons; // ボタンを管理する動的配列
};