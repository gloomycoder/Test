#pragma once

class Actor : public std::enable_shared_from_this<Actor>
{
public:
	Actor(const std::string& name)
		: _name(name)
	{
	}
	~Actor() = default;

public:
	Bool findTarget();
	Bool hasTarget();
	Bool isMovable();
	Bool isAttackable();
	Bool isArrive();
	Bool chooseUseSkill();
	Bool existUseSkill() const;
	const String& getSkillName() const;

	Void skillFired();

private:
	String _name;
	String _skillName;
	Bool _hasTarget = false;
};