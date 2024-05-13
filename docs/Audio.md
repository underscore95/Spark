# Audio

## Devices

Spark will automatically create a context for the 'default' audio device.
This context will be destroyed when the application exits.

Spark does not support multiple audio devices.

## Loading a sound effect

You can load a .wav file using the loadSound method.
```
std::unique_ptr<Sound> sound = Spark::Audio::AudioFactory::loadSound("resources/audio/player_walk.wav");
```

Sound is the actual sound effect data. This is not directly playable. You will need to create a source to play the sound.

## Sources

A source is a point in 3D space that plays a sound.

```
std::unique_ptr<Source> source = Spark::Audio::AudioFactory::createSource(*sound);
```

You can use the following methods to control the source:
```
setPitch(float pitch); // Default 1.0
setGain(float gain); // Default 1.0
setPosition(float x, float y, float z); // Default 0, 0, 0
setVelocity(float x, float y, float z); // Default 0, 0, 0
```

You must ensure that the source is deleted before the sound it uses is.
You must also ensure that the sound is not currently playing when it is deleted.

## Playing a sound

You can tell the source to play its sound effect using the play method.
Example below:

```
if (window->getUserInput().isKeyPressed(Spark::Window::Keyboard::ENTER)) {
	source->play();
}
```

## Unloading a sound effect

You can unload a sound effect by simply destroying the Sound object.

## Listener

You can modify the properties of the listener using the following methods:
```
setPosition(float x, float y, float z) // Default 0, 0, 0
setVelocity(float x, float y, float z) // Default 0, 0, 0
setOrientation(float forwardX, float forwardY, float forwardZ, float upX, float upY, float upZ) // Default 0, 0, -1, 0, 1, 0
```

The listener is a point in 3D space that listens to all sounds.
The listener is a singleton which can be accessed using the following method:
```
Listener& listener = Spark::AudioFactory::getListener();
```
