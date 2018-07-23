#pragma once

#include "Decorator.h"

namespace Behavior
{
	class Condition : public Decorator
	{
	public:
		Condition(ActorShaPtr owner)
			: Decorator(DecoratorType::Condition, owner)
		{
		}

		virtual ~Condition() = default;;

	protected:
		virtual Bool can() override;

	protected:
		virtual Bool check() abstract;
	};
}
