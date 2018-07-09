#pragma once

#include "Composite.h"

namespace Behavior
{
	class Action : public Composite
	{
	public:
		Action() = delete;
		explicit Action(ActorShaPtr owner);
		virtual ~Action() = default;

	public:
		virtual StatusType run();
		virtual void onSucceed();
	};
}