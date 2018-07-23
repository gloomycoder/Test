#include "stdafx.h"
#include "SimpleTest.h"

class Idle : public Behavior::Action
{
public:
	Idle(ActorShaPtr owner)
		: Behavior::Action(Behavior::ActionType::Max, owner)
	{
	}

protected:
	virtual Behavior::Status run() override final
	{
		auto diff = std::chrono::system_clock::now() - _start;

		if (5000 < diff.count())
		{
			std::cout << "아이들 상태를 종료했습니다." << std::endl;
			return Behavior::Status::Succeed;
		}

		return Behavior::Status::Running;
	}

	virtual Void enter() override final
	{
		_start = std::chrono::system_clock::now();

		std::cout << "아이들 상태로 진입했습니다." << std::endl;
	}

private:
	std::chrono::system_clock::time_point _start;
};

class Wander : public Behavior::Action
{
public:
	Wander(ActorShaPtr owner)
		: Behavior::Action(Behavior::ActionType::Max, owner)
	{
	}

protected:
	virtual Behavior::Status run() override final
	{
		if (_owner->hasTarget())
		{
			std::cout << "적을 탐지하여 배회를 중지합니다." << std::endl;
			return Behavior::Status::Failed;
		}

		if (_owner->isArrive())
		{
			std::cout << "배회를 완료했습니다." << std::endl;
			return Behavior::Status::Succeed;
		}

		return Behavior::Status::Running;
	}

	virtual Void enter() override final
	{
		std::cout << "주변을 배회하기 시작합니다." << std::endl;
	}
};

class Chase : public Behavior::Action
{
public:
	Chase(ActorShaPtr owner)
		: Behavior::Action(Behavior::ActionType::Max, owner)
	{
	}

protected:
	virtual Behavior::Status run() override final
	{
		if (false == _owner->hasTarget())
		{
			return Behavior::Status::Failed;
		}

		if (_owner->isArrive())
		{
			std::cout << "추적을 종료합니다." << std::endl;
			return Behavior::Status::Succeed;
		}

		std::cout << "추적 중입니다." << std::endl;
		return Behavior::Status::Running;
	}

	virtual Void enter() override final
	{
		std::cout << "추적을 시작합니다." << std::endl;
	}
};

class SkillCasting : public Behavior::Action
{
public:
	SkillCasting(ActorShaPtr owner)
		: Behavior::Action(Behavior::ActionType::Max, owner)
	{
	}

protected:
	virtual Behavior::Status run() override final
	{
		if (false == _owner->hasTarget())
		{
			std::cout << "타겟이 존재하지 않습니다." << std::endl;
			return Behavior::Status::Failed;
		}

		if (false == _owner->existUseSkill())
		{
			std::cout << "사용할 수 있는 스킬이 존재하지 않습니다." << std::endl;
			return Behavior::Status::Failed;
		}

		auto diff = std::chrono::system_clock::now() - _start;
		if (2000 < diff.count())
		{
			std::cout << "스킬 캐스팅이 종료됐습니다." << std::endl;
			return Behavior::Status::Succeed;
		}

		std::cout << "스킬 캐스팅 중입니다." << std::endl;
		return Behavior::Status::Running;
	}

	virtual Void enter() override final
	{
		_start = std::chrono::system_clock::now();

		std::cout << "스킬 캐스팅을 시작합니다." << std::endl;
	}

private:
	std::chrono::system_clock::time_point _start;
};

class UseSkill : public Behavior::Action
{
public:
	UseSkill(ActorShaPtr owner)
		: Behavior::Action(Behavior::ActionType::Max, owner)
	{
	}

protected:
	virtual Behavior::Status run() override final
	{
		if (false == _owner->hasTarget())
		{
			std::cout << "타겟이 존재하지 않습니다." << std::endl;
			return Behavior::Status::Failed;
		}

		if (false == _owner->existUseSkill())
		{
			std::cout << "사용할 수 있는 스킬이 존재하지 않습니다." << std::endl;
			return Behavior::Status::Failed;
		}

		std::cout << _owner->getSkillName() << "스킬을 사용했습니다." << std::endl;
		_owner->skillFired();
		return Behavior::Status::Succeed;
	}
};


class FindTarget : public Behavior::Condition
{
public:
	FindTarget(ActorShaPtr owner)
		: Behavior::Condition(owner)
	{
	}

	virtual ~FindTarget() = default;

protected:
	virtual Bool check() override final
	{
		if (_owner->hasTarget() || _owner->findTarget())
		{
			std::cout << "적을 찾았거나 이미 적이 존재합니다." << std::endl;
			return true;
		}

		std::cout << "적 탐색에 실패했습니다." << std::endl;
		return false;
	}
};

class ChooseUseSkill : public Behavior::Condition
{
public:
	ChooseUseSkill(ActorShaPtr owner)
		: Behavior::Condition(owner)
	{
	}

	virtual ~ChooseUseSkill() = default;

protected:
	virtual Bool check() override final
	{
		if (_owner->existUseSkill() || _owner->chooseUseSkill())
		{
			std::cout << "사용할 스킬 선택에 성공하거나 이미 사용할 스킬이 존재합니다." << std::endl;
			return true;
		}

		std::cout << "사용할 수 있는 스킬이 없습니다." << std::endl;
		return false;
	}
};

Void SimpleTest::doTest01()
{
	ActorShaPtr actor = std::make_shared<Actor>("테스터");

	Behavior::GroupCompositeShaPtr root = std::make_shared<Behavior::Selector>(actor);
	Behavior::GroupCompositeShaPtr idleComposite = std::make_shared<Behavior::Sequence>(actor);
	idleComposite->add(std::make_shared<Wander>(actor), std::make_shared<Idle>(actor));

	Behavior::GroupCompositeShaPtr combatComposite = std::make_shared<Behavior::Sequence>(actor);
	combatComposite->add(std::make_shared<Chase>(actor), std::make_shared<UseSkill>(actor), std::make_shared<SkillCasting>(actor));

	

	Behavior::GroupCompositeShaPtr activeComposite = std::make_shared<Behavior::Sequence>(actor);
	activeComposite->add(std::make_shared<FindTarget>(actor)->add(combatComposite));

	root->add(activeComposite, idleComposite);

	system_clock::time_point start = system_clock::now();

	root->start();
	Bool loop = true;

	Behavior::Status status = Behavior::Status::Max;
	while (loop)
	{
		if (Behavior::Status::Failed == status || root->isEnd())
		{
			root->start();
		}

		status = root->tick();
		std::this_thread::sleep_for(10ms);

		milliseconds diff = duration_cast<milliseconds>(system_clock::now() - start);
		if(9000 < diff.count())
		{
			break;
		}
	}

			
	return Void();
}
