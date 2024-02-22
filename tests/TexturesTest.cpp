#include <gtest/gtest.h>
#include "Spark.h"
#include "pch.h"

namespace SparkGraphics = SparkInternal::Graphics::Textures;
using Spark::Graphics::Texture;
using Spark::Graphics::TextureSlot;
using Spark::Graphics::NO_TEXTURE_SLOT;

TEST(SparkInternalGraphicsTexturesTest, bindTextureToSlot) {
    int a = 1;
    Texture* tex = reinterpret_cast<Texture*>(&a);
    SparkGraphics::updateBoundTexture(tex, 1); // Assuming TextureSlot 1 is valid
    ASSERT_EQ(SparkGraphics::getBoundSlot(tex), 1);
}

TEST(SparkInternalGraphicsTexturesTest, unbindTexture) {
    int a = 2;
    Texture* tex = reinterpret_cast<Texture*>(&a);
    SparkGraphics::updateBoundTexture(tex, 2); // Bind first
    SparkGraphics::unbindTexture(tex); // Then unbind
    ASSERT_EQ(SparkGraphics::getBoundSlot(tex), NO_TEXTURE_SLOT);
}

TEST(SparkInternalGraphicsTexturesTest, rebindTextureToDifferentSlot) {
    int a = 3, b = 4;
    Texture* texA = reinterpret_cast<Texture*>(&a);
    Texture* texB = reinterpret_cast<Texture*>(&b);

    SparkGraphics::updateBoundTexture(texA, 3);
    SparkGraphics::updateBoundTexture(texB, 4); // Bind texB to slot 4

    // Now rebind texA to where texB was bound
    SparkGraphics::updateBoundTexture(texA, 4);
    ASSERT_EQ(SparkGraphics::getBoundSlot(texA), 4);
    ASSERT_EQ(SparkGraphics::getBoundSlot(texB), NO_TEXTURE_SLOT); // texB should now be unbound
}

TEST(SparkInternalGraphicsTexturesTest, unbindNonExistentTexture) {
    int a = 5;
    Texture* tex = reinterpret_cast<Texture*>(&a);
    // Attempt to unbind a texture that was never bound
    SparkGraphics::unbindTexture(tex); // This should not crash or affect state
    ASSERT_EQ(SparkGraphics::getBoundSlot(tex), NO_TEXTURE_SLOT);
}