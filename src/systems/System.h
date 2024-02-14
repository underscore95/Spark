#pragma once

namespace Spark {
	class System {
	public:
		System() = default;
		System(const System&) = delete;
		~System() = default;

		virtual void onUpdate(const float dt) = 0;
		virtual void onRender() = 0;
	};
}