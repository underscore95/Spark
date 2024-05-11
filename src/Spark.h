#pragma once

// This will include most important .h files in spark

#include "core/Application.h"

// Window
#include "window/abstract/Window.h"
#include "window/api/WindowFactory.h"

// Input
#include "window/api/Input.h"
#include "window/api/KeysAndButtons.h"

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
#include "entities/EntityID.h"

// Systems
#include "systems/System.h"
#include "systems/SystemManager.h"

// Graphics
#include "graphics/api/GraphicsFactory.h"
#include "graphics/api/Camera/Camera.h"
#include "graphics/api/Camera/CameraController.h"
#include "graphics/api/Camera/KeyboardCameraController.h"
#include "graphics/api/models/FileParserMTL.h"
#include "graphics/api/models/FileParserOBJ.h"

// Audio
#include "audio/AudioFactory.h"