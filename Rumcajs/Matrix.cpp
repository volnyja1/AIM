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

void Matrix::multiplyMatrix(Matrix m){

}

/*Vector Matrix::multipliedVector(Vector v){
	return NULL;
}*/

Vector Matrix::getRow(int row){
	return row==1?Vector(a11,a12):Vector(a21,a22);
}