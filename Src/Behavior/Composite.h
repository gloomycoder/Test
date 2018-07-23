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
		Composite* _parent = null;	// ��ȯ���� ������ ���� raw pointer �� �����Ѵ�. �θ� �ڽĵ��� shared_ptr �� �����Ƿ� �ڽ��� ����ִٸ� �θ�� �׻� �������� �����Ѵ�.

		Enumerable<Status> _current;
	};
}