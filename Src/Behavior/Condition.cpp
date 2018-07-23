#include "stdafx.h"
#include "Condition.h"

namespace Behavior
{
	Bool Condition::can()
	{
		return check();
	}
}