#include "background.h"
#include "main.h"

/*
background from 1-400
background from 1-600
*/

Background::Background(float x,float y,color_t color){

    this->position = glm::vec3(x, y, 0);

    GLfloat vertex_buffer_data2[500*9];

    float xtrans=0;
    for(int i=0;i<60;i++)
    {
        vertex_buffer_data2[9*i]=-10+xtrans;
        vertex_buffer_data2[9*i+1]=-3;
        vertex_buffer_data2[9*i+2]=0;
        vertex_buffer_data2[9*i+3]=10+xtrans;
        vertex_buffer_data2[9*i+4]=-3;
        vertex_buffer_data2[9*i+5]=0;
        vertex_buffer_data2[9*i+6]=-10+xtrans;
        vertex_buffer_data2[9*i+7]=-10;
        vertex_buffer_data2[9*i+8]=0;
        vertex_buffer_data2[9*i+9]=10+xtrans;
        vertex_buffer_data2[9*i+10]=-3;
        vertex_buffer_data2[9*i+11]=0;
        vertex_buffer_data2[9*i+12]=10+xtrans;
        vertex_buffer_data2[9*i+13]=-3;
        vertex_buffer_data2[9*i+14]=0;
        vertex_buffer_data2[9*i+15]=10+xtrans;
        vertex_buffer_data2[9*i+16]=-10;
        vertex_buffer_data2[9*i+17]=0;
        xtrans+=10;
    }

    xtrans=0;
    for(int i=0;i<60;i++)
    {
        vertex_buffer_data2[540+9*i]=-10+xtrans;
        vertex_buffer_data2[540+9*i+1]=4.5;
        vertex_buffer_data2[540+9*i+2]=0;
        vertex_buffer_data2[540+9*i+3]=10+xtrans;
        vertex_buffer_data2[540+9*i+4]=4.5;
        vertex_buffer_data2[540+9*i+5]=0;
        vertex_buffer_data2[540+9*i+6]=-10+xtrans;
        vertex_buffer_data2[540+9*i+7]=10;
        vertex_buffer_data2[540+9*i+8]=0;
        vertex_buffer_data2[540+9*i+9]=10+xtrans;
        vertex_buffer_data2[540+9*i+10]=4.5;
        vertex_buffer_data2[540+9*i+11]=0;
        vertex_buffer_data2[540+9*i+12]=10+xtrans;
        vertex_buffer_data2[540+9*i+13]=4.5;
        vertex_buffer_data2[540+9*i+14]=0;
        vertex_buffer_data2[540+9*i+15]=10+xtrans;
        vertex_buffer_data2[540+9*i+16]=10;
        vertex_buffer_data2[540+9*i+17]=0;
        xtrans+=10;
    }

    this->object2 = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data2, COLOR_G2, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data2+60*9, COLOR_BACKGROUND, GL_FILL);



    static const GLfloat vertex_buffer_data[] = {
        
        //right

       0.5,-2,-1,
        0.5,3,-1,
        3.5,-2,-1,

        0.5,3,-1,
        3.5,-2,-1,
        3.5,3,-1,

        //small triangles
        2.1,3,-1,
        2.4,3,-1,
        2.4,3.3,-1,

        .2,3,-1,
        .5,3,-1,
        .5,3.3,-1,

        .2,-2,-1,
        .5,-2,-1,
        .5,-2.3,-1,

        1.9,3,-1,
        1.6,3,-1,
        1.6,3.3,-1,

        3.8,3,-1,
        3.5,3,-1,
        3.5,3.3,-1,

        3.8,-2,-1,
        3.5,-2,-1,
        3.5,-2.3,-1,

        2.1,-2,-1,
        2.4,-2,-1,
        2.4,-2.3,-1,

        1.9,-2,-1,
        1.6,-2,-1,
        1.6,-2.3,-1,

        //small rectangles

        2.4,3.3,-1,
        2.4,3,-1,
        3.5,3,-1,

        2.4,3.3,-1,
        3.5,3.3,-1,
        3.5,3,-1,

        .5,3.3,-1,
        .5,3,-1,
        1.6,3,-1,

        .5,3.3,-1,
        1.6,3.3,-1,
        1.6,3,-1,

        2.4,-2,-1,
        2.4,-2.3,-1,
        3.5,-2.3,-1,

        2.4,-2,-1,
        3.5,-2,-1,
        3.5,-2.3,-1,

        .5,-2,-1,
        .5,-2.3,-1,
        1.6,-2.3,-1,

        .5,-2,-1,
        1.6,-2,-1,
        1.6,-2.3,-1,

    
    };
    //this->object1 = create3DObject(GL_TRIANGLES, 18*3, vertex_buffer_data, COLOR_GREY, GL_FILL);


    GLfloat vertex_buffer_data3[200*18*9];
    xtrans=-2;
    
    int mid=18*9;
    int k=0;
    for(xtrans=-10;xtrans<389;xtrans+=3.5)
    {
        //this loop has 18 triangles
        for(int i=0;i<mid;i++)
        {
            if(i%3==0)
                vertex_buffer_data3[k*mid+i]=vertex_buffer_data[i]+xtrans;
            else
                vertex_buffer_data3[k*mid+i]=vertex_buffer_data[i];
        }
        k++;
    }
    this->object4 = create3DObject(GL_TRIANGLES, 114*18*3, vertex_buffer_data3, COLOR_GREY, GL_FILL);//114=389+10/3.5



}

void Background::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model ;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Background::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
