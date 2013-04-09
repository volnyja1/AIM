#include <iostream>
#include <vector>
#include <math.h>
#include "glut.h"
#include "../IL/il.h"
#include "../IL/ilu.h"
#include "../IL/ilut.h"
#include "Polygon.h"
#include "TexCoords.h"

using namespace std;

int WIDTH = 640;
int HEIGHT = 480;

enum primitive{
	POLYGON = 0,
	QUAD,
	STRIP,
	FAN,
};

bool edge = false;
bool deselect = false;
bool selectFlag = false;
bool insertFlag = true;
bool drawControlPointsFlag = false;
bool clear = false;
int prim = 0;
int polX = 1;
int polY = 1;

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

ILubyte* imageData;
ILuint texWidth,texHeight;

const float DEG2RAD = 3.14159/180;

vector<MyPolygon> polygons;
vector<Vertex> controlPoints;
vector<Vertex> oldControlPoints;
vector<Vertex> centeredControlPoints;
vector<Vertex> centeredOldControlPoints;
Vertex centroidP, centroidQ;
int original = 0;

void drawCircle(float x, float y, float r, float s);
void recalculatePolygons();

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
		imageData = ilGetData();
		texWidth = ilGetInteger(IL_IMAGE_WIDTH);
		texHeight = ilGetInteger(IL_IMAGE_HEIGHT);
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
	if(selectable){
		float i;
		float s = (3.14 * 2 / 25);
		float r = 3.0f;
		glColor3fv(RED);
		glBegin(GL_POLYGON);
		for(i = 3.14; i >= -3.14; i -= s)
		{
			glVertex2f(x + cos(i) * r, y + sin(i) * r);
		}
		glEnd();
	}
}

void Vertex::drawVertex(GLfloat *col, float r){
		float i;
		float s = (3.14 * 2 / 25);
		glColor3fv(col);
		glBegin(GL_POLYGON);
		for(i = 3.14; i >= -3.14; i -= s)
		{
			glVertex2f(x + cos(i) * r, y + sin(i) * r);
		}
		glEnd();
}

void drawControlPoints(){
		for(unsigned int i = 0; i < oldControlPoints.size(); i++)
			oldControlPoints[i].drawVertex(RED, 3);
		for(unsigned int i = 0; i < controlPoints.size(); i++)
			controlPoints[i].drawVertex(BLUE, 3);
	if(drawControlPointsFlag){
		centroidP.drawVertex(RED, 4);
		centroidQ.drawVertex(BLUE, 4);
	}
}

void MyPolygon::drawPolygon(){
	switch(prim){
		case POLYGON:{
			//cout << "polygon" << endl;
			glColor3fv(WHITE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glBegin(GL_POLYGON);
				//glTexCoord2f(0, 0);
				glTexCoord2f(getTexX0(), getTexY0());
				glVertex2f(vertices[0].getX(),vertices[0].getY());
				//glTexCoord2f(0, 1);
				glTexCoord2f(getTexX0(), getTexY1());
				glVertex2f(vertices[1].getX(),vertices[1].getY());
				//glTexCoord2f(1, 1);
				glTexCoord2f(getTexX1(), getTexY1());
				glVertex2f(vertices[2].getX(),vertices[2].getY());
				//glTexCoord2f(1, 0);
				glTexCoord2f(getTexX1(), getTexY0());
				glVertex2f(vertices[3].getX(),vertices[3].getY());
			glEnd();
			break;
		}
	}

	if(edge){
		switch(prim){
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
	/*
	for(int i=0;i<4;i++)
		vertices[i].drawVertex();
	*/
}

void drawPolygons()
{
	for (unsigned int i=original+1; i<polygons.size(); i++)
		polygons[i].drawPolygon();
}

void setCentroids(){
	int sumPx = 0;
	int sumQx = 0;
	int sumPy = 0;
	int sumQy = 0;
	for(unsigned int i=0; i<controlPoints.size(); i++){
		sumPx += oldControlPoints[i].getX();
		sumPy += oldControlPoints[i].getY();
		sumQx += controlPoints[i].getX();
		sumQy += controlPoints[i].getY();
	}
	centroidP.setVertex(sumPx/controlPoints.size(), sumPy/controlPoints.size());
	centroidQ.setVertex(sumQx/controlPoints.size(), sumQy/controlPoints.size());

	centeredControlPoints.clear();
	centeredOldControlPoints.clear();
	for(unsigned int i=0; i<controlPoints.size(); i++){
		centeredControlPoints.push_back(Vertex(controlPoints[i].getX()-centroidQ.getX(),controlPoints[i].getX()-centroidQ.getX()));
		centeredOldControlPoints.push_back(Vertex(oldControlPoints[i].getX()-centroidP.getX(),oldControlPoints[i].getY()-centroidP.getY()));
	}

}

/**
* Do the magic functions
*/

void AsSimilarAsPossible(){

}

void AsRigidAsPossible(){

}

void MyPolygon::transformPolygon(){
	for(int i=0; i<4; i++){
		for(unsigned int j=0; j<controlPoints.size(); j++){
			float w = 1/sqrt(pow((double)vertices[i].getX()-(double)oldControlPoints[j].getX(),2.0)+pow((double)vertices[i].getY()-(double)oldControlPoints[j].getY(),2.0));
			float mu1 = 0;
			float mu2 = 0;
			float R1 = 0;
			
			
			//vertices[i].move(vertices[i].getX()+(controlPoints[j].getX()-oldControlPoints[j].getX())*w,vertices[i].getY()+(controlPoints[j].getY()-oldControlPoints[j].getY())*w);
		}
		double mu = 1.0;//sqrt(1);
	}
}

void display(void)
{   
    glClearColor (1.0,1.0,1.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
	drawPolygons();
	drawControlPoints();
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

void recalculatePolygons(){
	if(polygons.size() != original+1){
		for(int i=polygons.size(); i>original+1; i--){
			polygons.pop_back();
		}
	}
	for(int i = 0; i <= original; i++){
		int x0 = polygons[i].getV0().getX();
		int y0 = polygons[i].getV0().getY();
		int x1 = polygons[i].getV1().getX();
		int y1 = polygons[i].getV1().getY();
		int x2 = polygons[i].getV2().getX();
		int y2 = polygons[i].getV2().getY();
		int x3 = polygons[i].getV3().getX();
		int y3 = polygons[i].getV3().getY();
		int divX = (x2-x0)/polX;
		int divY = (y1-y0)/polY;
		for(int j=0; j<polX; j++){
			for(int k=0; k<polY; k++){
				bool draw = true;
				/*bool draw = false;
				for(int r = j*(1.0f/(float)polX)*texWidth; r < (j+1)*(1.0f/(float)polX)*texWidth; r++){
					if(!draw){
						for(int s = k*(1.0f/(float)polY)*texHeight; s < (k+1)*(1.0f/(float)polY)*texHeight; s++){
							if(!draw){
								cout << (int)imageData[(r*texWidth + s)*4 + 0] << " " << (int)imageData[(r*texWidth + s)*4 + 1] << " " << (int)imageData[(r*texWidth + s)*4 + 2] << endl;
								if((int)imageData[(r*texWidth + s)*4 + 0] != 255 || (int)imageData[(r*texWidth + s)*4 + 1] != 255 || (int)imageData[(r*texWidth + s)*4 + 2] != 255)
									draw = true;
							}
						}
					}
				}*/
				if(draw)
					polygons.push_back(MyPolygon(Vertex(x0+j*divX,y0+k*divY),
												 Vertex(x0+j*divX,y0+(k+1)*divY),
												 Vertex(x0+(j+1)*divX,y0+(k+1)*divY),
												 Vertex(x0+(j+1)*divX,y0+k*divY),
											 
												 (float)j*(1.0f/(float)polX), // s0
												 (float)k*(1.0f/(float)polY), // t0
												 (float)(j+1)*(1.0f/(float)polX),   // s1
												 (float)(k+1)*(1.0f/(float)polY))); // t1
			}
		}
		cout << "Pocet polygonu: " << polygons.size()-1 << endl;
	}
	
	/*printf( "%s\n", "Red Value for Pixel");
	printf( "%d\n", imageData[(80*texWidth + 80)*4 + 0]);
	printf( "%s\n", "Green Value for Pixel");
	printf( "%d\n", imageData[(80*texWidth + 80)*4 + 1]);
	printf( "%s\n", "Blue Value for Pixel");
	printf( "%d\n", imageData[(80*texWidth + 80)*4 + 2]);*/
	//cout << (int)imageData[(80*texWidth + 80)*4 + 0] << " " << (int)imageData[(80*texWidth + 80)*4 + 0] << " " << (int)imageData[(80*texWidth + 80)*4 + 0] << endl;
	/*for (int i = 0; i < height; i++)
	{
		for (int j = 0; i < width; j++)
		{
			printf( "%s\n", "Red Value for Pixel");
			printf( "%d\n", bytes[(i*width + j)*4 + 0]); 
			printf( "%s\n", "Green Value for Pixel");
			printf( "%d\n", bytes[(i*width + j)*4 + 1]);
			printf( "%s\n", "Blue Value for Pixel");
			printf( "%d\n", bytes[(i*width + j)*4 + 2]);
		}
	}*/
	/*int width = 1;
	int height = 1;
	GLbyte data[4];
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &data);
	cout << data[0] << " " << data[1] << " " << data[2] << " " << data[3] << " " << endl;*/
	glutPostRedisplay();
}

void transformPolygons(){
	for(unsigned int i=original+1; i<polygons.size(); i++)
		polygons[i].transformPolygon();
	// set the new position
	for(unsigned int j=0; j<controlPoints.size(); j++)
		oldControlPoints[j].setVertex(controlPoints[j].getX(), controlPoints[j].getY());
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
	case 'q' : exit(0); break;
	case 'e' : edge = !edge; glutPostRedisplay(); break;
	case 'd' : deselect = !deselect; glutPostRedisplay(); break;
	case 's' : selectFlag = !selectFlag; glutPostRedisplay(); break;
	case 'c' : drawControlPointsFlag = !drawControlPointsFlag; glutPostRedisplay(); break;
	case 'a' : /*prim = (prim==3)?0:prim+1;*/ break;
	case 'n' : cout << x << " " << y << endl; break;
	case 'm' : cout << x << " " << y << endl; break;
	case 'i' : insertFlag = !insertFlag; break;
	case 'X' : polX++; recalculatePolygons(); break;
	case 'x' : polX = (polX==1)?1:polX-1; recalculatePolygons(); break;
	case 'Y' : polY++; recalculatePolygons(); break;
	case 'y' : polY = (polY==1)?1:polY-1; recalculatePolygons(); break;
    }
}

void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)   
    {
		if(insertFlag){
			controlPoints.push_back(Vertex(x,y*1.03));
			oldControlPoints.push_back(Vertex(x,y*1.03));
			setCentroids();
		} else {
			for (unsigned int i=0; i<controlPoints.size(); i++)
				controlPoints[i].hit(x,y*1.03);
		}
        glutPostRedisplay();
    }
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_UP)   
    {
		for (unsigned int i=0; i<controlPoints.size(); i++)
			controlPoints[i].setDeselected();
		setCentroids();
		transformPolygons();
        glutPostRedisplay();
    }
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)   
    {
		for (unsigned int i=0; i<controlPoints.size(); i++)
				controlPoints[i].deselect(x,y*1.03);
		clear = true;
		glutPostRedisplay();
    }
}

void mouseMotion(int x, int y){
	for (unsigned int i=0; i<controlPoints.size(); i++)
		controlPoints[i].move(x,y*1.03);
	setCentroids();
	transformPolygons();
	glutPostRedisplay();
}

void init(){
	loadTextures();
	polygons.push_back(MyPolygon());
	recalculatePolygons();
}

void idle(){
	if(clear){
		vector<Vertex> temp;
		for (unsigned int i=0; i<controlPoints.size(); i++)
			if(controlPoints[i].isSelectable())
				temp.push_back(controlPoints[i]);
		controlPoints.clear();
		oldControlPoints.clear();
		for (unsigned int i=0; i<temp.size(); i++){
			controlPoints.push_back(temp[i]);
			oldControlPoints.push_back(temp[i]);
		}
		clear = false;
		setCentroids();
	}
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
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	init();
    glutMainLoop();
}