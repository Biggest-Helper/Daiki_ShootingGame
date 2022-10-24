#include "SceneManager.h"
#include "KeyManager.h"

//�����o�ϐ��̒l������������̂��A�b�v�f�[�g�֐�
void SceneManeger::Update()
{
	KeyManager::Updata();
	//���݃V�[���̃A�b�v�f�[�g�����s
	mScene->Update();
}

//�`�揈���݂̂��s���֐�
void SceneManeger::Draw() const
{
	//���݃V�[���̕`��֐������s
	mScene->Draw();
}

//�V�[���̕ύX�����֐�
AbstractScene* SceneManeger::ChangeScene()
{
	AbstractScene* nextScene = mScene->ChangeScene();

	//���̃V�[�������݃V�[���ƕʂȂ�ύX
	if (nextScene != mScene)
	{
		delete mScene;
		mScene = nextScene;
	}

	return nextScene;
}