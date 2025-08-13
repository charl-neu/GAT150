#pragma once
#include "Game/Component.h"

namespace viper {
	class RendererComponent : public Component {
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}