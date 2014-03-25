#ifndef _IRRINTERVAL_H_
#define _IRRINTERVAL_H_	

#include "IrrMathUtils.h"

namespace irr_core
{
	template<class T>
	class IrrInterval
	{
	public:
		IrrInterval(T start,T end,float duration,bool smooth = false)
			:_start(start),
			_end(end),
			_current(start),
			_duration(duration),
			_timer(0.0f),
			_shouldStep(true),
			_smoothStep(smooth)
		{

		}

		IrrInterval()
		{
			_shouldStep = false;
		}

		T Step(float dt)
		{
			if (!_shouldStep)
			{
				return _current;
			}

			_timer += dt;

			if (_timer >= _duration)
			{
				_current = _end;
				_shouldStep = false;
			}
			else
			{
				float stepRatio = _timer / _duration;
				if (_smoothStep)
				{
					//smooth step
					_current = irr_utils::IrrMathUtils::SmoothStep(_start, _end, stepRatio);
				}
				else
				{
					//simple lerp
					_current = irr_utils::IrrMathUtils::Lerp(_start, _end, stepRatio);
				}
			}
			return _current;
		}
		
		float GetCurrent()
		{
			return _current;
		}
		
		bool ShouldStep()
		{
			return _shouldStep;
		}
	};
}



#endif	//_IRRINTERVAL_H_