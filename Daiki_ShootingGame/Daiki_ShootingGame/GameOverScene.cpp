#include "GameOverScene.h"
#include "TitleScene.h"
#include "KeyManager.h"
#include "DxLib.h"

//コンストラクタ
GameOverScene::GameOverScene()
{

}

//描画以外の更新を実装する
void GameOverScene::Update()
{
	
}

//描画に関することを実装する
void GameOverScene::Draw() const
{
	DrawString(350, 300, "GameOver", GetColor(255, 0, 0));
	DrawString(350, 320, "スペースキーでタイトル", GetColor(255, 255, 255));
}

//シーンの変更処理
AbstractScene* GameOverScene::ChangeScene()
{
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE)) {

		return new TitleScene;
	}
	return this;
}