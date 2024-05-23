#include "vecmat.h"

Vector4::Vector4() {
	data[0]=0.0; data[1]=0.0; data[2]=0.0; data[3]=1.0;
}

void Vector4::Set(double x,double y,double z) {
	data[0]=x; data[1]=y; data[2]=z;
}

double Vector4::GetX() {
	return data[0];
}

double Vector4::GetY() {
	return data[1];
}

double Vector4::GetZ() {
	return data[2];
}

Vector4 Vector4::operator- (const Vector4 &gVector) {
	unsigned int i;
	Vector4 Result;
	for (i=0;i<4;i++) Result.data[i]=data[i]-gVector.data[i];
	return Result;
}

Vector4 Vector4::operator+ (const Vector4& gVector) {
	unsigned int i;
	Vector4 Result;
	for (i = 0; i < 4; i++) Result.data[i] = data[i] + gVector.data[i];
	return Result;
}

Vector4 operator* (const Vector4 &gVector,double val) {
	unsigned int i;
	Vector4 Result;
	for (i=0;i<4;i++) Result.data[i]=gVector.data[i]*val;
	return Result;
}

Matrix4::Matrix4() {
	data[0][0]=0.0; data[0][1]=0.0; data[0][2]=0.0; data[0][3]=0.0;
	data[1][0]=0.0; data[1][1]=0.0; data[1][2]=0.0; data[1][3]=0.0;
	data[2][0]=0.0; data[2][1]=0.0; data[2][2]=0.0; data[2][3]=0.0;
	data[3][0]=0.0; data[3][1]=0.0; data[3][2]=0.0; data[3][3]=1.0;
}

Matrix4 Matrix4::operator* (const Matrix4 gMatrix) {
	Matrix4 tmp;

	for (int i=0; i<4; i++)
	for (int j=0; j<4; j++) {
		tmp.data[i][j] = 0.0;
		for (int k=0; k<4; k++)
		tmp.data[i][j] = tmp.data[i][j] + (data[i][k] * gMatrix.data[k][j]);
	}
	return tmp;
}

Vector4 operator* (const Matrix4 gMatrix,const Vector4 gVector) {
	Vector4 tmp;

	for (int i=0; i<4; i++) {
		tmp.data[i]=0.0;
		for (int j=0; j<4; j++) tmp.data[i]=tmp.data[i]+(gMatrix.data[i][j]*gVector.data[j]);
	}
	return tmp;
}
