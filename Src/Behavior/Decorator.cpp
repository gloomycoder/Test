#include "stdafx.h"
#include "Decorator.h"

namespace Behavior
{
	Void Decorator::setDecorator(CompositeShaPtr composite)
	{
		if (null != _decorator)
		{
			throw std::runtime_error("already setted");
		}
		_decorator = composite.get();
	}

	Enumerable<Status> Decorator::execute()
	{
		if (false == can())
		{
			co_yield Status::Failed;
			co_return;;
		}

		_decorator->start();
		while (Status::Running == _decorator->tick())
		{
			co_yield Status::Running;
		}

		_decorator->stop();
		if (Status::Failed == _decorator->getStatus())
		{
			co_yield Status::Failed;
			co_return;;
		}

		co_yield Status::Succeed;
		co_return;
	}

	Void Decorator::cleanup()
	{
		__super::cleanup();
	}

	Void Decorator::addedComposite(CompositeShaPtr composite)
	{
		setDecorator(composite);
	}
}