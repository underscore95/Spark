# Camera

A camera is used to render the world onto the screen.

There are two types of cameras: orthographic and perspective.
If you aren't familiar with projection matrices, see:
https://en.wikipedia.org/wiki/3D_projection#Orthographic_projection
https://en.wikipedia.org/wiki/3D_projection#Perspective_projection

You can create a camera using:
`Spark::Graphics::ortho(const float left, const float right, const float bottom, const float top, const float zNear = 0.1f, const float zFar = 100.0f);`
`Spark::Graphics::perspective(const float fovY, const float aspect, const float zNear = 0.1f, const float zFar = 100.0f);`

You can set the position and rotation of a camera to adjust the view matrix.
Although you can get the MVP from the camera with `getMatrix()`, editing it will cause undefined behaviour.

To move the camera you can use the setRotation and setPosition methods.
You can attach a CameraController to a camera like this:

`camera->setCameraController(cameraControllerUniquePtr);`

CameraController is a pure virtual class which you can implement yourself, or you can use one of the default Spark implementations:

`KeyboardCameraController` - WASD + space/sneak movement and arrow keys to control yaw & pitch, designed for perspective cameras.

Camera controllers have an update and handleInput method which Spark will call for you automatically. 
Spark will respect your controller being enabled or disabled.
Spark will manage the lifetime of your controller for you.

Note that you do not have to use a camera controller to control a camera, you can directly use setPosition and setRotation methods 
if it is easier for you.

You can use the methods `setPerspectiveProjection` and `setOrthographicProjection` to change the projection.
If you just want to update the window dimensions and don't want to change anything else, you can use the methods
`updatePerspectiveProjection` and `updateOrthographicProjection`.

Updating the projection every time the window is resized is annoying. You can use `linkWindow` which will automatically update
the camera projection matrix to be the correct size. Note that you must have a camera controller set to use window linking.