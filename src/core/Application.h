#pragma once

namespace Spark {
	class Application {
	private:
		bool running = true;
	public:
		Application();
		virtual ~Application();

		// Feel free to override this function, but make sure to call Application's stop() in your function
		virtual void stop();

		virtual void update() = 0;
		virtual void render() = 0;

		virtual const bool isRunning() const final;
	};
}