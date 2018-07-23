#include "stdafx.h"
#include "GroupComposite.h"

namespace Behavior
{
	Bool GroupComposite::isEnd() const
	{
		if (_child.empty())
		{
			throw std::runtime_error("child is empty");
		}

		if (null == _now)
		{
			return false;
		}

		return _child.back().get() == _now.get();
	}
}