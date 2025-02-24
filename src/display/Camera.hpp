/*
 * Camera.hpp
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef CAMERA_HPP_

#define CAMERA_HPP_

#include <memory>

#include "../core/Point3D.hpp"
#include "../core/Vector3D.hpp"
#include "../geometry/Mesh3D.hpp"
#include "../geometry/Triangle3D.hpp"
//#include "../utilities/Printable.hpp"

/*
 * ################
 *  Camera<T> :)
 * ################
 * @brief
 * This camera is a cone directed by a normal
 */
template<typename T> class Camera {
private:
	float m_aperture;		//Aperture angle in radians
	float m_roll_ang;		//Roll angle to the normal
	//m_window;

public:
	std::shared_ptr<Point3D<T>> ppoint;
	std::shared_ptr<Vector3D<T>> pnormal;

	Camera();
	virtual ~Camera();
	Camera(const Camera<T>& other);

	/*Point3D<float, char> getPoint() const;
	void setPoint(const Point3D<float, char>& p);*/
	//Vector3D* getPNormal();
	/*Vector3D getNormal() const;
	void setNormal(const Point3D<float, char>& p);*/
	std::shared_ptr<Vector3D<T>> getE1() const;
	std::shared_ptr<Vector3D<T>> getE2() const;

	void renderMesh(const Mesh3D<T>& mesh) const;
	void renderTriangle(const Triangle3D<T>& triangle) const;
	void renderPoint(const Point3D<T>& p) const;

	bool testInFielOfView(const Point3D<T>& p) const;
};

template<typename T> inline Camera<T>::Camera() {
	m_aperture=1;
	m_roll_ang=0;
	ppoint=NULL;
	pnormal=std::make_shared<Vector3D<T>>();
	*pnormal/=pnormal->getNorm();//Normalization
}

template<typename T> inline Camera<T>::~Camera() {
	;
}

template<typename T> inline Camera<T>::Camera(const Camera<T>& other) {
	m_aperture=1;
	m_roll_ang=0;
	this->ppoint=other.ppoint;
	this->pnormal=other.pnormal;
}


/*Point3D<float, char> Camera::getPoint() const {
	return *m_ppoint;
}

void Camera::setPoint(const Point3D<float, char>& p) {
	*m_ppoint=p;
}

Vector3D Camera::getNormal() const {
	return *m_pnormal;
}*/

template<typename T> inline std::shared_ptr<Vector3D<T>> Camera<T>::getE1() const {
	std::shared_ptr<Vector3D<T>> pv;
	if (ppoint!=NULL && pnormal!=NULL){
		pv=std::make_shared<Vector3D<T>>(
				ppoint, Point3D<T>{
				{1,0},
				{1,0},
				{(M)(-1.)/pnormal->pp2->z * (pnormal->pp2->x*((M)(1.)-ppoint->x) + pnormal->pp2->y*((M)(1.)-ppoint->y)) + ppoint->z}
				}
				);//One possible normal vector
		*pv/=pv->getNorm();//Normalisation
	}
	return pv;
}

template<typename T> inline std::shared_ptr<Vector3D<T>> Camera<T>::getE2() const {
	std::shared_ptr<Vector3D<T>> pv;
	if (ppoint!=NULL && pnormal!=NULL){
		pv=std::make_shared<Vector3D<T>>( *pnormal^*(this->getE1()) );
		*pv/=pv->getNorm();//Normalisation
	}
	return pv;
}



template<typename T> inline void Camera<T>::renderMesh(const Mesh3D<T>& mesh) const {
	;
}

template<typename T> inline void Camera<T>::renderTriangle(const Triangle3D<T>& triangle) const {
	;
}

template<typename T> inline void Camera<T>::renderPoint(const Point3D<T>& p) const {
	if (ppoint!=NULL){
		Vector3D<T> vpos(ppoint, p-*ppoint);
		SN<T> projx(*(this->getE1())*vpos);
		SN<T> projz=*(this->getE2())*vpos;

		SN<T> x_prime=projx/(vpos.getNorm()*tan(m_aperture/2));
		SN<T> z_prime=projz/(vpos.getNorm()*tan(m_aperture/2));
		//Draw on the screen
	}
}

template<typename T> inline bool Camera<T>::testInFielOfView(const Point3D<T>& p) const {
	bool test=false;
	if (ppoint!=NULL){
		Vector3D<T> vpos(ppoint, p-*ppoint);

		if (m_aperture/2. >= acos( ((*pnormal*vpos) / (pnormal->getNorm()*vpos.getNorm())).to_m_type() )){
			test=true;
		}
	}
	return test;
}




#endif /* CAMERA_HPP_ */
