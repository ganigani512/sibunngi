#pragma once 

#define SAFE_DELETE( p ){ \
    if( nullptr != p ){ \
        delete p ;\
        p = nullptr;\
    }\
}

//------------------------�����蔻�� AABB����----------------------------------------------
//�l�p�Ǝl�p pos�͒��S�̍��W
inline static bool BoxBoxHit(t2k::vec3 Box1pos, t2k::vec3 Box1Size ,t2k::vec3 Box2pos, t2k::vec3 Box2Size
	 ) {
	if ((Box1pos.x - (Box1Size.x / 2) >= Box2pos.x-(Box2Size.x/2)) && (Box1pos.x - (Box1Size.x / 2) <= Box2pos.x + (Box2Size.x / 2)) ||
		(Box1pos.x + (Box1Size.x / 2) >= Box2pos.x - (Box2Size.x / 2)) && (Box1pos.x + (Box1Size.x / 2) <= Box2pos.x + (Box2Size.x / 2))) {

		if ((Box1pos.y + (Box1Size.y / 2) >= Box2pos.y - (Box2Size.y/2)) && (Box1pos.y + (Box1Size.y / 2) <= Box2pos.y + (Box2Size.y / 2)) ||
			(Box1pos.y - (Box1Size.y / 2) >= Box2pos.y - (Box2Size.y / 2)) && (Box1pos.y - (Box1Size.y / 2) <= Box2pos.y + (Box2Size.y / 2))) {
			return true;
		}
	}
	return false;
}


//�l�p�Ɠ_
inline static bool BoxPointHit(t2k::vec3 Boxpos,int BoxW,int BoxH,t2k::vec3 Pointpos) {
	if (Boxpos.x < Pointpos.x&& Pointpos.x < Boxpos.x + BoxW&&
		Boxpos.y < Pointpos.y&& Pointpos.y < Boxpos.y + BoxH) {
		return true;
	}
	return false;
}

//�}�E�X�̏ꏊ�����Ă����ok
inline t2k::vec3 MousePos() {

	int mx, my;
	GetMousePoint(&mx, &my);
	t2k::vec3 mousepos;
	mousepos = t2k::vec3(mx, my, 0);
	return mousepos;
}

//----------���[�g���ԍ����o�����߂̊֐�ok-------------------------
inline DWORD BitSeparate32(DWORD n)
{
	n = (n | (n << 8)) & 0x00ff00ff;
	n = (n | (n << 4)) & 0x0f0f0f0f;
	n = (n | (n << 2)) & 0x33333333;
	return (n | (n << 1)) & 0x55555555;
}
inline DWORD Get2DMortonNumber(WORD x, WORD y)
{
	return (BitSeparate32(x) | (BitSeparate32(y) << 1));
}
//---------------------------------------------------------------
