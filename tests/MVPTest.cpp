#include <gtest/gtest.h>
#include "Spark.h"
#include "pch.h"

TEST(MVP, ensureInitialisedAsIdentity) {
    Spark::Utils::MVP mvp;
    auto identity = glm::identity<glm::mat4>();
    ASSERT_EQ(mvp.getModel(), identity);
    ASSERT_EQ(mvp.getView(), identity);
    ASSERT_EQ(mvp.getProj(), identity);
    ASSERT_EQ(mvp.getMVP(), identity);
}

TEST(MVP, setModel) {
    Spark::Utils::MVP mvp;
    auto newModel = glm::mat4(1.0f); // Example new model matrix

    mvp.setModel(newModel);

    ASSERT_EQ(mvp.getModel(), newModel);
    // May need to be changed if MVP is updated to multiply m * v * p
    ASSERT_EQ(mvp.getMVP(), mvp.getProj() * mvp.getView() * newModel);
}

TEST(MVP, setView) {
    Spark::Utils::MVP mvp;
    auto newView = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Example new view matrix

    mvp.setView(newView);

    ASSERT_EQ(mvp.getView(), newView);
    // May need to be changed if MVP is updated to multiply m * v * p
    ASSERT_EQ(mvp.getMVP(), mvp.getProj() * newView * mvp.getModel());
}

TEST(MVP, setProj) {
    Spark::Utils::MVP mvp;
    auto newProj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // Example new projection matrix

    mvp.setProj(newProj);

    ASSERT_EQ(mvp.getProj(), newProj);
    // May need to be changed if MVP is updated to multiply m * v * p
    ASSERT_EQ(mvp.getMVP(), newProj * mvp.getView() * mvp.getModel());
}
