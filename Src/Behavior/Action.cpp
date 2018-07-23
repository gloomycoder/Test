#include "stdafx.h"
#include "Action.h"

namespace Behavior
{
	Enumerable<Status> Action::execute()
	{
		Status status = Status::Running;
		enter();
		while (Status::Running == status)
		{
			co_yield run();
		}

		co_return;
	}

	Void Action::cleanup()
	{
		__super::cleanup();
	}
}