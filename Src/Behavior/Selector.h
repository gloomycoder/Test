#pragma once

#include "GroupComposite.h"

namespace Behavior
{
	class Selector : public GroupComposite
	{
	public:
		Selector(ActorShaPtr owner)
			: GroupComposite(CompositeType::Selector, owner)
		{
		}

		virtual ~Selector() = default;

	protected:
		virtual Enumerable<Status> execute() override;
	};
}