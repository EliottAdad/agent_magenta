/*
 * Point3D.hpp
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */

#ifndef POINT3D_HPP_

#define POINT3D_HPP_

#include <memory>

#include "utils_SN.hpp"





/**
 * ##############
 *  Point3D<T> :)
 * ##############
 */
template<typename T> struct Point3D {
	T x=(T)0;
	T y=(T)0;
	T z=(T)0;

	Point3D();
	Point3D(const T& x, const T& y, const T& z);
	virtual ~Point3D();
	Point3D(const Point3D<T>& point);//Copy constructor

	//virtual T getX() const;							// :)
	//virtual T getY() const;							// :)
	//virtual T getZ() const;							// :)

	virtual void operator=(const Point3D<T>& p);			// :)
	virtual void operator=(const T& nb);				// :)
	virtual void operator+=(const Point3D<T>& p);			// :)
	virtual void operator+=(const T& nb);				// :)
	virtual void operator-=(const Point3D<T>& p);			// :)
	virtual void operator-=(const T& nb);				// :)
	virtual void operator*=(const T& k);				// :)
	virtual void operator*=(const int& k);				// :)
	virtual void operator*=(const double& k);			// :)
	virtual void operator/=(const T& k);				// :)
	virtual void operator/=(const int& k);				// :)
	virtual void operator/=(const double& k);			// :)
};

template<typename T> bool operator==(const Point3D<T>& p1, const Point3D<T>& p2);		// :)
template<typename T> bool operator==(const Point3D<T>& p, const T& nb);		// :)
//template<typename T> bool operator==(const Point3D<T>& p, const int& nb);		// :)
template<typename T> bool operator==(const T& nb, const Point3D<T>& p);		// :)
//template<typename T> bool operator==(const int& nb, const Point3D<T>& p);		// :)
template<typename T> bool operator!=(const Point3D<T>& p1, const Point3D<T>& p2);		// :)
template<typename T> bool operator!=(const Point3D<T>& p, const T& nb);		// :)
template<typename T> bool operator!=(const T& nb, const Point3D<T>& p);		// :)
template<typename T> bool operator<=(const Point3D<T>& p1, const Point3D<T>& p2);		// :)
template<typename T> bool operator<=(const Point3D<T>& p, const T& nb);		// :)
template<typename T> bool operator<=(const T& nb, const Point3D<T>& p);		// :)
template<typename T> bool operator>=(const Point3D<T>& p1, const Point3D<T>& p2);		// :)
template<typename T> bool operator>=(const Point3D<T>& p, const T& nb);		// :)
template<typename T> bool operator>=(const T& nb, const Point3D<T>& p);		// :)
template<typename T> Point3D<T> operator+(const Point3D<T>& p1, const Point3D<T>& p2);	// :)
template<typename T> Point3D<T> operator-(const Point3D<T>& p1, const Point3D<T>& p2);	// :)
template<typename T> Point3D<T> operator*(const Point3D<T>& p, const T& k);				// :)
template<typename T> Point3D<T> operator*(const Point3D<T>& p, const int& k);			// :)
template<typename T> Point3D<T> operator*(const Point3D<T>& p, const double& k);		// :)
template<typename T> Point3D<T> operator*(const T& k, const Point3D<T>& p);				// :)
template<typename T> Point3D<T> operator*(const int& k, const Point3D<T>& p);			// :)
template<typename T> Point3D<T> operator*(const double& k, const Point3D<T>& p);		// :)
template<typename T> Point3D<T> operator/(const Point3D<T>& p, const T& k);				// :)
template<typename T> Point3D<T> operator/(const Point3D<T>& p, const int& k);			// :)
template<typename T> Point3D<T> operator/(const Point3D<T>& p, const double& k);		// :)

template<typename T> Point3D<T> abs(const Point3D<T>& p);								// :)






template<typename T> inline Point3D<T>::Point3D() {
	this->x=(T)0;
	this->y=(T)0;
	this->z=(T)0;
}

template<typename T> inline Point3D<T>::Point3D(const T& x, const T& y, const T& z) {
	this->x=x;
	this->y=y;
	this->z=z;
}

template<typename T> inline Point3D<T>::~Point3D() {
	// TODO Auto-generated destructor stub
}

template<typename T> inline Point3D<T>::Point3D(const Point3D<T>& point) {
	this->x=point.x;
	this->y=point.y;
	this->z=point.z;
}



/*template<typename T> T Point3D<T>::getX() const {
	return x;
}

template<typename T> T Point3D<T>::getY() const {
	return y;
}

template<typename T> T Point3D<T>::getZ() const {
	return z;
}*/

/*template<typename T> Point3D<T> Point3D<T>::getPosition() const {
	return {x, y, z};
}*/

template<typename T> inline void Point3D<T>::operator=(const Point3D<T>& p) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
}

template<typename T> inline void Point3D<T>::operator=(const T& nb) {
	this->x=nb;
	this->y=nb;
	this->z=nb;
}

template<typename T> inline void Point3D<T>::operator+=(const Point3D<T>& p) {
	this->x+=p.x;
	this->y+=p.y;
	this->z+=p.z;
}

template<typename T> inline void Point3D<T>::operator+=(const T& nb) {
	this->x+=nb;
	this->y+=nb;
	this->z+=nb;
}

template<typename T> inline void Point3D<T>::operator-=(const Point3D<T>& p) {
	this->x-=p.x;
	this->y-=p.y;
	this->z-=p.z;
}

template<typename T> inline void Point3D<T>::operator-=(const T& nb) {
	this->x-=nb;
	this->y-=nb;
	this->z-=nb;
}

template<typename T> inline void Point3D<T>::operator*=(const T& k) {
	this->x*=k;
	this->y*=k;
	this->z*=k;
}

template<typename T> inline void Point3D<T>::operator*=(const int& k) {
	this->x*=k;
	this->y*=k;
	this->z*=k;
}

template<typename T> inline void Point3D<T>::operator*=(const double& k) {
	this->x*=k;
	this->y*=k;
	this->z*=k;
}

template<typename T> inline void Point3D<T>::operator/=(const T& k) {
	this->x/=k;
	this->y/=k;
	this->z/=k;
}

template<typename T> inline void Point3D<T>::operator/=(const int& k) {
	this->x/=k;
	this->y/=k;
	this->z/=k;
}

template<typename T> inline void Point3D<T>::operator/=(const double& k) {
	this->x/=k;
	this->y/=k;
	this->z/=k;
}








template<typename T> inline bool operator==(const Point3D<T>& p1, const Point3D<T>& p2) {
	if (p1.x==p2.x && p1.y==p2.y && p1.z==p2.z){
		return true;
	}
	return false;
}

template<typename T> inline bool operator==(const Point3D<T>& p, const T& nb) {
	if (p.x==nb && p.y==nb && p.z==nb){
		return true;
	}
	return false;
}

template<typename T> inline bool operator==(const T& nb, const Point3D<T>& p) {
	if (nb==p.x && nb==p.y && nb==p.z){
		return true;
	}
	return false;
}

template<typename T> inline bool operator!=(const Point3D<T>& p1, const Point3D<T>& p2) {
	if (p1.x!=p2.x && p1.y!=p2.y && p1.z!=p2.z){
		return true;
	}
	return false;
}

template<typename T> inline bool operator!=(const Point3D<T>& p, const T& nb) {
	if (p.x!=nb && p.y!=nb && p.z!=nb){
		return true;
	}
	return false;
}

template<typename T> inline bool operator!=(const T& nb, const Point3D<T>& p) {
	if (nb!=p.x && nb!=p.y && nb!=p.z){
		return true;
	}
	return false;
}

template<typename T> inline bool operator<=(const Point3D<T>& p1, const Point3D<T>& p2) {
	if (p1.x<=p2.x && p1.y<=p2.y && p1.z<=p2.z){
		return true;
	}
	return false;
}

template<typename T> inline bool operator<=(const Point3D<T>& p, const T& nb) {
	if (p.x<=nb && p.y<=nb && p.z<=nb){
		return true;
	}
	return false;
}

template<typename T> inline bool operator<=(const T& nb, const Point3D<T>& p) {
	if (nb<=p.x && nb<=p.y && nb<=p.z){
		return true;
	}
	return false;
}

template<typename T> inline bool operator>=(const Point3D<T>& p1, const Point3D<T>& p2) {
	if (p1.x>=p2.x && p1.y>=p2.y && p1.z>=p2.z){
		return true;
	}
	return false;
}

template<typename T> inline bool operator>=(const Point3D<T>& p, const T& nb) {
	if (p.x>=nb && p.y>=nb && p.z>=nb){
		return true;
	}
	return false;
}

template<typename T> inline bool operator>=(const T& nb, const Point3D<T>& p) {
	if (nb>=p.x && nb>=p.y && nb>=p.z){
		return true;
	}
	return false;
}

template<typename T> inline Point3D<T> operator+(const Point3D<T>& p1, const Point3D<T>& p2) {
	return Point3D<T>{p1.x+p2.x, p1.y+p2.y, p1.z+p2.z};
}

template<typename T> inline Point3D<T> operator-(const Point3D<T>& p1, const Point3D<T>& p2) {
	return Point3D<T>{p1.x-p2.x, p1.y-p2.y, p1.z-p2.z};
}

template<typename T> inline Point3D<T> operator*(const Point3D<T>& p, const T& k) {
	return Point3D<T>{p.x*k, p.y*k, p.z*k};
}

template<typename T> inline Point3D<T> operator*(const Point3D<T>& p, const int& k) {
	return Point3D<T>{p.x*k, p.y*k, p.z*k};
}

template<typename T> inline Point3D<T> operator*(const Point3D<T>& p, const double& k) {
	return Point3D<T>{p.x*k, p.y*k, p.z*k};
}

template<typename T> inline Point3D<T> operator*(const T& k, const Point3D<T>& p) {
	return Point3D<T>{k*p.x, k*p.y, k*p.z};
}

template<typename T> inline Point3D<T> operator*(const int& k, const Point3D<T>& p) {
	return Point3D<T>{k*p.x, k*p.y, k*p.z};
}

template<typename T> inline Point3D<T> operator/(const Point3D<T>& p, const T& k) {
	return Point3D<T>{p.x/k, p.y/k, p.z/k};
}

template<typename T> inline Point3D<T> operator/(const Point3D<T>& p, const int& k) {
	return Point3D<T>{p.x/k, p.y/k, p.z/k};
}

template<typename T> inline Point3D<T> operator/(const Point3D<T>& p, const double& k) {
	return Point3D<T>{p.x/k, p.y/k, p.z/k};
}

/**
 * Gets the absolute value
 */
template<typename T> inline Point3D<T> abs(const Point3D<T>& p) {
	return Point3D<T>{abs(p.x), abs(p.y), abs(p.z)};
}






/*
 * Functions
 */

/**
 * Computes distance between two points.
 * Uses (0,0,0) as the ref if only one point is provided.
 */
template<typename T> inline T getDistance(const Point3D<T>& p1, const Point3D<T>& p2={(T)0, (T)0, (T)0}) {
	return (T)(sqrt(pow((p1.x-p2.x), 2) + pow((p1.y-p2.y), 2) + pow((p1.z-p2.z), 2)), 0);// d=sqrt( (xA-xB)²+(yA-yB)²+(zA-zB)² )
}

template<typename M, typename E> inline SN<M, E> getDistance(const Point3D<SN<M, E>>& p1, const Point3D<SN<M, E>>& p2={(SN<M, E>)0, (SN<M, E>)0, (SN<M, E>)0}) {
	return SN<M, E>(sqrt(pow((p1.x-p2.x).to_m_type(), 2) + pow((p1.y-p2.y).to_m_type(), 2) + pow((p1.z-p2.z).to_m_type(), 2)), 0);// d=sqrt( (xA-xB)²+(yA-yB)²+(zA-zB)² )
}

/**
 * Returns the points to be rendered.
 */
template<typename T> inline std::unordered_set<std::shared_ptr<Point3D<T>>> pixelizeCircle(std::shared_ptr<Point3D<T>> pcenter, int radius, int spacing=8){
    std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints;

    const int diameter=radius*2;

    T x=(T)(radius-spacing);
    T y=0;
    int tx=spacing;
    int ty=spacing;
    int error=tx-diameter;

    while(x>=y){
        // Each of the following renders an octant of the circle
        ppoints.insert(std::make_shared<Point3D<T>>(pcenter->x+x, pcenter->y-y, T{0, 0}));
        ppoints.insert(std::make_shared<Point3D<T>>(pcenter->x+x, pcenter->y+y, T{0, 0}));
        ppoints.insert(std::make_shared<Point3D<T>>(pcenter->x-x, pcenter->y-y, T{0, 0}));
        ppoints.insert(std::make_shared<Point3D<T>>(pcenter->x-x, pcenter->y+y, T{0, 0}));
        ppoints.insert(std::make_shared<Point3D<T>>(pcenter->x+y, pcenter->y-x, T{0, 0}));
        ppoints.insert(std::make_shared<Point3D<T>>(pcenter->x+y, pcenter->y+x, T{0, 0}));
        ppoints.insert(std::make_shared<Point3D<T>>(pcenter->x-y, pcenter->y-x, T{0, 0}));
        ppoints.insert(std::make_shared<Point3D<T>>(pcenter->x-y, pcenter->y+x, T{0, 0}));

        if(error<=0){
            //++y;
        	y+=(T)spacing;
            error+=ty;
            ty+=2*spacing;
        }

        if(error>0){
            //--x;
        	x-=(T)spacing;
            tx+=2*spacing;
            error+=tx-diameter;
        }
    }

    return ppoints; // RVO FTW
}


#endif /* POINT3D_HPP_ */
