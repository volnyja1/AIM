#include "TexCoords.h"

TexCoord::TexCoord(){
	coordX1 = 0;
	coordX2 = 0;
	coordX3 = 1;
	coordX4 = 1;
	coordY1 = 0;
	coordY2 = 1;
	coordY3 = 1;
	coordY4 = 0;
}

TexCoord::~TexCoord(){
}

TexCoord::TexCoord(float _coordX1, float _coordX2, float _coordX3, float _coordX4, float _coordY1, float _coordY2,
		float _coordY3, float _coordY4){
	coordX1 = _coordX1;
	coordX2 = _coordX2;
	coordX3 = _coordX3;
	coordX4 = _coordX4;
	coordY1 = _coordY1;
	coordY2 = _coordY2;
	coordY3 = _coordY3;
	coordY4 = _coordY4;
}

float TexCoord::getCoordX1(){
	return coordX1;
}

float TexCoord::getCoordX2(){
	return coordX2;
}

float TexCoord::getCoordX3(){
	return coordX3;
}

float TexCoord::getCoordX4(){
	return coordX4;
}

float TexCoord::getCoordY1(){
	return coordY1;
}

float TexCoord::getCoordY2(){
	return coordY2;
}

float TexCoord::getCoordY3(){
	return coordY3;
}

float TexCoord::getCoordY4(){
	return coordY4;
}