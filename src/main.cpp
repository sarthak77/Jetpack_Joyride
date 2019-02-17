//for sleep
#include <thread>
#include <chrono>

//main
#include "main.h"
#include "stdlib.h"

//other files
#include "timer.h"
#include "ball.h"
#include "dragon.h"
#include "projectile.h"
#include "baloon.h"
#include "dragonball.h"
#include "coins.h"
#include "magnet.h"
#include "ring.h"
#include "rocket.h"
#include "firebeam.h"
#include "fireline.h"
#include "background.h"

#define pi 3.14159265358979323846264338327950288

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
 * Customizable functions *
 **************************/


//declaring
Background background;
Ball ball1;
Dragon drg;
vector<Projectile> vector_p;
vector<Baloon> vector_bal;
vector<Dragonball> vector_dragonball;
vector<Coins> vector_c;
vector<Magnet> vector_mag;
vector<Ring> vector_ring;
vector<Rocket> vector_rocket;
vector<Firebeam> vector_fb;
vector<Fireline> vector_fl;

//camera properties
float screen_zoom = .5, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float cameye=0;
float camincrement=.05;

//firebeem
vector<float> fbcor;//points at which it will come
vector<bool> fbgenerate;//generate beam
vector<int> gentime;//flag for timer 


//rockets
Timer rock(4);
bool rocktime=false;
vector<bool>rspawn;

//magnets
int magno=0;
bool mflag=false;

//baloon
vector<bool> boon;
vector<bool> spawn;
float balspeed=10;
float balg=-8;
float balangle=pi/5;
int balno=-1;
bool bpress=false;
int maxbal=20;
Timer bt(3);

//dragon&ball
vector<bool> dspawn;
int dlife=10;
int maxdbal=20;
Timer dbt(5);
int dballno=0;

//coins
float xtr=1;
float ytr=.5;

//screen
float st;
float sb;
float sl;
float sr;

//timers
float fps=60;
Timer t60(1/fps);
Timer t30(1/120);

//score
int score=0;
Timer scoretimer(1);

//projectile
bool ptrigger=false;
int pcount=0;
int pcount2=800;

//ring
bool ringpath=false;
int ringcount=5;//saved by 5 enemies

//coins
bool speedup=false;
bool attract=false;
//bool attract=true;

//other
bool jetpack=false;
int level;
bool die=true;


/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
	// clear the color and depth in the frame buffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use the loaded shader program
	// Don't change unless you know what you are doing
	glUseProgram (programID);

	// Eye - Location of camera. Don't change unless you are sure!!
	//glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
	glm::vec3 eye (cameye,0,120);

	// Target - Where is the camera looking at.  Don't change unless you are sure!!
	glm::vec3 target (cameye, 0, 0);

	// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
	glm::vec3 up (0, 1, 0);

	// Compute Camera matrix (view)
	Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
	// Don't change unless you are sure!!
	//Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

	// Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
	// Don't change unless you are sure!!
	glm::mat4 VP = Matrices.projection * Matrices.view;

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	// Don't change unless you are sure!!
	glm::mat4 MVP;  // MVP = Projection * View * Model

	// Scene render

	//player
	ball1.draw(VP);
	if(jetpack)
		ball1.draw2(VP);

	//dragon
	drg.draw(VP);

	//baloons
	if(bpress && boon[balno])
	{
		if(spawn[balno])
		{
			vector_bal[balno].draw(VP,ball1.position.x,ball1.position.y);
			spawn[balno]=false;
		}
		else
		{
			vector_bal[balno].draw(VP,vector_bal[balno].position.x,vector_bal[balno].position.y);
		}
	}


	//dragonball
	if(ball1.position.x>570)
	{
		if(dspawn[dballno])
		{
			vector_dragonball[dballno].draw(VP,drg.position.x,drg.position.y);
			dspawn[dballno]=false;
		}
		else
		{
			vector_dragonball[dballno].draw(VP,vector_dragonball[dballno].position.x,vector_dragonball[dballno].position.y);
		}
	}
	if(dbt.processTick())
		dballno++;


	//firebeams
	for(int i=0;i<vector_fb.size();i++)
	{
		vector_fb[i].draw(VP);
		if(fbgenerate[i])
			vector_fb[i].draw2(VP);
	}

	//firelines
	for(int i=0;i<vector_fl.size();i++)
	{
		vector_fl[i].draw(VP);

	}

	//rings
	for(int i=0;i<vector_ring.size();i++)
	{
		vector_ring[i].draw(VP);

	}

	//rockets
	for(int i=0;i<vector_rocket.size();i++)
	{
		vector_rocket[i].draw(VP);

	}


	//coins
	for(int i=0;i<vector_c.size();i++)
	{
		vector_c[i].draw(VP);
	}


	//projectiles
	for(int i=0;i<vector_p.size();i++)
	{
		if(vector_p[i].position.x<cameye)
		{
			vector_p[i].draw(VP);
		}

	}

	//magnets
	for(int i=0;i<vector_mag.size();i++)
	{
		vector_mag[i].draw(VP);
	}

	background.draw(VP);
}

void tick_input(GLFWwindow *window) {
	int space = glfwGetKey(window, GLFW_KEY_SPACE);
	int b = glfwGetKey(window, GLFW_KEY_B);
	int right = glfwGetKey(window, GLFW_KEY_RIGHT);
	int left = glfwGetKey(window, GLFW_KEY_LEFT);

	if (space) {
		ball1.tick(1,cameye);
		jetpack=true;

	}
	else
		jetpack=false;

	if(right && !ptrigger && !mflag){
		ball1.tick(2,cameye);

	}
	if(left && !ptrigger && !mflag){
		ball1.tick(3,cameye);
	}

	if(b && bt.processTick()){
		bpress=true;
		if(balno<maxbal-1)
		{
			balno++;
			boon[balno]=true;
			spawn[balno]=true;
		}
	}
}

void tick_elements() {

	//for final battle
	if(ball1.position.x>590)
	{
		camincrement=0;
		drg.tick(0,0);
	}
	if(ball1.position.x>550)
	{
		screen_zoom=.4;
		reset_screen();
	}


	//dragonball
	if(ball1.position.x>570)
	{
		for(int i=0;i<=dballno;i++)
			vector_dragonball[dballno].tick(drg.position.x-ball1.position.x,drg.position.y-ball1.position.y);
	}


	//player
	ball1.tick(0,cameye);
	if(ringpath)
	{
		ball1.rp(ringpath,ringcount);
	}


	//water ballons
	if(bpress && boon[balno] && !spawn[balno])
		vector_bal[balno].tick(0);


	//firelines
	for(int i=0;i<vector_fl.size();i++)
		vector_fl[i].tick(0);


	//magnets
	if(vector_mag[magno].position.x<sr+cameye && vector_mag[magno].position.x>sl+cameye)
	{
		float x=ball1.position.x-vector_mag[magno].position.x;
		float y=ball1.position.y-vector_mag[magno].position.y;
		float mag=x*x+y*y;
		mag=sqrt(mag);
		x=x/mag;
		y=y/mag;
		x=-x*10;
		y=-y*10;

		ball1.velocity=glm::vec3(x,y,0);

		vector_mag[magno].tick(1);
		mflag=true;
	}
	else if(mflag)
	{
		magno++;
		ball1.acc = glm::vec3(0, -9, 0);//original
		ball1.velocity.x=.06;//original
		mflag=false;
	}


	//projectiles
	for(int i=0;i<vector_p.size();i++)
	{
		if(vector_p[i].position.x<cameye)
			vector_p[i].tick(1);
	}


	//rocket
	for(int i=0;i<vector_rocket.size();i++)
	{
		if(vector_rocket[i].position.x>sl+cameye && vector_rocket[i].position.x<sr+cameye)
		{
			vector_rocket[i].tick(1);
			rspawn[i]=false;
		}
		else if(!rspawn[i])
		{
			auto it=vector_rocket.begin();
			vector_rocket.erase(it+i);
			auto it2=rspawn.begin();
			rspawn.erase(it2+i);

		}
	}


	//coins
	for(int i=0;i<vector_c.size();i++)
	{
		vector_c[i].tick(1);
	}


	//screen
	cameye+=camincrement;


	//when player on screen
	//fire beam and powerups
	if(ball1.position.x-sl-cameye>1/screen_zoom && sr+cameye-ball1.position.x>1/screen_zoom)
	{
		//projectile
		//speedup
		if(speedup)
		{
			pcount=400;
			camincrement=4*camincrement;
			die=false;
			ptrigger=true;
			speedup=false;
		}
		if(ptrigger)//trigger timer for power to last for 10s
		{
			ball1.position.x=cameye;
			pcount--;
			if(pcount==0)
			{
				die=true;
				camincrement=camincrement/4;
				ptrigger=false;
			}
		}

		//attract
		if(attract)
		{
			die=false;
			pcount2--;
			if(pcount2==0)
			{
				die=true;
				pcount2=800;
				attract=false;
			}
			for(int i=0;i<vector_c.size();i++)
			{
				if(vector_c[i].position.x>sl+cameye && vector_c[i].position.x<sr+cameye)
				{
					float x=ball1.position.x-vector_c[i].position.x;
					float y=ball1.position.y-vector_c[i].position.y;
					float mag=x*x+y*y;
					mag=sqrt(mag);
					x=x/mag;
					y=y/mag;
					x=x*10;
					y=y*10;
					vector_c[i].velocity=glm::vec3(x,y,0);
				}
			}
		}
		else
		{
			for(int i=0;i<vector_c.size();i++)
			{
				vector_c[i].velocity=glm::vec3(0,0,0);
			}

		}


		//laser
		for(int i=0;i<vector_fb.size();i++)
		{

			if(fbcor[i]+vector_fb[i].dis+2<sr+cameye)
			{	
				vector_fb[i].tick(camincrement);//moves with camera

				//set position when will beam generate
				if(gentime[i]==0)
					gentime[i]=sr+cameye;

				//check for above position
				if(sr+cameye-gentime[i]>5)
					fbgenerate[i]=true;

				//position when will it disappear
				if(sr+cameye-gentime[i]>20)
					vector_fb[i].position.y=100;
			}
		}
	}

	//panning
	if(ball1.position.x-sl-cameye<1)
		ball1.position.x+=camincrement;

	if(ball1.position.x-sl-cameye<0)
		ball1.position.x=sl+cameye+.6;

	if(sr+cameye-ball1.position.x<0)
		ball1.position.x=sr+cameye-.6;

}
void collide(){

	//laser
	for(int i=0;i<vector_fb.size();i++)
	{
		if(detect_collision(ball1.bounding_box(),vector_fb[i].bounding_box()))
		{	
			if(vector_fb[i].position.y<50 && die)
			{
				cout << ":-((\n";
				cout << "BETTER LUCK NEXT TIME\n";
				quit(window);
			}
		}
	}

	//coins
	for(int i=0;i<vector_c.size();i++)
	{
		if(detect_collision(ball1.bounding_box(),vector_c[i].bounding_box()))
		{
			if(vector_c[i].colorid==1)//gold
				score+=15;
			if(vector_c[i].colorid==2)//bronze
				score+=10;
			if(vector_c[i].colorid==0)
			{
				Baloon bal;
				bal=Baloon(0,0,balspeed,balangle,balg);
				vector_bal.push_back(bal);
				boon.push_back(false);
				spawn.push_back(false);
				maxbal++;
			}
			auto it=vector_c.begin();
			vector_c.erase(it+i);
		}
	}

	//rocket
	for(int i=0;i<vector_rocket.size();i++)
	{
		if(detect_collision(ball1.bounding_box(),vector_rocket[i].bounding_box()))
		{
			if(scoretimer.processTick() && die)
			{
				cout << ":-((\n";
				cout << "BETTER LUCK NEXT TIME\n";
				quit(window);
			}
		}
	}

	//ring
	for(int i=0;i<vector_ring.size();i++)
	{
		if(detect_collision(ball1.bounding_box(),vector_ring[i].bounding_box()))
		{
			score+=50;
			ringpath=true;
			die=false;
			std::this_thread::sleep_for (std::chrono::seconds(1));
			auto it=vector_ring.begin();
			vector_ring.erase(it+i);
		}
	}

	//projectile
	for(int i=0;i<vector_p.size();i++)
	{
		if(detect_collision(ball1.bounding_box(),vector_p[i].bounding_box()))
		{	
			score+=150;
			if(vector_p[i].cid==0)//green for speedup
				speedup=true;
			if(vector_p[i].cid==1)//blue for attract
				attract=true;
			auto it=vector_p.begin();
			vector_p.erase(it+i);
		}
	}

	//fireline
	for(int i=0;i<vector_fl.size();i++)
	{

		if(detect_collision(ball1.bounding_box(),vector_fl[i].bounding_box()))
		{
			if(scoretimer.processTick())
			{
				score-=50;
				if(ringpath && ringcount>0)
				{
					score+=50;
					ringcount--;
					if(ringcount==0)
					{
						ringpath=false;
						die=true;
					}
				}
			}

		}

		//baloon
		if(detect_collision(vector_fl[i].bounding_box(),vector_bal[balno].bounding_box()))
		{
			//if(scoretimer.processTick())
			score+=25;
			auto it=vector_fl.begin();
			vector_fl.erase(it+i);
		}

	}
	//dragon&&baloon
	if(detect_collision(drg.bounding_box(),vector_bal[balno].bounding_box()))
	{
		dlife--;
		score+=100;
		auto it=vector_bal.begin();
		vector_bal.erase(it+balno);
		if(dlife==0)
		{
			drg.position.y=200;
			system("clear");
			cout << "YOU WON\n";
			cout << "FINAL_SCORE::" << score << "\n";
			quit(window);
		}
	}

	//dragonball and player
	if(detect_collision(ball1.bounding_box(),vector_dragonball[dballno].bounding_box()) && die)
	{
		cout << ":-((\n";
		cout << "BETTER LUCK NEXT TIME\n";
		quit(window);
	}

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {

	/* Objects should be created before any other gl function and shaders */
	// Create the models

	ball1       = Ball(0, -3, COLOR_RED,0);
	drg       = Dragon(600, 0, COLOR_RED,0);
	background=Background(0,0,COLOR_DARKGREEN);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

	reshapeWindow (window, width, height);

	//Background color of the scene
	glClearColor (COLOR_BLACK.r / 256.0, COLOR_BLACK.g / 256.0, COLOR_BLACK.b / 256.0, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

	cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
	cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
	cout << "VERSION: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

}


int main(int argc, char **argv) {

	system("clear");
	//////////////////////////////////////////////////////////////////////////////////
	cout << "             ---------------------------------\n";
	cout << "            |          STARTUP GUIDE          |\n";
	cout << "            |CONTROLS->>                      |\n";
	cout << "            |LEFT::LEFT ARROW KEY             |\n";
	cout << "            |RIGHT::RIGHTT ARROW KEY          |\n";
	cout << "            |JUMP::SPACE KEY                  |\n";
	cout << "            |BALOON::B KEY                    |\n";
	cout << "            |PAUSE::MOUSE CLICK               |\n";
	cout << "            |ZOOMIN/OUT::MOUSE SCROLL         |\n";
	cout << "             ---------------------------------\n";

	cout << " ------------------------------------------------------------\n";
	cout << "|                          GAMEPLAY                          |\n";
	cout << "|Player dies when in contact with rocket and lasers          |\n";
	cout << "|Can throw water baloons to extinguish firebeams             |\n";
	cout << "|Points deducted when in contact with firebeams              |\n";
	cout << "|Blue coins increase no of water baloons                     |\n";
	cout << "|Gold and bronze coins increase the score                    |\n";
	cout << "|Green projectile increases speed                            |\n";
	cout << "|Blue projectile attracts coins                              |\n";
	cout << "|Magnet attracts the player                                  |\n";
	cout << "|Circular ring protects player for some time from firebeams  |\n";
	cout << "|Level increases if distance>400                             |\n";
	cout << "|Shoot at dragon's head to kill it                           |\n";
	cout << " ------------------------------------------------------------\n";
	//////////////////////////////////////////////////////////////////////////////////

	cout << "SELECT LEVEL:: 1 OR 2\n";
	cin >> level;
	if(level==2)
		screen_center_x=390;

	cout << "Game starting in 3s\n\n";
	std::this_thread::sleep_for (std::chrono::seconds(3));
	system("clear");

	srand(time(0));
	int width  = 1000;
	int height = 800;
	int count=0;

	window = initGLFW(width, height);

	initGL (window, width, height);


	//50 firebeams from 20-400
	float flxtr=30;
	for(int i=0;i<60;i++)
	{
		Fireline fl;
		fl=Fireline(flxtr,rand()%5-2,COLOR_DARKGREEN);
		vector_fl.push_back(fl);
		vector_fl[i].rotation=rand()%(180)-90;
		flxtr+=rand()%10+5;
	}

	//lasers
	float laserx=50;
	for(int i=0;i<8;i++)
	{
		fbcor.push_back(laserx);//points at which it will come
		fbgenerate.push_back(false);//generate beam
		gentime.push_back(0);//flag for timer 		

		Firebeam fb;

		if(laserx<400)
			fb =Firebeam(fbcor[i],1,0);
		else
			fb =Firebeam(fbcor[i],1,1);
		vector_fb.push_back(fb);

		if(laserx<400)
			laserx+=70;
		else
			laserx+=40;

	}

	//50 baloons
	for(int i=0;i<maxbal;i++)
	{
		Baloon bal;
		bal=Baloon(0,0,balspeed,balangle,balg);
		vector_bal.push_back(bal);
		boon.push_back(false);
		spawn.push_back(false);
	}

	//dragonball
	for(int i=0;i<maxdbal;i++)
	{
		Dragonball dbal;
		dbal=Dragonball(620,0);
		vector_dragonball.push_back(dbal);
		dspawn.push_back(true);
	}

	//rockets
	float rocketxtr=10;
	for(int i=0;i<15;i++)
	{
		Rocket rocket;
		rocket=Rocket(rocketxtr,0,-.05,2);//x,y,speed,radius
		vector_rocket.push_back(rocket);
		rspawn.push_back(true);
		rocketxtr+=70;
		if(rocketxtr>450)
			rocketxtr+=20;
	}

	//projectiles
	float projxtr=40; 
	int procid=rand()%2;
	for(int i=0;i<5;i++)
	{
		if(procid==0)
			procid=1;
		else
			procid=0;
		color_t color;

		if(procid==0)
			color=COLOR_GREEN;
		else
			color=COLOR_BLUE;

		Projectile p1;
		p1= Projectile(projxtr, -1, 5, pi/6,-1,color,procid);//x,y,speed,angle,g,color,colorid
		vector_p.push_back(p1);
		projxtr+=rand()%50+50;
	}

	//ring
	float ringxtr=10; 
	for(int i=0;i<5;i++)
	{
		Ring r1;
		r1    =Ring(ringxtr,1,COLOR_DARKGREEN);
		vector_ring.push_back(r1);
		ringxtr+=rand()%100+50;
	}

	//magnets
	float magx=30;
	for(int i=0;i<6;i++)
	{
		Magnet mag;
		mag=Magnet(magx,3,COLOR_RED);
		vector_mag.push_back(mag);
		magx+=100;
	}

	//coins
	float xpos=0;
	float xpos2=0;
	float ypos=0;
	color_t color;
	int colorid=1;

	for(int k=0;k<20;k++)
	{
		for(int j=0;j<3;j++)
		{
			for(int i=0;i<10;i++)
			{
				if(rand()%3==0)
				{
					color=COLOR_CLAN;
					colorid=0;
				}
				if(rand()%3==1)
				{
					color=COLOR_GOLDEN;
					colorid=1;
				}
				if(rand()%3==2)
				{
					color=COLOR_BRONZE;
					colorid=2;
				}

				Coins coin;
				coin= Coins(xpos+xpos2, ypos, color,colorid);
				vector_c.push_back(coin);
				xpos+=xtr;
			}
			ypos=rand()%(6)-2;
			xpos=0;
		}
		xpos2+=rand()%(20)+15;
	}

	/* Draw in loop */
	while (!glfwWindowShouldClose(window)) {
		// Process timers

		system("clear");
		cout << "screen zoom->>" << screen_zoom << "\n";
		cout << "score->>" << score << "\n"; 
		cout << "distance->>" << cameye << "\n"; 
		cout << "baloon->>" << maxbal-balno-1 << "\n"; 
		if(cameye>=400)
			cout << "level->>" << level << "\n";
		else
			cout << "level->>" << level << "\n";
		if(ball1.position.x>590)
			cout << "dlife->>" << dlife << "\n";


		if (t60.processTick()) {


			// 60 fps
			// OpenGL Draw commands
			draw();
			// Swap Frame Buffer in double buffering
			glfwSwapBuffers(window);

			tick_elements();
			collide();
			tick_input(window);
		}

		// Poll for Keyboard and mouse events
		glfwPollEvents();
	}

	quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
	return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
		(abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
	st= screen_center_y + 4 / screen_zoom;
	sb= screen_center_y - 4 / screen_zoom;
	sl= screen_center_x - 4 / screen_zoom;
	sr= screen_center_x + 4 / screen_zoom;
	Matrices.projection = glm::ortho(sl, sr, sb, st, 0.1f, 500.0f);
}
