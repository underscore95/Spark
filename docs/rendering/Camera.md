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
If you want to modify the projection matrix, you can use:
`camera.getMatrix().setProjection(const glm::mat4&)`

Note that attempts to modify the view or model matrices in the MVP is undefined behaviour and may be overwritten by the camera or renderer.