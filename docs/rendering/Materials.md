# Materials

A material defines how a mesh should be drawn, for example the shader to use, the textures to bind.

You can create a material with `Material(std::shared_ptr<ShaderProgram> shaders)`.

You can bind and unbind materials, however the Renderer will do that for you, so it isn't recommended.

You can bind textures to specific texture slots (see Textures.md for an explanation of texture slots).
`withTexture(std::shared_ptr<Texture> texture, TextureSlot slot)`

You can use `setActiveTexture(const TextureSlot slot)` to reuse one shader and material for objects with different textures.
A `Sp_ActiveTexture` uniform will be set in your fragment shader. (see shaders documentation)