//Extremely simple vector and matrix classes by Janusz Malinowski. 
#include <stdio.h>
#pragma once
class Vector4 {
public:
	double data[4];
	Vector4();
	void Set(double x,double y,double z);
	double GetX();
	double GetY();
	double GetZ();
	Vector4 operator-(const Vector4 &);
	Vector4 operator+(const Vector4&);
	friend Vector4 operator*(const Vector4 &,double);
};

class Matrix4 {
public:
	double data[4][4];
	Matrix4();
	Matrix4 operator*(const Matrix4);
	friend Vector4 operator*(const Matrix4,const Vector4);
};
