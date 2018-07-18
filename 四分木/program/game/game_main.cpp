#include "DxLib.h"
#include "game_main.h"
#include "../support/Support.h"
#include "../myengine/sibunngi.h"



int game_main()
{

	Sibunngi *aaa = Sibunngi::getInstance();

//--------------------------↓全体描画↓---------------------------------------------------
	
	for (int i = 0; i < 1 << aaa->levelmax; i++) {
		for (int k = 0; k < 1 << aaa->levelmax; k++) {
			int v;
			v = Get2DMortonNumber(i, k);
			aaa->room[aaa->levelmax][v].render();
		}
	}

//-----------------------------------------------------------------------------------------
	
//--------------------↓テスト用の箱↓------------------------------------------------------------
	
	for (int i = 0; i < aaa->hakonokazu; i++) {
		int roomLUv = aaa->GetMortonNum(aaa->hako[i]->pos - (aaa->hako[i]->size / 2), aaa->room[aaa->levelmax][0].size);
		int roomRDv = aaa->GetMortonNum(aaa->hako[i]->pos + (aaa->hako[i]->size / 2), aaa->room[aaa->levelmax][0].size);
		aaa->hako[i]->move();//こいつ・・・うごくぞ・・・
		//範囲内にある時だけ描画
		if ((1 << aaa->levelmax)*(1 << aaa->levelmax) - 1 >= roomLUv &&
			(1 << aaa->levelmax)*(1 << aaa->levelmax) - 1 >= roomRDv) {
			int DivideLevel;
			DivideLevel = aaa->GetDivideLevel(roomLUv, roomRDv);
			//どのルームにあるのか登録↓
			aaa->room[aaa->levelmax - DivideLevel][roomLUv >> (DivideLevel << 1)].roomObjectList.push_back(aaa->hako[i]);
		}
	}
	
//---------------------------------------------------------------------------------------------


	
	aaa->hitcount=0;

	//しぶんぎい
	aaa->SibunngiCollision(0, 0);


//-----------------------確認用(コメントアウトしても大丈夫)----------------------------------------------
	//DrawStringEx(100, 550, 0xffffffff, "カ　右下　%d      左上　%d", mouseLUv, mouseRDv);
	DrawStringEx(100, 570, 0xffffffff, "あたり判定最大　%d", (aaa->hakonokazu*(aaa->hakonokazu-1))/2);
	DrawStringEx(100, 590, 0xffffffff,"あたり判定回数　%d", aaa->hitcount);
	float sakugennritu = (100-((float)aaa->hitcount / ((aaa->hakonokazu*(aaa->hakonokazu-1)) / 2)) * 100);
	//sakugennritu = 57.0f;
	DrawStringEx(100, 610, 0xffffffff, "削減率　%f", sakugennritu);
//------------------------------------------------------------------------------------
	
	//オブジェクトの描画処理
	for (int i = 0; i < aaa->hakonokazu; i++) {
		aaa->hako[i]->render();
	}

//ーーーーーールームオブジェクトリストの中身を全部削除ーーーーーーーー
	for (int i = 0; i <= aaa->levelmax; i++) {
		for (int v = 0; v < (1 << i)*(1 << i); v++) {
			aaa->room[i][v].roomObjectList.clear();
		}
	}
//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	return 0;
}


