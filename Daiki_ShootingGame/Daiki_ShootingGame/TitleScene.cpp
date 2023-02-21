#include "TitleScene.h"
#include "GameMainScene.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "DxLib.h"

//コンストラクタ
TitleScene::TitleScene()
{

}

//描画以外の更新を実装する
void TitleScene::Update()
{
	
}

//描画に関することを実装する
void TitleScene::Draw() const
{
	SetFontSize(100);
	DrawString(100, 100, "SUPER HOT Shoothing 3", GetColor(255, 0, 0));
	SetFontSize(20);
	DrawString(500, 450, "スペースキーで START !", GetColor(255, 255, 255));
}

//シーンの変更処理
AbstractScene* TitleScene::ChangeScene()
{
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE)) {
		
		return new GameMainScene;
	}

	return this;
}