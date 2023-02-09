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
	DrawString(350, 300, "�^�C�g�����", GetColor(255, 255, 255));
	DrawString(350, 320, "�X�y�[�X�L�[�ŃQ�[�����C��", GetColor(255, 255, 255));
}

//�V�[���̕ύX����
AbstractScene* TitleScene::ChangeScene()
{
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE)) {
		
		return new GameMainScene;
	}

	return this;
}