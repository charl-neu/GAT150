#include "Observer.h"

namespace nebula
{
	nebula::IObserver::~IObserver()
	{
		OBSERVER_REMOVE_SELF;
	}
}