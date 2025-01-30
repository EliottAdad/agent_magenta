/*
 * Physics.cpp
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#include "Physics.h"

Physics::Physics() {
	pps=40;//Computations per second
	speed=1;//Speed of the simulation

	fcollide=false;
	fpause=true;
}

Physics::Physics(const float& speed, const unsigned char& pps) {
	this->pps=pps;//Computations per second
	this->speed=speed;//Speed of the simulation

	fcollide=false;
	fpause=true;
}

Physics::~Physics() {
	ptime_sensitives.clear();
}

Physics::Physics(const Physics& phys) {
	pps=phys.pps;
	speed=phys.speed;

	fcollide=phys.fcollide;
	fpause=true;
}


std::unordered_set<std::shared_ptr<TimeSensitive>> Physics::getPTimeSensitives() {
	return ptime_sensitives;
}

bool Physics::addPTimeSensitive(std::shared_ptr<TimeSensitive> ptime_sensitive) {
	bool success=false;

	if (ptime_sensitive!=NULL){
		success=ptime_sensitives.insert(ptime_sensitive).second;
		//printf("Shush\n");
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
	while(!fpause){
		std::chrono::time_point t2=std::chrono::system_clock::now();
		std::chrono::duration dt=t2-t1;
		if (dt.count()>=1/(long double)m_cps*1000000000.){
			for(TimeSensitive* ptime_sensitive : ptime_sensitives){

				//std::cout << "\n delta t = " << dt.count() << "ns\n";

				ptime_sensitive->setT(dt.count()/1000000000.*speed);//The duration given by dt is in ns.
			}
			t1=t2;
		}
	}
	return fpause;
}*/

/*
 * If 0: infinite loop
 */
bool Physics::run(const unsigned int& steps) {
	std::chrono::time_point t1=std::chrono::system_clock::now();
	if (!fpause){
		unsigned int i(0);
		while (i<=steps){
			std::chrono::time_point t2=std::chrono::system_clock::now();
			std::chrono::duration dt=t2-t1;

			if (dt.count()>=1/(long double)pps*1000000000.){
				//printf("dt: %f\n", (float)(dt.count()/1000000000.));
				this->iterate(dt.count()/1000000000.);//The duration given by dt is in ns.

				t1=t2;
				if (steps!=0){//If steps is not null
					i++;
				}
			}
		}
	}
	return fpause;
}

bool Physics::iterate(const float& dt) {
	for (std::shared_ptr<TimeSensitive> ptime_sensitive : ptime_sensitives){
		//printf("\niterate(dt:%f)\n", dt*speed);
		ptime_sensitive->setT(dt*speed);
		//printf("%f\n", dt*speed);
		ptime_sensitive->apply();//THE PROBLEM(REPAIRED)
	}
	return fpause;
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
	mes+="speed=" + std::to_string(speed) + " | fcollide=" + std::to_string(fcollide) + " | fpause=" + std::to_string(fpause) + "\n";

	mes+=to_stringTabs(indent+1);
	mes+="* List Time Sensitive:\n";
	//int i=0;

	if (full_info){
		for (std::shared_ptr<TimeSensitive> ptime_sensitive : ptime_sensitives){
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



