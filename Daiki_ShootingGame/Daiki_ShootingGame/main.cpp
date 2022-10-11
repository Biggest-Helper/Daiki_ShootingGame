#include "DxLib.h"
#include "SceneManager.h"
#include "GameMainScene.h"

/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// �^�C�g���� test �ɕύX
	SetMainWindowText("�V���[�e�B���O�Q�[��");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	SetFontSize(20);		// �����T�C�Y��ݒ�

	//�V�[���}�l�W���[�̃I�u�W�F�N�g�̍쐬
	SceneManeger SceneMng( dynamic_cast<AbstractScene*>( new GameMainScene() ) );

	// �Q�[�����[�v
	while (ProcessMessage() == 0) 
	{

		ClearDrawScreen();		// ��ʂ̏�����

		SceneMng.Update();      //�V�[���̍X�V����
		SceneMng.Draw();        //�V�[���̕`�揈��
		if (SceneMng.ChangeScene() == nullptr)    //�V�[���̕ύX����
		{
			DxLib_End();	// DX���C�u�����g�p�̏I������
			return 0;	    // �\�t�g�̏I��
		}

		ScreenFlip();		// ����ʂ̓��e��\��ʂɔ��f
	}

	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;	    // �\�t�g�̏I��
}