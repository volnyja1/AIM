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
	Matrix(Vector v1, Vector v2, int i);
	~Matrix();
	void setMatrix(float _a11, float _a12, float _a21, float _a22);
	void multiplyMatrix(float scalar);
	void multiplyMatrixRight(Matrix m);
	void multiplyMatrixLeft(Matrix m);
	void addMatrix(Matrix m);
	Matrix multipliedMatrix(float scalar);
	Matrix addedMatrix(Matrix m);
	Vector multipliedVector(Vector v);
	Vector getRow(int row);
	void write();
	float a11, a12, a21, a22;
};