#include <iostream>
#include <vector>
#include "glut.h"
#include "../IL/il.h"
#include "../IL/ilu.h"
#include "../IL/ilut.h"
#include "Polygon.h"

using namespace std;

int WIDTH = 640;
int HEIGHT = 480;

enum primitive{
	QUAD = 0,
	STRIP,
	FAN,
	POLYGON
};

bool edge = false;
int prim = 0;

GLuint textureID;

GLfloat SIDE=50;
GLfloat RED[3] = {1,0,0};
GLfloat GREEN[3] = {0,1,0};
GLfloat BLUE[3] = {0,0,1};
GLfloat WHITE[3] = {1,1,1};
GLfloat BLACK[3] = {0,0,0};
GLfloat YELLOW[3] = {1,1,0};
GLfloat CYAN[3] = {0,1,1};
GLfloat MAGENTA[3] = {1,0,1};

const float DEG2RAD = 3.14159/180;

vector<MyPolygon> polygons;

void drawCircle(float x, float y, float r, float s);

int loadTextures(){
	cout << "Texture creation..." << endl;
	ilInit();
	ILuint imageID;				// Create an image ID as a ULuint
	ILboolean success;			// Create a flag to keep track of success/failure
	ILenum error;				// Create a flag to keep track of the IL error state
	ilGenImages(1, &imageID); 		// Generate the image ID
	ilBindImage(imageID); 			// Bind the image
	string path = "../data/homer2.jpg";
	success = ilLoadImage((const ILstring)path.c_str()); 	// Load the image file
 
	// If we managed to load the image, then we can start to do things with it...
	if (success)
	{
		// If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			//iluFlipImage();
		}
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		if (!success)
		{
			error = ilGetError();
			std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
			exit(-1);
		}

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		
		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 
		// Set texture interpolation method to use linear interpolation (no MIPMAPS)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Specify the texture specification
		glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
						0,				// Pyramid level (for mip-mapping) - 0 is the top level
						ilGetInteger(IL_IMAGE_BPP),	// Image colour depth
						ilGetInteger(IL_IMAGE_WIDTH),	// Image width
						ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
						0,				// Border width in pixels (can either be 1 or 0)
						ilGetInteger(IL_IMAGE_FORMAT),	// Image format (i.e. RGB, RGBA, BGR etc.)
						GL_UNSIGNED_BYTE,		// Image data type
						ilGetData());			// The actual image data itself
		
 	}
  	else // If we failed to open the image file in the first place...
  	{
		error = ilGetError();
		cout << "Image load failed - IL reports error: " << error << " - " << iluErrorString(error) << endl;
		system("pause");
		exit(-1);
  	}
 	//ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.
	cout << "Texture creation successful." << endl;
	return textureID; // Return the GLuint to the texture so you can use it!
}

void Vertex::drawVertex(){
    float i;
    float s = (3.14 * 2 / 25);
	float r = 2.0f;
	glColor3fv(RED);
    glBegin(GL_POLYGON);
    for(i = 3.14; i >= -3.14; i -= s)
    {
        glVertex2f(x + cos(i) * r, y + sin(i) * r);
    }
    glEnd();
}

void MyPolygon::drawPolygon(){
	switch(prim){
		case POLYGON:{
			//cout << "polygon" << endl;
			glColor3fv(WHITE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, 0);
				glVertex2f(vertices[0].getX(),vertices[0].getY());
				glTexCoord2f(0, 1);
				glVertex2f(vertices[1].getX(),vertices[1].getY());
				glTexCoord2f(1, 1);
				glVertex2f(vertices[2].getX(),vertices[2].getY());
				glTexCoord2f(1, 0);
				glVertex2f(vertices[3].getX(),vertices[3].getY());
			glEnd();
			break;
		}

		case FAN:{
			//cout << "fan" << endl;
			glColor3fv(WHITE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f(0, 0);
				glVertex2f(vertices[0].getX(),vertices[0].getY());
				glTexCoord2f(0, 1);
				glVertex2f(vertices[1].getX(),vertices[1].getY());
				glTexCoord2f(1, 1);
				glVertex2f(vertices[2].getX(),vertices[2].getY());
				glTexCoord2f(1, 0);
				glVertex2f(vertices[3].getX(),vertices[3].getY());
			glEnd();
			break;
		}

		case STRIP:{
			//cout << "strip" << endl;
			glColor3fv(WHITE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f(0, 0);
				glVertex2f(vertices[0].getX(),vertices[0].getY());
				glTexCoord2f(0, 1);
				glVertex2f(vertices[1].getX(),vertices[1].getY());
				glTexCoord2f(1, 1);
				glVertex2f(vertices[2].getX(),vertices[2].getY());
				glTexCoord2f(1, 0);
				glVertex2f(vertices[3].getX(),vertices[3].getY());
			glEnd();
			break;
		}

		case QUAD:{
			//cout << "quad" << endl;
			glColor3fv(WHITE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);
				glVertex2f(vertices[0].getX(),vertices[0].getY());
				glTexCoord2f(0, 1);
				glVertex2f(vertices[1].getX(),vertices[1].getY());
				glTexCoord2f(1, 1);
				glVertex2f(vertices[2].getX(),vertices[2].getY());
				glTexCoord2f(1, 0);
				glVertex2f(vertices[3].getX(),vertices[3].getY());
			glEnd();
			break;
		}
	}

	if(edge){
		switch(prim){
			case FAN:
			case STRIP:{
				glColor3fv(BLACK);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glBegin(GL_TRIANGLE_FAN);
					glVertex2f(vertices[0].getX(),vertices[0].getY());
					glVertex2f(vertices[1].getX(),vertices[1].getY());
					glVertex2f(vertices[2].getX(),vertices[2].getY());
					glVertex2f(vertices[3].getX(),vertices[3].getY());
				glEnd();
				break;
			}

			case POLYGON:
			case QUAD:{
				glColor3fv(BLACK);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glBegin(GL_POLYGON);
					glVertex2f(vertices[0].getX(),vertices[0].getY());
					glVertex2f(vertices[1].getX(),vertices[1].getY());
					glVertex2f(vertices[2].getX(),vertices[2].getY());
					glVertex2f(vertices[3].getX(),vertices[3].getY());
				glEnd();
				break;
			}
		}
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_TEXTURE_2D);
	for(int i=0;i<4;i++)
		vertices[i].drawVertex();
}

void drawPolygons()
{
	for (unsigned int i=0; i<polygons.size(); i++)
		polygons[i].drawPolygon();
}

void drawCircle(float x, float y, float r, float s)
{
    if(s >= 3)
    {
        float i;
        s = (3.14 * 2 / s);
		glColor3fv(WHITE);
        glBegin(GL_POLYGON);    
        for(i = 3.14; i >= -3.14; i -= s)
        {
            glVertex2f(x + cos(i) * r, y + sin(i) * r);
        }
        glEnd();
		glColor3fv(RED);
		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1);
		glBegin(GL_LINE_LOOP);
        for(i = 3.14; i >= -3.14; i -= s)
        {
            glVertex2f(x + cos(i) * r, y + sin(i) * r);
        }
        glEnd();
    }
}

void display(void)
{   
    glClearColor (1.0,1.0,1.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
	drawPolygons();
    glFlush();
}

void reshape(int w, int h)
{   
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,1368,768,0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void spindisplay(void)
{       
    //glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
	case 'q' : exit(0); break;
	case 'e' : edge = !edge; cout << edge << endl; break;
	case 'a' : prim = (prim==3)?0:prim+1; break;
    }
}


void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)   
    {
		for (unsigned int i=0; i<polygons.size(); i++)
			polygons[i].hit(x,y*1.04);
        glutPostRedisplay();
    }
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_UP)   
    {
		for (unsigned int i=0; i<polygons.size(); i++)
			polygons[i].move(x,y*1.04);
        glutPostRedisplay();
    }
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)   
    {
        exit(1);   // To Exit the Program
    }
}

void init(){
	loadTextures();
	polygons.push_back(MyPolygon());
}

int main(int argc, char **argv)
{   
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1366,768);
    glutInitWindowPosition(0,0);
    glutCreateWindow("AIM - Homer");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
    glutIdleFunc(spindisplay);
	init();
    glutMainLoop();
}