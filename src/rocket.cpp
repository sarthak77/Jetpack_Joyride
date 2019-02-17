#include "rocket.h"
#include "main.h"
#include "timer.h"

Timer t=(3);
Timer t2=(10);
bool flag=true;
bool flag2=true;

#define pi 3.14159265358979323846264338327950288

Rocket::Rocket(float x, float y, float speed ,float radius) {
	this->position = glm::vec3(x, y, 0);
	this->rotation = 0;
	this->radius=radius;
	this->speed=speed;

	static const GLfloat g_vertex_buffer_data[]={
		////////////////////////////////////////
		//////////////////
		//main body
		0,-radius+0,0,
		0,-radius+.75,0,
		.75,-radius+0,0,

		.75,-radius+0,0,
		.75,-radius+.75,0,
		0,-radius+.75,0,

		//in fire
		.75,-radius+0,1,
		.75,-radius+.75,1,
		1.125,-radius+.375,1,

		//front
		0,-radius+0,0,
		0,-radius+.75,0,
		-.375,-radius+.375,0,

		//wings
		.4,-radius+.75,0,
		.6,-radius+.75,0,
		.6,-radius+1.05,0,

		.4,-radius+0,0,
		.6,-radius+0,0,
		.6,-radius+-.25,0,

		//out fire
		.75,-radius+.95,0,
		.75,-radius+-.25,0,
		1.5,-radius+.375,0

	};


	this->object1 = create3DObject(GL_TRIANGLES, 1*3, g_vertex_buffer_data, COLOR_CLAN, GL_FILL);
	this->object2 = create3DObject(GL_TRIANGLES, 1*3, g_vertex_buffer_data+9*1, COLOR_CLAN, GL_FILL);
	this->object3 = create3DObject(GL_TRIANGLES, 1*3, g_vertex_buffer_data+9*2, COLOR_YELLOW, GL_FILL);
	this->object4 = create3DObject(GL_TRIANGLES, 1*3, g_vertex_buffer_data+9*3, COLOR_RED, GL_FILL);
	this->object5 = create3DObject(GL_TRIANGLES, 1*3, g_vertex_buffer_data+9*4, COLOR_RED, GL_FILL);
	this->object6 = create3DObject(GL_TRIANGLES, 1*3, g_vertex_buffer_data+9*5, COLOR_RED, GL_FILL);
	this->object7 = create3DObject(GL_TRIANGLES, 1*3, g_vertex_buffer_data+9*6, COLOR_FIRE, GL_FILL);

}

void Rocket::draw(glm::mat4 VP) {
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
	draw3DObject(this->object5);
	draw3DObject(this->object6);
	draw3DObject(this->object7);
}

void Rocket::set_position(float x, float y) {
	this->position = glm::vec3(x, y, 0);
}

//x is forward coming out of screen
void Rocket::tick(int up)
{
	if(t2.processTick())
	{
		flag2=false;
		this->position.y=100;
		flag=true;
		flag2=true;
		//t=(3);
		//t2=(10);
	}
	if(flag2)
	{
		if(t.processTick())
			flag=false;

		if(flag)
			this->position.x+=this->speed;
		else if(!flag && this->rotation>-180)
			this->rotation-=5;
		else
			this->position.x+=-this->speed;
	}

}

bounding_box_t Rocket::bounding_box() {
    float x = this->position.x;
	float y;
	if(this->rotation>-180)
		y = this->position.y-radius;
	else
		y = this->position.y+radius;
    float w = 1.875;
	float h = .75;
    bounding_box_t bbox = { x,y,w,h };
    return bbox;
}

