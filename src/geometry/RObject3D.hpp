/*
 * RObject3D.hpp
 *
 *  Created on: 09 janv 2025
 *      Author: esn
 */

#ifndef ROBJECT3D_HPP_

#define ROBJECT3D_HPP_


#include <string>
#include <vector>

#include "../utilities/functions.hpp"
#include "../core/SN.hpp"
#include "Shape3D.cpp"
//#include "Circle2D.cpp"
//#include "Polygon2D.cpp"
#include "Object3D.hpp"


/*
 * ################
 *  RObject3D<T> :)
 * ################
 */
template<typename T> class RObject3D : public Object3D<T> {
public:
	std::shared_ptr<T> pangle;
	std::shared_ptr<Shape3D<T>> pcollision_box;										// Collision box.

	RObject3D();//:)
	RObject3D(std::string name, SDL_Color* pcolor=NULL);//:)
	RObject3D(const RObject3D<T>& robject);//:)
	~RObject3D();
	
	void move(long double dt);//:)
	void spin(long double dt);//:)

	//void calculateInertiaMoment();//0

	void operator=(const RObject3D<T>& robject);//:)
	void operator+=(const RObject3D<T>& robject);//:)
	void operator-=(const RObject3D<T>& robject);//:)
	//void operator*=(double k);//:)
};

template<typename T> inline bool operator==(const RObject3D<T>& robject1, const RObject3D<T>& robject2);//:)

template<typename T> inline bool testCollide(const RObject3D<T>& robject1, const RObject3D<T>& robject2);//:)

//void print(RObject2D* probject, unsigned int indent=0);//:)


template<typename T> inline RObject3D<T>::RObject2D(){
	//printf("ROBJECT: CONSTRUCTOR START\n");
	m_name="robject";
	m_mass={1, 1};
	m_charge={0, 0};
	//m_inertia_moment={1, 0};
	m_pcolor=NULL;

	m_pcentroid=new Point2D{{0, 0}, {0, 0}};
	//m_prot_center=new Point2D{{0, 0}, {0, 0}};
	m_pshape=new Polygon2D("shape");
	m_pshape->setPPoint(m_pcentroid);
	m_pcollision_box=new Polygon2D("collision_box");
	m_pcollision_box->setPPoint(m_pcentroid);

	m_pforce=new Vector2D("force", m_pcentroid);
	m_plin_acceleration=new Vector2D("acceleration", m_pcentroid);
	m_plin_velocity=new Vector2D("velocity", m_pcentroid);
	m_torque={0, 0};
	m_rot_acceleration=0;
	m_rot_velocity=0;

	//printf("Hey4\n");
	m_fmove=true;
	m_fcollide=true;
	//printf("Hey5\n");
	//printf("ROBJECT: CONSTRUCTOR END\n");
}

/**
 * Calls first the Object2D CONSTRUCTOR / WHY!!!
 */
template<typename T> inline RObject3D<T>::RObject3D(std::string name, SDL_Color* pcolor) {
	//printf("ROBJECT: CONSTRUCTOR START\n");
	m_name=name;
	m_mass={1, 1};
	m_charge={0, 0};
	//m_inertia_moment={1, 0};
	m_pcolor=pcolor;

	printf("ROBJECT: CONSTRUCTOR2\n");
	m_pcentroid=new Point2D{{0, 0}, {0, 0}};
	//m_prot_center=new Point2D{{0, 0}, {0, 0}};
	printf("ROBJECT: CONSTRUCTOR3\n");
	m_pshape=new Polygon2D("shape");
	m_pshape->setPPoint(m_pcentroid);
	m_pcollision_box=new Polygon2D("collision_box");
	m_pcollision_box->setPPoint(m_pcentroid);
	printf("ROBJECT: CONSTRUCTOR4\n");

	m_pforce=new Vector2D("force", m_pcentroid);
	m_plin_acceleration=new Vector2D("acceleration", m_pcentroid);
	m_plin_velocity=new Vector2D("velocity", m_pcentroid);
	m_torque={0, 0};
	m_rot_acceleration=0;
	m_rot_velocity=0;

	//printf("Hey4\n");
	m_fmove=true;
	m_fcollide=true;
	//printf("ROBJECT: CONSTRUCTOR END\n");
}

template<typename T> inline RObject3D<T>::RObject3D(const RObject3D& robject) {
	//printf("ROBJECT COPY_CONSTRUCTOR START\n");
	m_name=probject->getName();
	m_mass=probject->getMass();
	m_charge=probject->getCharge();
	//m_inertia_moment=probject->getInertiaMoment();
	m_pcolor=probject->getPColor();

	m_pcentroid=new Point2D{*probject->getPCentroid()};
	//m_prot_center=new Point2D{*pobject->getPRotationCenter()};
	m_pshape=new Polygon2D("shape", m_pcentroid);
	//m_pshape->setPPoint(m_pcentroid);
	m_pshape->setPColor(m_pcolor);
	m_pcollision_box=new Polygon2D("collision_box", m_pcentroid);
	//m_pcollision_box->setPPoint(m_pcentroid);
	m_pcollision_box->setPColor(m_pcolor);

	m_pforce=new Vector2D("force", m_pcentroid);
	m_plin_acceleration=new Vector2D("acceleration", m_pcentroid);
	m_plin_velocity=new Vector2D("velocity", m_pcentroid);
	m_torque=probject->getTorque();
	m_rot_acceleration=probject->getRotAcceleration();
	m_rot_velocity=probject->getRotVelocity();

	m_fmove=probject->getFMove();
	m_fcollide=probject->getFCollide();
	//printf("ROBJECT COPY_CONSTRUCTOR END\n");
}

/**
 * Calls first the Object2D DESTRUCTOR
 */
template<typename T> inline RObject3D<T>::~RObject3D() {
	//printf("ROBJECT: DESTRUCTOR START\n");
	m_pcolor=NULL;
	/* We delete the properties.*/
	//this->delProperties();
	/* We delete the points and segments.*/
	//printf("ROBJECT: DESTRUCTOR2\n");
	delete m_pshape;
	delete m_pcollision_box;
	//delete m_pcollision_box;
	/* Give back the instances used.*/
	//printf("ROBJECT: DESTRUCTOR3\n");
	delete m_pforce;
	delete m_plin_acceleration;
	delete m_plin_velocity;

	//printf("ROBJECT: DESTRUCTOR4\n");
	delete m_pcentroid;
	//delete m_prot_center;
	//printf("ROBJECT: DESTRUCTOR END\n");
}




template<typename T> inline void RObject3D<T>::move(long double dt) {
	if (m_fmove)
	{
		Point2D dp=m_plin_acceleration->getEnd() * (1/2) * pow(dt, 2) + m_plin_velocity->getEnd() * dt;
		*m_pcentroid += dp;
	}

	//m_pshape->translate(dp);
	//*m_pcentroid += *(new Point2D{1, 1});
	////printf("*Norm velocity: %Lgm/s.\n", m_plin_velocity->getNorm());
	////printf("C3\n");
}

template<typename T> inline void RObject3D<T>::spin(long double dt) {
	//long double angle_plus=(1/2) * m_rot_acceleration * pow(dt, 2) + m_rot_velocity * dt;
	//m_pshape->rotate(angle_plus/*, m_rot_center*/);
}



////////////////////////////////////////////////


/*void RigidObject2D::delProperties()
{
	int szpproperties(m_pproperties.size());
	for (int i(0) ; i<szpproperties ; i++)
	{
		delete *m_pproperties.begin();
		m_pproperties.erase(m_pproperties.begin());
	}
}

void RigidObject2D::delEdges()
{
	int szpedges(m_ppolygon->getPoints().size());
	for (int i(0) ; i<szpedges ; i++)
	{
		delete *m_pedges.begin();
		m_ppoints.erase(m_ppoints.begin());
	}
}*/





/*void RObject2D::calculateInertiaMoment()//:) I=mr**2
{
	;
}*/







template<typename T> inline void RObject3D<T>::operator=(const RObject3D<T>& robject) {
	//printf("ROBJECT op= 1\n");
	m_name=robject.getName();
	m_mass=robject.getMass();
	m_charge=robject.getCharge();
	//m_inertia_moment=probject->getInertiaMoment();
	m_pcolor=robject.getPColor();

	m_pcentroid=new Point2D{*robject.getPCentroid()};
	//m_prot_center=new Point2D{*pobject->getPRotationCenter()};
	m_pshape=new Polygon2D("shape", m_pcentroid);
	//m_pshape->setPPoint(m_pcentroid);
	m_pshape->setPColor(m_pcolor);
	m_pcollision_box=new Polygon2D("collision_box", m_pcentroid);
	//m_pcollision_box->setPPoint(m_pcentroid);
	m_pcollision_box->setPColor(m_pcolor);

	m_pforce=new Vector2D("force", m_pcentroid);
	m_plin_acceleration=new Vector2D("acceleration", m_pcentroid);
	m_plin_velocity=new Vector2D("velocity", m_pcentroid);
	m_torque=robject.getTorque();
	m_rot_acceleration=robject.getRotAcceleration();
	m_rot_velocity=robject.getRotVelocity();

	m_fmove=robject.getFMove();
	m_fcollide=robject.getFCollide();
	//printf("ROBJECT op= 6\n");
}

/*void RObject2D::operator*=(double k)//:)
{
	;
}*/


/*bool testCollide(RObject2D& robject1, RObject2D& robject2)
{
	bool test(false);

	if (testIntersect(*(robject1.getPolygon()), *(robject2.getPolygon())))
		test=true;
	return test;
}*/

template<typename T> inline bool operator==(const RObject3D<T>& robject1, const RObject3D<T>& robject2) {
	bool test(false);
	return test;
}



/*void print(RObject2D* probject, unsigned int indent)
{
	if (probject!=NULL)
	{
		if (indent==0)
		{
			//printf("\nRigidObject2D(%lu)(%lu) (%p):\n", pobject->getPPoints().size(), pobject->getPEdges().size(), pobject);
			printf("\nRObject2D:\n");
		}

		printTabs(indent+1);
		printf(".Mass: ");
		print(&probject->getMass());
		printf("\n");

		printTabs(indent+1);
		printf(".Charge: ");
		print(&probject->getCharge());
		printf("\n");

//		printTabs(indent+1);
//		printf(".Inertia moment: ");
//		print(&probject->getInertiaMoment());
//		printf("\n");

		printTabs(indent+1);
		printf(".Centroid: \n");
		print(probject->getPCentroid(), indent+1);
		printf("\n");

//		printTabs(indent+1);
//		printf(".Rot center: \n");
//		print(prigid_object->getPRotationCenter(), indent+1);
//		printf("\n");

		printTabs(indent+1);
		printf(".Force: \n");
		print(probject->getPForce(), indent+1);
		printf("\n");

		printTabs(indent+1);
		printf(".Lin Acceleration: \n");
		print(probject->getPLinAcceleration(), indent+1);
		printf("\n");

		printTabs(indent+1);
		printf(".Lin Velocity: \n");
		print(probject->getPLinVelocity(), indent+1);
		printf("\n");

		printTabs(indent+1);
		printf(".Torque: ");
		print(&probject->getTorque());
		printf("\n");

		printTabs(indent+1);
		printf(".Rot Acceleration: ");
		print(&probject->getRotAcceleration());
		printf("\n");

		printTabs(indent+1);
		printf(".Rot Velocity: ");
		print(&probject->getRotVelocity());
		printf("\n");

		printTabs(indent+1);
		printf(".Move?: %s\n", probject->getFMove() ? "True" : "False");

		printTabs(indent+1);
		printf(".Collide?: %s\n", probject->getFCollide() ? "True" : "False");

		//printTabs(indent+1);
		//printf(".Polygon(%lu)(%lu): \n", pobject->getPPoints().size(), pobject->getPEdges().size());
		//print(pobject->getPPolygon(), indent+1);
		//printf("\n");
	}
}*/


#endif /* ROBJECT3D_HPP_ */
