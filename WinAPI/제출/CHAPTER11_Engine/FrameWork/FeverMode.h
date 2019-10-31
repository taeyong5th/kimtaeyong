#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "SingleTon.h"

class FeverMode : public SingleTon<FeverMode>
{
private:
	JEngine::BitMap* m_pFeverEffect;
	JEngine::BitMap* m_pFeverBack;
	JEngine::BitMap* m_pFeverBar;

	int m_iFeverScore;
	const int m_iFeverScoreMax = 10;

	float m_fFeverTime; // �ǹ���尡 �����ð�
	float m_fFeverAnimTime; // ������ �ִϸ��̼� �ð�
	const float m_fFeverLimitTime = 5.0f;
	const float m_fFeverAnimTick = 0.3f; // ���ʸ��� ���ڰŸ���

	bool m_bFeverDraw; // �ǹ�ȿ�� ������ �׸��� ����
	bool m_bFeverMode; // �ǹ���尡 ��������

public:
	FeverMode();
	~FeverMode();
	void init(); 
	void update(float fEtime);
	void draw();
	void addFever(int score = 1);
	bool isFeverMode();
};