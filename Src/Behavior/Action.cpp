#include "stdafx.h"
#include "Action.h"

namespace Behavior
{
	Enumerable<Status> Action::execute()
	{
		Status status = getStatus();

		while (Status::Running == status)
		{
			co_yield run();
		}
	}

	Void Action::cleanup()
	{
		Composite::cleanup();
	}
}