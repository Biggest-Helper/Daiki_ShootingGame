#include "SceneManager.h"
#include "KeyManager.h"

//メンバ変数の値を書き換えるのがアップデート関数
void SceneManeger::Update()
{
	KeyManager::Updata();
	//現在シーンのアップデートを実行
	mScene->Update();
}

//描画処理のみを行う関数
void SceneManeger::Draw() const
{
	//現在シーンの描画関数を実行
	mScene->Draw();
}

//シーンの変更処理関数
AbstractScene* SceneManeger::ChangeScene()
{
	AbstractScene* nextScene = mScene->ChangeScene();

	//次のシーンが現在シーンと別なら変更
	if (nextScene != mScene)
	{
		delete mScene;
		mScene = nextScene;
	}

	return nextScene;
}