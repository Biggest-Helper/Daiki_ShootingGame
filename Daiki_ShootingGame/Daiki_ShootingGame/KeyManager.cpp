#include "DxLib.h"
#include "KeyManager.h"

//�L�[�ϐ��̏�����
char KeyManager::oldKey[256];    //�O�̃L�[
char KeyManager::nowKey[256];    //���݂̃L�[

int KeyManager::oldMouse;   //�O�̃}�E�X�L�[
int KeyManager::nowMouse;   //���݂̃}�E�X�L�[

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
	//�{�^���𗣂����u��
	bool ret = ((nowKey[key] != 1) && (oldKey[key] == 1));
	return ret;
}

bool KeyManager::OnKeyPressed(int key)
{
	//�{�^�����������u��
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
	//�}�E�X�𗣂����u��
	bool ret = ((~nowMouse & key) && (oldMouse & key));
	return ret;
}

bool KeyManager::OnMousePressed(int key)
{
	//�}�E�X���������u��
	bool ret = (nowMouse & key);
	return ret;
}