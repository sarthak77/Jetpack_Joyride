#include "main.h"

#ifndef ROCKET_H
#define ROCKET_H


class Rocket {
public:
    Rocket() {}
    Rocket(float x, float y, float speed ,float radius);
    glm::vec3 position;
    float rotation;
    float radius;
    float speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int up);
    bounding_box_t bounding_box();

private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
};

#endif // ROCKET_H
