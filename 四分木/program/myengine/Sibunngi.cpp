#include "sibunngi.h"

//ルーム作成用
void Sibunngi::set(int i, int v, int x, int y) {

	room[i][v].size.x = maxsize.x / (1 << i);
	room[i][v].size.y = maxsize.y / (1 << i);

	room[i][v].pos = t2k::vec3(x * room[i][v].size.x, y * room[i][v].size.y, 0);
	room[i][v].mortonNum = v;
}

//点の位置からモートンナンバー取得用
int Sibunngi::GetMortonNum(t2k::vec3 pos, t2k::vec3 size) {
	int x = pos.x / size.x;
	int y = pos.y / size.y;
	int vv = Get2DMortonNumber(x, y);
	return vv;
}

//シフトした回数を教えてくれる
int Sibunngi::GetDivideLevel(int LeftUp, int RightDown) {
	int a = LeftUp ^ RightDown;
	int shift = 0;//シフトした回数
	while (a >> (shift << 1) != 0) {
		shift++;
	}
	return shift;
}

int Sibunngi::warizan(int a) {
	if (a == 0) return a;
	int x = rand() % a;
	return x;
}

//しょーきーかー　1回しかやらないよー
void Sibunngi::syokika() {
	srand(time(NULL));
	mouse = new Object(MousePos(), t2k::vec3(20, 20, 0));
	obj.push_back(mouse);


	t2k::vec3 pos[hakonokazu];


	for (int i = 0; i < hakonokazu; i++) {

		int x = warizan(maxsize.x);
		int y = warizan(maxsize.y);
		int z = warizan(maxsize.z);

		pos[i] = t2k::vec3(x, y, z);
		hako[i] = new Object(pos[i], t2k::vec3(20, 20, 0));
		obj.push_back(hako[i]);
	}

	for (int i = 0; i <= levelmax; i++) {
		room[i].resize((1 << i) * (1 << i));//先に配列の箱だけ作る
		for (int x = 0; x < 1 << i; x++) {
			for (int y = 0; y < 1 << i; y++) {
				int morton;
				morton = Get2DMortonNumber(x, y);
				set(i, morton, x, y);//情報を入れる
			}
		}
	}

	unsigned int color = 0xffffffff;
}

void Sibunngi::SibunngiCollision(int dividelevel, int mortonnum)
{

	//--------------自分の部屋のあたり判定------------------------------------
	auto me_it = room[dividelevel][mortonnum].roomObjectList.begin();
	auto me_end_it = room[dividelevel][mortonnum].roomObjectList.end();
	if (room[dividelevel][mortonnum].roomObjectList.size() > 1) {
		while (me_it != me_end_it) {
			auto you_it = me_it;
			you_it++;
			while (you_it != me_end_it) {
				hitcount++;
				if (BoxBoxHit((*me_it)->pos, (*me_it)->size, (*you_it)->pos, (*you_it)->size)) {
					(*me_it)->hit = true;
					(*you_it)->hit = true;
				}
				you_it++;
			}
			me_it++;
		}

	}
	//---------------------------------------------------------------------------

	Room* ptr = nullptr;
	if (room[dividelevel][mortonnum].roomObjectList.size() > 0) {
		ptr = &room[dividelevel][mortonnum];
	}
	//------------ルームリストとのあたり判定------------------------------------
	//ルームが入ってるリストのitを回す
	auto it_inroomlist = InroomList.begin();
	while (it_inroomlist != InroomList.end()) {
		//今いるルームのobjlistのitを回す
		auto it_me = room[dividelevel][mortonnum].roomObjectList.begin();
		auto it_me_end = room[dividelevel][mortonnum].roomObjectList.end();
		while (it_me != it_me_end) {
			//ルームリストの中のobjlistのitを回す
			auto it_you = (*it_inroomlist)->roomObjectList.begin();
			auto it_you_end = (*it_inroomlist)->roomObjectList.end();
			while (it_you != it_you_end) {
				hitcount++;
				if (BoxBoxHit((*it_me)->pos, (*it_me)->size, (*it_you)->pos, (*it_you)->size)) {
					(*it_me)->hit = true;
					(*it_you)->hit = true;
				}
				it_you++;
			}
			it_me++;
		}
		it_inroomlist++;
	}
	//----------------------------------------------------------------------------------

	//ルームオブジェクトリストにオブジェクトが登録されてたら自分をルームリストに登録
	if (dividelevel < levelmax && ptr != nullptr) {
		InroomList.push_back(ptr);
	}

	//ディバイドレベルが最大じゃなかったら１こ下がる
	if (dividelevel < levelmax) {
		for (int i = 0; i < 4; i++) {
			SibunngiCollision(dividelevel + 1, (mortonnum << 2) + i);
		}
	}
	//ルームリストから自分を消す
	if (ptr != nullptr) {
		InroomList.remove(ptr);
	}

}