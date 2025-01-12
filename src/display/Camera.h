/*
 * Camera.h
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef CAMERA_H_

#define CAMERA_H_

#include <memory>

#include "../core/Point3D.h"
#include "../core/Vector3D.h"
#include "../geometry/Mesh3D.h"
#include "../geometry/Triangle3D.h"
#include "../utilities/Printable.h"

/*
 * ################
 *  Camera<M, E> :)
 * ################
 * This camera is a cone directed by a normal
 */
template<typename M, typename E> class Camera : public Printable {
private:
	float m_aperture;		//Aperture angle in radians
	float m_roll_ang;		//Roll angle to the normal
	//m_window;

public:
	std::shared_ptr<Point3D<M, E>> ppoint;
	std::shared_ptr<Vector3D<M, E>> pnormal;

	Camera();
	virtual ~Camera();
	Camera(const Camera<M, E>& other);

	/*Point3D<float, char> getPoint() const;
	void setPoint(const Point3D<float, char>& p);*/
	//Vector3D* getPNormal();
	/*Vector3D getNormal() const;
	void setNormal(const Point3D<float, char>& p);*/
	std::shared_ptr<Vector3D<M, E>> getE1() const;
	std::shared_ptr<Vector3D<M, E>> getE2() const;

	void renderMesh(const Mesh3D<M, E>& mesh) const;
	void renderTriangle(const Triangle3D<M, E>& triangle) const;
	void renderPoint(const Point3D<M, E>& p) const;

	bool testInFielOfView(const Point3D<M, E>& p) const;

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

template<typename M, typename E> Camera<M, E>::Camera() {
	m_aperture=1;
	m_roll_ang=0;
	ppoint=NULL;
	pnormal=std::make_shared<Vector3D<M, E>>();
	*pnormal/=pnormal->getNorm();//Normalization
}

template<typename M, typename E> Camera<M, E>::~Camera() {
	;
}

template<typename M, typename E> Camera<M, E>::Camera(const Camera<M, E>& other) {
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

template<typename M, typename E> std::shared_ptr<Vector3D<M, E>> Camera<M, E>::getE1() const {
	std::shared_ptr<Vector3D<M, E>> pv;
	if (ppoint!=NULL && pnormal!=NULL){
		pv=std::make_shared<Vector3D<M, E>>(
				ppoint, Point3D<M, E>{
				{1,0},
				{1,0},
				{(M)(-1.)/pnormal->pp2->z * (pnormal->pp2->x*((M)(1.)-ppoint->x) + pnormal->pp2->y*((M)(1.)-ppoint->y)) + ppoint->z}
				}
				);//One possible normal vector
		*pv/=pv->getNorm();//Normalisation
	}
	return pv;
}

template<typename M, typename E> std::shared_ptr<Vector3D<M, E>> Camera<M, E>::getE2() const {
	std::shared_ptr<Vector3D<M, E>> pv;
	if (ppoint!=NULL && pnormal!=NULL){
		pv=std::make_shared<Vector3D<M, E>>( *pnormal^*(this->getE1()) );
		*pv/=pv->getNorm();//Normalisation
	}
	return pv;
}



template<typename M, typename E> void Camera<M, E>::renderMesh(const Mesh3D<M, E>& mesh) const {
	;
}

template<typename M, typename E> void Camera<M, E>::renderTriangle(const Triangle3D<M, E>& triangle) const {
	;
}

template<typename M, typename E> void Camera<M, E>::renderPoint(const Point3D<M, E>& p) const {
	if (ppoint!=NULL){
		Vector3D<M, E> vpos(ppoint, p-*ppoint);
		SN<M, E> projx(*(this->getE1())*vpos);
		SN<M, E> projz=*(this->getE2())*vpos;

		SN<M, E> x_prime=projx/(vpos.getNorm()*tan(m_aperture/2));
		SN<M, E> z_prime=projz/(vpos.getNorm()*tan(m_aperture/2));
		//Draw on the screen
	}
}

template<typename M, typename E> bool Camera<M, E>::testInFielOfView(const Point3D<M, E>& p) const {
	bool test=false;
	if (ppoint!=NULL){
		Vector3D<M, E> vpos(ppoint, p-*ppoint);

		if (m_aperture/2. >= acos( ((*pnormal*vpos) / (pnormal->getNorm()*vpos.getNorm())).to_m_type() )){
			test=true;
		}
	}
	return test;
}


template<typename M, typename E> std::string Camera<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="CAMERA";

	return mes;
}

template<typename M, typename E> void Camera<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* CAMERA_H_ */
