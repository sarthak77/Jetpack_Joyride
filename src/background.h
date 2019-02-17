#include "main.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background
{
public:
    Background() {}
    Background(float x, float y,color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // BACKGROUND_H
