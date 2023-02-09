#include "GameClearScene.h"
#include "TitleScene.h"
#include "KeyManager.h"
#include "DxLib.h"

//コンストラクタ
GameClearScene::GameClearScene()
{

}

//描画以外の更新を実装する
void GameClearScene::Update()
{

}

//描画に関することを実装する
void GameClearScene::Draw() const
{
	DrawString(350, 300, "GameClear", GetColor(255, 0, 0));
	DrawString(350, 320, "スペースキーでタイトル", GetColor(255, 255, 255));
}

//シーンの変更処理
AbstractScene* GameClearScene::ChangeScene()
{
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE)) {

		return new TitleScene;
	}
	return this;
}