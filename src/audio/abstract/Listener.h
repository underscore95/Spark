#pragma once

namespace Spark::Audio {
	class Listener {
	private:

	public:
		virtual void setPosition(float x, float y, float z) = 0;
		virtual void setVelocity(float x, float y, float z) = 0;
		virtual void setOrientation(float forwardX, float forwardY, float forwardZ, float upX, float upY, float upZ) = 0;
	};
}