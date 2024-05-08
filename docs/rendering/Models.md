# Models

Spark has rudimentary OBJ model support.
It is able to load and display OBJ models with MTL materials, see graphics/api/models/FileParserOBJ.h and graphics/api/models/FileParserMTL.h for more information on the limitations.

# Loading a model
```
Spark::Graphics::Models::OBJProperties properties;
properties.shaders = shader; // Shader to use for rendering
properties.textureSlots.push_back(8); // Texture slot 8 will be used for the model
std::unique_ptr<Spark::Graphics::Model> model = Spark::Graphics::Models::parseObj("resources/models/cat/cat.obj", properties);
```

# Rendering a model
```
renderer->renderModel(*model);
```