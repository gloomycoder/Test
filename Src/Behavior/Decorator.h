#pragma once

#include "GroupComposite.h"

namespace Behavior
{
	enum class DecoratorType
	{
		Condition,

		Max,
	};

	class Decorator : public GroupComposite
	{
	protected:
		Decorator(DecoratorType type, ActorShaPtr owner)
			: GroupComposite(CompositeType::Decorator, owner)
			, _type(type)
		{
		}
		virtual ~Decorator() = default;

	private:
		Void setDecorator(CompositeShaPtr composite);

	protected:
		virtual Bool can() abstract;
		virtual Enumerable<Status> execute() override;
		virtual Void cleanup() override;
		virtual Void addedComposite(CompositeShaPtr composite) override;

	private:
		Composite* _decorator = null;
		DecoratorType _type = DecoratorType::Max;
	};
}
