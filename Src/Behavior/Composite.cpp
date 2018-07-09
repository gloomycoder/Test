#include "stdafx.h"
#include "Composite.h"

namespace Behavior
{
	Composite::Composite(CompositeType type, ActorShaPtr owner)
		: _type(type)
		, _owner(owner)
	{
	}

	Void Composite::setParent(CompositeShaPtr parent)
	{
		_parent = parent;
	}

	CompositeShaPtr Composite::getParent() const
	{
		return _parent;
	}

	StatusType Composite::start()
	{
		return StatusType();
	}

	StatusType Composite::onTick()
	{

		return StatusType();
	}
}
