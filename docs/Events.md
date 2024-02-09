# Events

# How to listen for events?
Create a class that extends `Spark::Events::EventListener`.

The listener will automatically be registered upon construction and unregistered upon destruction.

You will need to specify the events your listener is subcribed to.

You can subscribe to a single event by passing a `Spark::Events::EventType` into the constructor.

You can listen to multiple events by passing an unordered set of event types into the constructor, note that you only have one onEvent method so
if you go with this route, you will need to check the event type manually. (`eventContainer.event.type`)

You can optionally specify a priority (signed short, lower numbers will receive the event first), the default priority is 0.

If you handle an event (`eventContainer.handled = true`) then the event will not be sent to any more listeners.

# Custom Events
You can call any event using `Spark::Events::callEvent()`.

Custom events are currently not supported - all events require a value in the `Spark::Events::EventType` enum.
This is a planned feature in the future though.