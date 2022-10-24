#pragma once
class KeyManager
{
private:
	static char oldKey[256];    //前のキー
	static char nowKey[256];    //現在のキー

	static int oldMouse;   //前のマウスキー
	static int nowMouse;   //現在のマウスキー

private:
	KeyManager() = default;     //コンストラクタ―

public:
	static void Updata();
	static bool OnKeyClicked(int key);
	static bool OnKeyReleased(int key);  //ボタンを離した瞬間
	static bool OnKeyPressed(int key);   //ボタンを押した瞬間

	static bool OnMouseClicked(int key);
	static bool OnMouseReleased(int key);  //ボタンを離した瞬間
	static bool OnMousePressed(int key);   //ボタンを押した瞬間
};