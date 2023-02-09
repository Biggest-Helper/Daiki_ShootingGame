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
	DrawString(350, 300, "タイトル画面", GetColor(255, 255, 255));
	DrawString(350, 320, "スペースキーでゲームメイン", GetColor(255, 255, 255));
}

//シーンの変更処理
AbstractScene* TitleScene::ChangeScene()
{
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE)) {
		
		return new GameMainScene;
	}

	return this;
}