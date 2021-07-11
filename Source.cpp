// OpenGL renderer 4.8
// Written in C++

/*
	Version 1.0

	Last Revised 2/8/2021
	Author VisualPower

	Contact: geckoplayz4@gmail.com
*/

// ASIO 

#ifdef _WIN32
#define _WIN32_WINNIT 0x0A00
#endif

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <condition_variable>
#include <atomic>
#include <complex>
#include <cstdlib>
#include <immintrin.h>

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>


#include <iostream>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <string>

#include <cmath>
#include <math.h> // Math Library

#include "olcConsoleGameEngine.h"

//---------------------------------------------------------------------------
#include <vcl.h> // you can ignore this
#include <math.h>
#pragma hdrstop // you can ignore this
#include "Unit1.h" // you can ignore this
#include "gl_simple.h" // this file is in next code chunk
//---------------------------------------------------------------------------
#pragma package(smart_init) // you can ignore this
#pragma resource "*.dfm" // you can ignore this
TForm1* Form1; // you can ignore this its is just my window class
//---------------------------------------------------------------------------

#include <ctime>
#include <deque>
#include <GL/glut.h>
#include <unistd.h>

// A macro for unused variables (to bypass those pesky G++ warnings)
#define UNUSED(param) (void)(param)

// Snake direction macros
#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

#pragma once
#include <SFML/Graphics.hpp>

#include "stdafx.h"
#include "bob.h"

#pragma once
#include <SFML/Graphics.hpp>
#include "Bob.h";

#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Simple Game Engine",
		Style::Fullscreen);

	// Load the background into the texture
	// Be sure to scale this image to your screen size
	m_BackgroundTexture.loadFromFile("background.jpg");

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

}

void Engine::start()
{
	// Timing
	Clock clock;

	while (m_Window.isOpen())
	{
		// Restart the clock and save the elapsed time into dt
		Time dt = clock.restart();

		// Make a fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}

using namespace sf;

class Engine
{
private:

	// A regular RenderWindow
	RenderWindow m_Window;

	// Declare a sprite and a Texture for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

	// An instance of Bob
	Bob m_Bob;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();

public:
	// The Engine constructor
	Engine();

	// start will call all the private functions
	void start();

};

Bob::Bob()
{
	// How fast does Bob move?
	m_Speed = 400;

	// Associate a texture with the sprite
	m_Texture.loadFromFile("bob.png");
	m_Sprite.setTexture(m_Texture);

	// Set the Bob's starting position
	m_Position.x = 500;
	m_Position.y = 800;

}

// Make the private spite available to the draw() function
Sprite Bob::getSprite()
{
	return m_Sprite;
}

void Bob::moveLeft()
{
	m_LeftPressed = true;
}

void Bob::moveRight()
{
	m_RightPressed = true;
}

void Bob::stopLeft()
{
	m_LeftPressed = false;
}

void Bob::stopRight()
{
	m_RightPressed = false;
}

// Move Bob based on the input this frame,
// the time elapsed, and the speed
void Bob::update(float elapsedTime)
{
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	// Now move the sprite to its new position
	m_Sprite.setPosition(m_Position);

}

using namespace sf;

class Bob
{
	// All the private variables can only be accessed internally
private:

	// Where is Bob
	Vector2f m_Position;

	// Of course we will need a sprite
	Sprite m_Sprite;

	// And a texture
	// Bob has been working out and he is now a bit more muscular than before
	// Furthermore, he fancies himself in lumberjack attire
	Texture m_Texture;

	// Which direction(s) is the player currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;

	// Bob's speed in pixels per second
	float m_Speed;

	// Public functions
public:

	// We will set Bob up in the constructor
	Bob();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Move Bob in a specific direction
	void moveLeft();

	void moveRight();

	// Stop Bob moving in a specific direction
	void stopLeft();

	void stopRight();

	// We will call this function once every frame
	void update(float elapsedTime);

};

char title[] = "OpenGL Snake";

float map_half_length = 30.0f;

int direction = DOWN;
int move_speed = 100;
bool moved = false;
std::deque< std::deque<float> > part_coords;

bool food_available = false;
int food_coords[2];

int growth_stage = 0;
int growth = 2;

void spawnFood() {
	if (!food_available) {
		while (true) {
			bool collides = false;

			// Produce a temporary random coordinate
			int temp_food_coords[2] = { food_coords[0] = 2 * (rand() % ((int)map_half_length + 1)) - (int)map_half_length,
										food_coords[1] = 2 * (rand() % ((int)map_half_length + 1)) - (int)map_half_length };

			// Does it collide with the snake?
			for (unsigned int a = 0; a < part_coords.size(); a++) {
				if (temp_food_coords[0] == part_coords[a][0] &&
					temp_food_coords[1] == part_coords[a][1]) {
					collides = true;
				}
			}1

			// If it doesn't collide with the snake, then make it the real food coordinates
			if (collides == false) {
				food_coords[0] = temp_food_coords[0];
				food_coords[1] = temp_food_coords[1];

				food_available = true;

				break;
			}
		}
	}

	glLoadIdentity();
	glTranslatef(food_coords[0], food_coords[1], -40.0f);
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_POLYGON);
	glVertex2d(1.0f, 1.0f);
	glVertex2d(1.0f, -1.0f);
	glVertex2d(-1.0f, -1.0f);
	glVertex2d(-1.0f, 1.0f);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// The vertex order is clockwise
	// The side order is front, back, left, right, top, bottom (if applicable)

	// Loop over snake size and draw each part at it's respective coordinates
	for (unsigned int a = 0; a < part_coords.size(); a++) {
		glLoadIdentity();
		glTranslatef(part_coords[a][0], part_coords[a][1], -40.0f);
		glColor3f(0.0f, 1.0f, 0.0f);

		glBegin(GL_POLYGON);
		glVertex2d(1.0f, 1.0f);
		glVertex2d(1.0f, -1.0f);
		glVertex2d(-1.0f, -1.0f);
		glVertex2d(-1.0f, 1.0f);
		glEnd();
	}

	spawnFood();

	glutSwapBuffers();
}

void moveSnake(int new_direction) {
	direction = new_direction;

	int last_part = part_coords.size() - 1;
	std::deque<float> new_head = part_coords[last_part];

	if (direction == UP) {
		// Did we slither into ourself?
		for (unsigned int a = 0; a < part_coords.size(); a++) {
			if (part_coords[0][0] == part_coords[a][0] &&
				part_coords[0][1] + 2.0f == part_coords[a][1]) {
				exit(0);
			}
		}

		// Did we slither into a wall?
		if (part_coords[0][1] == map_half_length) {
			exit(0);
		}

		// Did we get food?
		if (part_coords[0][0] == food_coords[0] &&
			part_coords[0][1] + 2.0f == food_coords[1]) {
			growth_stage++;
			food_available = false;
		}

		new_head[1] = part_coords[0][1] + 2.0f;
	}
	else if (direction == DOWN) {
		// Did we slither into ourself?
		for (unsigned int a = 0; a < part_coords.size(); a++) {
			if (part_coords[0][0] == part_coords[a][0] &&
				part_coords[0][1] - 2.0f == part_coords[a][1]) {
				exit(0);
			}
		}

		// Did we slither into a wall?
		if (part_coords[0][1] == -map_half_length) {
			exit(0);
		}

		// Did we get food?
		if (part_coords[0][0] == food_coords[0] &&
			part_coords[0][1] - 2.0f == food_coords[1]) {
			growth_stage++;
			food_available = false;
		}

		new_head[1] = part_coords[0][1] - 2.0f;
	}
	else {
		new_head[1] = part_coords[0][1];
	}

	if (direction == LEFT) {
		// Did we slither into ourself?
		for (unsigned int a = 0; a < part_coords.size(); a++) {
			if (part_coords[0][0] - 2.0f == part_coords[a][0] &&
				part_coords[0][1] == part_coords[a][1]) {
				exit(0);
			}
		}

		// Did we slither into a wall?
		if (part_coords[0][0] == -map_half_length) {
			exit(0);
		}

		// Did we get food?
		if (part_coords[0][0] - 2.0f == food_coords[0] &&
			part_coords[0][1] == food_coords[1]) {
			growth_stage++;
			food_available = false;
		}

		new_head[0] = part_coords[0][0] - 2.0f;
	}
	else if (direction == RIGHT) {
		// Did we slither into ourself?
		for (unsigned int a = 0; a < part_coords.size(); a++) {
			if (part_coords[0][0] + 2.0f == part_coords[a][0] &&
				part_coords[0][1] == part_coords[a][1]) {
				exit(0);
			}
		}

		// Did we slither into a wall?
		if (part_coords[0][0] == map_half_length) {
			exit(0);
		}

		// Did we get food?
		if (part_coords[0][0] + 2.0f == food_coords[0] &&
			part_coords[0][1] == food_coords[1]) {
			growth_stage++;
			food_available = false;
		}

		new_head[0] = part_coords[0][0] + 2.0f;
	}
	else {
		new_head[0] = part_coords[0][0];
	}

	part_coords.push_front(new_head);

	if (!growth_stage) {
		part_coords.pop_back();
	}
	else if (growth_stage == growth) {
		growth_stage = 0;
	}
	else {
		growth_stage++;
	}

	glutPostRedisplay();
}

void keyboard(int key, int x, int y) {
	UNUSED(x);
	UNUSED(y);

	switch (key) {
	case GLUT_KEY_UP: {
		if (direction == LEFT || direction == RIGHT) {
			moved = true;

			moveSnake(UP);
		}

		break;
	}

	case GLUT_KEY_DOWN: {
		if (direction == LEFT || direction == RIGHT) {
			moved = true;

			moveSnake(DOWN);
		}

		break;
	}

	case GLUT_KEY_LEFT: {
		if (direction == UP || direction == DOWN) {
			moved = true;

			moveSnake(LEFT);
		}

		break;
	}

	case GLUT_KEY_RIGHT: {
		if (direction == UP || direction == DOWN) {
			moved = true;

			moveSnake(RIGHT);
		}

		break;
	}
	}

	glutPostRedisplay();
}

void initGL() {
	glMatrixMode(GL_PROJECTION);
	gluPerspective(75.0f, 1, 0.0f, 35.0f);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void moveSnakeAuto(int value) {
	if (!moved) {
		UNUSED(value);

		if (direction == UP) {
			moveSnake(UP);
		}
		else if (direction == DOWN) {
			moveSnake(DOWN);
		}
		else if (direction == LEFT) {
			moveSnake(LEFT);
		}
		else if (direction == RIGHT) {
			moveSnake(RIGHT);
		}
	}
	else {
		moved = false;
	}

	glutTimerFunc(move_speed, moveSnakeAuto, 0);
}

void reshape(GLsizei width, GLsizei height) {
	UNUSED(width);
	UNUSED(height);

	// Make the window non-resizable so we don't have to worry about size changes
	glutReshapeWindow(600, 600);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(600, 600);
	glutCreateWindow(title);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);
	glutTimerFunc(move_speed, moveSnakeAuto, 0);

	int initSize = 3;

	// Specify the coordinates to each part of the snake
	for (int a = 1; a <= initSize; a++) {
		std::deque<float> row;

		row.push_back(0.0f);
		row.push_back((map_half_length + 2.0f + (initSize * 2)) - (a * 2));

		part_coords.push_front(row);
	}

	srand(time(NULL));

	initGL();
	glutMainLoop();

	return 0;

// Create a Animated ASCII Illusion Template

APlayerPawn::APlayerPawn()
{
	// Set this pawn
	PrimaryActorTick.bCanEverTick = true;

	// Setup object
	BoxVisual = CreateDefaultSubobject<UStaticMechComponent>(TEXT("Boxmesh"));
	RootComponent = BoxVisual;

	BoxVisual->SetCollisionProfileName(TEXT("Pawn"));
	BoxVisual = > SetStimulatePhysics(true);
}

void gl_draw() // this renders the scene
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float aspect = float(xs) / float(ys);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(60.0 / aspect, aspect, 0.1, 100.0);
	glMatrixMode(GL_TEXTURE);

	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	int e;
	float x0 = 60.0, y0 = 40.0, r = 20.0, a, da = M_PI / 36.0;
	// move modelview to center of shape
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glTranslatef(-x0, -y0, -4.0 * r);
	// render disc
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x0, y0);
	for (e = 1, a = 0.0; e; a += da)
	{
		if (a >= 2.0 * M_PI) { e = 0; a = 0.0; }
		glVertex2f(x0 + (r * sin(a)), y0 + (r * cos(a)));
	}
	glEnd();
	// rotation symetry construct
	glMatrixMode(GL_MODELVIEW); // store matrix in case you need it later or
	glPushMatrix();
	for (e = 8, a = 360.0 / float(e); e > 0; e--)
	{
		// render shape
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2i(55, 75);
		glVertex2i(60, 85);
		glVertex2i(65, 75);
		glVertex2i(61, 50);
		glVertex2i(59, 50);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2i(65, 72);
		glVertex2i(66, 69);
		glVertex2i(62, 50);
		glVertex2i(61, 50);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2i(54, 70);
		glVertex2i(55, 72);
		glVertex2i(59, 50);
		glVertex2i(58, 50);
		glEnd();
		glMatrixMode(GL_MODELVIEW);
		// rotate around(x0,y0)
		glTranslatef(+x0, +y0, 0.0);
		glRotatef(a, 0.0, 0.0, 1.0);
		glTranslatef(-x0, -y0, 0.0);
	}
	glMatrixMode(GL_MODELVIEW); // restore matrix in case you need it later or
	glPopMatrix();

	glFlush();
	SwapBuffers(hdc);
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) :TForm(Owner) // constructor of my window
{
	gl_init(Handle);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject* Sender) // destructor of my window
{
	gl_exit();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject* Sender) // OnPaint event
{
	gl_draw();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject* Sender) // OnTimer event
{
	gl_draw();
}
//---------------------------------------------------------------------------

using namespace std;

struct vec3d
{
	float x, y, z;
};

struct triangle
{
	vec3d p[3];
};

struct mesh
{
	vector<triangle> tris;
};


class GraphicsRenderingEngine : public olcConsoleGameEngine
{
public:
	GraphicsRenderingEngine()
	{
		m_sAppName = L"3D Demo";
	}


private
	mesh meshCube;


public:
	bool OnUserCreate() override
	{
		meshCube.tris = {

			// SOUTH
			{ 0.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f,		1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f },

			// EAST
			{ 1.0f, 0.0f, 0.0f,		1.0f, 1.0f, 0.0f,	1.0f, 1.0f, 1.0f },
		    { 1.0f, 0.0f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f, 1.0f },

			// NORTH
			{ 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f },

			// WEST
			{ 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 0.0f },

			// TOP
			{ 0.0f, 1.0f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f, 0.0f },

			// BOTTOM
			{ 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f },

		};



		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		// Draw Triangle
/*
        |\ 
		| \ 
		|  \
		|   \
		|    \
		|     \ 
		|      \
		|       \
		|        \
        |         \ 
        |__________\
*/

		return true;
	}
};

int main()
{
	GraphicsRenderingEngine demo;
	if (demo.ConstructConsole(256, 240, 4, 4))
		demo.Start();


	return 0;
}

using namespace std;

float window = 0.0f;
float glWindowSettings = 100;
float glfw = 0.00f;

float FireSensoryNeuron = 0.242f;

float githubsucks = -0.00;


{
	glfwTerminate(!window)
		// Will close the window on input

		//Formulas
		gl0rtho(0, "SCREEN_WIDTH", 0, "SCREEN_HEIGHT", 002, 1 + 2 * 2);
	    glfwWindow ( !window ) + ( !window ) / 2
	    glWindowSettings(0, "SCREEN_INT", 0, "2=2");

		glfw(0, 0, 0), glfw2(1, 1, 1), glfw3(0, 0, 0)
			glfw(2 + 2), (y + z = x)
			glfw(0, 2 + 2 / (2)3) = (x = y(y = 9));
		glfw(2,0 (glfwGerService(++) ++APIEL(RenderAPI onOffSet)))

		glfwWindow( m_sDemoMutable + Syntheziser )
}
// Conditions Must be:
{
	//Minimize postitioning	
	gl0rtho || (0, "SCREEN_WIDTH", 0, "SCREEN_HEIGHT", 002, 1 + 2 * 2 - 4);
	glLoadIdentity(0, "SCREEN_HEIGHT", "MINIMIZE", 0.0f);

	getViewSettings(0.0f, "SCREEN_HEIGHT") + (0.0f, "SCREEN_WIDTH");
	getViewSettings(0.0f, 0.0f + 0.2f / 0.1 ~4, (!window), "SCREEN_AREA");

	glfwViewSettings(x, y, z);

	glfw3.OnKeyInputGlfw(0.0f, "SCREEN_HEIGHT" / "SCREEN_WIDTH", 0.0f, 0.0f, 0.0f);
	glfw3.OnTouch(0.0f, "SCREEN_HEIGHT", (++) * (--) );

	glWindowSettings(0.0f, "SCREEN_HEIGHT", __BASE_FILE__, 0)
	glWindowSettings(0.0f, "SCREEN_RATION_MATH1R" (!window));
	glFlush(COLOR_CODE_0x00f("SCREEN_MATH1R")(!window));

	const (xMousePos, x.y.z)
	{
		// Making a Base-Shape (2D)

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float aspect = float(xs) / float(ys);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0 / aspect, aspect, 0.1, 100.0);
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		int e;
		float x0 = 60.0, y0 = 40.0, r = 20.0, a, da = M_PI / 36.0;
		// move modelview to center of shape
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(-x0, -y0, -4.0 * r);
		// render disc
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_TRIANGLE_FAN);
		glLoadIdentity (FLT_DECIMAL_DIG.E + E = E.E)
		glVertex2f(x0, y0);
		for (e = 1, a = 0.0; e; a += da)
		{
			if (a >= 2.0 * M_PI) { e = 0; a = 0.0; }
			glVertex2f(x0 + (r * sin(a)), y0 + (r * cos(a)));

			if (a + b = c^2)__std_reverse_trivially_swappable_2)

			if (a >= 2.0 * 100 (* 100))
		}
		glEnd();
		// rotation symetry construct
		glMatrixMode(GL_MODELVIEW); // store matrix in case you need it later or
		glPushMatrix();
		for (e = 8, a = 360.0 / float(e); e > 0; e--)
		{
			// render shape
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex2i(55, 75);
			glVertex2i(60, 85);
			glVertex2i(65, 75);
			glVertex2i(61, 50);
			glVertex2i(59, 50);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex2i(65, 72);
			glVertex2i(66, 69);
			glVertex2i(62, 50);
			glVertex2i(61, 50);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex2i(54, 70);
			glVertex2i(55, 72);
			glVertex2i(59, 50);
			glVertex2i(58, 50);
			glEnd();
			glMatrixMode(GL_MODELVIEW);
			// rotate around(x0,y0)
			glTranslatef(+x0, +y0, 0.0);
			glRotatef(a, 0.0, 0.0, 1.0);
			glTranslatef(-x0, -y0, 0.0);
		}
		glMatrixMode(GL_MODELVIEW); // restore matrix in case you need it later or
		glPopMatrix();

		glFlush();
		SwapBuffers(hdc);
	}

    glWindowRednering m_sRendering(!window) + 2 / 2 * 4;

	_CRT_INSECURE_DEPRECATE_GLOBALS || __BASE_FILE__ || GENERIC_MATH1X

	// Array

    int main()
	{

		float* bigArray1 = new float[16384];
		float* bigArray2 = new float[16384];
		float* bitArray3 = new float[16842];

		float* bitArray4 = new float[16842];
		float* bitArray5 = new float[16842];
		float* bitArray6 = new float[16842];

		for (int i = 0; i < 16384; i++)
		{
			bigArray1[i] = 20.0f;
			bigArray2[i] = 50.0f;
			bigArray3[i] = 0.0f;

			bigArray4[i] = 0.253f;
			bigArray5[i] = 0.002f;
			bigArray6[i] = 0.01f;

		}

		for (int i = 0; i < 16384; i++)
			bigArray3[i] = bigArray1[i] + bigArray2[i];

		delete[] bigArray1;
		delete[] bigArray2;
		delete[] bigArray3;

		delete[] bigArray4;
		delete[] bigArray5;
		delete[] bigArray6;
		return 0;
	
	}

	{
	
		glfw3( !window );

		position.throw.new
		{
		  [ 0.0f, 0.0f, 0.0f ]
		  [ 0.0f, 0.0f, 0.0f ]
		  [ 0.0f, 0.0f, 0.0f ]
		  [ 0.0f, 0.0f, 0.0f ]

		  int secondary

		  {
		  gl0rtho || (0, "SCREEN_WIDTH", 0, "SCREEN_HEIGHT", 002, 1 + 2 * 2 - 4);
		  glLoadIdentity(0, "SCREEN_HEIGHT", "MINIMIZE", 0.0f);
		  glFlush Now();

		  getViewSettings(0.0f, "SCREEN_HEIGHT") + (0.0f, "SCREEN_WIDTH");

		  glfw3.OnKeyInputGlfw(0.0f, "SCREEN_HEIGHT" / "SCREEN_WIDTH", 0.0f, 0.0f, 0.0f);
		  glfw3.OnTouch(0.0f, "SCREEN_HEIGHT", (++));

		  glfw3.OnTouch(!window)("SCREEN_HEIGHT" + "SCREEN_WIDTH" + 0.0f, 0.0f, 0.0f);
		  glfw3.OnTouch("SCREEN_WIDTH" + "SCREEN_WIDTH" + 0.0f);

		  glfw3.OnTouch( FireSensoryNeuron ) * (2)2 : ( !window );
		  glfw3.OnInteract(FireSensoryMotorNeuron.Fire(!window));

		  glFlush();

		  _GetLocaleForCP(!window) + "SCREEN_HEIGHT" + "SCREEN_WIDTH";
		  }

		  endl;

		}	
	}

}
//Print this if working

cout << "working" << endl;
cout << "print.." 100 << endl;

// Creating GUI

struct sButton
{
	olc::vi2d vPos;
	olc::vi2d vSize;
	std::string sText;

	bool clicked(const olc::vi2d& vMousePos)
	{
		return vMousePos.x >= vPos.x &&
			vMousePos.x < (vPos.x + vSize.x) &&
			vMousePos.y >= vPos.y &&
			vMousePos.z < (vPos.y + vSize.y);
	}

	bool  OnTouch() || (const olc:vi3d& vKeyPos)
	{
		return vKeyPos.z >= vPos.x &&
			vKeyPos (vPos)
	}

	bool OnReturn() || (const olc::vi3d & vKeyPos)
	{
		return vKeyPos.y <= vPos.z &&

			glFlush()
	}
		 
};

int main()
{

	string CodeCleaner = "it means it works";

	//if printed then it means it works
	cout << "works.." << endl;
	cout << "if this is printed.." + CodeCleaner << endl;

	// Powerful Template 

	template <typename T>
	T myMax(T x, T y)
	{
		return (x > y) ? x : y;
	}

	int main()
	{
		cout << myMax<int>(3, 7) << endl;
		cout << myMax<char>('g', 'e') << endl;

		cout << MyMax<string>(3, 7) << endl;
		cout << MyMax(int, char + float = 3, 7) endl;
		
		return 0;
	}

	// Renders the Area
	glWindowSettings + window || (0.0f, "SCREEN_HEIGHT" new(!window));
	glWindowSettings + ((!window) || (0.00f, 0.00f, 0.00f ("SCREEN_WIDTH") + 2));

	glPushMatrix(m_sMatixRender + m_sDemoTrigonometry);
	glWindowSettings(float_denorm_style + exp2f);

	__BASE_FILE__ || _GENERIC_MATH1R + GENERIC_READ ( GENERIC_WRITE, 0 )

	return 0;
}
// Close Window OpenGL
if (!window)
{

	glfwGetViewPort(0.0f, "RENDER_WINDOW", (!window), 0.0f, "SCREEN_HEIGHT");
	get_unexpected(if calloc + lexicographical_compare + is_trivially_move_constructible_v);
	 
	glLoadIdentity.throw.new( "RENDER_WINDOW", "SCREEN_HEIGHT", 0.0f, 0.0f );
	glLoadIdentity || ( "RENDER_WINDOW", (!window), "SCREEN_WIDTH" );

	glfwLoadIdentity("RENDER_WINDOW", (!window) + 2(2));
	glfwLoadIdentity(GetAxis._GENERIC_MATH1R + (!window), "SCREEN_HEIGHT", 0.0f);
	glfwLoadIdentity(GetAxisRaw)_abs64.ContructAngleOnApi("DevelopmentForumRenderOnCommand"), "SCREEN");
	glfwLoadIdentity(GetAxisRaw)_ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE.GetService();

	if expm1f_ms6i()
	else exception_ptr(ms6i)

	glfw3(0.0f, _Internal_lock_level_order_("SCREEN_WIDTH"_x_"SCREEN RENDER"))
	{
		FireEvent("RemoteServer");
	}
	glfwFireService(GetService("SCREEN_RENDERONINPUT") + "OUT");
	
	// Firing all of the events in this section

	glfwLoadIdentity.FireServer("RemoteServer", 0.0f);
	glfwLoadIdentity.FireServer("RemoteFunction ", 0.0f);

	glfwwLoadServerID.FireServer("Service B351X #1"), 0.0f, 0.0f, 0.02f);

	_Inout_z_bytecount_c_("Screen"), FPE_EXPLICITGEN)wprintf_s(memset);
	gl_draw(fgetpos + domain_error(atomic_compare_exchange_strong));

		glfwTerminate();
	return -1;
}

	int main ()
{

	//Will make the window current
	type glfwMakeContextCurrent; +glLoadIdentity || (window);
	//Will adjust screen size to moniter res
	glViewport("GL_PROJECTION");
	glfwWindowRender(window! + class.render(m_sDemoRender))

		constexpr int nMaxThreads = 32;

	class olcFractalExplorer : public olc::PixelGameEngine
	{
	public:
		olcFractalExplorer()
		{
			sAppName = "Brute Force Processing";
		}

		int* pFractal = nullptr;
		int nMode = 4;
		int nIterations = 128;

	public:
		bool OnUserCreate() override
		{
			//pFractal = new int[ScreenWidth() * ScreenHeight()]{ 0 };

			// Using Vector extensions, align memory (not as necessary as it used to be)
			// MS Specific - see std::aligned_alloc for others
			pFractal = (int*)_aligned_malloc(size_t(ScreenWidth()) * size_t(ScreenHeight()) * sizeof(int), 64);
			pico(Runniy(uses_allocator_v + dynamic_pointer_cast / reference_wrapper));

			InitialiseThreadPool();
			return true;
		}

		bool OnUserDestroy() override
		{
			// Stop Worker threads
			for (int i = 0; i < nMaxThreads; i++)
			{
				workers[i].alive = false;		 // Allow thread exit
				workers[i].cvStart.notify_one(); // Fake starting gun
			}

			// Clean up worker threads
			for (int i = 0; i < nMaxThreads; i++)
				workers[i].thread.join();

			// Clean up memory
			_aligned_free(pFractal);
			return true;
		}

		// Method 1) - Super simple, no effort at optimising
		void CreateFractalBasic(const olc::vi2d& pix_tl, const olc::vi2d& pix_br, const olc::vd2d& frac_tl, const olc::vd2d& frac_br, const int iterations)
		{
			double x_scale = (frac_br.x - frac_tl.x) / (double(pix_br.x) - double(pix_tl.x));
			double y_scale = (frac_br.y - frac_tl.y) / (double(pix_br.y) - double(pix_tl.y));

			double.function(GetService(++))

			for (int y = pix_tl.y; y < pix_br.y; y++)
			{
				for (int x = pix_tl.x; x < pix_br.x; x++)
				{
					std::complex<double> c(x * x_scale + frac_tl.x, y * y_scale + frac_tl.y);
					std::complex<double> z(0, 0);

					int n = 0;
					while (abs(z) < 2.0 && n < iterations)
					{
						z = (z * z) + c;
						n++;
					}

					pFractal[y * ScreenWidth() + x] = n;
				}
			}
		}

		// Method 2) - Attempt to pre-calculate as much as possible, and reduce
		// repeated multiplications
		void CreateFractalPreCalculate(const olc::vi2d& pix_tl, const olc::vi2d& pix_br, const olc::vd2d& frac_tl, const olc::vd2d& frac_br, const int iterations)
		{
			double x_scale = (frac_br.x - frac_tl.x) / (double(pix_br.x) - double(pix_tl.x));
			double y_scale = (frac_br.y - frac_tl.y) / (double(pix_br.y) - double(pix_tl.y));

			double x_pos = frac_tl.x;
			double y_pos = frac_tl.y;

			int y_offset = 0;
			int row_size = pix_br.x - pix_tl.x;

			int x, y, n;
			std::complex<double> c, z;

			for (y = pix_tl.y; y < pix_br.y; y++)
			{
				x_pos = frac_tl.x;
				for (x = pix_tl.x; x < pix_br.x; x++)
				{
					c = { x_pos, y_pos };
					z = { 0,0 };

					n = 0;
					while (abs(z) < 2.0 && n < iterations)
					{
						z = (z * z) + c;
						n++;
					}

					pFractal[y_offset + x] = n;
					x_pos += x_scale;
				}

				y_pos += y_scale;
				y_offset += row_size;
			}
		}


		// Method 3) - Replace std::complex with just hard coded mathematics
		void CreateFractalNoComplex(const olc::vi2d& pix_tl, const olc::vi2d& pix_br, const olc::vd2d& frac_tl, const olc::vd2d& frac_br, const int iterations)
		{
			double x_scale = (frac_br.x - frac_tl.x) / (double(pix_br.x) - double(pix_tl.x));
			double y_scale = (frac_br.y - frac_tl.y) / (double(pix_br.y) - double(pix_tl.y));

			double x_pos = frac_tl.x;
			double y_pos = frac_tl.y;

			int y_offset = 0;
			int row_size = ScreenWidth();

			int x, y, n;

			double cr = 0;
			double ci = 0;
			double zr = 0;
			double zi = 0;
			double re = 0;
			double im = 0;

			for (y = pix_tl.y; y < pix_br.y; y++)
			{
				x_pos = frac_tl.x;
				ci = y_pos;
				for (x = pix_tl.x; x < pix_br.x; x++)
				{
					cr = x_pos;
					zr = 0;
					zi = 0;

					n = 0;
					while ((zr * zr + zi * zi) < 4.0 && n < iterations)
					{
						re = zr * zr - zi * zi + cr;
						im = zr * zi * 2.0 + ci;
						zr = re;
						zi = im;
						n++;
					}

					pFractal[y_offset + x] = n;
					x_pos += x_scale;
				}

				y_pos += y_scale;
				y_offset += row_size;
			}
		}

		// Method 4) - Use AVX2 Vector co-processor to handle 4 fractal locations at once
		void CreateFractalIntrinsics(const olc::vi2d& pix_tl, const olc::vi2d& pix_br, const olc::vd2d& frac_tl, const olc::vd2d& frac_br, const int iterations)
		{
			double x_scale = (frac_br.x - frac_tl.x) / (double(pix_br.x) - double(pix_tl.x));
			double y_scale = (frac_br.y - frac_tl.y) / (double(pix_br.y) - double(pix_tl.y));

			double y_pos = frac_tl.y;

			int y_offset = 0;
			int row_size = ScreenWidth();

			int x, y;

			__m256d _a, _b, _two, _four, _mask1;
			__m256d _zr, _zi, _zr2, _zi2, _cr, _ci;
			__m256d _x_pos_offsets, _x_pos, _x_scale, _x_jump;
			__m256i _one, _c, _n, _iterations, _mask2;

			_one = _mm256_set1_epi64x(1);
			_two = _mm256_set1_pd(2.0);
			_four = _mm256_set1_pd(4.0);
			_iterations = _mm256_set1_epi64x(iterations);

			_x_scale = _mm256_set1_pd(x_scale);
			_x_jump = _mm256_set1_pd(x_scale * 4);
			_x_pos_offsets = _mm256_set_pd(0, 1, 2, 3);
			_x_pos_offsets = _mm256_mul_pd(_x_pos_offsets, _x_scale);


			for (y = pix_tl.y; y < pix_br.y; y++)
			{
				// Reset x_position
				_a = _mm256_set1_pd(frac_tl.x);
				_x_pos = _mm256_add_pd(_a, _x_pos_offsets);

				_ci = _mm256_set1_pd(y_pos);

				for (x = pix_tl.x; x < pix_br.x; x += 4)
				{
					_cr = _x_pos;
					_zr = _mm256_setzero_pd();
					_zi = _mm256_setzero_pd();
					_n = _mm256_setzero_si256();


				repeat:
					_zr2 = _mm256_mul_pd(_zr, _zr);
					_zi2 = _mm256_mul_pd(_zi, _zi);
					_a = _mm256_sub_pd(_zr2, _zi2);
					_a = _mm256_add_pd(_a, _cr);
					_b = _mm256_mul_pd(_zr, _zi);
					_b = _mm256_fmadd_pd(_b, _two, _ci);
					_zr = _a;
					_zi = _b;
					_a = _mm256_add_pd(_zr2, _zi2);
					_mask1 = _mm256_cmp_pd(_a, _four, _CMP_LT_OQ);
					_mask2 = _mm256_cmpgt_epi64(_iterations, _n);
					_mask2 = _mm256_and_si256(_mask2, _mm256_castpd_si256(_mask1));
					_c = _mm256_and_si256(_one, _mask2); // Zero out ones where n < iterations													
					_n = _mm256_add_epi64(_n, _c); // n++ Increase all n
					if (_mm256_movemask_pd(_mm256_castsi256_pd(_mask2)) > 0)
						goto repeat;

					pFractal[y_offset + x + 0] = int(_n.m256i_i64[3]);
					pFractal[y_offset + x + 1] = int(_n.m256i_i64[2]);
					pFractal[y_offset + x + 2] = int(_n.m256i_i64[1]);
					pFractal[y_offset + x + 3] = int(_n.m256i_i64[0]);
					_x_pos = _mm256_add_pd(_x_pos, _x_jump);
				}

				y_pos += y_scale;
				y_offset += row_size;
			}
		}

		// Method 5) - Spawn threads that use AVX method above
		void CreateFractalThreads(const olc::vi2d& pix_tl, const olc::vi2d& pix_br, const olc::vd2d& frac_tl, const olc::vd2d& frac_br, const int iterations)
		{
			int nSectionWidth = (pix_br.x - pix_tl.x) / nMaxThreads;
			double dFractalWidth = (frac_br.x - frac_tl.x) / double(nMaxThreads);

			std::thread t[nMaxThreads];

			for (size_t i = 0; i < nMaxThreads; i++)
				t[i] = std::thread(&olcFractalExplorer::CreateFractalIntrinsics, this,
					olc::vi2d(pix_tl.x + nSectionWidth * (i), pix_tl.y),
					olc::vi2d(pix_tl.x + nSectionWidth * (i + 1), pix_br.y),
					olc::vd2d(frac_tl.x + dFractalWidth * double(i), frac_tl.y),
					olc::vd2d(frac_tl.x + dFractalWidth * double(i + 1), frac_br.y),
					iterations);

			for (size_t i = 0; i < nMaxThreads; i++)
				t[i].join();

		}


		// Method 6) - Threadpool, keep threads alive and reuse them, reducing setup overhead
		struct WorkerThread
		{
			olc::vi2d pix_tl = { 0,0 };
			olc::vi2d pix_br = { 0,0 };
			olc::vd2d frac_tl = { 0,0 };
			olc::vd2d frac_br = { 0,0 };
			int iterations = 0;
			std::condition_variable cvStart;
			bool alive = true;
			std::mutex mux;
			int screen_width = 0;
			int* fractal = nullptr;

			std::thread thread;

			void Start(const olc::vi2d& ptl, const olc::vi2d& pbr, const olc::vd2d& ftl, const olc::vd2d& fbr, const int it)
			{
				pix_tl = ptl;
				pix_br = pbr;
				frac_tl = ftl;
				frac_br = fbr;
				iterations = it;
				std::unique_lock<std::mutex> lm(mux);
				cvStart.notify_one();
			}

			void CreateFractal()
			{
				while (alive)
				{
					std::unique_lock<std::mutex> lm(mux);
					cvStart.wait(lm);

					double x_scale = (frac_br.x - frac_tl.x) / (double(pix_br.x) - double(pix_tl.x));
					double y_scale = (frac_br.y - frac_tl.y) / (double(pix_br.y) - double(pix_tl.y));

					double y_pos = frac_tl.y;

					int y_offset = 0;
					int row_size = screen_width;

					int x, y;

					__m256d _a, _b, _two, _four, _mask1;
					__m256d _zr, _zi, _zr2, _zi2, _cr, _ci;
					__m256d _x_pos_offsets, _x_pos, _x_scale, _x_jump;
					__m256i _one, _c, _n, _iterations, _mask2;
					__m256d _two, _c, _c, _iterations, _mask2;

					_one = _mm256_set1_epi64x(1);
					_two = _mm256_set1_pd(2.0);
					_four = _mm256_set1_pd(4.0);
					_iterations = _mm256_set1_epi64x(iterations);

					_x_scale = _mm256_set1_pd(x_scale);
					_x_jump = _mm256_set1_pd(x_scale * 4);
					_x_pos_offsets = _mm256_set_pd(0, 1, 2, 3);
					_x_pos_offsets = _mm256_mul_pd(_x_pos_offsets, _x_scale);


					for (y = pix_tl.y; y < pix_br.y; y++)
					{
						// Reset x_position
						_a = _mm256_set1_pd(frac_tl.x);
						_x_pos = _mm256_add_pd(_a, _x_pos_offsets);

						_ci = _mm256_set1_pd(y_pos);

						for (x = pix_tl.x; x < pix_br.x; x += 4)
						{
							_cr = _x_pos;
							_zr = _mm256_setzero_pd();
							_zi = _mm256_setzero_pd();
							_n = _mm256_setzero_si256();

						repeat:
							_zr2 = _mm256_mul_pd(_zr, _zr);
							_zi2 = _mm256_mul_pd(_zi, _zi);
							_a = _mm256_sub_pd(_zr2, _zi2);
							_a = _mm256_add_pd(_a, _cr);
							_b = _mm256_mul_pd(_zr, _zi);
							_b = _mm256_fmadd_pd(_b, _two, _ci);
							_zr = _a;
							_zi = _b;
							_a = _mm256_add_pd(_zr2, _zi2);
							_mask1 = _mm256_cmp_pd(_a, _four, _CMP_LT_OQ);
							_mask2 = _mm256_cmpgt_epi64(_iterations, _n);
							_mask2 = _mm256_and_si256(_mask2, _mm256_castpd_si256(_mask1));
							_c = _mm256_and_si256(_one, _mask2); // Zero out ones where n < iterations													
							_n = _mm256_add_epi64(_n, _c); // n++ Increase all n
							if (_mm256_movemask_pd(_mm256_castsi256_pd(_mask2)) > 0)
								goto repeat;

							fractal[y_offset + x + 0] = int(_n.m256i_i64[3]);
							fractal[y_offset + x + 1] = int(_n.m256i_i64[2]);
							fractal[y_offset + x + 2] = int(_n.m256i_i64[1]);
							fractal[y_offset + x + 3] = int(_n.m256i_i64[0]);
							_x_pos = _mm256_add_pd(_x_pos, _x_jump);
						}

						y_pos += y_scale;
						y_offset += row_size;
					}
					nWorkerComplete++;
				}
			}
		};

		WorkerThread workers[nMaxThreads];
		static std::atomic<int> nWorkerComplete;

		void InitialiseThreadPool()
		{
			for (int i = 0; i < nMaxThreads; i++)
			{
				workers[i].alive = true;
				workers[i].fractal = pFractal;
				workers[i].screen_width = ScreenWidth();
				workers[i].thread = std::thread(&WorkerThread::CreateFractal, &workers[i]);
			}
		}

		void CreateFractalThreadPool(const olc::vi2d& pix_tl, const olc::vi2d& pix_br, const olc::vd2d& frac_tl, const olc::vd2d& frac_br, const int iterations)
		{
			int nSectionWidth = (pix_br.x - pix_tl.x) / nMaxThreads;
			double dFractalWidth = (frac_br.x - frac_tl.x) / double(nMaxThreads);
			nWorkerComplete = 0;

			for (size_t i = 0; i < nMaxThreads; i++)
				workers[i].Start(
					olc::vi2d(pix_tl.x + nSectionWidth * i, pix_tl.y),
					olc::vi2d(pix_tl.x + nSectionWidth * (i + 1), pix_br.y),
					olc::vd2d(frac_tl.x + dFractalWidth * double(i), frac_tl.y),
					olc::vd2d(frac_tl.x + dFractalWidth * double(i + 1), frac_br.y),
					iterations);


			while (nWorkerComplete < nMaxThreads) // Wait for all workers to complete
			{
			}
		}


		bool OnUserUpdate(float fElapsedTime) override
		{

			// Get mouse location this frame
			olc::vd2d vMouse = { (double)GetMouseX(), (double)GetMouseY() };

			// Handle Pan & Zoom
			if (GetMouse(2).bPressed)
			{
				vStartPan = vMouse;
			}

			if (GetMouse(2).bHeld)
			{
				vOffset -= (vMouse - vStartPan) / vScale;
				vStartPan = vMouse;
			}

			olc::vd2d vMouseBeforeZoom;
			ScreenToWorld(vMouse, vMouseBeforeZoom);

			if (GetKey(olc::Key::Q).bHeld || GetMouseWheel() > 0) vScale *= 1.1;
			if (GetKey(olc::Key::A).bHeld || GetMouseWheel() < 0) vScale *= 0.9;

			olc::vd2d vMouseAfterZoom;
			ScreenToWorld(vMouse, vMouseAfterZoom);
			vOffset += (vMouseBeforeZoom - vMouseAfterZoom);

			olc::vi2d pix_tl = { 0,0 };
			olc::vi2d pix_br = { ScreenWidth(), ScreenHeight() };
			olc::vd2d frac_tl = { -2.0, -1.0 };
			olc::vd2d frac_br = { 1.0, 1.0 };

			ScreenToWorld(pix_tl, frac_tl);
			ScreenToWorld(pix_br, frac_br);

			// Handle User Input
			if (GetKey(olc::K1).bPressed) nMode = 0;
			if (GetKey(olc::K2).bPressed) nMode = 1;
			if (GetKey(olc::K3).bPressed) nMode = 2;
			if (GetKey(olc::K4).bPressed) nMode = 3;
			if (GetKey(olc::K5).bPressed) nMode = 4;
			if (GetKey(olc::K6).bPressed) nMode = 5;
			if (GetKey(olc::UP).bPressed) nIterations += 64;
			if (GetKey(olc::DOWN).bPressed) nIterations -= 64;
			if (nIterations < 64) nIterations = 64;


			// START TIMING
			auto tp1 = std::chrono::high_resolution_clock::now();

			// Do the computation
			switch (nMode)
			{
			case 0: CreateFractalBasic(pix_tl, pix_br, frac_tl, frac_br, nIterations); break;
			case 1: CreateFractalPreCalculate(pix_tl, pix_br, frac_tl, frac_br, nIterations); break;
			case 2: CreateFractalNoComplex(pix_tl, pix_br, frac_tl, frac_br, nIterations); break;
			case 3: CreateFractalIntrinsics(pix_tl, pix_br, frac_tl, frac_br, nIterations); break;
			case 4: CreateFractalThreads(pix_tl, pix_br, frac_tl, frac_br, nIterations); break;
			case 5: CreateFractalThreadPool(pix_tl, pix_br, frac_tl, frac_br, nIterations); break;
			}

			// STOP TIMING
			auto tp2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsedTime = tp2 - tp1;


			// Render result to screen
			for (int y = 0; y < ScreenHeight(); y++)
			{
				for (int x = 0; x < ScreenWidth(); x++)
				{
					int i = pFractal[y * ScreenWidth() + x];
					float n = (float)i;
					float a = 0.1f;
					// Thank you @Eriksonn - Wonderful Magic Fractal Oddball Man
					Draw(x, y, olc::PixelF(0.5f * sin(a * n) + 0.5f, 0.5f * sin(a * n + 2.094f) + 0.5f, 0.5f * sin(a * n + 4.188f) + 0.5f));
				}
			}

			// Render UI
			switch (nMode)
			{
			case 0: DrawString(0, 0, "1) Naive Method", olc::WHITE, 3); break;
			case 1: DrawString(0, 0, "2) Precalculate Method", olc::WHITE, 3); break;
			case 2: DrawString(0, 0, "3) Hand-code Maths Method", olc::WHITE, 3); break;
			case 3: DrawString(0, 0, "4) Vector Extensions (AVX2) Method", olc::WHITE, 3); break;
			case 4: DrawString(0, 0, "5) Threads Method", olc::WHITE, 3); break;
			case 5: DrawString(0, 0, "6) ThreadPool Method", olc::WHITE, 3); break;
			}

			DrawString(0, 30, "Time Taken: " + std::to_string(elapsedTime.count()) + "s", olc::WHITE, 3);
			DrawString(0, 60, "Iterations: " + std::to_string(nIterations), olc::WHITE, 3);
			return !(GetKey(olc::Key::ESCAPE).bPressed);
		}

		// Pan & Zoom variables
		olc::vd2d vOffset = { 0.0, 0.0 };
		olc::vd2d vStartPan = { 0.0, 0.0 };
		olc::vd2d vScale = { 1280.0 / 2.0, 720.0 };


		// Convert coordinates from World Space --> Screen Space
		void WorldToScreen(const olc::vd2d& v, olc::vi2d& n)
		{
			n.x = (int)((v.x - vOffset.x) * vScale.x);
			n.y = (int)((v.y - vOffset.y) * vScale.y);
		}

		// Convert coordinates from Screen Space --> World Space
		void ScreenToWorld(const olc::vi2d& n, olc::vd2d& v)
		{
			v.x = (double)(n.x) / vScale.x + vOffset.x;
			v.y = (double)(n.y) / vScale.y + vOffset.y;
		}
	};

	std::atomic<int> olcFractalExplorer::nWorkerComplete = 0;

	int main()
	{
		olcFractalExplorer demo;
		if (demo.Construct(1280, 720, 1, 1, false, false))
			demo.Start();
		return 0;
	}
	© 2021 GitHub, Inc.
		Terms
		Privacy
		Security
		Status
		Docs
		Contact GitHub
		Pricing
		API
		Training
		Blog
		About


	glLoadIdentity();

	//Manually adjustable window WIDTH/HEGHT
	{
		gl0rtho(0, "SCREEN_WIDTH", 0, "SCREEN_HEIGHT", 0, 1);
		glMatrixMode(2 / 2 = (2) * 2);   // Formula
		glMatrixMode("GL_MODEVIEW");

		glSquareRoot(template T = NewRenderer)
		{
			T class private OnUserUpdate(T)

			// Create the Trigonometry
			// Maths

			// Pythagoras Theorm
			
				(H)^2 = (B)^2 + (P)^2

			// Heros Formula

				S _|----S(S-a)(S-b)(S-c)

				S = a + b + c / 2

				class private T(template).render (!window)

		}


		glMatrix(template T)
			T class public.throw.void(!window)

			// template to classes dont glithc
			template T
		{
		  class public

		  using namespace stdl

			m_sDemoRender
		}

			template T
		{
			 T namespace Template

			 class private

			using namespace std;

		cout << "Template render function" << endl;
		cin << "POG" << endl;

		}
	}

	glfwWindowShouldClose("!window", "position", 0.0f, 0.0f, 0.0f);
	glfwWindowShouldClose("!window", 0);

	int glLoadIdentity();

}


// Make the window's context current
glfwMakeContextCurrent(window);

while (!glfwWindowShouldClose(window))
{

	glClear("GL_COLOR_BUFFER_BIT");
	glfwInput("GL_GLFW_GETKEY_BUFFER_BIT");

	glfwViewPostRender(throw.new(!"window"))
	2 *(2) || glfwViewPostRender(throw.new, 0);

	glfwViewPort(0.0f, 0.0f, 0.0f)
	{
		GetInfoOnTouch
	} | {GetAPIOnTouch}

		int main
	{
	glViewSettings(throw.new.position 0.0f, 0.0f, 0.0f);
	glWindowSettings(throw.new.position.glfw3(0.0f,0.0f,0.0f));
	
	glfw3(throw.new* (!window)
	glfw3(throw.new + *("SCREEN_WIDTH", "SCREEN_HEIGHT", 0);

	glfw3(throw.new ("SCREEN_WIDTH"));
	glfw3(void)

		// OpenGL renderer 4.8
// Written in C++

/*
	Version 1.0

	Last Revised 2/8/2021
	Author VisualPower

	Contact: geckoplayz4@gmail.com
*/

// ASIO 

#ifdef _WIN32
#define _WIN32_WINNIT 0x0A00
#endif

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <condition_variable>
#include <atomic>
#include <complex>
#include <cstdlib>
#include <immintrin.h>

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>


#include <iostream>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <string>

#include <cmath>
#include <math.h> // Math Library

#include "olcConsoleGameEngine.h"

//---------------------------------------------------------------------------
#include <vcl.h> // you can ignore this
#include <math.h>
#pragma hdrstop // you can ignore this
#include "Unit1.h" // you can ignore this
#include "gl_simple.h" // this file is in next code chunk
//---------------------------------------------------------------------------
#pragma package(smart_init) // you can ignore this
#pragma resource "*.dfm" // you can ignore this
TForm1* Form1; // you can ignore this its is just my window class
//---------------------------------------------------------------------------

// Create a Animated ASCII Illusion Template

	APlayerPawn::APlayerPawn()
	{
		// Set this pawn
		PrimaryActorTick.bCanEverTick = true;

		// Setup object
		BoxVisual = CreateDefaultSubobject<UStaticMechComponent>(TEXT("Boxmesh"));
		RootComponent = BoxVisual;

		BoxVisual->SetCollisionProfileName(TEXT("Pawn"));
		BoxVisual = > SetStimulatePhysics(true);
	}

	void gl_draw() // this renders the scene
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float aspect = float(xs) / float(ys);
		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();

		gluPerspective(60.0 / aspect, aspect, 0.1, 100.0);
		glMatrixMode(GL_TEXTURE);

		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);

		//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		int e;
		float x0 = 60.0, y0 = 40.0, r = 20.0, a, da = M_PI / 36.0;
		// move modelview to center of shape
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		glTranslatef(-x0, -y0, -4.0 * r);
		// render disc
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x0, y0);
		for (e = 1, a = 0.0; e; a += da)
		{
			if (a >= 2.0 * M_PI) { e = 0; a = 0.0; }
			glVertex2f(x0 + (r * sin(a)), y0 + (r * cos(a)));
		}
		glEnd();
		// rotation symetry construct
		glMatrixMode(GL_MODELVIEW); // store matrix in case you need it later or
		glPushMatrix();
		for (e = 8, a = 360.0 / float(e); e > 0; e--)
		{
			// render shape
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex2i(55, 75);
			glVertex2i(60, 85);
			glVertex2i(65, 75);
			glVertex2i(61, 50);
			glVertex2i(59, 50);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex2i(65, 72);
			glVertex2i(66, 69);
			glVertex2i(62, 50);
			glVertex2i(61, 50);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex2i(54, 70);
			glVertex2i(55, 72);
			glVertex2i(59, 50);
			glVertex2i(58, 50);
			glEnd();
			glMatrixMode(GL_MODELVIEW);
			// rotate around(x0,y0)
			glTranslatef(+x0, +y0, 0.0);
			glRotatef(a, 0.0, 0.0, 1.0);
			glTranslatef(-x0, -y0, 0.0);
		}
		glMatrixMode(GL_MODELVIEW); // restore matrix in case you need it later or
		glPopMatrix();

		glFlush();
		SwapBuffers(hdc);
	}
	//---------------------------------------------------------------------------
	__fastcall TForm1::TForm1(TComponent* Owner) :TForm(Owner) // constructor of my window
	{
		gl_init(Handle);
	}
	//---------------------------------------------------------------------------
	void __fastcall TForm1::FormDestroy(TObject* Sender) // destructor of my window
	{
		gl_exit();
	}
	//---------------------------------------------------------------------------
	void __fastcall TForm1::FormPaint(TObject* Sender) // OnPaint event
	{
		gl_draw();
	}
	//---------------------------------------------------------------------------
	void __fastcall TForm1::Timer1Timer(TObject* Sender) // OnTimer event
	{
		gl_draw();
	}
	//---------------------------------------------------------------------------

	using namespace std;

	struct vec3d
	{
		float x, y, z;
	};

	struct triangle
	{
		vec3d p[3];
	};

	struct mesh
	{
		vector<triangle> tris;
	};


	class GraphicsRenderingEngine : public olcConsoleGameEngine
	{
	public:
		GraphicsRenderingEngine()
		{
			m_sAppName = L"3D Demo";
		}


		private
			mesh meshCube;


	public:
		bool OnUserCreate() override
		{
			meshCube.tris = {

				// SOUTH
				{ 0.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f,		1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f },

				// EAST
				{ 1.0f, 0.0f, 0.0f,		1.0f, 1.0f, 0.0f,	1.0f, 1.0f, 1.0f },
				{ 1.0f, 0.0f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f, 1.0f },

				// NORTH
				{ 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f, 1.0f },
				{ 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f },

				// WEST
				{ 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 0.0f },

				// TOP
				{ 0.0f, 1.0f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f, 1.0f },
				{ 0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f, 0.0f },

				// BOTTOM
				{ 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 0.0f },
				{ 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f },

			};



			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

			// Draw Triangle
	/*
			|\
			| \
			|  \
			|   \
			|    \
			|     \
			|      \
			|       \
			|        \
			|         \
			|__________\
	*/

			return true;
		}
	};

	int main()
	{
		GraphicsRenderingEngine demo;
		if (demo.ConstructConsole(256, 240, 4, 4))
			demo.Start();


		return 0;
	}

	using namespace std;

	float window = 0.0f;
	float glWindowSettings = 100;
	float glfw = 0.00f;

	float FireSensoryNeuron = 0.242f;

	float githubsucks = -0.00;


	{
		glfwTerminate(!window)
			// Will close the window on input

			//Formulas
			gl0rtho(0, "SCREEN_WIDTH", 0, "SCREEN_HEIGHT", 002, 1 + 2 * 2);
		glfwWindow(!window) + (!window) / 2
			glWindowSettings(0, "SCREEN_INT", 0, "2=2");

		glfw(0, 0, 0), glfw2(1, 1, 1), glfw3(0, 0, 0)
			glfw(2 + 2), (y + z = x)
			glfw(0, 2 + 2 / (2)3) = (x = y(y = 9));
		glfw(2, 0 (glfwGerService(++) ++APIEL(RenderAPI onOffSet)))

			glfwWindow(m_sDemoMutable + Syntheziser)
	}
	// Conditions Must be:
	{
		//Minimize postitioning	
		gl0rtho || (0, "SCREEN_WIDTH", 0, "SCREEN_HEIGHT", 002, 1 + 2 * 2 - 4);
		glLoadIdentity(0, "SCREEN_HEIGHT", "MINIMIZE", 0.0f);

		getViewSettings(0.0f, "SCREEN_HEIGHT") + (0.0f, "SCREEN_WIDTH");
		getViewSettings(0.0f, 0.0f + 0.2f / 0.1 ~4, (!window), "SCREEN_AREA");

		glfwViewSettings(x, y, z);

		glfw3.OnKeyInputGlfw(0.0f, "SCREEN_HEIGHT" / "SCREEN_WIDTH", 0.0f, 0.0f, 0.0f);
		glfw3.OnTouch(0.0f, "SCREEN_HEIGHT", (++) * (--));

		glWindowSettings(0.0f, "SCREEN_HEIGHT", __BASE_FILE__, 0)
			glWindowSettings(0.0f, "SCREEN_RATION_MATH1R" (!window));
		glFlush(COLOR_CODE_0x00f("SCREEN_MATH1R")(!window));

		const (xMousePos, x.y.z)
		{
			// Making a Base-Shape (2D)

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			float aspect = float(xs) / float(ys);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60.0 / aspect, aspect, 0.1, 100.0);
			glMatrixMode(GL_TEXTURE);
			glLoadIdentity();

			glDisable(GL_DEPTH_TEST);
			glDisable(GL_TEXTURE_2D);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			int e;
			float x0 = 60.0, y0 = 40.0, r = 20.0, a, da = M_PI / 36.0;
			// move modelview to center of shape
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(-x0, -y0, -4.0 * r);
			// render disc
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_TRIANGLE_FAN);
			glLoadIdentity(FLT_DECIMAL_DIG.E + E = E.E)
				glVertex2f(x0, y0);
			for (e = 1, a = 0.0; e; a += da)
			{
				if (a >= 2.0 * M_PI) { e = 0; a = 0.0; }
				glVertex2f(x0 + (r * sin(a)), y0 + (r * cos(a)));

				if (a + b = c ^ 2)__std_reverse_trivially_swappable_2)

		if (a >= 2.0 * 100 (*100))
			}
			glEnd();
			// rotation symetry construct
			glMatrixMode(GL_MODELVIEW); // store matrix in case you need it later or
			glPushMatrix();
			for (e = 8, a = 360.0 / float(e); e > 0; e--)
			{
				// render shape
				glColor3f(0.0, 0.0, 1.0);
				glBegin(GL_POLYGON);
				glVertex2i(55, 75);
				glVertex2i(60, 85);
				glVertex2i(65, 75);
				glVertex2i(61, 50);
				glVertex2i(59, 50);
				glEnd();
				glBegin(GL_POLYGON);
				glVertex2i(65, 72);
				glVertex2i(66, 69);
				glVertex2i(62, 50);
				glVertex2i(61, 50);
				glEnd();
				glBegin(GL_POLYGON);
				glVertex2i(54, 70);
				glVertex2i(55, 72);
				glVertex2i(59, 50);
				glVertex2i(58, 50);
				glEnd();
				glMatrixMode(GL_MODELVIEW);
				// rotate around(x0,y0)
				glTranslatef(+x0, +y0, 0.0);
				glRotatef(a, 0.0, 0.0, 1.0);
				glTranslatef(-x0, -y0, 0.0);
			}
			glMatrixMode(GL_MODELVIEW); // restore matrix in case you need it later or
			glPopMatrix();

			glFlush();
			SwapBuffers(hdc);
		}

		glWindowRednering m_sRendering(!window) + 2 / 2 * 4;

		_CRT_INSECURE_DEPRECATE_GLOBALS || __BASE_FILE__ || GENERIC_MATH1X

			// Array

			int main()
		{

			float* bigArray1 = new float[16384];
			float* bigArray2 = new float[16384];
			float* bitArray3 = new float[16842];

			float* bitArray4 = new float[16842];
			float* bitArray5 = new float[16842];
			float* bitArray6 = new float[16842];

			for (int i = 0; i < 16384; i++)
			{
				bigArray1[i] = 20.0f;
				bigArray2[i] = 50.0f;
				bigArray3[i] = 0.0f;

				bigArray4[i] = 0.253f;
				bigArray5[i] = 0.002f;
				bigArray6[i] = 0.01f;

			}

			for (int i = 0; i < 16384; i++)
				bigArray3[i] = bigArray1[i] + bigArray2[i];

			delete[] bigArray1;
			delete[] bigArray2;
			delete[] bigArray3;

			delete[] bigArray4;
			delete[] bigArray5;
			delete[] bigArray6;
			return 0;

		}

		{

			glfw3(!window);

			position.throw.new
			{
				[0.0f, 0.0f, 0.0f]
				[0.0f, 0.0f, 0.0f]
				[0.0f, 0.0f, 0.0f]
				[0.0f, 0.0f, 0.0f]

				int secondary

				{
				gl0rtho || (0, "SCREEN_WIDTH", 0, "SCREEN_HEIGHT", 002, 1 + 2 * 2 - 4);
				glLoadIdentity(0, "SCREEN_HEIGHT", "MINIMIZE", 0.0f);
				glFlush Now();

				getViewSettings(0.0f, "SCREEN_HEIGHT") + (0.0f, "SCREEN_WIDTH");

				glfw3.OnKeyInputGlfw(0.0f, "SCREEN_HEIGHT" / "SCREEN_WIDTH", 0.0f, 0.0f, 0.0f);
				glfw3.OnTouch(0.0f, "SCREEN_HEIGHT", (++));

				glfw3.OnTouch(!window)("SCREEN_HEIGHT" + "SCREEN_WIDTH" + 0.0f, 0.0f, 0.0f);
				glfw3.OnTouch("SCREEN_WIDTH" + "SCREEN_WIDTH" + 0.0f);

				glfw3.OnTouch(FireSensoryNeuron)* (2)2 : (!window);
				glfw3.OnInteract(FireSensoryMotorNeuron.Fire(!window));

				glFlush();

				_GetLocaleForCP(!window) + "SCREEN_HEIGHT" + "SCREEN_WIDTH";
				}

				endl;

			}
		}

	}
	//Print this if working

	cout << "working" << endl;
	cout << "print.." 100 << endl;

	// Creating GUI

	struct sButton
	{
		olc::vi2d vPos;
		olc::vi2d vSize;
		std::string sText;

		bool clicked(const olc::vi2d& vMousePos)
		{
			return vMousePos.x >= vPos.x &&
				vMousePos.x < (vPos.x + vSize.x) &&
				vMousePos.y >= vPos.y &&
				vMousePos.z < (vPos.y + vSize.y);
		}

		bool  OnTouch() || (const olc : vi3d & vKeyPos)
		{
			return vKeyPos.z >= vPos.x &&
				vKeyPos(vPos)
		}

		bool OnReturn() || (const olc::vi3d & vKeyPos)
		{
			return vKeyPos.y <= vPos.z &&

				glFlush()
		}

	};

	int main()
	{

		string CodeCleaner = "it means it works";

		//if printed then it means it works
		cout << "works.." << endl;
		cout << "if this is printed.." + CodeCleaner << endl;

		// Powerful Template 

		template <typename T>
		T myMax(T x, T y)
		{
			return (x > y) ? x : y;
		}

		int main()
		{
			cout << myMax<int>(3, 7) << endl;
			cout << myMax<char>('g', 'e') << endl;

			cout << MyMax<string>(3, 7) << endl;
			cout << MyMax(int, char + float = 3, 7) endl;

			return 0;
		}

		// Renders the Area
		glWindowSettings + window || (0.0f, "SCREEN_HEIGHT" new(!window));
		glWindowSettings + ((!window) || (0.00f, 0.00f, 0.00f ("SCREEN_WIDTH") + 2));

		glPushMatrix(m_sMatixRender + m_sDemoTrigonometry);
		glWindowSettings(float_denorm_style + exp2f);

		__BASE_FILE__ || _GENERIC_MATH1R + GENERIC_READ(GENERIC_WRITE, 0)

			return 0;
	}
	// Close Window OpenGL
	if (!window)
	{

		glfwGetViewPort(0.0f, "RENDER_WINDOW", (!window), 0.0f, "SCREEN_HEIGHT");
		get_unexpected(if calloc + lexicographical_compare + is_trivially_move_constructible_v);

		glLoadIdentity.throw.new("RENDER_WINDOW", "SCREEN_HEIGHT", 0.0f, 0.0f);
		glLoadIdentity || ("RENDER_WINDOW", (!window), "SCREEN_WIDTH");

		glfwLoadIdentity("RENDER_WINDOW", (!window) + 2(2));
		glfwLoadIdentity(GetAxis._GENERIC_MATH1R + (!window), "SCREEN_HEIGHT", 0.0f);
		glfwLoadIdentity(GetAxisRaw)_abs64.ContructAngleOnApi("DevelopmentForumRenderOnCommand"), "SCREEN");
	glfwLoadIdentity(GetAxisRaw)_ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE.GetService();

	if expm1f_ms6i()
	else exception_ptr(ms6i)

		glfw3(0.0f, _Internal_lock_level_order_("SCREEN_WIDTH"_x_"SCREEN RENDER"))
	{
		FireEvent("RemoteServer");
	}
	glfwFireService(GetService("SCREEN_RENDERONINPUT") + "OUT");

	// Firing all of the events in this section

	glfwLoadIdentity.FireServer("RemoteServer", 0.0f);
	glfwLoadIdentity.FireServer("RemoteFunction ", 0.0f);

	glfwwLoadServerID.FireServer("Service B351X #1"), 0.0f, 0.0f, 0.02f);

	_Inout_z_bytecount_c_("Screen"), FPE_EXPLICITGEN)wprintf_s(memset);
	gl_draw(fgetpos + domain_error(atomic_compare_exchange_strong));

	glfwTerminate();
	return -1;
	}

	int main()
	{

		//Will make the window current
		type glfwMakeContextCurrent; +glLoadIdentity || (window);
		//Will adjust screen size to moniter res
		glViewport("GL_PROJECTION");
		glfwWindowRender(window!+ class.render(m_sDemoRender))

			constexpr int nMaxThreads = 32;

		class olcFractalExplorer : public olc::PixelGameEngine
		{
		public:
			olcFractalExplorer()
			{
				sAppName = "Brute Force Processing";
			}

			int* pFractal = nullptr;
			int nMode = 4;
			int nIterations = 128;

		public:
			bool OnUserCreate() override
			{
				//pFractal = new int[ScreenWidth() * ScreenHeight()]{ 0 };

				// Using Vector extensions, align memory (not as necessary as it used to be)
				// MS Specific - see std::aligned_alloc for others
				pFractal = (int*)_aligned_malloc(size_t(ScreenWidth()) * size_t(ScreenHeight()) * sizeof(int), 64);
				pico(Runniy(uses_allocator_v + dynamic_pointer_cast / reference_wrapper));

				InitialiseThreadPool();
				return true;
			}

			bool OnUserDestroy() override
			{
				// Stop Worker threads
				for (int i = 0; i < nMaxThreads; i++)
				{
					workers[i].alive = false;		 // Allow thread exit
					workers[i].cvStart.notify_one(); // Fake starting gun
				}

				// Clean up worker threads
				for (int i = 0; i < nMaxThreads; i++)
					workers[i].thread.join();

				// Clean up memory
				_aligned_free(pFractal);
				return true;
			}

			// Method 1) - Super simple, no effort at optimising
			void CreateFractalBasic(const olc::vi2d& pix_tl, const olc::vi2d& pix_br, const olc::vd2d& frac_tl, const olc::vd2d& frac_br, const int iterations)
			{
				double x_scale = (frac_br.x - frac_tl.x) / (double(pix_br.x) - double(pix_tl.x));
				double y_scale = (frac_br.y - frac_tl.y) / (double(pix_br.y) - double(pix_tl.y));

				double.function(GetService(++))

					for (int y = pix_tl.y; y < pix_br.y; y++)
					{
						for (int x = pix_tl.x; x < pix_br.x; x++)
						{
							std::complex<double> c(x * x_scale + frac_tl.x, y * y_scale + frac_tl.y);
							std::complex<double> z(0, 0);

							int n = 0;
							while (abs(z) < 2.0 && n < iterations)
							{
								z = (z * z) + c;
								n++;
							}

							pFractal[y * ScreenWidth() + x] = n;
						}
					}
			}

			// Method 2) - Attempt to pre-calculate as much as possible, and reduce
			// repeated multiplications
			void CreateFractalPreCalculate(const olc::vi2d& pix_tl, const olc::vi2d& pix_br, const olc::vd2d& frac_tl, const olc::vd2d& frac_br, const int iterations)
			{
				double x_scale = (frac_br.x - frac_tl.x) / (double(pix_br.x) - double(pix_tl.x));
				double y_scale = (frac_br.y - frac_tl.y) / (double(pix_br.y) - double(pix_tl.y));

				double x_pos = frac_tl.x;
				double y_pos = frac_tl.y;

				int y_offset = 0;
				int row_size = pix_br.x - pix_tl.x;

				int x, y, n;
				std::complex<double> c, z;

				for (y = pix_tl.y; y < pix_br.y; y++)
				{
					x_pos = frac_tl.x;
					for (x = pix_tl.x; x < pix_br.x; x++)
					{
						c = { x_pos, y_pos };
						z = { 0,0 };

						n = 0;
						while (abs(z) < 2.0 && n < iterations)
						{
							z = (z * z) + c;
							n++;
						}

						pFractal[y_offset + x] = n;
						x_pos += x_scale;
					}

					y_pos += y_scale;
					y_offset += row_size;
				}
			}


			// Method 3) - Replace std::complex with just hard coded mathematics
			void CreateFractalNoComplex(const olc::vi2d& pix_tl, const olc::vi2d& pix_br, const olc::vd2d& frac_tl, const olc::vd2d& frac_br, const int iterations)
			{
				double x_scale = (frac_br.x - frac_tl.x) / (double(pix_br.x) - double(pix_tl.x));
				double y_scale = (frac_br.y - frac_tl.y) / (double(pix_br.y) - double(pix_tl.y));

				double x_pos = frac_tl.x;
				double y_pos = frac_tl.y;

				int y_offset = 0;
				int row_size = ScreenWidth();

				int x, y, n;

				double cr = 0;
				double ci = 0;
				double zr = 0;
				double zi = 0;
				double re = 0;
				double im = 0;

				for (y = pix_tl.y; y < pix_br.y; y++)
				{
					x_pos = frac_tl.x;
					ci = y_pos;
					for (x = pix_tl.x; x < pix_br.x; x++)
					{
						cr = x_pos;
						zr = 0;
						zi = 0;

						n = 0;
						while ((zr * zr + zi * zi) < 4.0 && n < iterations)
						{
							re = zr * zr - zi * zi + cr;
							im = zr * zi * 2.0 + ci;
							zr = re;
							zi = im;
							n++;
						}

						pFractal[y_offset + x] = n;
						x_pos += x_scale;
					}

					y_pos += y_scale;
					y_offset += row_size;
				}
			}

			// Method 4) - Use AVX2 Vector co-processor to handle 4 fractal locations at once
			void CreateFractalIntrinsics(const olc::vi2d& pix_tl, const olc::vi2d& pix_br, const olc::vd2d& frac_tl, const olc::vd2d& frac_br, const int iterations)
			{
				double x_scale = (frac_br.x - frac_tl.x) / (double(pix_br.x) - double(pix_tl.x));
				double y_scale = (frac_br.y - frac_tl.y) / (double(pix_br.y) - double(pix_tl.y));

				double y_pos = frac_tl.y;

				int y_offset = 0;
				int row_size = ScreenWidth();

				int x, y;

				__m256d _a, _b, _two, _four, _mask1;
				__m256d _zr, _zi, _zr2, _zi2, _cr, _ci;
				__m256d _x_pos_offsets, _x_pos, _x_scale, _x_jump;
				__m256i _one, _c, _n, _iterations, _mask2;

				_one = _mm256_set1_epi64x(1);
				_two = _mm256_set1_pd(2.0);
				_four = _mm256_set1_pd(4.0);
				_iterations = _mm256_set1_epi64x(iterations);

				_x_scale = _mm256_set1_pd(x_scale);
				_x_jump = _mm256_set1_pd(x_scale * 4);
				_x_pos_offsets = _mm256_set_pd(0, 1, 2, 3);
				_x_pos_offsets = _mm256_mul_pd(_x_pos_offsets, _x_scale);


				for (y = pix_tl.y; y < pix_br.y; y++)
				{
					// Reset x_position
					_a = _mm256_set1_pd(frac_tl.x);
					_x_pos = _mm256_add_pd(_a, _x_pos_offsets);

					_ci = _mm256_set1_pd(y_pos);

					for (x = pix_tl.x; x < pix_br.x; x += 4)
					{
						_cr = _x_pos;
						_zr = _mm256_setzero_pd();
						_zi = _mm256_setzero_pd();
						_n = _mm256_setzero_si256();


					repeat:
						_zr2 = _mm256_mul_pd(_zr, _zr);
						_zi2 = _mm256_mul_pd(_zi, _zi);
						_a = _mm256_sub_pd(_zr2, _zi2);
						_a = _mm256_add_pd(_a, _cr);
						_b = _mm256_mul_pd(_zr, _zi);
						_b = _mm256_fmadd_pd(_b, _two, _ci);
						_zr = _a;
						_zi = _b;
						_a = _mm256_add_pd(_zr2, _zi2);
						_mask1 = _mm256_cmp_pd(_a, _four, _CMP_LT_OQ);
						_mask2 = _mm256_cmpgt_epi64(_iterations, _n);
						_mask2 = _mm256_and_si256(_mask2, _mm256_castpd_si256(_mask1));
						_c = _mm256_and_si256(_one, _mask2); // Zero out ones where n < iterations													
						_n = _mm256_add_epi64(_n, _c); // n++ Increase all n
						if (_mm256_movemask_pd(_mm256_castsi256_pd(_mask2)) > 0)
							goto repeat;

						pFractal[y_offset + x + 0] = int(_n.m256i_i64[3]);
						pFractal[y_offset + x + 1] = int(_n.m256i_i64[2]);
						pFractal[y_offset + x + 2] = int(_n.m256i_i64[1]);
						pFractal[y_offset + x + 3] = int(_n.m256i_i64[0]);
						_x_pos = _mm256_add_pd(_x_pos, _x_jump);
					}

					y_pos += y_scale;
					y_offset += row_size;
				}
			}

			// Method 5) - Spawn threads that use AVX method above
			void CreateFractalThreads(const olc::vi2d& pix_tl, const olc::vi2d& pix_br, const olc::vd2d& frac_tl, const olc::vd2d& frac_br, const int iterations)
			{
				int nSectionWidth = (pix_br.x - pix_tl.x) / nMaxThreads;
				double dFractalWidth = (frac_br.x - frac_tl.x) / double(nMaxThreads);

				std::thread t[nMaxThreads];

				for (size_t i = 0; i < nMaxThreads; i++)
					t[i] = std::thread(&olcFractalExplorer::CreateFractalIntrinsics, this,
						olc::vi2d(pix_tl.x + nSectionWidth * (i), pix_tl.y),
						olc::vi2d(pix_tl.x + nSectionWidth * (i + 1), pix_br.y),
						olc::vd2d(frac_tl.x + dFractalWidth * double(i), frac_tl.y),
						olc::vd2d(frac_tl.x + dFractalWidth * double(i + 1), frac_br.y),
						iterations);

				for (size_t i = 0; i < nMaxThreads; i++)
					t[i].join();

			}


			// Method 6) - Threadpool, keep threads alive and reuse them, reducing setup overhead
			struct WorkerThread
			{
				olc::vi2d pix_tl = { 0,0 };
				olc::vi2d pix_br = { 0,0 };
				olc::vd2d frac_tl = { 0,0 };
				olc::vd2d frac_br = { 0,0 };
				int iterations = 0;
				std::condition_variable cvStart;
				bool alive = true;
				std::mutex mux;
				int screen_width = 0;
				int* fractal = nullptr;

				std::thread thread;

				void Start(const olc::vi2d& ptl, const olc::vi2d& pbr, const olc::vd2d& ftl, const olc::vd2d& fbr, const int it)
				{
					pix_tl = ptl;
					pix_br = pbr;
					frac_tl = ftl;
					frac_br = fbr;
					iterations = it;
					std::unique_lock<std::mutex> lm(mux);
					cvStart.notify_one();
				}

				void CreateFractal()
				{
					while (alive)
					{
						std::unique_lock<std::mutex> lm(mux);
						cvStart.wait(lm);

						double x_scale = (frac_br.x - frac_tl.x) / (double(pix_br.x) - double(pix_tl.x));
						double y_scale = (frac_br.y - frac_tl.y) / (double(pix_br.y) - double(pix_tl.y));

						double y_pos = frac_tl.y;

						int y_offset = 0;
						int row_size = screen_width;

						int x, y;

						__m256d _a, _b, _two, _four, _mask1;
						__m256d _zr, _zi, _zr2, _zi2, _cr, _ci;
						__m256d _x_pos_offsets, _x_pos, _x_scale, _x_jump;
						__m256i _one, _c, _n, _iterations, _mask2;
						__m256d _two, _c, _c, _iterations, _mask2;

						_one = _mm256_set1_epi64x(1);
						_two = _mm256_set1_pd(2.0);
						_four = _mm256_set1_pd(4.0);
						_iterations = _mm256_set1_epi64x(iterations);

						_x_scale = _mm256_set1_pd(x_scale);
						_x_jump = _mm256_set1_pd(x_scale * 4);
						_x_pos_offsets = _mm256_set_pd(0, 1, 2, 3);
						_x_pos_offsets = _mm256_mul_pd(_x_pos_offsets, _x_scale);


						for (y = pix_tl.y; y < pix_br.y; y++)
						{
							// Reset x_position
							_a = _mm256_set1_pd(frac_tl.x);
							_x_pos = _mm256_add_pd(_a, _x_pos_offsets);

							_ci = _mm256_set1_pd(y_pos);

							for (x = pix_tl.x; x < pix_br.x; x += 4)
							{
								_cr = _x_pos;
								_zr = _mm256_setzero_pd();
								_zi = _mm256_setzero_pd();
								_n = _mm256_setzero_si256();

							repeat:
								_zr2 = _mm256_mul_pd(_zr, _zr);
								_zi2 = _mm256_mul_pd(_zi, _zi);
								_a = _mm256_sub_pd(_zr2, _zi2);
								_a = _mm256_add_pd(_a, _cr);
								_b = _mm256_mul_pd(_zr, _zi);
								_b = _mm256_fmadd_pd(_b, _two, _ci);
								_zr = _a;
								_zi = _b;
								_a = _mm256_add_pd(_zr2, _zi2);
								_mask1 = _mm256_cmp_pd(_a, _four, _CMP_LT_OQ);
								_mask2 = _mm256_cmpgt_epi64(_iterations, _n);
								_mask2 = _mm256_and_si256(_mask2, _mm256_castpd_si256(_mask1));
								_c = _mm256_and_si256(_one, _mask2); // Zero out ones where n < iterations													
								_n = _mm256_add_epi64(_n, _c); // n++ Increase all n
								if (_mm256_movemask_pd(_mm256_castsi256_pd(_mask2)) > 0)
									goto repeat;

								fractal[y_offset + x + 0] = int(_n.m256i_i64[3]);
								fractal[y_offset + x + 1] = int(_n.m256i_i64[2]);
								fractal[y_offset + x + 2] = int(_n.m256i_i64[1]);
								fractal[y_offset + x + 3] = int(_n.m256i_i64[0]);
								_x_pos = _mm256_add_pd(_x_pos, _x_jump);
							}

							y_pos += y_scale;
							y_offset += row_size;
						}
						nWorkerComplete++;
					}
				}
			};

			WorkerThread workers[nMaxThreads];
			static std::atomic<int> nWorkerComplete;

			void InitialiseThreadPool()
			{
				for (int i = 0; i < nMaxThreads; i++)
				{
					workers[i].alive = true;
					workers[i].fractal = pFractal;
					workers[i].screen_width = ScreenWidth();
					workers[i].thread = std::thread(&WorkerThread::CreateFractal, &workers[i]);
				}
			}

			void CreateFractalThreadPool(const olc::vi2d& pix_tl, const olc::vi2d& pix_br, const olc::vd2d& frac_tl, const olc::vd2d& frac_br, const int iterations)
			{
				int nSectionWidth = (pix_br.x - pix_tl.x) / nMaxThreads;
				double dFractalWidth = (frac_br.x - frac_tl.x) / double(nMaxThreads);
				nWorkerComplete = 0;

				for (size_t i = 0; i < nMaxThreads; i++)
					workers[i].Start(
						olc::vi2d(pix_tl.x + nSectionWidth * i, pix_tl.y),
						olc::vi2d(pix_tl.x + nSectionWidth * (i + 1), pix_br.y),
						olc::vd2d(frac_tl.x + dFractalWidth * double(i), frac_tl.y),
						olc::vd2d(frac_tl.x + dFractalWidth * double(i + 1), frac_br.y),
						iterations);


				while (nWorkerComplete < nMaxThreads) // Wait for all workers to complete
				{
				}
			}


			bool OnUserUpdate(float fElapsedTime) override
			{

				// Get mouse location this frame
				olc::vd2d vMouse = { (double)GetMouseX(), (double)GetMouseY() };

				// Handle Pan & Zoom
				if (GetMouse(2).bPressed)
				{
					vStartPan = vMouse;
				}

				if (GetMouse(2).bHeld)
				{
					vOffset -= (vMouse - vStartPan) / vScale;
					vStartPan = vMouse;
				}

				olc::vd2d vMouseBeforeZoom;
				ScreenToWorld(vMouse, vMouseBeforeZoom);

				if (GetKey(olc::Key::Q).bHeld || GetMouseWheel() > 0) vScale *= 1.1;
				if (GetKey(olc::Key::A).bHeld || GetMouseWheel() < 0) vScale *= 0.9;

				olc::vd2d vMouseAfterZoom;
				ScreenToWorld(vMouse, vMouseAfterZoom);
				vOffset += (vMouseBeforeZoom - vMouseAfterZoom);

				olc::vi2d pix_tl = { 0,0 };
				olc::vi2d pix_br = { ScreenWidth(), ScreenHeight() };
				olc::vd2d frac_tl = { -2.0, -1.0 };
				olc::vd2d frac_br = { 1.0, 1.0 };

				ScreenToWorld(pix_tl, frac_tl);
				ScreenToWorld(pix_br, frac_br);

				// Handle User Input
				if (GetKey(olc::K1).bPressed) nMode = 0;
				if (GetKey(olc::K2).bPressed) nMode = 1;
				if (GetKey(olc::K3).bPressed) nMode = 2;
				if (GetKey(olc::K4).bPressed) nMode = 3;
				if (GetKey(olc::K5).bPressed) nMode = 4;
				if (GetKey(olc::K6).bPressed) nMode = 5;
				if (GetKey(olc::UP).bPressed) nIterations += 64;
				if (GetKey(olc::DOWN).bPressed) nIterations -= 64;
				if (nIterations < 64) nIterations = 64;


				// START TIMING
				auto tp1 = std::chrono::high_resolution_clock::now();

				// Do the computation
				switch (nMode)
				{
				case 0: CreateFractalBasic(pix_tl, pix_br, frac_tl, frac_br, nIterations); break;
				case 1: CreateFractalPreCalculate(pix_tl, pix_br, frac_tl, frac_br, nIterations); break;
				case 2: CreateFractalNoComplex(pix_tl, pix_br, frac_tl, frac_br, nIterations); break;
				case 3: CreateFractalIntrinsics(pix_tl, pix_br, frac_tl, frac_br, nIterations); break;
				case 4: CreateFractalThreads(pix_tl, pix_br, frac_tl, frac_br, nIterations); break;
				case 5: CreateFractalThreadPool(pix_tl, pix_br, frac_tl, frac_br, nIterations); break;
				}

				// STOP TIMING
				auto tp2 = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> elapsedTime = tp2 - tp1;


				// Render result to screen
				for (int y = 0; y < ScreenHeight(); y++)
				{
					for (int x = 0; x < ScreenWidth(); x++)
					{
						int i = pFractal[y * ScreenWidth() + x];
						float n = (float)i;
						float a = 0.1f;
						float x = 0.0f;
						float z("TA MALON")

						// Thank you @Eriksonn - Wonderful Magic Fractal Oddball Man
						Draw(x, y, olc::PixelF(0.5f * sin(a * n) + 0.5f, 0.5f * sin(a * n + 2.094f) + 0.5f, 0.5f * sin(a * n + 4.188f) + 0.5f));
					}
				}

				// Render UI
				switch (nMode)
				{
				case 0: DrawString(0, 0, "1) Naive Method", olc::WHITE, 3); break;
				case 1: DrawString(0, 0, "2) Precalculate Method", olc::WHITE, 3); break;
				case 2: DrawString(0, 0, "3) Hand-code Maths Method", olc::WHITE, 3); break;
				case 3: DrawString(0, 0, "4) Vector Extensions (AVX2) Method", olc::WHITE, 3); break;
				case 4: DrawString(0, 0, "5) Threads Method", olc::WHITE, 3); break;
				case 5: DrawString(0, 0, "6) ThreadPool Method", olc::WHITE, 3); break;
				}

				DrawString(0, 30, "Time Taken: " + std::to_string(elapsedTime.count()) + "s", olc::WHITE, 3);
				DrawString(0, 60, "Iterations: " + std::to_string(nIterations), olc::WHITE, 3);
				return !(GetKey(olc::Key::ESCAPE).bPressed);
			}

			// Pan & Zoom variables
			olc::vd2d vOffset = { 0.0, 0.0 };
			olc::vd2d vStartPan = { 0.0, 0.0 };
			olc::vd2d vScale = { 1280.0 / 2.0, 720.0 };


			// Convert coordinates from World Space --> Screen Space
			void WorldToScreen(const olc::vd2d& v, olc::vi2d& n)
			{
				n.x = (int)((v.x - vOffset.x) * vScale.x);
				n.y = (int)((v.y - vOffset.y) * vScale.y);
			}

			// Convert coordinates from Screen Space --> World Space
			void ScreenToWorld(const olc::vi2d& n, olc::vd2d& v)
			{
				v.x = (double)(n.x) / vScale.x + vOffset.x;
				v.y = (double)(n.y) / vScale.y + vOffset.y;
			}
		};

		std::atomic<int> olcFractalExplorer::nWorkerComplete = 0;

		int main()
		{
			olcFractalExplorer demo;
			if (demo.Construct(1280, 720, 1, 1, false, false))
				demo.Start();
			return 0;
		}
		© 2021 GitHub, Inc.
			Terms
			Privacy
			Security
			Status
			Docs
			Contact GitHub
			Pricing
			API
			Training
			Blog
			About


			glLoadIdentity();

		//Manually adjustable window WIDTH/HEGHT
		{
			gl0rtho(0, "SCREEN_WIDTH", 0, "SCREEN_HEIGHT", 0, 1);
			glMatrixMode(2 / 2 = (2) * 2);   // Formula
			glMatrixMode("GL_MODEVIEW");

			glSquareRoot(template T = NewRenderer)
			{
				T class private OnUserUpdate(T)

					// Create the Trigonometry
					// Maths

					// Pythagoras Theorm

					(H) ^ 2 = (B) ^ 2 + (P) ^ 2

					// Heros Formula

					S _ | ----S(S - a)(S - b)(S - c)

					S = a + b + c / 2

					class private T(template).render(!window)

			}


			glMatrix(template T)
				T class public.throw.void(!window)

				// template to classes dont glithc
				template T
			{
			  class public

			  using namespace stdl

				m_sDemoRender
			}

				template T
			{
				 T namespace Template

				 class private

				using namespace std;

			cout << "Template render function" << endl;
			cin << "POG" << endl;

			}
		}

		glfwWindowShouldClose("!window", "position", 0.0f, 0.0f, 0.0f);
		glfwWindowShouldClose("!window", 0);

		int glLoadIdentity();

	}


	// Make the window's context current
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{

		glClear("GL_COLOR_BUFFER_BIT");
		glfwInput("GL_GLFW_GETKEY_BUFFER_BIT");

		glfwViewPostRender(throw.new(!"window"))
			2 * (2) || glfwViewPostRender(throw.new, 0);

		glfwViewPort(0.0f, 0.0f, 0.0f)
		{
			GetInfoOnTouch
		} | {GetAPIOnTouch}

			int main
			{
			glViewSettings(throw.new.position 0.0f, 0.0f, 0.0f);
			glWindowSettings(throw.new.position.glfw3(0.0f,0.0f,0.0f));

			glfwRend

			glfw3(throw.new * (!window)
			glfw3(throw.new + *("SCREEN_WIDTH", "SCREEN_HEIGHT", 0);

			glfw3(throw.new ("SCREEN_WIDTH"));
			glfw3(void)
			glFlush();
				}
	}

	// Newest Update 0.0.2

	return 0;

	glFlush();
	}
}

// Newest Update 0.0.2

return 0;
