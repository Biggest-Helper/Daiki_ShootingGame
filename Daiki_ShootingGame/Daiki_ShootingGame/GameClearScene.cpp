#include "GameClearScene.h"
#include "TitleScene.h"
#include "KeyManager.h"
#include "DxLib.h"

//�R���X�g���N�^
GameClearScene::GameClearScene()
{

}

//�`��ȊO�̍X�V����������
void GameClearScene::Update()
{

}

//�`��Ɋւ��邱�Ƃ���������
void GameClearScene::Draw() const
{
	DrawString(350, 300, "GameClear", GetColor(255, 0, 0));
	DrawString(350, 320, "�X�y�[�X�L�[�Ń^�C�g��", GetColor(255, 255, 255));
}

//�V�[���̕ύX����
AbstractScene* GameClearScene::ChangeScene()
{
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE)) {

		return new TitleScene;
	}
	return this;
}