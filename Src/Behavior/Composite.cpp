#include "stdafx.h"
#include "Composite.h"

namespace Behavior
{
	Composite::Composite(CompositeType type, ActorShaPtr owner)
		: _type(type)
		, _owner(owner)
	{
	}

	Void Composite::setParent(Composite* parent)
	{
		_parent = parent;
	}

	Composite* Composite::getParent() const
	{
		return _parent;
	}

	Void Composite::start()
	{
		_status = Status::Max;
		_current = execute();
	}

	Void Composite::stop()
	{
		cleanup();

		if (_current.isGood())
		{
			_current.reset();
		}

		if (Status::Running == _status)
		{
			_status = Status::Failed;
		}
	}

	Status Composite::getStatus() const
	{
		return _status;
	}

	ActorShaPtr Composite::getOwner() const
	{
		return _owner;
	}

	Void Composite::cleanup()
	{
	}

	Status Composite::tick()
	{
		if (Status::Max != _status)
		{
			if (Status::Running != _status)
			{
				return _status;
			}
		}
		
		try
		{
			if (false == _current.isGood())
			{
				throw std::runtime_error("invalid composite value");
			}

			if (_current.moveNext())
			{
				_status = _current.currentValue();
			}
			else
			{
				throw std::runtime_error("empty composite?");
			}

			if (_status != Status::Running)
			{
				stop();
			}
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		

		return _status;
	}
}
