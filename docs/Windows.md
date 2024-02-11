# Windows

Creating a window in Spark is simple!
You should define a `std::unique_ptr<Spark::Window::Window> window` (preferably in your application class).

The following code will create the window using a supported dependency (e.g glfw).
```
window = Spark::Window::create("My Spark Game");

if (!window->isSuccessfullyInitialised()) {
	logger.severe("Failed to init window");
}
```

Your application update method should look something like this:
```
window->update();

if (!window->isWindowOpen()) {
	stop();
}
```