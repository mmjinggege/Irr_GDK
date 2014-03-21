#ifndef _IRRSINGLETON_H_
#define _IRRSINGLETON_H_

namespace irr_base
{
	template <typename T>
	class IrrSingleton
	{
	private:
		IrrSingleton(const IrrSingleton<T>&){};
		IrrSingleton& operator=(const IrrSingleton<T>&){};

	protected:
		virtual ~IrrSingleton(){_mInstance = 0;}
		IrrSingleton(){};
		static T* _mInstance;
	public:
		static void pugerSingleton() { if (_mInstance) delete _mInstance;}
		static T* getInstance()
		{
			if(_mInstance == 0)
				_mInstance = new T();
			return _mInstance;
		}
	};
	template <typename T> 
	T* IrrSingleton<T>::_mInstance = 0;
}


#endif	//_IRRSINGLETON_H_
