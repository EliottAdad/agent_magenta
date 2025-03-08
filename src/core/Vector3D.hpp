/*
 * Vector3D.hpp
 *
 *  Created on: 11 juin 2024
 *      Author: esn
 */

#ifndef VECTOR3D_HPP_

#define VECTOR3D_HPP_


#include <memory>

#include "utils_Line3D.hpp"
#include "utils_Point3D.hpp"

/*
 * ###############
 *  Vector3D<T> :)
 * ###############
 * @brief
 * T: Unit for distances
 * Overwritten for T, doubles and ints (not really yet for T):
 * 		3.14 is by default double
 * 		2 is by default int
 */
template<typename T> class Vector3D : public Line3D<T> {
public:
	Vector3D() : Line3D<T>() {};
	Vector3D(const Point3D<T>& p2) : Line3D<T>(p2) {};
	Vector3D(const Point3D<T>& p1, const Point3D<T>& p2) : Line3D<T>(p1, p2) {};
	Vector3D(std::shared_ptr<Point3D<T>> pp1, std::shared_ptr<Point3D<T>> pp2) : Line3D<T>(pp1, pp2) {};
	Vector3D(std::shared_ptr<Point3D<T>> pp1, const Point3D<T>& p2) : Line3D<T>(pp1, p2) {};
	Vector3D(const Point3D<T>& p1, std::shared_ptr<Point3D<T>> pp2) : Line3D<T>(p1, pp2) {};
	//virtual ~Vector3D() : ~Line3D<T>();//:)
	Vector3D(const Vector3D<T>& v) : Line3D<T>(v) {};

	T getNorm() const;																	// :)
	void setNorm(const T& norm);														// :)
	
	// From Line3D
	Point3D<T> getOrigin() const {return Line3D<T>::getP1();}							//:)
	std::shared_ptr<Point3D<T>> getPOrigin() const {return Line3D<T>::getPP1();}		//:)
	void setOrigin(const Point3D<T>& origin) {Line3D<T>::setP1(origin);}				//:)
	void setPOrigin(std::shared_ptr<Point3D<T>> porigin) {Line3D<T>::setPP1(porigin);}	//:)
	Point3D<T> getEnd() const {return Line3D<T>::getP2();}								//:)
	std::shared_ptr<Point3D<T>> getPEnd() const {return Line3D<T>::getPP2();}			//:)
	void setEnd(const Point3D<T>& end) {Line3D<T>::setP2(end);}				//:)
	void setPEnd(std::shared_ptr<Point3D<T>> pend) {Line3D<T>::setPP2(pend);}	//:)

	// Operators
	virtual void operator=(const Vector3D<T>& v);			// :)
	virtual void operator+=(const Vector3D<T>& v);			// :)
	virtual void operator-=(const Vector3D<T>& v);			// :)
	virtual void operator*=(const T& k);					// :)
	//virtual void operator*=(const int& k);					// :)
	//virtual void operator*=(const double& k);				// :)
	virtual void operator/=(const T& k);					// :)
	//virtual void operator/=(const int& k);					// :)
	//virtual void operator/=(const double& k);				// :)

	virtual bool operator==(const Vector3D<T>& v) const;	// :)
	virtual bool operator<=(const Vector3D<T>& v) const;	// :)
	virtual bool operator>=(const Vector3D<T>& v) const;	// :)
};

template<typename T> Vector3D<T> operator+(const Vector3D<T>& v1, const Vector3D<T>& v2);	// :)
template<typename T> Vector3D<T> operator-(const Vector3D<T>& v1, const Vector3D<T>& v2);	// :)
template<typename T> Vector3D<T> operator*(const Vector3D<T>& v, const T& k);				// :)
//template<typename T> Vector3D<T> operator*(const Vector3D<T>& v, const int& k);				// :)
//template<typename T> Vector3D<T> operator*(const Vector3D<T>& v, const double& k);			// :)
template<typename T> Vector3D<T> operator/(const Vector3D<T>& v, const T& k);				// :)
//template<typename T> Vector3D<T> operator/(const Vector3D<T>& v, const int& k);				// :)
//template<typename T> Vector3D<T> operator/(const Vector3D<T>& v, const double& k);			// :)

//Scalar product
template<typename T> T operator*(const Vector3D<T>& v1, const Vector3D<T>& v2);// :)

//Vector product
template<typename T> Vector3D<T> operator^(const Vector3D<T>& v1, const Vector3D<T>& v2);// :)


//#########################################################################################################################



/**
 * @brief
 * @return Returns the norm
 */
template<typename T> inline T Vector3D<T>::getNorm() const {
	return getDistance(*this->m_pp2, Point3D<T>{(T)0,(T)0,(T)0});
}

template<typename T> inline void Vector3D<T>::setNorm(const T& norm) {
	if (*this->m_pp2!=Point3D<T>{(T)0,(T)0,(T)0}){
		T k=norm/getDistance(*this->m_pp2, Point3D<T>{(T)0,(T)0,(T)0});
		*this->m_pp2*=k;
	}else{
		*this->m_pp2=Point3D<T>{(T)1,(T)1,(T)1};
		this->setNorm(norm);
	}
}


template<typename T> inline void Vector3D<T>::operator=(const Vector3D<T>& v) {
	*this->m_pp2=v.getP2();
}

template<typename T> inline void Vector3D<T>::operator+=(const Vector3D<T>& v) {// The end of the vector must be diff than null
	*this->m_pp2+=v.getP2();
}

template<typename T> inline void Vector3D<T>::operator-=(const Vector3D<T>& v) {
	*this->m_pp2-=*v.m_pp2;
}

template<typename T> inline void Vector3D<T>::operator*=(const T& k) {
	*this->m_pp2*=k;
}

/*template<typename T> inline void Vector3D<T>::operator*=(const int& k) {
	*this->m_pp2*=k;
}

template<typename T> inline void Vector3D<T>::operator*=(const double& k) {
	*this->m_pp2*=k;
}*/

template<typename T> inline void Vector3D<T>::operator/=(const T& k) {
	*this->m_pp2/=k;
}

/*template<typename T> inline void Vector3D<T>::operator/=(const int& k) {
	*this->m_pp2/=k;
}

template<typename T> inline void Vector3D<T>::operator/=(const double& k) {
	*this->m_pp2/=k;
}*/


template<typename T> inline bool Vector3D<T>::operator==(const Vector3D<T>& v) const {
	if (*this->m_pp1==v.getP2()){
		return true;
	}
	return false;
}

template<typename T> inline bool Vector3D<T>::operator<=(const Vector3D<T>& v) const {
	if (*this->m_pp1<=v.getP2()){
		return true;
	}
	return false;
}

template<typename T> inline bool Vector3D<T>::operator>=(const Vector3D<T>& v) const {
	if (*this->m_pp1>=v.getP2()){
		return true;
	}
	return false;
}






template<typename T> inline Vector3D<T> operator+(const Vector3D<T>& v1, const Vector3D<T>& v2) {
	/*std::shared_ptr<Vector3D<T>> pnv(new Vector3D<T>(v1.pp1, *v1.pp2+*v2.pp2));
	return *pnv;*/
	return *std::make_shared<Vector3D<T>>(v1.getPP1(), *v1.getPP2()+*v2.getPP2());
}

template<typename T> inline Vector3D<T> operator-(const Vector3D<T>& v1, const Vector3D<T>& v2) {
	/*std::shared_ptr<Vector3D<T>> pnv(new Vector3D<T>(v1.pp1, *v1.pp2-*v2.pp2));
	return *pnv;*/
	return *std::make_shared<Vector3D<T>>(v1.getPP1(), *v1.getPP2()-*v2.getPP2());
}

template<typename T> inline Vector3D<T> operator*(const Vector3D<T>& v, const T& k) {
	/*std::shared_ptr<Vector3D<T>> pnv(new Vector3D<T>(v.pp1, *(v.pp2)*k));
	return *pnv;*/
	return *std::make_shared<Vector3D<T>>(v.getPP1(), *(v.getPP2())*k);
}

/*template<typename T> inline Vector3D<T> operator*(const Vector3D<T>& v, const int& k) {
	return *std::make_shared<Vector3D<T>>(v.getPP1(), *(v.getPP2())*k);
}

template<typename T> inline Vector3D<T> operator*(const Vector3D<T>& v, const double& k) {
	return *std::make_shared<Vector3D<T>>(v.getPP1(), *(v.getPP2())*k);
}*/

template<typename T> inline Vector3D<T> operator/(const Vector3D<T>& v, const T& k) {
	/*std::shared_ptr<Vector3D<T>> pnv(new Vector3D<T>(v.pp1, *(v.pp2)/k));
	return *pnv;*/
	return *std::make_shared<Vector3D<T>>(v.getPP1(), *(v.getPP2())/k);
}

/*template<typename T> inline Vector3D<T> operator/(const Vector3D<T>& v, const int& k) {
	return *std::make_shared<Vector3D<T>>(v.getPP1(), *(v.getPP2())/k);
}

template<typename T> inline Vector3D<T> operator/(const Vector3D<T>& v, const double& k) {
	return *std::make_shared<Vector3D<T>>(v.getPP1(), *(v.getPP2())/k);
}*/


/**
 * @brief
 * Scalar product
 */
template<typename T> inline T operator*(const Vector3D<T>& v1, const Vector3D<T>& v2) {
	return v1.getP2().x*v2.getP2().x + v1.getP2().y*v2.getP2().y + v1.getP2().z*v2.getP2().z;
}

/**
 * @brief
 * Vectorial product
 */
template<typename T> inline Vector3D<T> operator^(const Vector3D<T>& v1, const Vector3D<T>& v2) {
	/*std::shared_ptr<Vector3D<T>> pnv(new Vector3D<T>(v1.pp1, {
			{v1.pp2->y*v2.pp2->z-v1.pp2->z*v2.pp2->y},
			{v1.pp2->z*v2.pp2->x-v1.pp2->x*v2.pp2->z},
			{v1.pp2->x*v2.pp2->y-v1.pp2->y*v2.pp2->x}
	}));
	return *pnv;*/
	return *std::make_shared<Vector3D<T>>(v1.pp1, {
			{v1.getP2().y*v2.getP2().z-v1.getP2().z*v2.getP2().y},
			{v1.getP2().z*v2.getP2().x-v1.getP2().x*v2.getP2().z},
			{v1.getP2().x*v2.getP2().y-v1.getP2().y*v2.getP2().x}
	});
}






#endif /* VECTOR3D_HPP_ */
