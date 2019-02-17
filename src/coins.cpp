#include "coins.h"
#include "main.h"

#define pi 3.14159265358979323846264338327950288

Coins::Coins(float x, float y, color_t color, int a) {
	this->position = glm::vec3(x, y, 0);
	this->velocity = glm::vec3(0, 0, 0);
	this->acc = glm::vec3(0, 0, 0);
	this->rotation = 0;
	this->colorid=a;
	speed=0.05;
	speedup = 0.1;
	speeddown = 0.025;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	//static const GLfloat vertex_buffer_data[] = {
	//  
	//  0,0,0,
	//  0,5,0,
	//  5,0,0
	//};

	int n=20;//n triangles
	float r=.2 ;
	float theta=(2*pi)/n;

	GLfloat g_vertex_buffer_data[9*n];
	
	//1st triangle
	g_vertex_buffer_data[0]=0;
	g_vertex_buffer_data[1]=0;
	g_vertex_buffer_data[2]=0;
	
	g_vertex_buffer_data[3]=r;
	g_vertex_buffer_data[4]=0;
	g_vertex_buffer_data[5]=0;
	
	g_vertex_buffer_data[6]=r*cos(theta);
	g_vertex_buffer_data[7]=r*sin(theta);
	g_vertex_buffer_data[8]=0;

	float prev[2];
	prev[0]=g_vertex_buffer_data[6];
	prev[1]=g_vertex_buffer_data[7];

	for(int i=1;i<n;i++)
	{
		g_vertex_buffer_data[9*i]=0;
		g_vertex_buffer_data[9*i+1]=0;
		g_vertex_buffer_data[9*i+2]=0;
		
		g_vertex_buffer_data[9*i+3]=prev[0];
		g_vertex_buffer_data[9*i+4]=prev[1];
		g_vertex_buffer_data[9*i+5]=0;
		
		g_vertex_buffer_data[9*i+6]=prev[0]*cos(theta)-prev[1]*sin(theta);
		g_vertex_buffer_data[9*i+7]=prev[0]*sin(theta)+prev[1]*cos(theta);
		g_vertex_buffer_data[9*i+8]=0;

		prev[0]=g_vertex_buffer_data[9*i+6];
		prev[1]=g_vertex_buffer_data[9*i+7];
	}

    this->object1 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, color, GL_FILL);

}

void Coins::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object1);
	//draw3DObject(this->object3);
	//draw3DObject(this->object4);
	//draw3DObject(this->object5);
}

void Coins::set_position(float x, float y) {
	this->position = glm::vec3(x, y, 0);
}

//x is forward coming out of screen
void Coins::tick(int up) {
	this->position=this->position+this->velocity*(glm::vec3(.01,.01,.01));
    this->velocity=this->velocity+this->acc*(glm::vec3(.01,.01,.01));
}

bounding_box_t Coins::bounding_box() {
    float x = this->position.x;
	float y = this->position.y;
    float w = .2;//r
	float h = .2;//r
    bounding_box_t bbox = { x,y,2*w,2*h };
    return bbox;
}