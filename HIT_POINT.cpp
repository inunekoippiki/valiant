#include <algorithm>
#include "HIT_POINT.h"
HIT_POINT::HIT_POINT() {
}

HIT_POINT::~HIT_POINT() {
}

//ダメージを与える
void HIT_POINT::damage(int damage) {
	Hp = std::max(Hp - damage, 0);
}
