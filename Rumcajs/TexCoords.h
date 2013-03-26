class TexCoord{
public:
	TexCoord();
	TexCoord(float _coordX1, float _coordX2, float _coordX3, float _coordX4, float _coordY1, float _coordY2,
		float _coordY3, float _coordY4);
	~TexCoord();
	float getCoordX1();
	float getCoordX2();
	float getCoordX3();
	float getCoordX4();
	float getCoordY1();
	float getCoordY2();
	float getCoordY3();
	float getCoordY4();
private:
	float coordX1, coordX2, coordX3, coordX4, coordY1, coordY2, coordY3, coordY4;
};