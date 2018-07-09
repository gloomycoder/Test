#pragma once

#include "Composite.h"

namespace Behavior
{
	enum class ActionType
	{
		Max
	};

	class Action : public Composite
	{
	public:
		Action() = delete;
		explicit Action(ActionType type, ActorShaPtr owner)
			: Composite(CompositeType::Action, owner)
			, _actionType(type)
		{
		}
		virtual ~Action() = default;

	protected:
		virtual Status run() abstract;

	protected:
		virtual Enumerable<Status> execute() override final;
		virtual Void cleanup() override;

	private:
		ActionType _actionType = ActionType::Max;
	};
}