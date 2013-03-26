#include "Polygon.h"

MyPolygon::MyPolygon(){
	vertices[0] = Vertex(100,100);
	vertices[1] = Vertex(100,600);
	vertices[2] = Vertex(600,600);
	vertices[3] = Vertex(600,100);
	texX0 = 0;
	texX1 = 1;
	texY0 = 0;
	texY1 = 1;
}

MyPolygon::MyPolygon(Vertex v0, Vertex v1, Vertex v2, Vertex v3){
	vertices[0] = v0;
	vertices[1] = v1;
	vertices[2] = v2;
	vertices[3] = v3;
}

MyPolygon::MyPolygon(Vertex v0, Vertex v1, Vertex v2, Vertex v3,float _texX0, float _texY0, float _texX1, float _texY1){
	vertices[0] = v0;
	vertices[1] = v1;
	vertices[2] = v2;
	vertices[3] = v3;
	texX0 = _texX0;
	texX1 = _texX1;
	texY0 = _texY0;
	texY1 = _texY1;
}

MyPolygon::~MyPolygon(){

}

void MyPolygon::hit(int _x, int _y){
	for(int i=0;i<4;i++)
		vertices[i].hit(_x, _y);
}

void MyPolygon::select(int _x, int _y){
	for(int i=0;i<4;i++)
		vertices[i].select(_x, _y);
}

void MyPolygon::deselect(int _x, int _y){
	for(int i=0;i<4;i++)
		vertices[i].deselect(_x, _y);
}

void MyPolygon::move(int _x, int _y){
	for(int i=0;i<4;i++)
		if(vertices[i].isSelected())
			vertices[i].move(_x, _y);
}

Vertex MyPolygon::getV0(){
	return vertices[0];
}

Vertex MyPolygon::getV1(){
	return vertices[1];
}

Vertex MyPolygon::getV2(){
	return vertices[2];
}

Vertex MyPolygon::getV3(){
	return vertices[3];
}

void MyPolygon::setTex(float _texX0, float _texY0, float _texX1, float _texY1){
	texX0 = _texX0;
	texX1 = _texX1;
	texY0 = _texY0;
	texY1 = _texY1;
}

float MyPolygon::getTexX0(){
	return texX0;
}

float MyPolygon::getTexX1(){
	return texX1;
}

float MyPolygon::getTexY0(){
	return texY0;
}

float MyPolygon::getTexY1(){
	return texY1;
}