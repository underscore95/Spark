# Windows

Creating a window in Spark is simple!
You should define a `std::unique_ptr<Spark::Window::Window> window` (preferably in your application class).

The following code will create the window using a supported dependency (e.g glfw).
```
window = Spark::Window::create("My Spark Game");

if (!window->isSuccessfullyInitialised()) {
	std::cout << "Failed to init window\n";
}
```

Your game loop should look something like this:
```
while (window->isWindowOpen()) {
	window->update();
}
```