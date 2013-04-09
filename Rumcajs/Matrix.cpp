#include "Matrix.h"

Matrix::Matrix(){
	a11 = 0;
	a12 = 0;
	a21 = 0;
	a22 = 0;
}

Matrix::Matrix(float _a11, float _a12, float _a21, float _a22){
	a11 = _a11;
	a12 = _a12;
	a21 = _a21;
	a22 = _a22;
}

Matrix::Matrix(Vector v1, Vector v2){
	a11 = v1.getX();
	a12 = v1.getY();
	a21 = v2.getX();
	a22 = v2.getY();
}

Matrix::Matrix(Vector v1, Vector v2, int i){
	a11 = v1.getX();
	a12 = v2.getX();
	a21 = v1.getY();
	a22 = v2.getY();
}
	
Matrix::~Matrix(){}

void Matrix::setMatrix(float _a11, float _a12, float _a21, float _a22){
	a11 = _a11;
	a12 = _a12;
	a21 = _a21;
	a22 = _a22;
}

void Matrix::multiplyMatrix(float scalar){
	a11 *= scalar;
	a12 *= scalar;
	a21 *= scalar;
	a22 *= scalar;
}

Matrix Matrix::multipliedMatrix(float scalar){
	return Matrix(a11*scalar, a12*scalar, a21*scalar, a22*scalar);
}

void Matrix::multiplyMatrixRight(Matrix m){
	a11 = a11*m.a11+a12*m.a21;
	a12 = a11*m.a12+a12*m.a22;
	a21 = a21*m.a11+a22*m.a21;
	a22 = a21*m.a12+a22*m.a22;
}

void Matrix::multiplyMatrixLeft(Matrix m){
	a11 = m.a11*a11+m.a12*a21;
	a12 = m.a11*a12+m.a12*a22;
	a21 = m.a21*a11+m.a22*a21;
	a22 = m.a21*a12+m.a22*a22;
}

void Matrix::addMatrix(Matrix m){
	a11 += m.a11;
	a12 += m.a12;
	a21 += m.a21;
	a22 += m.a22;
}

Matrix Matrix::addedMatrix(Matrix m){
	return Matrix(a11+m.a11, a12+m.a12, a21+m.a21, a22+m.a22);
}

Vector Matrix::multipliedVector(Vector v){
	return Vector(v.getX()*a11+v.getY()*a12, v.getX()*a21+v.getY()*a22);
}

Vector Matrix::getRow(int row){
	return row==1?Vector(a11,a12):Vector(a21,a22);
}

void Matrix::write(){
	printf("%d %d\n%d %d\n\n",a11,a12,a21,a22);
}