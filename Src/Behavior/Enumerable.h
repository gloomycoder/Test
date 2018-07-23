#pragma once

/*
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
		//_handle.destroy();
		std::experimental::generator
	}

	Enumerable()
		: _handle(null)
	{
	}
private:
	explicit Enumerable(promise_type* handle)
		: _handle(coroutine_handle<promise_type>::from_promise(*handle))
	{}
	coroutine_handle<promise_type> _handle;
};
*/

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
		promise_type& get_return_object() { return *this; }
	};

	Bool isGood() { return !!_handle; }
	Bool moveNext() { _handle.resume(); return !_handle.done(); }
	Void reset() { if (isGood()) { _handle.destroy(); _handle = null; } }
	return_type currentValue() { return _handle.promise()._value; }

	~Enumerable()
	{
		if (_handle)
		{
			_handle.destroy();
		}
	}

	Enumerable() = default;
	Enumerable(Enumerable const &) = delete;
	Enumerable& operator=(Enumerable const &) = delete;
	Enumerable(Enumerable&& right)
		: _handle(right._handle)
	{
		right._handle = null;
	}
	Enumerable& operator=(Enumerable&& right)
	{
		if (this != std::addressof(right))
		{
			_handle = right._handle;
			right._handle = null;
		}

		return *this;
	}

	Enumerable(promise_type& handle)
		: _handle(coroutine_handle<promise_type>::from_promise(handle))
	{}
public:
	coroutine_handle<promise_type> _handle;
};