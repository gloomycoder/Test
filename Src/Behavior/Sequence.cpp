#include "stdafx.h"
#include "Sequence.h"

namespace Behavior
{
	Enumerable<Status> Sequence::execute()
	{
		for (auto& i : _child)
		{
			i->start();
			while (Status::Running == i->tick())
			{
				_now = i;
				co_yield Status::Running;
			}

			_now = null;
			i->stop();

			if (i->getStatus() == Status::Failed)
			{
				co_yield Status::Failed;
				co_return;;
			}
		}

		co_yield Status::Succeed;
		co_return;
	}
}