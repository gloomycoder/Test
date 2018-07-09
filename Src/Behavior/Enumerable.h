#pragma once


template<typename _TRet>
struct Enumerable
{
	using return_type = _TRet;

	struct promise_type
	{
		return_type _value;
		suspend_always yield_value(return_type value)
		{
			_value = value;
			return {};
		}

		suspend_always initial_suspend() { return {}; }
		suspend_always final_suspend() { return {}; }
		Enumerable get_return_object() { return Enumerable{ this }; }
	};

	Bool isGood() { return !!_handle; }
	Bool moveNext() { _handle.resume(); return !_handle.done(); }
	Void reset() { if (isGood()) { _handle.destroy(); _handle = null; } }
	return_type currentValue() { return _handle.promise()._value; }

	~Enumerable()
	{
		reset();
	}

	Enumerable() = default;
private:
	explicit Enumerable(promise_type* handle)
		: _handle(coroutine_handle<promise_type>::from_promise(*handle))
	{}
	coroutine_handle<promise_type> _handle;
};