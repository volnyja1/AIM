#include <stdio.h>

class Vertex
{
public:
	Vertex();
	Vertex(int _x, int _y);
	~Vertex();
	void setVertex(int _x, int _y);
	bool isSelected();
	void setSelected(bool _selected);
	void setDeselected();
	bool isSelectable();
	void setSelectable(bool _selectable);
	void select(int _x, int _y);
	void deselect(int _x, int _y);
	void hit(int _x, int _y);
	void move(int _x, int _y);
	void drawVertex();
	void drawVertex(int col, float r);
	void deleteVertex(int _x, int _y);
	int getX();
	int getY();
private:
	bool selected, selectable;
	int x, y;
	int range;
};