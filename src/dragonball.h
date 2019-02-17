#include "main.h"

#ifndef DRAGONBALL_H
#define DRAGONBALL_H


class Dragonball {
public:
    Dragonball() {}
    Dragonball(float x, float y);
    glm::vec3 position;
    glm::vec3 velocity;
    float rotation;
    void draw(glm::mat4 VP,float x,float y);
    void set_position(float x, float y);
    void tick(float x,float y);
    bounding_box_t bounding_box();

private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
};

#endif // DRAGONBALL_H
