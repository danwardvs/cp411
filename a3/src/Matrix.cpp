
#include "Matrix.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

Matrix::Matrix() {
	loadIdentity();
}

// mat <- identity matrix
void Matrix::loadIdentity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}
}

// multiplication  mat <- m * mat
void Matrix::matrixPreMultiply(Matrix* m) {
	GLint row, col;
	GLfloat matTemp[4][4];  
	for (row = 0; row < 4; row++)
		for (col = 0; col < 4; col++)
			matTemp[row][col] = mat[row][0] * m->mat[0][col] + mat[row][1] * m->mat[1][col] + mat[row][2] * m->mat[2][col] + mat[row][3] * m->mat[3][col];
	for (row = 0; row < 4; row++)
		for (col = 0; col < 4; col++)
			m->mat[row][col] = matTemp[row][col];
}

// transpose  mat <- mat'
void Matrix::transpose() {
	GLint row, col;
	GLfloat temp;
	for (row = 0; row < 4; row++)
		for (col = row+1; col < 4; col++) {
			temp = mat[row][col];
			mat[row][col] = mat[col][row];
			mat[col][row] = temp;
		}
	}

// normalize MC
void Matrix::normalize() {
	// add code here
}

// v  <- mat * v
void Matrix::multiplyVector(GLfloat* v) {
	GLfloat sum, temp[4];
	for (int i = 0; i < 4; i++) {
	sum = 0;
	for (int j = 0; j < 4; j++) {
	sum += mat[i][j] * v[j];
	}
	temp[i] = sum;
	}
	for (int i = 0; i < 4; i++) {
	v[i] = temp[i];
	};
}

void Matrix::rotateMatrix(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
// add code here
}



