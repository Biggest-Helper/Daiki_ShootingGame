#include "DxLib.h"
#include "KeyManager.h"

//キー変数の初期化
char KeyManager::oldKey[256];    //前のキー
char KeyManager::nowKey[256];    //現在のキー

int KeyManager::oldMouse;   //前のマウスキー
int KeyManager::nowMouse;   //現在のマウスキー

void KeyManager::Updata()
{
	for (int i = 0; i < 256; i++)
	{
		oldKey[i] = nowKey[i];
	}

	if (GetHitKeyStateAll(nowKey) == -1)
	{
		throw - 1;
	}

	oldMouse = nowMouse;
	nowMouse = GetMouseInput();
}

bool KeyManager::OnKeyClicked(int key)
{
	bool ret = ((nowKey[key] == 1) && (oldKey[key] != 1));
	return ret;
}

bool KeyManager::OnKeyReleased(int key)
{
	//ボタンを離した瞬間
	bool ret = ((nowKey[key] != 1) && (oldKey[key] == 1));
	return ret;
}

bool KeyManager::OnKeyPressed(int key)
{
	//ボタンを押した瞬間
	bool ret = (nowKey[key] == 1);
	return ret;
}

bool KeyManager::OnMouseClicked(int key)
{
	bool ret = ((nowMouse & key) && (~oldMouse & key));
	return ret;
}

bool KeyManager::OnMouseReleased(int key)
{
	//マウスを離した瞬間
	bool ret = ((~nowMouse & key) && (oldMouse & key));
	return ret;
}

bool KeyManager::OnMousePressed(int key)
{
	//マウスを押した瞬間
	bool ret = (nowMouse & key);
	return ret;
}