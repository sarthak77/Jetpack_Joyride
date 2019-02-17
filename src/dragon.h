#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H

class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y, color_t color,int rot);
    
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acc;
    
    float rotation;
    float jetspeed;
    void draw(glm::mat4 VP);
    void draw2(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int up,int cameye);
    void rp(bool ringpath,int ringcount);
    bounding_box_t bounding_box();

private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
};

#endif // DRAGON_H
