#include "Vector.h"
/* Matrix:
* (a11 a12)
* (a21 a22)
*/
class Matrix{
public:
	Matrix();
	Matrix(float _a11, float _a12, float _a21, float _a22);
	Matrix(Vector v1, Vector v2);
	~Matrix();
	void setMatrix(float _a11, float _a12, float _a21, float _a22);
	void multiplyMatrix(float scalar);
	void multiplyMatrix(Matrix m);
	Vector multipliedVector(Vector v);
	Vector getRow(int row);
private:
	float a11, a12, a21, a22;
};