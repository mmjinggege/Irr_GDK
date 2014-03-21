#ifndef _IRRCALLBACK_H_
#define _IRRCALLBACK_H_

namespace irr_utils
{
	template <class ClassInstance, class ParamType>
	class IrrGenericCallback
	{
	public:
		IrrGenericCallback()
		{
			_function = 0;
		}

		typedef void (ClassInstance::*FunctionPointer)(ParamType param);

		virtual void Execute(ParamType param) const
		{
			if (_function) 
				(_instance->*_function)(param);
			else 
				printf("WARNING: No callback function specified!");
		}

		void SetCallback( ClassInstance* instance, FunctionPointer function)
		{
			_instance = instance;
			_function = function;
		}

		const ClassInstance* GetInstance()
		{
			return _instance;
		}

		const FunctionPointer GetFunction()
		{
			return _function;
		}
	private:
		ClassInstance*	_instance;
		FunctionPointer  _function;
	};
}

#endif	//_IRRCALLBACK_H_