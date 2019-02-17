#include "fireline.h"
#include "main.h"

#define pi 3.14159265358979323846264338327950288

Fireline::Fireline(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed=0.01;
    speedup = 0.1;
    speeddown = 0.025;
    dis=2;
    

    int n=100;//n triangles
	float r=.5 ;
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

    int i;
	for(i=1;i<n;i++)
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
    this->object1 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, COLOR_FIRE, GL_FILL);

	r=r/2;
GLfloat b_vertex_buffer_data[9*n];

	//1st triangle
	b_vertex_buffer_data[0]=0;
	b_vertex_buffer_data[1]=0;
	b_vertex_buffer_data[2]=0;
	
	b_vertex_buffer_data[3]=r;
	b_vertex_buffer_data[4]=0;
	b_vertex_buffer_data[5]=0;
	
	b_vertex_buffer_data[6]=r*cos(theta);
	b_vertex_buffer_data[7]=r*sin(theta);
	b_vertex_buffer_data[8]=0;

	prev[2];
	prev[0]=b_vertex_buffer_data[6];
	prev[1]=b_vertex_buffer_data[7];

	for(i=1;i<n;i++)
	{
		b_vertex_buffer_data[9*i]=0;
		b_vertex_buffer_data[9*i+1]=0;
		b_vertex_buffer_data[9*i+2]=0;
		
		b_vertex_buffer_data[9*i+3]=prev[0];
		b_vertex_buffer_data[9*i+4]=prev[1];
		b_vertex_buffer_data[9*i+5]=0;
		
		b_vertex_buffer_data[9*i+6]=prev[0]*cos(theta)-prev[1]*sin(theta);
		b_vertex_buffer_data[9*i+7]=prev[0]*sin(theta)+prev[1]*cos(theta);
		b_vertex_buffer_data[9*i+8]=0;

		prev[0]=b_vertex_buffer_data[9*i+6];
		prev[1]=b_vertex_buffer_data[9*i+7];
        
	}
    this->object4 = create3DObject(GL_TRIANGLES, n*3, b_vertex_buffer_data, COLOR_YELLOW, GL_FILL);

	
GLfloat c_vertex_buffer_data[9*n];

    //1st triangle
	c_vertex_buffer_data[0]=0+dis;
	c_vertex_buffer_data[1]=0;
	c_vertex_buffer_data[2]=0;
	
	c_vertex_buffer_data[3]=r+dis;
	c_vertex_buffer_data[4]=0;
	c_vertex_buffer_data[5]=0;
	
	c_vertex_buffer_data[6]=r*cos(theta)+dis;
	c_vertex_buffer_data[7]=r*sin(theta);
	c_vertex_buffer_data[8]=0;

	
	prev[0]=c_vertex_buffer_data[6]-dis;
	prev[1]=c_vertex_buffer_data[7];

    i;
	for(i=1;i<n;i++)
	{
		c_vertex_buffer_data[9*i]=0+dis;
		c_vertex_buffer_data[9*i+1]=0;
		c_vertex_buffer_data[9*i+2]=0;
		
		c_vertex_buffer_data[9*i+3]=prev[0]+dis;
		c_vertex_buffer_data[9*i+4]=prev[1];
		c_vertex_buffer_data[9*i+5]=0;
		
		c_vertex_buffer_data[9*i+6]=prev[0]*cos(theta)-prev[1]*sin(theta)+dis;
		c_vertex_buffer_data[9*i+7]=prev[0]*sin(theta)+prev[1]*cos(theta);
		c_vertex_buffer_data[9*i+8]=0;

		prev[0]=c_vertex_buffer_data[9*i+6]-dis;
		prev[1]=c_vertex_buffer_data[9*i+7];
        
	}
    this->object5 = create3DObject(GL_TRIANGLES, n*3, c_vertex_buffer_data, COLOR_YELLOW, GL_FILL);





r=2*r;
	GLfloat vertex_buffer_data[9*n];

    //1st triangle
	vertex_buffer_data[0]=0+dis;
	vertex_buffer_data[1]=0;
	vertex_buffer_data[2]=0;
	
	vertex_buffer_data[3]=r+dis;
	vertex_buffer_data[4]=0;
	vertex_buffer_data[5]=0;
	
	vertex_buffer_data[6]=r*cos(theta)+dis;
	vertex_buffer_data[7]=r*sin(theta);
	vertex_buffer_data[8]=0;

	
	prev[0]=vertex_buffer_data[6]-dis;
	prev[1]=vertex_buffer_data[7];

    i;
	for(i=1;i<n;i++)
	{
		vertex_buffer_data[9*i]=0+dis;
		vertex_buffer_data[9*i+1]=0;
		vertex_buffer_data[9*i+2]=0;
		
		vertex_buffer_data[9*i+3]=prev[0]+dis;
		vertex_buffer_data[9*i+4]=prev[1];
		vertex_buffer_data[9*i+5]=0;
		
		vertex_buffer_data[9*i+6]=prev[0]*cos(theta)-prev[1]*sin(theta)+dis;
		vertex_buffer_data[9*i+7]=prev[0]*sin(theta)+prev[1]*cos(theta);
		vertex_buffer_data[9*i+8]=0;

		prev[0]=vertex_buffer_data[9*i+6]-dis;
		prev[1]=vertex_buffer_data[9*i+7];
        
	}
    this->object2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_FIRE, GL_FILL);


    r=.3;
	GLfloat a_vertex_buffer_data[]={

        0,-r/2,0,
        0+dis,-r/2,0,
        0,r/2,0,
        0,r/2,0,
        0+dis,-r/2,0,
        0+dis,r/2,0
    };

    this->object3 = create3DObject(GL_TRIANGLES, 2*3, a_vertex_buffer_data, COLOR_FIRE, GL_FILL);


}

void Fireline::draw(glm::mat4 VP) {
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
}

void Fireline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

//x is forward coming out of screen
void Fireline::tick(int up) {
    //this->rotation += .2;
    //this->position.x += speed;
    
}

bounding_box_t Fireline::bounding_box() {
    float x = (this->position.x+(this->dis)/2);
	float y = (this->position.y+0);
    float w = (this->dis)/2+.5;
	float h = .5;
    bounding_box_t bbox = { x,y,2*w,2*h };
    return bbox;
}

