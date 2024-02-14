#pragma once

// This will include most important .h files in spark

#include "core/Application.h"

// Window
#include "window/abstract/Window.h"
#include "window/api/WindowFactory.h"

// Logging
#include "logging/Logger.h"
#include "logging/Logging.h"

// Events
#include "events/Events.h"
#include "events/EventListener.h"
#include "events/EventContainer.h"

// Entities
#include "entities/BaseComponent.h"
#include "entities/EntityManager.h"
#include "entities/ComponentTypeRegistry.h"
#include "entities/View.h"