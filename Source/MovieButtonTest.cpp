#include "MovieButtonTest.h"
#include <DxLib.h>
#include "../Library/Input.h"
#include "../Library/SceneManager.h"
#include "../Library/GuiButton.h"

/// <summary>
/// ボタンに動画もつけれます
/// 読み込めたかの確認に下書きのテキストを活用
/// 今回はmovie_07がありません。
/// </summary>

MovieButtonTest::MovieButtonTest()
    : bgImage(-1)
    , b01(nullptr), b02(nullptr)
    , movie_05(-1), movie_07(-1)
    , currentSelect(0)
{
    //背景画像のロード
    bgImage = LoadGraph("data/BG_Ti_01.png");

    //ボタンの配置情報設定 
    int bx = 200;  //ボタンのX座標
    int by = 200;  //1つ目のボタンのY座標
    int bw = 800;  //ボタンの横幅
    int bh = 200;  //ボタンの高さ
    int bi = 250;  //ボタン同士の間隔

    //動画ファイルのロード
    int movie_04 = OpenMovieToGraph("data/UI_Ti_04.mp4");
    int movie_06 = OpenMovieToGraph("data/UI_Ti_06.mp4");

    //切り替え用のペア動画
    movie_05 = OpenMovieToGraph("data/UI_Ti_05.mp4");
    movie_07 = OpenMovieToGraph("data/UI_Ti_07.mp4");


    //ボタン1の生成と設定
    b01 = new GuiButton(bx, by, bw, bh, "Button 1");
    b01->SetImage(movie_04);
    b01->SetIsMovie(true);

    //ボタン1のクリック処理：04 と 05 を交互に切り替える
    b01->onClick = [this, movie_04]() {
        //現在のボタンの画像が 04 の場合
        if (this->b01->imageHandle == movie_04) {
            //05 に切り替えて、動画を最初に戻す
            this->b01->SetImage(this->movie_05);
            SeekMovieToGraph(this->movie_05, 0);
        }
        //現在のボタンの画像が 05 の場合
        else if (this->b01->imageHandle == this->movie_05) {
            //04 に切り替えて、動画を最初に戻す
            this->b01->SetImage(movie_04);
            SeekMovieToGraph(movie_04, 0);
        }
        };


    //ボタン2の生成と設定
    b02 = new GuiButton(bx, by + bi, bw, bh, "Button 2");
    b02->SetImage(movie_06);
    b02->SetIsMovie(true);

    //ボタン2のクリック処理：06 と 07 を交互に切り替える（往復処理）
    b02->onClick = [this, movie_06]() {
        //現在のボタンの画像が 06 の場合
        if (this->b02->imageHandle == movie_06) {
            //07 に切り替えて、動画を最初に戻す
            this->b02->SetImage(this->movie_07);
            SeekMovieToGraph(this->movie_07, 0);
        }
        //現在のボタンの画像が 07 の場合
        else if (this->b02->imageHandle == this->movie_07) {
            //06 に切り替えて、動画を最初に戻す
            this->b02->SetImage(movie_06);
            SeekMovieToGraph(movie_06, 0);
        }
        };
}

MovieButtonTest::~MovieButtonTest()
{
    //背景画像の削除
    DeleteGraph(bgImage);

    //ボタン1用の動画ハンドルを両方とも解放する
    if (b01 != nullptr) {
        if (b01->imageHandle == movie_05) {
            //現在05がセットされているなら、まだ消えていない04を削除
            int movie_04 = OpenMovieToGraph("data/UI_Ti_04.mp4"); // 安全な紐付けのため
            DeleteGraph(movie_04);
        }
        else {
            //現在04がセットされている（またはエラー）なら05を削除
            if (movie_05 != -1) DeleteGraph(movie_05);
        }
    }

    //ボタン2用の動画ハンドルを両方とも解放する
    if (b02 != nullptr) {
        if (b02->imageHandle == movie_07) {
            int movie_06 = OpenMovieToGraph("data/UI_Ti_06.mp4");
            DeleteGraph(movie_06);
        }
        else {
            if (movie_07 != -1) DeleteGraph(movie_07);
        }
    }
}

void MovieButtonTest::Update()
{
    if (Input::IsKeyDown(KEY_INPUT_ESCAPE)) {
        SceneManager::ChangeScene("TEST");
        return;
    }

    //上下キー選択
    if (Input::IsKeyDown(KEY_INPUT_DOWN)) currentSelect = (currentSelect + 1) % 2;
    if (Input::IsKeyDown(KEY_INPUT_UP))   currentSelect = (currentSelect - 1 + 2) % 2;

    //マウスオーバー選択
    if (b01->IsMouseOver()) currentSelect = 0;
    if (b02->IsMouseOver()) currentSelect = 1;

    b01->SetFocus(currentSelect == 0);
    b02->SetFocus(currentSelect == 1);

    //ボタンの更新処理（GuiButton内の動画再生/一時停止処理が走ります）
    b01->Update();
    b02->Update();

	//再生中の動画があれば、フレームを進める
    if (b01->imageHandle != -1 && GetMovieStateToGraph(b01->imageHandle) == 1) {
        UpdateMovieToGraph(b01->imageHandle);
    }
    if (b02->imageHandle != -1 && GetMovieStateToGraph(b02->imageHandle) == 1) {
        UpdateMovieToGraph(b02->imageHandle);
    }

    //下書きのテキストをデバッグ情報表示に
    //ボタン1の確認
    std::string h01_str = " (Handle: " + std::to_string(b01->imageHandle);
    if (b01->imageHandle != -1) {
        h01_str += " State: " + std::to_string(GetMovieStateToGraph(b01->imageHandle)) + ")";
    }
    else {
        h01_str += " INVALID)";
    }
    b01->label = "Button 1" + h01_str;

    //ボタン2の確認
    std::string h02_str = " (Handle: " + std::to_string(b02->imageHandle);
    if (b02->imageHandle != -1) {
        h02_str += " State: " + std::to_string(GetMovieStateToGraph(b02->imageHandle)) + ")";
    }
    else {
        h02_str += " INVALID)";
    }
    b02->label = "Button 2" + h02_str;
}

void MovieButtonTest::Draw()
{
    //背景の描画
    if (bgImage != -1) {
        DrawExtendGraph(0, 0, 1280, 720, bgImage, FALSE);
    }

    //各ボタンの描画
    b01->Draw();
    b02->Draw();
}