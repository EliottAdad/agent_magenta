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
	m_pnormal=new Vector3D();
	*m_pnormal/=m_pnormal->getNorm();//Normalisation
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
	Vector3D pv(m_ppoint, {
			{1, 0},
			{1, 0},
			{-1/m_pnormal->getP2().z * (m_pnormal->getP2().x*(1-m_ppoint->x) + m_pnormal->getP2().y*(1-m_ppoint->y)) + m_ppoint->z}
			});//One possible normal vector
	pv/=pv.getNorm();//Normalisation
	return pv;
}

Vector3D Camera::getE2() const {
	Vector3D pv(*m_pnormal^this->getE1());
	pv/=pv.getNorm();//Normalisation
	return pv;
}



void Camera::renderMesh(const Mesh3D& mesh) const {
	;
}

void Camera::renderTriangle(const Triangle3D& triangle) const {
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


std::string Camera::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="CAMERA";

	return mes;
}

void Camera::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

