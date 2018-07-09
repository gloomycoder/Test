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
		generator2 get_return_object() { return generator2{ this }; }
	};

	Bool isGood() { return !!_handle; }
	Bool moveNext() { _handle.resume(); return !_handle.done(); }
	return_type currentValue() { return _handle.promise()._value; }

	~Enumerable()
	{
		_handle.destroy();
	}

	Enumerable() = default;
private:
	explicit Enumerable(promise_type* handle)
		: _handle(coroutine_handle<promise_type>::from_promise(*handle))
	{}
	coroutine_handle<promise_type> _handle;
};