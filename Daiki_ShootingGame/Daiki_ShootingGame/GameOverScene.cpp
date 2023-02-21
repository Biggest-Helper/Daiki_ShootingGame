#include "GameOverScene.h"
#include "TitleScene.h"
#include "KeyManager.h"
#include "DxLib.h"

//�R���X�g���N�^
GameOverScene::GameOverScene()
{

}

//�`��ȊO�̍X�V����������
void GameOverScene::Update()
{
	
}

//�`��Ɋւ��邱�Ƃ���������
void GameOverScene::Draw() const
{
	SetFontSize(100);
	DrawString(420, 200, "GameOver", GetColor(0, 0, 255));
	SetFontSize(20);
	DrawString(500, 400, "�X�y�[�X�L�[�Ń^�C�g��", GetColor(255, 255, 255));
}

//�V�[���̕ύX����
AbstractScene* GameOverScene::ChangeScene()
{
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE)) {

		return new TitleScene;
	}
	return this;
}