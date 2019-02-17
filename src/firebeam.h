#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H


class Firebeam {
public:
    Firebeam() {}
    Firebeam(float x, float y, int color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void draw2(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float up);
    float dis;
    bounding_box_t bounding_box();

private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
};

#endif // FIREBEAM_H
