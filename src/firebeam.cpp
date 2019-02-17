#include "firebeam.h"
#include "main.h"

#define pi 3.14159265358979323846264338327950288

Firebeam::Firebeam(float x, float y, int color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->dis=12;
    

    int n=100;//n triangles
	float r=.5 ;
	float theta=(2*pi)/n;
	float prev[2];
    int i;
    float ytrans=0;
    float ytransinc=-1.5;

	GLfloat g_vertex_buffer_data[3*9*n];
	GLfloat vertex_buffer_data[3*9*n];

for(int k=0;k<3;k++)
{
//1st circle
	//1st triangle
	g_vertex_buffer_data[n*9*k+0]=0;
	g_vertex_buffer_data[n*9*k+1]=0+ytrans;
	g_vertex_buffer_data[n*9*k+2]=0;
	
	g_vertex_buffer_data[n*9*k+3]=r;
	g_vertex_buffer_data[n*9*k+4]=0+ytrans;
	g_vertex_buffer_data[n*9*k+5]=0;
	
	g_vertex_buffer_data[9*n*k+6]=r*cos(theta);
	g_vertex_buffer_data[9*n*k+7]=r*sin(theta)+ytrans;
	g_vertex_buffer_data[9*n*k+8]=0;

	prev[0]=g_vertex_buffer_data[n*9*k+6];
	prev[1]=g_vertex_buffer_data[n*9*k+7]-ytrans;

	for(i=1;i<n;i++)
	{
		g_vertex_buffer_data[n*9*k+9*i]=0;
		g_vertex_buffer_data[n*9*k+9*i+1]=0+ytrans;
		g_vertex_buffer_data[n*9*k+9*i+2]=0;
		
		g_vertex_buffer_data[n*9*k+9*i+3]=prev[0];
		g_vertex_buffer_data[n*9*k+9*i+4]=prev[1]+ytrans;
		g_vertex_buffer_data[n*9*k+9*i+5]=0;
		
		g_vertex_buffer_data[n*9*k+9*i+6]=prev[0]*cos(theta)-prev[1]*sin(theta);
		g_vertex_buffer_data[n*9*k+9*i+7]=prev[0]*sin(theta)+prev[1]*cos(theta)+ytrans;
		g_vertex_buffer_data[n*9*k+9*i+8]=0;

		prev[0]=g_vertex_buffer_data[n*9*k+9*i+6];
		prev[1]=g_vertex_buffer_data[n*9*k+9*i+7]-ytrans;
        
	}

//2nd circle
    //1st triangle
	vertex_buffer_data[n*9*k+0]=0+dis;
	vertex_buffer_data[n*9*k+1]=0+ytrans;
	vertex_buffer_data[n*9*k+2]=0;
	
	vertex_buffer_data[n*9*k+3]=r+dis;
	vertex_buffer_data[n*9*k+4]=0+ytrans;
	vertex_buffer_data[n*9*k+5]=0;
	
	vertex_buffer_data[n*9*k+6]=r*cos(theta)+dis;
	vertex_buffer_data[n*9*k+7]=r*sin(theta)+ytrans;
	vertex_buffer_data[n*9*k+8]=0;

	
	prev[0]=vertex_buffer_data[n*9*k+6]-dis;
	prev[1]=vertex_buffer_data[n*9*k+7]-ytrans;

	for(i=1;i<n;i++)
	{
		vertex_buffer_data[n*9*k+9*i]=0+dis;
		vertex_buffer_data[n*9*k+9*i+1]=0+ytrans;
		vertex_buffer_data[n*9*k+9*i+2]=0;
		
		vertex_buffer_data[n*9*k+9*i+3]=prev[0]+dis;
		vertex_buffer_data[n*9*k+9*i+4]=prev[1]+ytrans;
		vertex_buffer_data[n*9*k+9*i+5]=0;
		
		vertex_buffer_data[n*9*k+9*i+6]=prev[0]*cos(theta)-prev[1]*sin(theta)+dis;
		vertex_buffer_data[n*9*k+9*i+7]=prev[0]*sin(theta)+prev[1]*cos(theta)+ytrans;
		vertex_buffer_data[n*9*k+9*i+8]=0;

		prev[0]=vertex_buffer_data[n*9*k+9*i+6]-dis;
		prev[1]=vertex_buffer_data[n*9*k+9*i+7]-ytrans;
        
	}
    ytrans+=ytransinc;
}

	//std::cout << color << "\n\n";
	if(!color)
	{
    	this->object1 = create3DObject(GL_TRIANGLES, 3*n*3, g_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    	this->object2 = create3DObject(GL_TRIANGLES, 3*n*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
	}
	else
	{
    	this->object1 = create3DObject(GL_TRIANGLES, 3*n*3, g_vertex_buffer_data, COLOR_FIRE, GL_FILL);
    	this->object2 = create3DObject(GL_TRIANGLES, 3*n*3, vertex_buffer_data, COLOR_FIRE, GL_FILL);

	}

//beam
	GLfloat a_vertex_buffer_data[]={

        0,-r/4,0,
        dis,-r/4,0,
        0,r/4,0,
        0,r/4,0,
        dis,r/4,0,
        dis,-r/4,0,

        0,-r/4+ytransinc,0,
        dis,-r/4+ytransinc,0,
        0,r/4+ytransinc,0,
        0,r/4+ytransinc,0,
        dis,r/4+ytransinc,0,
        dis,-r/4+ytransinc,0,

        0,-r/4+2*ytransinc,0,
        dis,-r/4+2*ytransinc,0,
        0,r/4+2*ytransinc,0,
        0,r/4+2*ytransinc,0,
        dis,r/4+2*ytransinc,0,
        dis,-r/4+2*ytransinc,0
    };
    this->object3 = create3DObject(GL_TRIANGLES, 3*2*3, a_vertex_buffer_data, COLOR_FIRE, GL_FILL);



}

void Firebeam::draw(glm::mat4 VP) {
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
}


void Firebeam::draw2(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object3);
}

void Firebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

//x is forward coming out of screen
void Firebeam::tick(float up) {
    this->position.x += up;
    
}


bounding_box_t Firebeam::bounding_box() {
    float x = this->position.x+(this->dis)/2;
	float y = -1.5;//ytransinc
    float w = (this->dis)/2+.5;//r
	float h = 1.5+.5;//ytransinc+r
    bounding_box_t bbox = { x,y,2*w,2*h };
    return bbox;
}