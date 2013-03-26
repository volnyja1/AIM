#include "Vertex.h"

Vertex::Vertex(){
	x = 0;
	y = 0;
	range = 20;
}

Vertex::~Vertex(){
}

Vertex::Vertex(int _x, int _y){
	x = _x;
	y = _y;
	range = 20;
}

void Vertex::setVertex(int _x, int _y){
	x = _x;
	y = _y;
}

int Vertex::getX(){
	return x;
}

int Vertex::getY(){
	return y;
}

void Vertex::hit(int _x, int _y){
	if(_x > x-range && _x < x+range && _y > y-range && _y < y+range){
		setSelected(true);
	} else {
		setSelected(false);
	}
}

void Vertex::select(int _x, int _y){
	if(_x > x-range && _x < x+range && _y > y-range && _y < y+range){
		setSelectable(true);
	}
}

void Vertex::deselect(int _x, int _y){
	if(_x > x-range && _x < x+range && _y > y-range && _y < y+range){
		setSelectable(false);
	}
}

void Vertex::move(int _x, int _y){
	x = _x;
	y = _y;
	setSelected(false);
}

bool Vertex::isSelected(){
	return selected;
}

void Vertex::setSelected(bool _selected){
	if(selectable)
		selected = _selected;
}

void Vertex::setSelectable(bool _selectable){
	selectable = _selectable;
}