#include "ball.h"
#include "main.h"
Ball::Ball(float x, float y, color_t color,int jetpack) {
    this->position = glm::vec3(x, y, 0);
    this->velocity = glm::vec3(.06, 0, 0);
    this->acc = glm::vec3(0, -10, 0);
    this->rotation = 0;
    this->jetspeed=.1;
    

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
      //face
       0,0,100,//extreme ends are 4 and -4
        0,.4,100,
        .4,0,100,

        0,.4,100,
        .4,0,100,
        .4,.4,100,

        //glares
        .4,.2,100,
        .4,.35,100,
        .25,.2,100,

        .25,.35,100,
        .4,.35,100,
        .25,.2,100,


        //hair

        .4,.4,100,
        0,.4,100,
        0,.5,100,

        .4,.4,100,
        .4,.5,100,
        .5,.5,100,

        .4,.4,100,
        .4,.5,100,
        0,.5,100,

        -.1,.5,100,
        0,.5,100,
        0,.1,100,

        0,.1,100,
        -.1,.5,100,
        -.1,.1,100,

        0,0,100,
        0,.1,100,
        -.1,.1,100,

        //rocket
        0,0,100,
        -.1,.1,100,
        -.2,0,100,

        0,0,100,
        0,-.5,100,
        -.2,0,100,//

        -.2,-.5,100,//
        0,0,100,
        -.2,0,100,

        //lower body

        0,-.4,100,
        0,0,100,
        .3,-.4,100,
        
        .3,-.4,100,
        0,0,100,
        .3,0,100,

        //shoes

        0,-.4,100,
        0,-.5,100,
        0.4,-.5,100,

        .3,-.5,100,
        0,-.4,100,
        .3,-.4,100,

        .3,-.4,100,
        .3,-.5,100,
        .4,-.5,100
    };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_SKIN, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+2*9, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data+4*9, COLOR_BROWN, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data+10*9, COLOR_BLACK, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+13*9, COLOR_BLUE, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data+15*9, COLOR_RED, GL_FILL);


    static const GLfloat a_vertex_buffer_data[] = {
        0,-.5,100,
        -.2,-.5,100,
        -.1,-.25,100,

        0,-.5,100,
        -.2,-.5,100,
        -.1,-.75,100


    } ;
    this->object7 = create3DObject(GL_TRIANGLES, 2*3, a_vertex_buffer_data, COLOR_FIRE, GL_FILL);

}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
}

void Ball::draw2(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object7);
    
}



void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick(int up,int cameye) {

    //for magnet
    if(this->position.y>3.5)
        this->position.y=3.4;

    //up
    if(up==1 && this->position.y+this->velocity.y<3.5)
    {
        this->velocity.y=0;
        this->position.y += this->jetspeed;
    }
    
    //down
    if(up==0 && this->position.y>-3)
    {
        //std::cout <<this->velocity.y << "\n\n";
        this->position=this->position+this->velocity*(glm::vec3(.01,.01,.01));
        this->velocity=this->velocity+this->acc*(glm::vec3(.01,.01,.01));
    }

    //right
    if(up==2)
        this->position.x += this->velocity.x;
    
    //left
    if(up==3)
        this->position.x -= this->velocity.x;
    
}

void Ball::rp(bool ringpath,int ringcount){
    
    this->position.y=sin(this->position.x);


}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x+.1;
    float y = this->position.y;
    float w = .3;
    float h = .5;
    bounding_box_t bbox = { x,y,2*w,2*h };
    return bbox;
}
