#pragma once

namespace SparkInternal::Audio {
	typedef int AudioFormat;

	extern const AudioFormat MONO8;
	extern const AudioFormat MONO16;
	extern const AudioFormat STEREO8;
	extern const AudioFormat STEREO16;

	void init();
	void exit();
}