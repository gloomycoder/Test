#include "stdafx.h"
#include "Selector.h"

namespace Behavior
{
	Enumerable<Status> Selector::execute()
	{
		for (auto& i : _child)
		{
			i->start();
			while (Status::Running == i->tick())
			{
				_now = i;
				co_yield Status::Running;
			}

			if (Status::Failed == i->getStatus())
			{
				i->stop();
				continue;
			}

			if (Status::Succeed == i->getStatus())
			{
				co_yield Status::Succeed;
				co_return;;
			}
		}

		_now = null;
		co_yield Status::Failed;
		co_return;
	}
}