/*
 * Physics.cpp
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#include "Physics.h"

Physics::Physics() {
	m_cps=60;//Computations per second
	m_speed=1;//Speed of the simulation

	m_fcollide=false;
	m_fpause=true;
}

Physics::~Physics() {
	// TODO Auto-generated destructor stub
}

Physics::Physics(const Physics& phys) {
	m_cps=phys.getCPS();
	m_speed=phys.getSpeed();

	m_fcollide=phys.getFCollide();
	m_fpause=true;
}



unsigned int Physics::getCPS() const {
	return m_cps;
}

void Physics::setCPS(const unsigned int& cps) {
	m_cps=cps;
}

float Physics::getSpeed() const {
	return m_speed;
}

void Physics::setSpeed(const float& speed) {
	m_speed=speed;
}

unsigned int Physics::getFCollide() const {
	return m_fcollide;
}

void Physics::setFCollide(const bool& fcollide) {
	m_fcollide=fcollide;
}

unsigned int Physics::getFPause() const {
	return m_fpause;
}

void Physics::setFPause(const bool& fpause) {
	m_fpause=fpause;
}

std::unordered_set<TimeSensitive*> Physics::getPTimeSensitives() {
	return m_ptime_sensitives;
}

bool Physics::addPTimeSensitive(TimeSensitive* ptime_sensitive) {
	bool success=false;
	if (ptime_sensitive!=NULL){
		success=m_ptime_sensitives.insert(ptime_sensitive).second;
	}
	return success;
}

std::unordered_set<Moveable*> Physics::getPMoveables() {
	return m_pmoveables;
}

bool Physics::addPMoveable(Moveable* pmoveable) {
	bool success=false;
	if (pmoveable!=NULL){
		success=m_pmoveables.insert(pmoveable).second;
	}
	return success;
}


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

			if (dt.count()>=1/(long double)m_cps*1000000000.){

				//std::cout << "\n delta t = " << dt.count() << "ns\n";
				//std::cout << "\n delta t = " << dt.count()/1000000000. << "s\n";
				//std::cout << "\n 1/cps = " << 1/(long double)m_cps*1000000000 << "ns\n";

				for (TimeSensitive* ptime_sensitive : m_ptime_sensitives){
					ptime_sensitive->setT(dt.count()/1000000000.*m_speed);//The duration given by dt is in ns.
				}

				for (Moveable* pmoveable : m_pmoveables){
					//long double dT=;
					pmoveable->setT(dt.count()/1000000000.*m_speed);//The duration given by dt is in ns.
					pmoveable->apply();
				}
				t1=t2;
				if (steps!=0){//If steps is not null
					i++;
				}
			}
		}
	}
	return m_fpause;
}

/*bool Physics::iterate() {
	return m_fpause;
}*/


std::string Physics::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="PHYSICS";

	if (full_info){
		mes+="():";//Pointer
	}
	mes+=((spread)?"\n" : " ");
	mes+="speed=" + std::to_string(m_speed) +";cps=" + std::to_string(m_cps) + ";fcollide=" + std::to_string(m_fcollide) + ";fpause=" + std::to_string(m_fpause) + "\n";

	mes+="Time Sensitive list:\n";
	int i=0;
	for (TimeSensitive* ptime_sensitive : m_ptime_sensitives){
		i++;
		mes+=std::to_string(i);
		mes+=ptime_sensitive->to_string(true, true, indent+1);
	}
	mes+="\nMoveable list:\n";
	int j=0;
	for (Moveable* pmoveable : m_pmoveables){
		j++;
		mes+=std::to_string(j);
		mes+=pmoveable->to_string(true, true, indent+1);
	}
	return mes;
}

void Physics::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {// :)
	printTabs(indent);
	printf((this->to_string(spread, indent, full_info)).c_str());
}



