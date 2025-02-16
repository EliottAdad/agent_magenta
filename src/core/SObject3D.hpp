/*
 * SObject3D.hpp
 *
 *  Created on: 09 janv 2025
 *      Author: esn
 */

#ifndef SOBJECT2D_HPP_

#define SOBJECT2D_HPP_


#include <memory>
#include <string>
#include <unordered_set>

#include "../core/Point3D.hpp"
#include "../utilities/functions.hpp"
#include "../core/SN.hpp"
#include "../core/Vector3D.hpp"
#include "Particle3D.hpp"
#include "Object3D.hpp"
//#include "/home/elitim/Documents/EliottL/C++/Tools/Maths/Matrix.cpp"


/*
 * ################
 *  SObject3D<T> :)
 * ################
 */
template<typename T> class SObject3D : public Object3D<T> {
	public:
	SObject3D();//:)
	//SObject3D(std::string name="sobject", SDL_Color pcolor=NULL);//:)
	SObject3D(const SObject3D& sobject);//:)
	~SObject3D();

	T& getMass();//:)
	void setMass(T mass=(T)1);//:)
	T& getCharge();//:)
	void setCharge(T charge=(T)0);//:)
	//LSN& getInertiaMoment();//:)
	//void setInertiaMoment(LSN inertia_moment={1, 0});//:)

	//Point2D* getPosition(long double delta_t);//0
	//Point2D& getCentroid();//:)
	//Point2D& getRotationCenter();
	//Point2D* getPRotationCenter();
	//void setRotationCenter(Point2D rot_center);
	
	//std::vector<Point2D*>& getPPoints();//:)
	//void setPoints(std::vector<Point2D*> ppoints, char coords_system='l');//:)
	//void setPoint(Point2D point, char coords_system='l');//:)
	//std::vector<Line2D*>& getPEdges();//:)
	//void setEdges(std::vector<Point2D*> ppoints);//:)
	//void setEdge(Point2D* ppoint1=NULL, Point2D* ppoint2=NULL);//:)
	//void setEdges(std::vector<Segment2D*> pedges);//:)
	
	//Vector2D& getForce();//:)
	/*Vector2D* getPForce();//:)
	void setForce(Vector2D force, bool fadd=false, long double delta_t=0);
	//Vector2D& getLinAcceleration();//:)
	Vector2D* getPLinAcceleration();//:)
	void setLinAcceleration(Vector2D lin_acceleration, bool fadd=false, long double delta_t=0);//:)
	//Vector2D& getLinVelocity();//:)
	Vector2D* getPLinVelocity();//:)
	void setLinVelocity(Vector2D lin_velocity, bool fadd=false);
	LSN& getTorque();//:)
	void setTorque(LSN torque={0, 0}, bool fadd=false, long double delta_t=0);//:)
	LSN& getRotAcceleration();//:)
	void setRotAcceleration(LSN acceleration={0, 0}, bool fadd=false, long double delta_t=0);//:)
	LSN& getRotVelocity();//:)
	void setRotVelocity(LSN velocity={0, 0}, bool fadd=false);//:)*/
	
	void move(long double dt);//:)
	void spin(long double dt);//:)
	
	//void delProperties();//:)
	//void delEdges();//:)
	
	//bool testPresencePoint(Point2D* ppoint=NULL);//:) Test the presence of a point in a system of coords.
	//bool testPresenceProperty(void* pproperty=NULL);//:) Test the presence of a point in a system of coords.
	//void calculateGeometricCenter();//:)
	//void calculateInertiaMoment();//0

	//void operator*=(double k);//:)


	private:
	std::unordered_set<std::shared_ptr<Particle3D<T>>> m_pparticules;							// Array of particules forming the mesh.
	Matrix<float> m_C;														// Matrix of the coefficients.
	Matrix<T> m_Di;													// Matrix of the initial distances between the particules.
	Matrix<T> m_D;														// Matrix of the actual distances between the particules.
	
	//Vector2D* m_pforce;												// Resultant force
	//Vector2D* m_plin_acceleration;									// Resultant acceleration vector
	//Vector2D* m_plin_velocity;										// Resultant velocity vector

	//LSN m_torque;													// Resultant rotational torque(moment) (in Nm)
	//LSN m_rot_acceleration;											// Resultant rotational acceleration (in rad/s**2)
	//LSN m_rot_velocity;												// Resultant rotational velocity (in rad/s)
};


//void print(SObject2D* psobject, unsigned int indent=0);//:)


template<typename T> inline SObject3D<T>::SObject3D() {
	/*m_mass=1;
	m_charge={0, 0};
	m_inertia_moment={1, 0};
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
	//printf("Hey5\n");*/
}

/*template<typename T> SObject3D<T>::SObject3D(std::string name, SDL_Color pcolor) {
	m_name=name;
	m_mass={1, 1};
	m_charge={0, 0};
	m_inertia_moment={1, 0};
	m_pcolor=pcolor;

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
}*/

template<typename T> inline SObject3D<T>::SObject3D(const SObject3D& sobject) {
	/*printf("OU1\n");
	m_name=psobject->getName();
	printf("OU2\n");
	m_mass=psobject->getMass();
	printf("OU3\n");
	m_charge=psobject->getCharge();
	printf("OU4\n");
	m_inertia_moment=pobject->getInertiaMoment();
	printf("OU5\n");
	m_pcolor=psobject->getPColor();
	printf("OU6\n");

	printf("%p\n", m_pcentroid);
	printf("%p\n", psobject->getPCentroid());
	m_pcentroid=new Point2D{psobject->getPCentroid()};
	printf("OU7\n");
	m_prot_center=new Point2D{*psobject->getPRotationCenter()};
	printf("OU8\n");
	//m_ppolygon=new Polygon2D(pobject->getPPolygon());
	printf("OU9\n");
	//m_pcollision_box=new Polygon2D(pobject->getPCollisionBox());
	printf("OU10\n");

	m_pforce=new Vector2D(m_pcentroid, psobject->getPForce()->getEnd());
	m_plin_acceleration=new Vector2D(m_pcentroid, psobject->getPLinAcceleration()->getEnd());
	m_plin_velocity=new Vector2D(m_pcentroid, psobject->getPLinVelocity()->getEnd());
	m_torque=psobject->getTorque();
	m_rot_acceleration=psobject->getRotAcceleration();
	m_rot_velocity=psobject->getRotVelocity();

	m_fmove=psobject->getFMove();
	m_fcollide=psobject->getFCollide();*/
}

template<typename T> inline SObject3D<T>::~SObject3D() {
	//m_pcolor=NULL;
	/* We delete the properties.*/
	//this->delProperties();
	/* We delete the points and segments.*/
	//delete m_ppolygon;
	//delete m_pcollision_box;
	/* Give back the instances used.*/
	delete m_pcentroid;
	delete m_prot_center;

	delete m_pforce;
	delete m_plin_acceleration;
	delete m_plin_velocity;
}






/*LSN& SObject2D::getMass()
{
	return m_mass;
}

void SObject2D::setMass(LSN mass)
{
	m_mass=mass;
}

LSN& Object2D::getCharge()
{
	return m_charge;
}

void Object2D::setCharge(LSN charge)
{
	m_charge=charge;
}*/





/*Point2D& Object2D::getCentroid(){
	return *m_pcentroid;
}*/

/*Point2D* Object2D::getPCentroid()
{
	return m_pcentroid;
}

void Object2D::setCentroid(Point2D point)
{
	*m_pcentroid=point;
	//m_pforce->translateTo(ppoint);
	//m_plin_acceleration->translateTo(ppoint);
	//m_plin_velocity->translateTo(ppoint);
}*/

/*Point2D& Object2D::getRotationCenter()
{
	return *m_prot_center;
}*/

/*Point2D* Object2D::getPRotationCenter()
{
	return m_prot_center;
}

void Object2D::setRotationCenter(Point2D rot_center)
{
	*m_prot_center=rot_center;
}*/







/*Polygon2D* Object2D::getPPolygon()
{
	return m_ppolygon;
}

void Object2D::setPolygon(Polygon2D& polygon)
{
	*m_ppolygon=polygon;
}*/

/*Polygon2D* Object2D::getPCollisionBox()
{
	return m_pcollision_box;
}

void Object2D::setCollisionBox(Polygon2D& collision_box)
{
	*m_pcollision_box=collision_box;
}*/

/*void Object2D::setEdges(std::vector<Segment2D*> pedges)//:)
{
	for (int i(0) ; i<(int)pedges.size() ; i++)
	{
		this->setEdge(pedges[i]);
	}
}*/

/*std::vector<Point2D*>& Object2D::getPPoints()
{
	return m_ppolygon->getPPoints();
}

void Object2D::setPoints(std::vector<Point2D*> ppoints, char coords_system)
{
	printf("AAA\n");
	int szppoints(ppoints.size());
	for (int i(0) ; i<szppoints ; i++)
	{
		printf("AAA1\n");
		this->setPoint(*ppoints[i], coords_system);
		printf("AAA2\n");
	}
	printf("BBB\n");
	//this->calculateGeometricCenter();
}

void Object2D::setPoint(Point2D point, char coords_system)
{
	printf("SETPOINT\n");
	if (coords_system=='g')
		point-=*m_pcentroid;
	m_ppolygon->setPoint(point);
}

std::vector<Line2D*>& Object2D::getPEdges()
{
	return m_ppolygon->getPEdges();
}

void Object2D::setEdges(std::vector<Point2D*> ppoints)//:)
{
	m_ppolygon->setEdges(ppoints);
}

void Object2D::setEdge(Point2D* ppoint1, Point2D* ppoint2)//:)
{
	m_ppolygon->setEdge(ppoint1, ppoint2);
}*/



/////////////////////////////////////////////////////////////////////////

/*Vector2D* Object2D::getPForce()//:)
{
	return m_pforce;
}

void Object2D::setForce(Vector2D force, bool fadd, long double delta_t)//:)
{
	////printf("Delta_t: %Lg\n", delta_t);
	//*pforce *= m_damping;
	//printf("Norm forceBEF: %Lg\n", pforce->getNorm());
	//printf("Norm force resultantBEF: %Lg\n", m_pforce->getNorm());
	if (fadd)
		*m_pforce+=force;
	else
		*m_pforce=force;
	//*m_plin_force += *(*pforce*delta_t);
	//m_plin_force->setEnd((*pforce*delta_t)->getEnd());
	//printf("Norm force resultantAF: %Lg\n", m_pforce->getNorm());
	//this->setTorque(getVectorialProduct(new Vector2D(pforce->getOrigin(), m_prot_center)), delta_t );// Calculate the resultant torque.

	// If the object can move.
	if (m_fmove)
	{
		//*pforce/=m_mass;
		this->setLinAcceleration(force/m_mass, fadd, delta_t);
	}
}*/

/*Vector2D& Object2D::getLinAcceleration()//:)
{
	return *m_plin_acceleration;
}*/

/*Vector2D* Object2D::getPLinAcceleration()//:)
{
	return m_plin_acceleration;
}

void Object2D::setLinAcceleration(Vector2D lin_acceleration, bool fadd, long double delta_t)//:|
{
	//printf("*Norm acceleration: %Lgx10^%li\n", plin_acceleration->getNorm().m, plin_acceleration->getNorm().exp);
	//printf("*Norm m_accelerationBEFORE: %Lg\n", m_plin_acceleration->getNorm());
	////printf("*Norm force: %Lg\n", m_plin_force->getNorm());
	if (fadd)
		*m_plin_acceleration+=lin_acceleration;
	else
		*m_plin_acceleration=lin_acceleration;
	//*m_plin_acceleration += *(*m_plin_force / m_mass);
	//m_plin_acceleration->setEnd((*m_plin_force / m_mass)->getEnd());
	//printf("*Norm m_accelerationAFTER: %Lg\n", m_plin_acceleration->getNorm());

	////printf("Delay: %Lg\n", delta_t);
	//*plin_acceleration*=delta_t;
	this->setLinVelocity(lin_acceleration*delta_t, true);
	//printf("99999999999999999999 B3_2_3_3\n");
}*/

/*Vector2D& Object2D::getLinVelocity()//:)
{
	return *m_plin_velocity;
}*/

/*Vector2D* Object2D::getPLinVelocity()//:)
{
	return m_plin_velocity;
}

void Object2D::setLinVelocity(Vector2D lin_velocity, bool fadd)//:)
{
	//printf("*fAdd2: %i\n", fadd);
	//printf("*Norm velocityBEFORE: %Lg\n", plin_velocity->getNorm());
	//printf("*Norm m_velocityBEFORE: %Lg\n", m_plin_velocity->getNorm());
	if (fadd)
		*m_plin_velocity+=lin_velocity;
	else
		*m_plin_velocity=lin_velocity;
	//printf("*Norm m_velocityAFTER: %Lg\n", m_plin_velocity->getNorm());
}

LSN& Object2D::getTorque()//:)
{
	return m_torque;
}

void Object2D::setTorque(LSN torque, bool fadd, long double delta_t)//:)
{
	if (fadd)
		m_torque+=torque;
	else
		m_torque=torque;
	// If the object can move.
	if (m_fmove)
		this->setRotAcceleration(torque/m_inertia_moment, fadd, delta_t);
}

LSN& Object2D::getRotAcceleration()//:)
{
	return m_rot_acceleration;
}

void Object2D::setRotAcceleration(LSN rot_acceleration, bool fadd, long double delta_t)//:|
{
	if (fadd)
		m_rot_acceleration+=rot_acceleration;
	else
		m_rot_acceleration=rot_acceleration;

	this->setRotVelocity(m_rot_acceleration*delta_t, true);
}

LSN& Object2D::getRotVelocity()//:)
{
	return m_rot_velocity;
}

void Object2D::setRotVelocity(LSN rot_velocity, bool fadd)//:|
{
	if (fadd)
		m_rot_velocity+=rot_velocity;
	else
		m_rot_velocity=rot_velocity;

	//this->calculateRotation(delta_t);
}*/

template<typename T> inline void SObject3D<T>::move(long double delta_t) {
	printf("C1\n");
	//printf("*Norm velocity: %Lgx10^%lim/s.\n", m_plin_velocity->getNorm().m, m_plin_velocity->getNorm().exp);
	//m_lin_velocity * delta_t;
	printf("C1_1\n");
	//Vector2D pos_plus=m_lin_acceleration * (1/2) * pow(delta_t, 2) + m_lin_velocity * delta_t;
	printf("C1_2\n");
	printf("%p\n", m_pcentroid);
	printf("%p\n", m_plin_acceleration->getPOrigin());
	Point2D delta_d=/*m_plin_acceleration->getEnd() * (1/2) * pow(delta_t, 2) + */m_plin_velocity->getEnd() * delta_t;
	print(&delta_d);
	*m_pcentroid += delta_d;
	printf("C2\n");
	//printf("/////////ppos_plus->getNorm(): %Lg\n", ppos_plus->getNorm());
	printf("/////////pos_plus.getEnd(): \n");
	//print(pos_plus.getEnd());
	printf("\n");
	//m_polygon.translate(pos_plus);
	//*m_pcentroid += *(new Point2D{1, 1});
	////printf("*Norm velocity: %Lgm/s.\n", m_plin_velocity->getNorm());
	////printf("C3\n");
}

template<typename T> void SObject3D<T>::spin(long double delta_t) {
	long double angle_plus=(1/2) * m_rot_acceleration * pow(delta_t, 2) + m_rot_velocity * delta_t;
	//m_ppolygon->rotate(angle_plus/*, m_rot_center*/);
}



////////////////////////////////////////////////


/*void Object2D::delProperties()
{
	int szpproperties(m_pproperties.size());
	for (int i(0) ; i<szpproperties ; i++)
	{
		delete *m_pproperties.begin();
		m_pproperties.erase(m_pproperties.begin());
	}
}

void Object2D::delEdges()
{
	int szpedges(m_ppolygon->getPoints().size());
	for (int i(0) ; i<szpedges ; i++)
	{
		delete *m_pedges.begin();
		m_ppoints.erase(m_ppoints.begin());
	}
}*/





/*bool Object2D::getFMove()
{
	return m_fmove;
}

void Object2D::setFMove(bool fmove)
{
	m_fmove=fmove;
}

bool Object2D::getFCollide()
{
	return m_fcollide;
}

void Object2D::setFCollide(bool fcollide)
{
	m_fcollide=fcollide;
}*/






/*bool Object2D::testPresencePoint(Point2D* ppoint)
{
	return m_ppolygon->testPresencePoint(ppoint);
}*/

/*bool Object2D::testPresenceProperty(void* pproperty)
{
	bool test(false);

	if (pproperty!=NULL)
	{
		int szpproperties(m_pproperties.size());
		for (int i(0) ; i<szpproperties ; i++)
		{
			if (m_pproperties[i]==pproperty)
			{
				test=true;
				// To stop the loop.
				i=szpproperties;
			}
		}
	}
	return test;
}*/



/*void Object2D::calculateGeometricCenter()//:)TOpt
{
	//float average_x(0);
	//float average_y(0);
	Point2D average_point={{0, 0}, {0, 0}};

	int szppoints(m_ppolygon->getPPoints().size());
	for (int i(0) ; i<szppoints ; i++)
	{
		average_point+=*m_ppolygon->getPPoints()[i];
	}
	average_point/=szppoints;

	*m_pcentroid=average_point;
}

void Object2D::calculateInertiaMoment()//:) I=mr**2
{
	;
}



bool operator==(Object2D const& object1, Object2D const& object2)//:)
{
	bool test(false);
	return test;
}

void Object2D::operator*=(double k)//:)
{
	;
}*/


/*bool testCollide(Object2D& object1, Object2D& object2)
{
	bool test(false);

	if (testIntersect(*(object1.getPolygon()), *(object2.getPolygon())))
		test=true;
	return test;
}*/



/*void print(SObject3D* psobject, unsigned int indent)
{
	if (psobject!=NULL)
	{
		if (indent==0)
		{
			printf("\nSObject2D(%p):\n", psobject);
		}

		printTabs(indent+1);
		printf(".Mass: ");
		print(&psobject->getMass());
		printf("\n");

		printTabs(indent+1);
		printf(".Charge: ");
		print(&psobject->getCharge());
		printf("\n");

		printTabs(indent+1);
		printf(".Inertia moment: ");
		print(&psobject->getInertiaMoment());
		printf("\n");

		printTabs(indent+1);
		printf(".Centroid: \n");
		print(psobject->getPCentroid(), indent+1);
		printf("\n");

		printTabs(indent+1);
		printf(".Rot center: \n");
		print(psobject->getPRotationCenter(), indent+1);
		printf("\n");

		printTabs(indent+1);
		printf(".Force: \n");
		print(psobject->getPForce(), indent+1);
		printf("\n");

		printTabs(indent+1);
		printf(".Lin Acceleration: \n");
		print(psobject->getPLinAcceleration(), indent+1);
		printf("\n");

		printTabs(indent+1);
		printf(".Lin Velocity: \n");
		print(psobject->getPLinVelocity(), indent+1);
		printf("\n");

		printTabs(indent+1);
		printf(".Torque: ");
		print(&psobject->getTorque());
		printf("\n");

		printTabs(indent+1);
		printf(".Rot Acceleration: ");
		print(&psobject->getRotAcceleration());
		printf("\n");

		printTabs(indent+1);
		printf(".Rot Velocity: ");
		print(&psobject->getRotVelocity());
		printf("\n");

		printTabs(indent+1);
		printf(".Move?: %s\n", psobject->getFMove() ? "True" : "False");

		printTabs(indent+1);
		printf(".Collide?: %s\n", psobject->getFCollide() ? "True" : "False");

		//printTabs(indent+1);
		//printf(".Polygon(%lu)(%lu): \n", psoftobject->getPPoints().size(), psoftobject->getPEdges().size());
		//print(pobject->getPPolygon(), indent+1);
		//printf("\n");
	}
}*/








#endif
