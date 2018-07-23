#pragma once

#include "Composite.h"

namespace Behavior
{
	template <class F, class... Args>
	void for_each_argument(F f, Args&&... args) {
		[](...) {}((f(std::forward<Args>(args)), 0)...);
	}

	class GroupComposite : public Composite
	{
	protected:
		using ChildList = std::vector<CompositeShaPtr>;
		explicit GroupComposite(CompositeType type, ActorShaPtr owner)
			: Composite(type, owner)
		{
		}

	public:
		virtual ~GroupComposite() = default;

	public:
		template<typename... Args>
		CompositeShaPtr add(CompositeShaPtr composite, Args&&... args)
		{
			addComposite(composite);
			add(std::forward<Args>(args)...);
			
			return shared_from_this();
		}
		template<typename... Args>
		CompositeShaPtr add()
		{
			return shared_from_this();
		}

		virtual Bool isEnd() const override;

	protected:
		Void addComposite(CompositeShaPtr composite)
		{
			if (null != composite)
			{
				_child.push_back(composite);
				addedComposite(composite);
			}
		}

	protected:
		virtual Void addedComposite(CompositeShaPtr composite)
		{
		}

	protected:
		ChildList _child;
		CompositeShaPtr _now;
	};
}