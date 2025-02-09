/*
 * Point2D.h
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */

#ifndef POINT2D_H_

#define POINT2D_H_

#include <memory>

#include "SN.h"
#include "../utilities/Printable.h"





/*
 * ##############
 *  Point2D<T> :)
 * ##############
 */
template<typename T> struct Point2D : public Printable {
	T x;
	T y;

	Point2D();
	Point2D(const T& x, const T& y);
	virtual ~Point2D();
	Point2D(const Point2D<T>& point);//Copy constructor

	virtual T getX() const;							// :)
	virtual T getY() const;							// :)

	virtual void operator=(const Point2D<T>& p);			// :)
	virtual void operator=(const T& nb);				// :)
	virtual void operator+=(const Point2D<T>& p);			// :)
	virtual void operator+=(const T& nb);				// :)
	virtual void operator-=(const Point2D<T>& p);			// :)
	virtual void operator-=(const T& nb);				// :)
	virtual void operator*=(const T& k);				// :)
	virtual void operator*=(const int& k);				// :)
	virtual void operator/=(const T& k);				// :)
	virtual void operator/=(const int& k);				// :)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

template<typename T> bool operator==(const Point2D<T>& p1, const Point2D<T>& p2);		// :)
template<typename T> bool operator==(const Point2D<T>& p, const T& nb);		// :)
template<typename T> bool operator==(const T& nb, const Point2D<T>& p);		// :)
template<typename T> bool operator!=(const Point2D<T>& p1, const Point2D<T>& p2);		// :)
template<typename T> bool operator!=(const Point2D<T>& p, const T& nb);		// :)
template<typename T> bool operator!=(const T& nb, const Point2D<T>& p);		// :)
template<typename T> bool operator<=(const Point2D<T>& p1, const Point2D<T>& p2);		// :)
template<typename T> bool operator<=(const Point2D<T>& p, const T& nb);		// :)
template<typename T> bool operator<=(const T& nb, const Point2D<T>& p);		// :)
template<typename T> bool operator>=(const Point2D<T>& p1, const Point2D<T>& p2);		// :)
template<typename T> bool operator>=(const Point2D<T>& p, const T& nb);		// :)
template<typename T> bool operator>=(const T& nb, const Point2D<T>& p);		// :)
template<typename T> Point2D<T> operator+(const Point2D<T>& p1, const Point2D<T>& p2);	// :)
template<typename T> Point2D<T> operator-(const Point2D<T>& p1, const Point2D<T>& p2);	// :)
template<typename T> Point2D<T> operator*(const Point2D<T>& p, const T& k);			// :)
template<typename T> Point2D<T> operator*(const Point2D<T>& p, const int& k);			// :)
template<typename T> Point2D<T> operator*(const T& k, const Point2D<T>& p);			// :)
template<typename T> Point2D<T> operator*(const int& k, const Point2D<T>& p);			// :)
template<typename T> Point2D<T> operator/(const Point2D<T>& p, const T& k);			// :)
template<typename T> Point2D<T> operator/(const Point2D<T>& p, const int& k);			// :)
template<typename T> Point2D<T> abs(const Point2D<T>& p);	// :)




template<typename T> Point2D<T>::Point2D() {
	this->x=T{0,0};
	this->y=T{0,0};
}

template<typename T> Point2D<T>::Point2D(const T& x, const T& y, const T& z) {
	this->x=x;
	this->y=y;
}

template<typename T> Point2D<T>::~Point2D() {
	// TODO Auto-generated destructor stub
}

template<typename T> Point2D<T>::Point2D(const Point2D<T>& point) {
	this->x=point.x;
	this->y=point.y;
}



template<typename T> T Point2D<T>::getX() const {
	return x;
}

template<typename T> T Point2D<T>::getY() const {
	return y;
}

/*template<typename T> Point2D<T> Point2D<T>::getPosition() const {
	return {x, y, z};
}*/

template<typename T> void Point2D<T>::operator=(const Point2D<T>& p) {
	this->x=p.x;
	this->y=p.y;
}

template<typename T> void Point2D<T>::operator=(const T& nb) {
	this->x=nb;
	this->y=nb;
}

template<typename T> void Point2D<T>::operator+=(const Point2D<T>& p) {
	this->x+=p.x;
	this->y+=p.y;
}

template<typename T> void Point2D<T>::operator+=(const T& nb) {
	this->x+=nb;
	this->y+=nb;
}

template<typename T> void Point2D<T>::operator-=(const Point2D<T>& p) {
	this->x-=p.x;
	this->y-=p.y;
}

template<typename T> void Point2D<T>::operator-=(const T& nb) {
	this->x-=nb;
	this->y-=nb;
}

template<typename T> void Point2D<T>::operator*=(const T& k) {
	this->x*=k;
	this->y*=k;
}

template<typename T> void Point2D<T>::operator*=(const int& k) {
	this->x*=k;
	this->y*=k;
}

template<typename T> void Point2D<T>::operator/=(const T& k) {
	this->x/=k;
	this->y/=k;
}

template<typename T> void Point2D<T>::operator/=(const int& k) {
	this->x/=k;
	this->y/=k;
}





template<typename T> std::string Point2D<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	//std::cout<<"Help1\n";
	std::string mes=((spread)?"\n" : "");
	mes+=to_stringTabs(indent);
	//printf("Help2\n");
	if (full_info){
		mes+="Point2D[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" + to_stringTabs(1) : "");
	}
	//printf("Help3\n");
	mes+=to_stringTabs(indent);
	mes+="(x:" + x.to_string(false, false, 0) + " ; y:" + y.to_string(false, false, 0) + ")";

	return mes;
}

template<typename T> void Point2D<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}






template<typename T> bool operator==(const Point2D<T>& p1, const Point2D<T>& p2) {
	if (p1.x==p2.x && p1.y==p2.y){
		return true;
	}
	return false;
}

template<typename T> bool operator==(const Point2D<T>& p, const T& nb) {
	if (p.x==nb && p.y==nb){
		return true;
	}
	return false;
}

template<typename T> bool operator==(const T& nb, const Point2D<T>& p) {
	if (nb==p.x && nb==p.y){
		return true;
	}
	return false;
}

template<typename T> bool operator!=(const Point2D<T>& p1, const Point2D<T>& p2) {
	if (p1.x!=p2.x && p1.y!=p2.y){
		return true;
	}
	return false;
}

template<typename T> bool operator!=(const Point2D<T>& p, const T& nb) {
	if (p.x!=nb && p.y!=nb){
		return true;
	}
	return false;
}

template<typename T> bool operator!=(const T& nb, const Point2D<T>& p) {
	if (nb!=p.x && nb!=p.y){
		return true;
	}
	return false;
}

template<typename T> bool operator<=(const Point2D<T>& p1, const Point2D<T>& p2) {
	if (p1.x<=p2.x && p1.y<=p2.y){
		return true;
	}
	return false;
}

template<typename T> bool operator<=(const Point2D<T>& p, const T& nb) {
	if (p.x<=nb && p.y<=nb){
		return true;
	}
	return false;
}

template<typename T> bool operator<=(const T& nb, const Point2D<T>& p) {
	if (nb<=p.x && nb<=p.y){
		return true;
	}
	return false;
}

template<typename T> bool operator>=(const Point2D<T>& p1, const Point2D<T>& p2) {
	if (p1.x>=p2.x && p1.y>=p2.y){
		return true;
	}
	return false;
}

template<typename T> bool operator>=(const Point2D<T>& p, const T& nb) {
	if (p.x>=nb && p.y>=nb){
		return true;
	}
	return false;
}

template<typename T> bool operator>=(const T& nb, const Point2D<T>& p) {
	if (nb>=p.x && nb>=p.y){
		return true;
	}
	return false;
}

template<typename T> Point2D<T> operator+(const Point2D<T>& p1, const Point2D<T>& p2) {
	return Point2D<T>{p1.x+p2.x, p1.y+p2.y};
}

template<typename T> Point2D<T> operator-(const Point2D<T>& p1, const Point2D<T>& p2) {
	return Point2D<T>{p1.x-p2.x, p1.y-p2.y};
}

template<typename T> Point2D<T> operator*(const Point2D<T>& p, const T& k) {
	return Point2D<T>{p.x*k, p.y*k};
}

template<typename T> Point2D<T> operator*(const Point2D<T>& p, const int& k) {
	return Point2D<T>{p.x*k, p.y*k};
}

template<typename T> Point2D<T> operator*(const T& k, const Point2D<T>& p) {
	return Point2D<T>{k*p.x, k*p.y};
}

template<typename T> Point2D<T> operator*(const int& k, const Point2D<T>& p) {
	return Point2D<T>{k*p.x, k*p.y};
}

template<typename T> Point2D<T> operator/(const Point2D<T>& p, const T& k) {
	return Point2D<T>{p.x/k, p.y/k};
}

template<typename T> Point2D<T> operator/(const Point2D<T>& p, const int& k) {
	return Point2D<T>{p.x/k, p.y/k};
}

template<typename T> Point2D<T> abs(const Point2D<T>& p){
	return Point2D<T>{abs(p.x), abs(p.y)};
}






/*
 * Functions
 */

//template <typename U> SN<S, T> getDistance(const U& p1, const U& p2);
/*
 * The type T needs: .to_long_double(), .getX(), .getY(), .getZ() that return SNs
 */
/*template<typename T, typename M, typename E> T getDistance(const T& p1, const T& p2) {
	return T(sqrt(pow((p1.getX()-p2.getX()).to_m_type(), 2) + pow((p1.getY()-p2.getY()).to_m_type(), 2) + pow((p1.getZ()-p2.getZ()).to_m_type(), 2)), 0);// d=sqrt( (xA-xB)²+(yA-yB)² )
}*/

//template<typename T> T getDistance(const Point2D<T>& p1, const Point2D<T>& p2);

/**
 * Computes distance between two points.
 * Uses (0,0) as the ref if only one point is provided.
 */
template<typename T> T getDistance(const Point2D<T>& p1, const Point2D<T>& p2={(T)0, (T)0}) {
	return T(sqrt(pow((p1.x-p2.x).to_m_type(), 2) + pow((p1.y-p2.y).to_m_type(), 2) ), 0);// d=sqrt( (xA-xB)²+(yA-yB)² )
}

/**
 * Returns the points to be rendered.
 */
template<typename T> std::unordered_set<std::shared_ptr<Point2D<T>>> pixelizeCircle(std::shared_ptr<Point2D<T>> pcenter, int radius, int spacing=8){
    std::unordered_set<std::shared_ptr<Point2D<T>>> ppoints;

    // 35 / 49 is a slightly biased approximation of 1/sqrt(2)
    //const int arrSize=roundUpToMultipleOfEight(radius*8*35/49);
    //points.reserve(arrSize);

    const int diameter=radius*2;

//    int32_t x=radius-1;
//    int32_t y=0;
//    int32_t tx=1;
//    int32_t ty=1;
//    int32_t error=tx-diameter;
    //int spacing=(int)(radius*ratio);
    //printf("%d\n", spacing);
    T x=(T)(radius-spacing);
    T y=0;
    int tx=spacing;
    int ty=spacing;
    int error=tx-diameter;

    while(x>=y){
        // Each of the following renders an octant of the circle
        ppoints.insert(std::make_shared<Point2D<T>>(pcenter->x+x, pcenter->y-y));
        ppoints.insert(std::make_shared<Point2D<T>>(pcenter->x+x, pcenter->y+y));
        ppoints.insert(std::make_shared<Point2D<T>>(pcenter->x-x, pcenter->y-y));
        ppoints.insert(std::make_shared<Point2D<T>>(pcenter->x-x, pcenter->y+y));
        ppoints.insert(std::make_shared<Point2D<T>>(pcenter->x+y, pcenter->y-x));
        ppoints.insert(std::make_shared<Point2D<T>>(pcenter->x+y, pcenter->y+x));
        ppoints.insert(std::make_shared<Point2D<T>>(pcenter->x-y, pcenter->y-x));
        ppoints.insert(std::make_shared<Point2D<T>>(pcenter->x-y, pcenter->y+x));

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


#endif /* POINT2D_H_ */
