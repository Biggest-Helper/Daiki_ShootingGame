#pragma once
class KeyManager
{
private:
	static char oldKey[256];    //�O�̃L�[
	static char nowKey[256];    //���݂̃L�[

	static int oldMouse;   //�O�̃}�E�X�L�[
	static int nowMouse;   //���݂̃}�E�X�L�[

private:
	KeyManager() = default;     //�R���X�g���N�^�\

public:
	static void Updata();
	static bool OnKeyClicked(int key);
	static bool OnKeyReleased(int key);  //�{�^���𗣂����u��
	static bool OnKeyPressed(int key);   //�{�^�����������u��

	static bool OnMouseClicked(int key);
	static bool OnMouseReleased(int key);  //�{�^���𗣂����u��
	static bool OnMousePressed(int key);   //�{�^�����������u��
};