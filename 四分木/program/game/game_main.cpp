#include "DxLib.h"
#include "game_main.h"
#include "../support/Support.h"
#include "../myengine/sibunngi.h"



int game_main()
{

	Sibunngi *aaa = Sibunngi::getInstance();

//--------------------------���S�̕`�恫---------------------------------------------------
	
	for (int i = 0; i < 1 << aaa->levelmax; i++) {
		for (int k = 0; k < 1 << aaa->levelmax; k++) {
			int v;
			v = Get2DMortonNumber(i, k);
			aaa->room[aaa->levelmax][v].render();
		}
	}

//-----------------------------------------------------------------------------------------
	
//--------------------���e�X�g�p�̔���------------------------------------------------------------
	
	for (int i = 0; i < aaa->hakonokazu; i++) {
		int roomLUv = aaa->GetMortonNum(aaa->hako[i]->pos - (aaa->hako[i]->size / 2), aaa->room[aaa->levelmax][0].size);
		int roomRDv = aaa->GetMortonNum(aaa->hako[i]->pos + (aaa->hako[i]->size / 2), aaa->room[aaa->levelmax][0].size);
		aaa->hako[i]->move();//�����E�E�E���������E�E�E
		//�͈͓��ɂ��鎞�����`��
		if ((1 << aaa->levelmax)*(1 << aaa->levelmax) - 1 >= roomLUv &&
			(1 << aaa->levelmax)*(1 << aaa->levelmax) - 1 >= roomRDv) {
			int DivideLevel;
			DivideLevel = aaa->GetDivideLevel(roomLUv, roomRDv);
			//�ǂ̃��[���ɂ���̂��o�^��
			aaa->room[aaa->levelmax - DivideLevel][roomLUv >> (DivideLevel << 1)].roomObjectList.push_back(aaa->hako[i]);
		}
	}
	
//---------------------------------------------------------------------------------------------


	
	aaa->hitcount=0;

	//���Ԃ񂬂�
	aaa->SibunngiCollision(0, 0);


//-----------------------�m�F�p(�R�����g�A�E�g���Ă����v)----------------------------------------------
	//DrawStringEx(100, 550, 0xffffffff, "�J�@�E���@%d      ����@%d", mouseLUv, mouseRDv);
	DrawStringEx(100, 570, 0xffffffff, "�����蔻��ő�@%d", (aaa->hakonokazu*(aaa->hakonokazu-1))/2);
	DrawStringEx(100, 590, 0xffffffff,"�����蔻��񐔁@%d", aaa->hitcount);
	float sakugennritu = (100-((float)aaa->hitcount / ((aaa->hakonokazu*(aaa->hakonokazu-1)) / 2)) * 100);
	//sakugennritu = 57.0f;
	DrawStringEx(100, 610, 0xffffffff, "�팸���@%f", sakugennritu);
//------------------------------------------------------------------------------------
	
	//�I�u�W�F�N�g�̕`�揈��
	for (int i = 0; i < aaa->hakonokazu; i++) {
		aaa->hako[i]->render();
	}

//�[�[�[�[�[�[���[���I�u�W�F�N�g���X�g�̒��g��S���폜�[�[�[�[�[�[�[�[
	for (int i = 0; i <= aaa->levelmax; i++) {
		for (int v = 0; v < (1 << i)*(1 << i); v++) {
			aaa->room[i][v].roomObjectList.clear();
		}
	}
//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	return 0;
}


