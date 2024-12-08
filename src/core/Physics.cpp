/*
 * Physics.cpp
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#include "Physics.h"

Physics::Physics() {
	m_pps=30;//Computations per second
	m_speed=1;//Speed of the simulation

	m_fcollide=false;
	m_fpause=true;
}

Physics::~Physics() {
	m_ptime_sensitives.clear();
}

Physics::Physics(const Physics& phys) {
	m_pps=phys.getPPS();
	m_speed=phys.getSpeed();

	m_fcollide=phys.getFCollide();
	m_fpause=true;
}



unsigned char Physics::getPPS() const {
	return m_pps;
}

void Physics::setPPS(const unsigned char& pps) {
	m_pps=pps;
}

float Physics::getSpeed() const {
	return m_speed;
}

void Physics::setSpeed(const float& speed) {
	m_speed=speed;
}

bool Physics::getFCollide() const {
	return m_fcollide;
}

void Physics::setFCollide(const bool& fcollide) {
	m_fcollide=fcollide;
}

bool Physics::getFPause() const {
	return m_fpause;
}

void Physics::setFPause(const bool& fpause) {
	m_fpause=fpause;
}

std::unordered_set<TimeSensitive*> Physics::getPTimeSensitives() {
	return m_ptime_sensitives;
}

bool Physics::addPTimeSensitive(std::shared_ptr<TimeSensitive> ptime_sensitive) {
	bool success=false;
	if (ptime_sensitive!=NULL){
		success=m_ptime_sensitives.insert(ptime_sensitive.get()).second;
	}
	return success;
}

/*std::unordered_set<Moveable*> Physics::getPMoveables() {
	return m_pmoveables;
}*/

/*bool Physics::addPMoveable(Moveable* pmoveable) {
	bool success=false;
	if (pmoveable!=NULL){
		success=m_pmoveables.insert(pmoveable).second;
	}
	return success;
}*/


/*bool Physics::loop() {

	std::chrono::time_point t1=std::chrono::system_clock::now();
	while(!m_fpause){
		std::chrono::time_point t2=std::chrono::system_clock::now();
		std::chrono::duration dt=t2-t1;
		if (dt.count()>=1/(long double)m_cps*1000000000.){
			for(TimeSensitive* ptime_sensitive : m_ptime_sensitives){

				//std::cout << "\n delta t = " << dt.count() << "ns\n";

				ptime_sensitive->setT(dt.count()/1000000000.*m_speed);//The duration given by dt is in ns.
			}
			t1=t2;
		}
	}
	return m_fpause;
}*/

/*
 * If 0: infinite loop
 */
bool Physics::run(const unsigned int& steps) {
	std::chrono::time_point t1=std::chrono::system_clock::now();
	if (!m_fpause){
		unsigned int i(0);
		while (i<=steps){
			std::chrono::time_point t2=std::chrono::system_clock::now();
			std::chrono::duration dt=t2-t1;

			if (dt.count()>=1/(long double)m_pps*1000000000.){
				//printf("dt: %f\n", (float)(dt.count()/1000000000.));
				this->iterate(dt.count()/1000000000.);//The duration given by dt is in ns.

				t1=t2;
				if (steps!=0){//If steps is not null
					i++;
				}
			}
		}
	}
	return m_fpause;
}

bool Physics::iterate(const float& dt) {
	for (TimeSensitive* ptime_sensitive : m_ptime_sensitives){
		//printf("\nHello1\n");
		ptime_sensitive->setT(dt*m_speed);
		//printf("%f\n", dt*m_speed);
		ptime_sensitive->apply();//THE PROBLEM(REPAIRED)
	}
	return m_fpause;
}


std::string Physics::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";
	mes+=to_stringTabs(indent);

	//if (full_info){
		mes+="PHYSICS[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" : "");
	//}
	//mes+=((spread)?"\n" : " ");
	mes+=to_stringTabs(indent+1);
	mes+="speed=" + std::to_string(m_speed) + " | fcollide=" + std::to_string(m_fcollide) + " | fpause=" + std::to_string(m_fpause) + "\n";

	mes+=to_stringTabs(indent+1);
	mes+="* List Time Sensitive:\n";
	//int i=0;

	if (full_info){
		for (TimeSensitive* ptime_sensitive : m_ptime_sensitives){
			//i++;
			mes+="\n";
			mes+=to_stringTabs(indent+2);
			mes+="*\n";
			//mes+=std::to_string(i);
			//mes+=" ";
			mes+=ptime_sensitive->to_string(spread, full_info, indent+2);
		}
	}

	return mes;
}

void Physics::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



