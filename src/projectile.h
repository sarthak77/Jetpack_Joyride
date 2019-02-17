#include "main.h"

#ifndef PROJECTILE_H
#define PROJECTILE_H


class Projectile {
public:
    Projectile() {}
    Projectile(float x, float y, float speed,float angle,float g,color_t color,int colorid);
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acc;
    float rotation;
    int cid;
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
};

#endif // PROJECTILE_H
