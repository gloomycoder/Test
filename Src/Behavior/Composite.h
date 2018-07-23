#pragma once

namespace Behavior
{
	enum class Status
	{
		Succeed,
		Failed,
		Running,

		Max,
	};

	enum class CompositeType
	{
		Action,
		Decorator,
		Selector,
		Sequence,

		Max,
	};

	class Composite : public std::enable_shared_from_this<Composite>
	{
	public:
		Composite(CompositeType type, ActorShaPtr owner);
		virtual ~Composite() = default;

	public:
		Void setParent(Composite* parent);
		Composite* getParent() const;

		Void start();
		Void stop();

		Status getStatus() const;
		ActorShaPtr getOwner() const;

		virtual Bool isEnd() const { return false; }

	protected:
		virtual Enumerable<Status> execute() abstract;
		virtual Void cleanup();

	public:
		Status tick();

	protected:
		ActorShaPtr _owner = null;

	private:
		Status _status = Status::Max;
		CompositeType _type = CompositeType::Max;
		Composite* _parent = null;	// 순환참조 방지를 위해 raw pointer 로 보관한다. 부모가 자식들을 shared_ptr 로 가지므로 자식이 살아있다면 부모는 항상 존재함을 보장한다.

		Enumerable<Status> _current;
	};
}