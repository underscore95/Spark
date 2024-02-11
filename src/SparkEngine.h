#pragma once
#include "core/Application.h"
#include "pch.h"

namespace SparkInternal {
	void init(std::function<Spark::Application*()> appInitialiser);
}

namespace Spark {
	template<typename T>
	typename std::enable_if<std::is_base_of<Spark::Application, T>::value && !std::is_same<Spark::Application, T>::value>::type
	init() {
		SparkInternal::init([] { return new T(); });
	}
}