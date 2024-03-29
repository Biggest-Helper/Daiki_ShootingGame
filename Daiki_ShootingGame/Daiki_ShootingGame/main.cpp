#include "DxLib.h"
#include "common.h"
#include "SceneManager.h"
#include "GameMainScene.h"
#include "TitleScene.h"

/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// タイトルを test に変更
	SetMainWindowText("シューティングゲーム");

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	//画面サイズ変更
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_BIT_16);

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	SetFontSize(20);		// 文字サイズを設定

	//シーンマネジャーのオブジェクトの作成
	SceneManeger SceneMng( dynamic_cast<AbstractScene*>( new TitleScene()) );
	/*SceneManeger SceneMng( dynamic_cast<AbstractScene*>( new TitleScene() ) );*/

	// ゲームループ
	while (ProcessMessage() == 0) 
	{

		ClearDrawScreen();		// 画面の初期化

		

		SceneMng.Update();      //シーンの更新処理
		SceneMng.Draw();        //シーンの描画処理
		if (SceneMng.ChangeScene() == nullptr)    //シーンの変更処理
		{
			DxLib_End();	// DXライブラリ使用の終了処理
			return 0;	    // ソフトの終了
		}

		ScreenFlip();		// 裏画面の内容を表画面に反映
	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	    // ソフトの終了
}