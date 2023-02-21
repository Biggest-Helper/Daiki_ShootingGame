#include "TitleScene.h"
#include "GameMainScene.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "DxLib.h"

//�R���X�g���N�^
TitleScene::TitleScene()
{

}

//�`��ȊO�̍X�V����������
void TitleScene::Update()
{
	
}

//�`��Ɋւ��邱�Ƃ���������
void TitleScene::Draw() const
{
	SetFontSize(100);
	DrawString(100, 100, "SUPER HOT Shoothing 3", GetColor(255, 0, 0));
	SetFontSize(20);
	DrawString(500, 450, "�X�y�[�X�L�[�� START !", GetColor(255, 255, 255));
}

//�V�[���̕ύX����
AbstractScene* TitleScene::ChangeScene()
{
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE)) {
		
		return new GameMainScene;
	}

	return this;
}