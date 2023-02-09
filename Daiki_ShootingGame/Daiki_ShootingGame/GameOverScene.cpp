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
	DrawString(350, 300, "GameOver", GetColor(255, 0, 0));
	DrawString(350, 320, "�X�y�[�X�L�[�Ń^�C�g��", GetColor(255, 255, 255));
}

//�V�[���̕ύX����
AbstractScene* GameOverScene::ChangeScene()
{
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE)) {

		return new TitleScene;
	}
	return this;
}