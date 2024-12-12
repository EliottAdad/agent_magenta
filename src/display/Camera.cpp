/*
 * Camera.cpp
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#include "Camera.h"

Camera::Camera() {
	m_aperture=1;
	m_roll_ang=0;
	ppoint=NULL;
	pnormal=std::make_shared<Vector3D>();
	*pnormal/=pnormal->getNorm();//Normalization
}

Camera::~Camera() {
	/*if (m_deln){
		delete m_pnormal;
	}else{
		m_pnormal=NULL;
	}*/
	;
}

Camera::Camera(const Camera& other) {
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

std::shared_ptr<Vector3D> Camera::getE1() const {
	std::shared_ptr<Vector3D> pv;
	if (ppoint!=NULL && pnormal!=NULL){
		pv=std::make_shared<Vector3D>(
				ppoint, Point3D<float, char>{
				{1,0},
				{1,0},
				{(float)(-1.)/pnormal->pp2->z * (pnormal->pp2->x*((float)(1.)-ppoint->x) + pnormal->pp2->y*((float)(1.)-ppoint->y)) + ppoint->z}
				}
				);//One possible normal vector
		*pv/=pv->getNorm();//Normalisation
	}
	return pv;
}

std::shared_ptr<Vector3D> Camera::getE2() const {
	std::shared_ptr<Vector3D> pv;
	if (ppoint!=NULL && pnormal!=NULL){
		pv=std::make_shared<Vector3D>( *pnormal^*(this->getE1()) );
		*pv/=pv->getNorm();//Normalisation
	}
	return pv;
}



void Camera::renderMesh(const Mesh3D& mesh) const {
	;
}

void Camera::renderTriangle(const Triangle3D& triangle) const {
	;
}

void Camera::renderPoint(const Point3D<float, char>& p) const {
	if (ppoint!=NULL){
		Vector3D vpos(ppoint, p-*ppoint);
		SN<float, char> projx(*(this->getE1())*vpos);
		SN<float, char> projz=*(this->getE2())*vpos;

		SN<float, char> x_prime=projx/(vpos.getNorm()*tan(m_aperture/2));
		SN<float, char> z_prime=projz/(vpos.getNorm()*tan(m_aperture/2));
		//Draw on the screen
	}
}

bool Camera::testInFielOfView(const Point3D<float, char>& p) const {
	bool test=false;
	if (ppoint!=NULL){
		Vector3D vpos(ppoint, p-*ppoint);

		if (m_aperture/2. >= acos( ((*pnormal*vpos) / (pnormal->getNorm()*vpos.getNorm())).to_m_type() )){
			test=true;
		}
	}
	return test;
}


std::string Camera::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="CAMERA";

	return mes;
}

void Camera::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

