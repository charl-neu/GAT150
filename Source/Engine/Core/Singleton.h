#pragma once

namespace viper {
	template <typename T>
	class Singleton {
		public:
			Singleton(const Singleton&) = delete;
			Singleton& operator = (const Singleton&) = delete;


		protected:
			Singleton() = default;

	};

}