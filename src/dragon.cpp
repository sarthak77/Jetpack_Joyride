#include "dragon.h"
#include "main.h"

Dragon::Dragon(float x, float y, color_t color,int rot) {
    this->position = glm::vec3(x, y, 0);
    this->velocity = glm::vec3(.06, 0, 0);
    this->acc = glm::vec3(0, -10, 0);
    this->rotation = 90;
    this->jetspeed=.1;
    

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        0,0,110,
        0,-1,110,
        -1,-1,110,

        0,-1,110,
        -1,-1,110,
         0,-2,110,

         -1,-2,110,
        -1,-1,110,
         0,-2,110,

         -1,-2,110,
         -1,-4,110,
         -1.5,-4,110,

         -1,-2,110,
         -1,-4,110,
         0,-4,110,

         0,-2,110,
         0,-4,110,
         -1,-2,110,

         -0,-4,110,
         -4.5,-4,110,
         -3,-3,110,

         -3.5,-4,110,
         0,-4,110,
         0,-7,110,

         -3.5,-4,110,
         -4,-4.5,110,
         0,-4,110,

         -3,-4.3,110,
         -3.5,-5,110,
         0,-4.5,110,

         0,0,110,
         0,-7,110,
         -1.5,-9,110
      
    };

    GLfloat a_vertex_buffer_data[11*9];
    for(int i=0;i<11*9;i++)
    {
        if(i%3==0)
            a_vertex_buffer_data[i]=-vertex_buffer_data[i];
        else
            a_vertex_buffer_data[i]=vertex_buffer_data[i];
    }

    this->object1 = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data, COLOR_GOLDEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data+10*9, COLOR_FIRE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES,10*3, a_vertex_buffer_data, COLOR_GOLDEN, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES,1*3, a_vertex_buffer_data+10*9, COLOR_FIRE, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Dragon::draw2(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object7);
    
}



void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick(int up,int cameye) {

this->position.y+=jetspeed;
if(this->position.y>3)
    jetspeed=-jetspeed;
if(this->position.y<-3)
    jetspeed=-jetspeed;

    
}

void Dragon::rp(bool ringpath,int ringcount){
    
    this->position.y=sin(this->position.x);


}

bounding_box_t Dragon::bounding_box() {
    float x = this->position.x+1;
    float y = this->position.y;
    float w = .5;
    float h = .5;
    bounding_box_t bbox = { x,y,2*w,2*h };
    return bbox;
}
