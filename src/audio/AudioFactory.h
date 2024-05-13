#pragma once

#include "abstract/Listener.h"
#include "abstract/Sound.h"
#include "abstract/Source.h"
#include "pch.h"

namespace Spark::Audio {
	class AudioFactory {
	public:
		static [[nodiscard]] Listener& getListener();
		static [[nodiscard]] std::shared_ptr<Sound> loadSound(const std::string_view& path);
		static [[nodiscard]] std::unique_ptr<Source> createSource(const Sound& sound);
	};
}