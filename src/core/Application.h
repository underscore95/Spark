#pragma once

namespace Spark {
	class Application {
	private:
		bool running = true;
	public:
		Application();
		virtual ~Application();

		// Feel free to override this function, but make sure to call Application's stop() in your function
		// This function being called is the only way for an Application to stop.
		virtual void stop();

		virtual void update(const float dt) = 0;
		virtual void render() = 0;

		virtual const bool isRunning() const final;
	};
}