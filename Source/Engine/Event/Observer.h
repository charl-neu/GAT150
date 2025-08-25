#pragma once

namespace viper
{
	class IObserver {
		public:
		virtual ~IObserver() = default;
		virtual void OnNotify() = 0;
	};
}