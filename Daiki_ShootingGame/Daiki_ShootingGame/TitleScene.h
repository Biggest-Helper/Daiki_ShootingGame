#pragma once
#include "AbstractScene.h"
class TitleScene : public AbstractScene
{
public:
	//�R���X�g���N�^
	TitleScene();

	//�f�X�g���N�^
	virtual ~TitleScene() {};

public:
	//�`��ȊO�̍X�V����������
	virtual void Update() override;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const override;

	//�V�[���̕ύX����
	virtual AbstractScene* ChangeScene() override;
};