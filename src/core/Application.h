#pragma once

namespace Spark {
	class Application {
	private:
		bool running = false;
	public:
		Application();
		virtual ~Application();

		virtual void start() = 0;
	};
}