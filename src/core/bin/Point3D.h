/*
 * Point3D.h
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */

#ifndef POINT3D_H_

#define POINT3D_H_

#include <memory>

#include "../core/SN.h"
#include "../utilities/Printable.h"





/*
 * #################
 *  Point3D<M, E> :)
 * #################
 */
template<typename M, typename E> struct Point3D : public Printable {
	SN<M, E> x;
	SN<M, E> y;
	SN<M, E> z;

	Point3D();
	Point3D(const SN<M, E>& x, const SN<M, E>& y, const SN<M, E>& z);
	virtual ~Point3D();
	Point3D(const Point3D<M, E>& point);//Copy constructor

	virtual SN<M, E> getX() const;							// :)
	virtual SN<M, E> getY() const;							// :)
	virtual SN<M, E> getZ() const;							// :)
	//virtual Point3D<M, E> getPosition() const;				// :) To be inherited

	virtual void operator=(const Point3D<M, E>& p);			// :)
	virtual void operator=(const SN<M, E>& nb);				// :)
	virtual void operator+=(const Point3D<M, E>& p);			// :)
	virtual void operator+=(const SN<M, E>& nb);				// :)
	virtual void operator+=(const M& nb);		// :)
	virtual void operator-=(const Point3D<M, E>& p);			// :)
	virtual void operator-=(const SN<M, E>& nb);				// :)
	virtual void operator-=(const M& nb);		// :)
	virtual void operator*=(const SN<M, E>& k);				// :)
	virtual void operator*=(const M& k);		// :)
	virtual void operator/=(const SN<M, E>& k);				// :)
	virtual void operator/=(const M& k);		// :)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

template<typename M, typename E> bool operator==(const Point3D<M, E>& p1, const Point3D<M, E>& p2);		// :)
template<typename M, typename E> bool operator==(const Point3D<M, E>& p, const SN<M, E>& nb);		// :)
template<typename M, typename E> bool operator==(const SN<M, E>& nb, const Point3D<M, E>& p);		// :)
template<typename M, typename E> bool operator!=(const Point3D<M, E>& p1, const Point3D<M, E>& p2);		// :)
template<typename M, typename E> bool operator!=(const Point3D<M, E>& p, const SN<M, E>& nb);		// :)
template<typename M, typename E> bool operator!=(const SN<M, E>& nb, const Point3D<M, E>& p);		// :)
template<typename M, typename E> bool operator<=(const Point3D<M, E>& p1, const Point3D<M, E>& p2);		// :)
template<typename M, typename E> bool operator<=(const Point3D<M, E>& p, const SN<M, E>& nb);		// :)
template<typename M, typename E> bool operator<=(const SN<M, E>& nb, const Point3D<M, E>& p);		// :)
template<typename M, typename E> bool operator>=(const Point3D<M, E>& p1, const Point3D<M, E>& p2);		// :)
template<typename M, typename E> bool operator>=(const Point3D<M, E>& p, const SN<M, E>& nb);		// :)
template<typename M, typename E> bool operator>=(const SN<M, E>& nb, const Point3D<M, E>& p);		// :)
template<typename M, typename E> Point3D<M, E> operator+(const Point3D<M, E>& p1, const Point3D<M, E>& p2);	// :)
template<typename M, typename E> Point3D<M, E> operator-(const Point3D<M, E>& p1, const Point3D<M, E>& p2);	// :)
template<typename M, typename E> Point3D<M, E> operator*(const Point3D<M, E>& p, const SN<M, E>& k);			// :)
template<typename M, typename E> Point3D<M, E> operator*(const SN<M, E>& k, const Point3D<M, E>& p);			// :)
template<typename M, typename E> Point3D<M, E> operator*(const Point3D<M, E>& p, const M& k);
template<typename M, typename E> Point3D<M, E> operator*(const M& k, const Point3D<M, E>& p);
template<typename M, typename E> Point3D<M, E> operator/(const Point3D<M, E>& p, const SN<M, E>& k);			// :)
template<typename M, typename E> Point3D<M, E> operator/(const Point3D<M, E>& p, const M& k);	// :)
template<typename M, typename E> Point3D<M, E> abs(const Point3D<M, E>& p);	// :)




template<typename M, typename E> Point3D<M, E>::Point3D() {
	this->x=SN<M, E>{0,0};
	this->y=SN<M, E>{0,0};
	this->z=SN<M, E>{0,0};
}

template<typename M, typename E> Point3D<M, E>::Point3D(const SN<M, E>& x, const SN<M, E>& y, const SN<M, E>& z) {
	this->x=x;
	this->y=y;
	this->z=z;
}

template<typename M, typename E> Point3D<M, E>::~Point3D() {
	// TODO Auto-generated destructor stub
}

template<typename M, typename E> Point3D<M, E>::Point3D(const Point3D<M, E>& point) {
	this->x=point.x;
	this->y=point.y;
	this->z=point.z;
}



template<typename M, typename E> SN<M, E> Point3D<M, E>::getX() const {
	return x;
}

template<typename M, typename E> SN<M, E> Point3D<M, E>::getY() const {
	return y;
}

template<typename M, typename E> SN<M, E> Point3D<M, E>::getZ() const {
	return z;
}

/*template<typename M, typename E> Point3D<M, E> Point3D<M, E>::getPosition() const {
	return {x, y, z};
}*/

template<typename M, typename E> void Point3D<M, E>::operator=(const Point3D<M, E>& p) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
}

template<typename M, typename E> void Point3D<M, E>::operator=(const SN<M, E>& nb) {
	this->x=nb;
	this->y=nb;
	this->z=nb;
}

template<typename M, typename E> void Point3D<M, E>::operator+=(const Point3D<M, E>& p) {
	this->x+=p.x;
	this->y+=p.y;
	this->z+=p.z;
}

template<typename M, typename E> void Point3D<M, E>::operator+=(const SN<M, E>& nb) {
	this->x+=nb;
	this->y+=nb;
	this->z+=nb;
}

template<typename M, typename E> void Point3D<M, E>::operator+=(const M& nb) {
	this->x+=nb;
	this->y+=nb;
	this->z+=nb;
}

template<typename M, typename E> void Point3D<M, E>::operator-=(const Point3D<M, E>& p) {
	this->x-=p.x;
	this->y-=p.y;
	this->z-=p.z;
}

template<typename M, typename E> void Point3D<M, E>::operator-=(const SN<M, E>& nb) {
	this->x-=nb;
	this->y-=nb;
	this->z-=nb;
}

template<typename M, typename E> void Point3D<M, E>::operator-=(const M& nb) {
	this->x-=nb;
	this->y-=nb;
	this->z-=nb;
}

template<typename M, typename E> void Point3D<M, E>::operator*=(const SN<M, E>& k) {
	this->x*=k;
	this->y*=k;
	this->z*=k;
}

template<typename M, typename E> void Point3D<M, E>::operator*=(const M& k) {
	this->x*=k;
	this->y*=k;
	this->z*=k;
}

template<typename M, typename E> void Point3D<M, E>::operator/=(const SN<M, E>& k) {
	this->x/=k;
	this->y/=k;
	this->z/=k;
}

template<typename M, typename E> void Point3D<M, E>::operator/=(const M& k) {
	this->x/=k;
	this->y/=k;
	this->z/=k;
}





template<typename M, typename E> std::string Point3D<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	//std::cout<<"Help1\n";
	std::string mes=((spread)?"\n" : "");
	mes+=to_stringTabs(indent);
	//printf("Help2\n");
	if (full_info){
		mes+="POINT3D[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" + to_stringTabs(1) : "");
	}
	//printf("Help3\n");
	mes+=to_stringTabs(indent);
	mes+="(x:" + x.to_string(false, false, 0) + " ; y:" + y.to_string(false, false, 0) + " ; z:" + z.to_string(false, false, 0) + ")";

	return mes;
}

template<typename M, typename E> void Point3D<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}






template<typename M, typename E> bool operator==(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	if (p1.x==p2.x && p1.y==p2.y && p1.z==p2.z){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator==(const Point3D<M, E>& p, const SN<M, E>& nb) {
	if (p.x==nb && p.y==nb && p.z==nb){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator==(const SN<M, E>& nb, const Point3D<M, E>& p) {
	if (nb==p.x && nb==p.y && nb==p.z){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator!=(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	if (p1.x!=p2.x && p1.y!=p2.y && p1.z!=p2.z){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator!=(const Point3D<M, E>& p, const SN<M, E>& nb) {
	if (p.x!=nb && p.y!=nb && p.z!=nb){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator!=(const SN<M, E>& nb, const Point3D<M, E>& p) {
	if (nb!=p.x && nb!=p.y && nb!=p.z){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator<=(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	if (p1.x<=p2.x && p1.y<=p2.y && p1.z<=p2.z){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator<=(const Point3D<M, E>& p, const SN<M, E>& nb) {
	if (p.x<=nb && p.y<=nb && p.z<=nb){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator<=(const SN<M, E>& nb, const Point3D<M, E>& p) {
	if (nb<=p.x && nb<=p.y && nb<=p.z){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator>=(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	if (p1.x>=p2.x && p1.y>=p2.y && p1.z>=p2.z){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator>=(const Point3D<M, E>& p, const SN<M, E>& nb) {
	if (p.x>=nb && p.y>=nb && p.z>=nb){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator>=(const SN<M, E>& nb, const Point3D<M, E>& p) {
	if (nb>=p.x && nb>=p.y && nb>=p.z){
		return true;
	}
	return false;
}

template<typename M, typename E> Point3D<M, E> operator+(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	return Point3D<M, E>{p1.x+p2.x, p1.y+p2.y, p1.z+p2.z};
}

template<typename M, typename E> Point3D<M, E> operator-(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	return Point3D<M, E>{p1.x-p2.x, p1.y-p2.y, p1.z-p2.z};
}

template<typename M, typename E> Point3D<M, E> operator*(const Point3D<M, E>& p, const SN<M, E>& k) {
	return Point3D<M, E>{p.x*k, p.y*k, p.z*k};
}

template<typename M, typename E> Point3D<M, E> operator*(const SN<M, E>& k, const Point3D<M, E>& p) {
	return Point3D<M, E>{k*p.x, k*p.y, k*p.z};
}

template<typename M, typename E> Point3D<M, E> operator*(const Point3D<M, E>& p, const M& k) {
	return Point3D<M, E>{p.x*k, p.y*k, p.z*k};
}

template<typename M, typename E> Point3D<M, E> operator*(const M& k, const Point3D<M, E>& p) {
	return Point3D<M, E>{k*p.x, k*p.y, k*p.z};
}

template<typename M, typename E> Point3D<M, E> operator/(const Point3D<M, E>& p, const SN<M, E>& k) {
	return Point3D<M, E>{p.x/k, p.y/k, p.z/k};
}

template<typename M, typename E> Point3D<M, E> operator/(const Point3D<M, E>& p, const M& k) {
	return Point3D<M, E>{p.x/k, p.y/k, p.z/k};
}

template<typename M, typename E> Point3D<M, E> abs(const Point3D<M, E>& p){
	return Point3D<M, E>{abs(p.x), abs(p.y), abs(p.z)};
}






/*
 * Functions
 */

//template <typename U> SN<S, T> getDistance(const U& p1, const U& p2);
/*
 * The type T needs: .to_long_double(), .getX(), .getY(), .getZ() that return SNs
 */
/*template<typename T, typename M, typename E> SN<M, E> getDistance(const T& p1, const T& p2) {
	return SN<M, E>(sqrt(pow((p1.getX()-p2.getX()).to_m_type(), 2) + pow((p1.getY()-p2.getY()).to_m_type(), 2) + pow((p1.getZ()-p2.getZ()).to_m_type(), 2)), 0);// d=sqrt( (xA-xB)²+(yA-yB)² )
}*/

//template<typename M, typename E> SN<M, E> getDistance(const Point3D<M, E>& p1, const Point3D<M, E>& p2);

template<typename M, typename E> SN<M, E> getDistance(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	return SN<M, E>(sqrt(pow((p1.x-p2.x).to_m_type(), 2) + pow((p1.y-p2.y).to_m_type(), 2) + pow((p1.z-p2.z).to_m_type(), 2)), 0);// d=sqrt( (xA-xB)²+(yA-yB)² )
}

/**
 * Returns the points to be rendered.
 */
template<typename M, typename E> std::unordered_set<std::shared_ptr<Point3D<M, E>>> pixelizeCircle(std::shared_ptr<Point3D<M, E>> pcenter, int radius, int spacing=8){
    std::unordered_set<std::shared_ptr<Point3D<M, E>>> ppoints;

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
    SN<M, E> x{(M)(radius-spacing),0};
    SN<M, E> y{0,0};
    int tx=spacing;
    int ty=spacing;
    int error=tx-diameter;

    while(x>=y){
        // Each of the following renders an octant of the circle
        ppoints.insert(std::make_shared<Point3D<M, E>>(pcenter->x+x, pcenter->y-y, SN<M, E>{0, 0}));
        ppoints.insert(std::make_shared<Point3D<M, E>>(pcenter->x+x, pcenter->y+y, SN<M, E>{0, 0}));
        ppoints.insert(std::make_shared<Point3D<M, E>>(pcenter->x-x, pcenter->y-y, SN<M, E>{0, 0}));
        ppoints.insert(std::make_shared<Point3D<M, E>>(pcenter->x-x, pcenter->y+y, SN<M, E>{0, 0}));
        ppoints.insert(std::make_shared<Point3D<M, E>>(pcenter->x+y, pcenter->y-x, SN<M, E>{0, 0}));
        ppoints.insert(std::make_shared<Point3D<M, E>>(pcenter->x+y, pcenter->y+x, SN<M, E>{0, 0}));
        ppoints.insert(std::make_shared<Point3D<M, E>>(pcenter->x-y, pcenter->y-x, SN<M, E>{0, 0}));
        ppoints.insert(std::make_shared<Point3D<M, E>>(pcenter->x-y, pcenter->y+x, SN<M, E>{0, 0}));

        if(error<=0){
            //++y;
        	y+=SN<M, E>{(M)spacing, 0};
            error+=ty;
            ty+=2*spacing;
        }

        if(error>0){
            //--x;
        	x-=SN<M, E>{(M)spacing, 0};
            tx+=2*spacing;
            error+=tx-diameter;
        }
    }

    return ppoints; // RVO FTW
}



#endif /* POINT3D_H_ */
