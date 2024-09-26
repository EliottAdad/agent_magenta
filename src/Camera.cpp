/*
 * Camera.cpp
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#include "Camera.h"

Camera::Camera() {
	m_aperture=1;
	m_ppoint=new Point3D{};
	m_pnormal=new Vector3D{};
	m_roll_ang=0;

	m_delp=true;
	m_deln=true;
}

Camera::~Camera() {
	if (m_delp){
		delete m_ppoint;
	}else{
		m_ppoint=NULL;
	}
	if (m_deln){
		delete m_pnormal;
	}else{
		m_pnormal=NULL;
	}
}

/*Camera::Camera(const Camera &other) {
	// TODO Auto-generated constructor stub

}*/


Point3D Camera::getPoint() const {
	return *m_ppoint;
}

void Camera::setPoint(const Point3D& p) {
	*m_ppoint=p;
}

Vector3D Camera::getNormal() const {
	return *m_pnormal;
}

Vector3D Camera::getE1() const {
	Vector3D pv;
	return pv;
}

Vector3D Camera::getE2() const {
	Vector3D pv;
	return pv;
}



void Camera::renderMesh(const Mesh3D& mesh) const {
	;
}

void Camera::renderPoint(const Point3D& p) const {
	Vector3D vpos(m_ppoint, p-*m_ppoint);
	LSN projx=this->getE1()*vpos;
	LSN projz=this->getE2()*vpos;

	LSN x_prime=projx/(vpos.getNorm()*tan(m_aperture/2));
	LSN z_prime=projz/(vpos.getNorm()*tan(m_aperture/2));
	//Draw on the screen

}

bool Camera::testInFielOfView(const Point3D& p) const {
	bool test=false;
	Vector3D vpos(m_ppoint, p-*m_ppoint);

	if (m_aperture/2 >= acos( ((*m_pnormal*vpos) / (m_pnormal->getNorm()*vpos.getNorm())).to_long_double() )){
		test=true;
	}
	return test;
}
