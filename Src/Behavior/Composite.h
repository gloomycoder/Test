#pragma once

namespace Behavior
{
	enum class StatusType
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

	class Composite
	{
	public:
		Composite(CompositeType type, ActorShaPtr owner);
		virtual ~Composite() = default;

	public:
		Void setParent(CompositeShaPtr parent);
		CompositeShaPtr getParent() const;

		StatusType start();

	protected:
		virtual Enumerable<StatusType> execute() abstract;

		virtual void onEnter() abstract;
		virtual void onLeave() abstract;

	private:
		StatusType onTick();

	protected:
		ActorShaPtr _owner = null;

	private:
		StatusType _status = StatusType::Max;
		CompositeType _type = CompositeType::Max;
		CompositeShaPtr _parent = null;

		Enumerable<StatusType> _current;
	};
}