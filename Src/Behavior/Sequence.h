#pragma once

#include "GroupComposite.h"

namespace Behavior
{
	class Sequence : public GroupComposite
	{
	public:
		Sequence(ActorShaPtr owner)
			: GroupComposite(CompositeType::Sequence, owner)
		{
		}
		virtual ~Sequence() = default;

	protected:
		virtual Enumerable<Status> execute() override;
	};
}
