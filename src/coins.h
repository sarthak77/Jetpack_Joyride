#include "main.h"

#ifndef COINS_H
#define COINS_H


class Coins {
public:
    Coins() {}
    Coins(float x, float y, color_t color ,int a);
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acc;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int up);
    float speedup;
    float speeddown;
    float speed;
    int colorid;
    bounding_box_t bounding_box();

private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
};

#endif // COINS_H
