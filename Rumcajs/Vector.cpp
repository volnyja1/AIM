#include "Vector.h"

Vector::Vector(){
	x = 0;
	y = 0;
}

Vector::Vector(float _x, float _y){
	x = _x;
	y = _y;
}

Vector::~Vector(){}

void Vector::setVector(float _x, float _y){
	x = _x;
	y = _y;
}

void Vector::addVector(Vector v){
	x += v.getX();
	y += v.getY();
}

Vector Vector::addedVector(Vector v){
	return Vector(x+v.getX(), y+v.getY());
}

Vector Vector::perpendicularVector(){
	return Vector(y, -x);
}

float Vector::dotProduct(Vector v){
	return x*v.getX() + y*v.getY();
}

float Vector::getX(){
	return x;
}

float Vector::getY(){
	return y;
}