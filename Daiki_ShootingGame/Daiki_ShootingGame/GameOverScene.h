#pragma once
#include "AbstractScene.h"
class GameOverScene : public AbstractScene
{
public:
	//�R���X�g���N�^
	GameOverScene();

	//�f�X�g���N�^
	virtual ~GameOverScene() {};

public:
	//�`��ȊO�̍X�V����������
	virtual void Update() override;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const override;

	//�V�[���̕ύX����
	virtual AbstractScene* ChangeScene() override;
};

