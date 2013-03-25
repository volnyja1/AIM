#include "Polygon.h"

MyPolygon::MyPolygon(){
	vertices[0] = Vertex(100,100);
	vertices[1] = Vertex(100,600);
	vertices[2] = Vertex(600,600);
	vertices[3] = Vertex(600,100);
}

MyPolygon::~MyPolygon(){

}

void MyPolygon::hit(int _x, int _y){
	for(int i=0;i<4;i++)
		vertices[i].hit(_x, _y);
}

void MyPolygon::move(int _x, int _y){
	for(int i=0;i<4;i++)
		if(vertices[i].isSelected())
			vertices[i].move(_x, _y);
}