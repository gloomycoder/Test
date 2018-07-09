#pragma once

#include "Composite.h"

namespace Behavior
{
	class GroupComposite : public Composite
	{
	protected:
		using ChildList = std::vector<CompositeShaPtr>;
		explicit GroupComposite(CompositeType type, ActorShaPtr owner)
			: Composite(type, owner)
		{
		}
		virtual ~GroupComposite() = default;

	public:
		Void add(CompositeShaPtr child)
		{
			child->setParent(this);
		}

	protected:
		ChildList _child;
		CompositeShaPtr _now;
	};
}