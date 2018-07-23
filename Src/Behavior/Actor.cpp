#include "stdafx.h"
#include "Actor.h"

namespace
{
	std::mt19937_64 engin((std::random_device())());
	std::uniform_int_distribution <UInt32> random(0, std::numeric_limits<UInt32>::max());

	UInt32 getRandom()
	{
		return random(engin);
	}
}



Bool Actor::findTarget()
{
	_hasTarget = getRandom() % 2 < 1;
	return hasTarget();
}

Bool Actor::hasTarget()
{
	return _hasTarget;
}

Bool Actor::isMovable()
{
	return getRandom() % 2 < 1;
}

Bool Actor::isAttackable()
{
	return getRandom() % 2 < 1;
}

Bool Actor::isArrive()
{
	return getRandom() % 10 < 1;
}

Bool Actor::chooseUseSkill()
{
	if (getRandom() % 2 < 1)
	{
		_skillName = "돌진 베기";
		return true;
	}
	return false;
}

Bool Actor::existUseSkill() const
{
	return false == _skillName.empty();
}

const String& Actor::getSkillName() const
{
	return _skillName;
}

Void Actor::skillFired()
{
	_skillName.clear();
}


