#pragma once
#include <math.h>
#include "BILLBOARD_ENTITY_LIGHT_BULLET.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/CONTAINER.h"
#include "../Library/ANIMATION.h"
#include "../Library/VECTOR2.h"
#include "../Library/MATRIX.h"
#include "ENTITY_MANAGER.h"
#include "SOUND_MANAGER.h"
#include "ENTITY_PLAYER.h"
#include "INPUT_COMMON.h"
#include "ENTITY_STATE.h"
class ENTITY_PLAYER_STATE_SHOT :public ENTITY_STATE<ENTITY_PLAYER> {
public:
	ENTITY_PLAYER_STATE_SHOT(ENTITY_PLAYER* owner) :ENTITY_STATE<ENTITY_PLAYER>(owner) {
	}
	void onEnter() {
		auto e = owner();
		e->tree()->setNextAnimation(e->anim_Shot(), e->toAnim_shot(),0.0f,e->animSpeed_Shot() * e->attackSpeedBoost());
		Cnt = 0;
	}
	void update() {
		auto e = owner();
		DEBUG_STR* ds = DEBUG_STR::instance();
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		INPUT_COMMON* in = INPUT_COMMON::instance();
		VECTOR3 camera = e->camera()->lookDirection();
		camera.y = 0.0f;
		camera = normalize(camera);
		VECTOR3 move = e->velo();
		bool isWalk = !in->isNoneMoveAxis();
		if (isWalk) {
			move += VECTOR3(-camera.z, 0.0f, camera.x) * in->moveAxisHorizontal();
			move += VECTOR3(camera.x, 0.0f, camera.z) * in->moveAxisVertical();
			if (!move.isZero()) {
				move = normalize(move);
			}
		}
		if (!e->velo().xz().isZero()) {
			move *= length(e->velo().xz());
		}
		else{
			move = VECTOR3();
		}
		if (isWalk) {
			e->setRy(e->ry() + rotate(VECTOR2(sinf(e->rad().y), cosf(e->rad().y)), normalize(e->velo().xz())) / 15.0f);
		}
		e->setVx(move.x * e->walkInertia());
		e->setVz(move.z * e->walkInertia());
		//�w��̃t���[���ɒB�����疂�@�U�����s
		if (Cnt == (int)(e->activateFrame_Shot() / e->attackSpeedBoost())){
			sm->playSound(e->soundShot());
			e->Shot();
		}
		//�A�j���[�V�����t���[�����I������玟�̃X�e�[�g��
		if (Cnt > (int)(e->animEndFrame_Shot() / e->attackSpeedBoost())) {
			if (isWalk) {
				e->states()->change("MOVE");
			}
			else {
				e->states()->change("IDEL");
			}
		}
		if (in->isTriggerAvoid()) {
			e->states()->change("AVOID");
		}
		//�X�L���^�C�v�`�F���W
		if (in->isTriggerSkillChange()) {
			sm->playSound(e->soundSkillChange());
			e->SkillTypeChange();
		}
		//hp��0�ȉ��ɂȂ�����DOWN�X�e�[�g��
		if (e->hp() <= 0) {
			States->change("DOWN");
		}
		e->setVy(e->velo().y + e->gravity());
		e->posUpdate();
		Cnt++;
	}
	void onExit() {

	}
	const char* name()const {
		return "SHOT";
	}
private:
	int Cnt = 0;
};