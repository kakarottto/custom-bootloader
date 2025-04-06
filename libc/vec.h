#pragma once

#include <math.h>

#ifndef PI
#define PI 3.1415926f
#endif

//struct in cpp is really a class with default of public
struct Vec3{
	double x,y,z;
	Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z){}
	Vec3(double x, double y, double z) : x(x), y(y), z(z){}
	Vec3(double f) : x(f), y(f), z(f){}
	
	~Vec3(){}
	//if used as a color. its trivial but its not bad idea to be incluede
	double r(){return x;}
	double g(){return y;}
	double b(){return z;}
	double length2(){
		return x*x+y*y+z*z;
	}
	double length(){
		return sqrt(length2());
	}
	double normalize(){
		double len = length();
		*this /= len;
		return len;
	}
	Vec3 normalised(){
		Vec3 v(x,y,z);
		v.normalize();
		return v;
	}
	
	
	//the needed operators are probably only these
	Vec3& operator =(const Vec3& v){
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	Vec3& operator +=(const Vec3& v){
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vec3& operator -=(const Vec3& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	Vec3& operator *=(const Vec3& v){
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	Vec3& operator /=(double f){
		return *this *= 1/f;
	}
	Vec3 operator -() const{
		return Vec3(-x,-y,-z);
	}
};


inline Vec3 operator +(const Vec3& v1, const Vec3& v2){
	return Vec3(v1.x+v2.x,v1.y+v2.y,v1.z+v2.z);	
}

Vec3 operator -(const Vec3& v1, const Vec3& v2){
	return Vec3(v1.x-v2.x,v1.y-v2.y,v1.z-v2.z);	
}

Vec3 operator *(const Vec3& v1, const Vec3& v2){
	return Vec3(v1.x*v2.x,v1.y*v2.y,v1.z*v2.z);	
}

Vec3 operator /(const Vec3& v1, const Vec3& v2){
	return Vec3(v1.x/v2.x,v1.y/v2.y,v1.z/v2.z);	
}

Vec3 operator *(const Vec3& v1, double f){
	return Vec3(v1.x*f,v1.y*f,v1.z*f);	
}

Vec3 operator *(double f, const Vec3& v1){
	return Vec3(f*v1.x,f*v1.y,f*v1.z);	
}

Vec3 operator /(const Vec3& v1, double f){
	return Vec3(v1.x/f,v1.y/f,v1.z/f);	
}

Vec3 operator /(double f, const Vec3& v1){
	return Vec3(f/v1.x,f/v1.y,f/v1.z);	
}

double dot(Vec3 v1, Vec3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 cross(Vec3 v1, Vec3 v2)
{
	return Vec3(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

Vec3 reflect(const Vec3& v, const Vec3& n){
	return v - 2*dot(v,n)*n;
}

typedef Vec3 Point3;
typedef Point3 Point;
typedef Vec3 Vec;

struct Vec2{
	double x,y;
	
	Vec2() : x(0), y(0) {}
	Vec2(const Vec2& v) : x(v.x), y(v.y) {}
	Vec2(double u, double v) : x(u), y(v){}
	Vec2(double f) : x(f), y(f){}
	
	~Vec2(){}
	 
	 //the needed operators are probably only these
	Vec2& operator =(const Vec2& v){
		x = v.x;
		y = v.y;
		return *this;
	}
	Vec2& operator +=(const Vec2& v){
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2& operator -=(const Vec2& v){
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vec2& operator *=(const Vec2& v){
		x *= v.x;
		y *= v.y;
		return *this;
	}
	Vec2& operator /=(double f){
		x /= f;
		y /= f;
		return *this;
	}
	Vec2 operator -() const{
		return Vec2(-x,-y);
	}
	
	 
};

Vec2 operator +(const Vec2& v1, const Vec2& v2){
	return Vec2(v1.x+v2.x,v1.y+v2.y);	
}

Vec2 operator -(const Vec2& v1, const Vec2& v2){
	return Vec2(v1.x-v2.x,v1.y-v2.y);	
}

Vec2 operator *(const Vec2& v1, const Vec2& v2){
	return Vec2(v1.x*v2.x,v1.y*v2.y);	
}

Vec2 operator /(const Vec2& v1, const Vec2& v2){
	return Vec2(v1.x/v2.x,v1.y/v2.y);	
}

Vec2 operator *(const Vec2& v1, double f){
	return Vec2(v1.x*f,v1.y*f);	
}

Vec2 operator *(double f, const Vec2& v1){
	return Vec2(f*v1.x,f*v1.y);	
}

Vec2 operator /(const Vec2& v1, double f){
	return Vec2(v1.x/f,v1.y/f);	
}

Vec2 operator /(double f, const Vec2& v1){
	return Vec2(f/v1.x,f/v1.y);	
}

double dot(Vec2 v1, Vec2 v2){ 
	return v1.x*v2.x + v1.y*v2.y;	
}

typedef Vec2 Point2;
