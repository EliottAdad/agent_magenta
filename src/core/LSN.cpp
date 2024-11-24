/*
 * LSN.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#include "LSN.h"



/*
 * Methods of LSN
 */

LSN::LSN() {
	m=0;
	e=0;
}

LSN::LSN(long double m, long int e) {
	this->m=m;
	this->e=e;
	this->recal();
}

/* :( Doesn't work for negative numbers
 * Recalculate the LSN under scientific notation.
 * Ex: 1.27x10⁹
 */
void LSN::recal() {//Sometimes doesn't work properly (because of the cast to an int Ex: (int)10.0000=9 when 10 is a double)
	//printf(("Number : "+this->to_string()+"\n").c_str());
	if (m==0){
		e=0;
	}else{
		//std::cout<<"m!=0\n";
		int l_m=std::log(abs(m)) / std::log(10);//Number of chiffres avant/après la virgule

		e+=(l_m);
		m/=std::pow(10, (l_m));
	}
}

long double LSN::to_long_double() const {
	return (this->m)*(long double)(pow(10, this->e));
}

void LSN::operator=(const LSN& nb) {
	this->m=nb.m;
	this->e=nb.e;
	this->recal();
}

void LSN::operator=(const long double& nb) {
	this->m=nb;
	this->e=0;
	this->recal();
}

void LSN::operator+=(const LSN& nb) {
	this->m+=nb.m*pow(10., (long double)(nb.e-this->e));
	this->recal();
}

void LSN::operator+=(const long double& nb) {//X
	this->m+=nb/pow(10., (long double)(this->e));
	this->recal();
}

void LSN::operator-=(const LSN& nb) {
	this->m-=nb.m*pow(10., (long double)(nb.e-this->e));
	this->recal();
}

void LSN::operator-=(const long double& nb) {
	this->m-=nb/pow(10., (long double)(this->e));
	this->recal();
}

void LSN::operator*=(const LSN& nb) {
	this->m*=nb.m;
	this->e+=nb.e;
	this->recal();
}

void LSN::operator/=(const LSN& nb) {
	this->m/=nb.m;
	this->e-=nb.e;
	this->recal();
}

void LSN::operator*=(const long double& k) {
	this->m*=k;
	this->recal();
}

void LSN::operator/=(const long double& k) {
	this->m/=k;
	this->recal();
}







/*:)
 *
 */
bool operator==(const LSN& nb1, const LSN& nb2) {
	if (nb1.m==nb2.m && nb1.e==nb2.e)							// If e and m are the same. A and B.
		return true;

	return false;
}

/*
 * :)
 */
bool operator!=(const LSN& nb1, const LSN& nb2) {
	if (nb1.m!=nb2.m || nb1.e!=nb2.e)							// If e and m are not the same. n(A and B)=nA or nB.
		return true;

	return false;
}

bool operator!=(const LSN& nb1, const long double& nb2) {
	if (nb1.m!=nb2/pow(10., (long double)nb1.e))							//
		return true;

	return false;
}

bool operator!=(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10., (long double)nb2.e)!=nb2.m)							//
		return true;

	return false;
}

/*
 * :)
 */
bool operator<=(const LSN& nb1, const LSN& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e-nb2.e))<=nb2.m){	// .
		return true;
	}
	return false;
}

bool operator<=(const LSN& nb1, const long double& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e))<=nb2){
		return true;
	}
	return false;
}

bool operator<=(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10., (long double)(nb2.e))<=nb2.m){	//
		return true;
	}
	return false;
}

bool operator>=(const LSN& nb1, const LSN& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e-nb2.e))>=nb2.m){	// .
		return true;
	}
	return false;
}

bool operator>=(const LSN& nb1, const long double& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e))>=nb2){	// .
		return true;
	}
	return false;
}

bool operator>=(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10., (long double)(nb2.e))>=nb2.m){	// .
		return true;
	}
	return false;
}

bool operator<(const LSN& nb1, const LSN& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e-nb2.e))<nb2.m){	// .
	//if (nb1.e<nb2.e or (nb1.e==nb2.e and nb1.m<nb2.m)){		// Else if the e are the same but m1<m2.
		return true;
	}
	return false;
}

bool operator<(const LSN& nb1, const long double& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e))<nb2){	// .
	//if (nb1.m<nb2/pow(10, nb1.e)){
		return true;
	}
	return false;
}

bool operator<(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10., (long double)(nb2.e))<nb2.m){	// .
	//if (nb1/pow(10, nb2.e)<nb2.m){
		return true;
	}
	return false;
}

bool operator>(const LSN& nb1, const LSN& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e-nb2.e))>nb2.m){	// .
	//if (nb1.e>nb2.e or (nb1.e==nb2.e and nb1.m>nb2.m)){		// Else if the e are the same but m1>m2.
		return true;
	}
	return false;
}

bool operator>(const LSN& nb1, const long double& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e))>nb2){	// .
	//if (nb1.m>nb2/pow(10, nb1.e)){
		return true;
	}
	return false;
}

bool operator>(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10., (long double)(nb2.e))>nb2.m){	// .
	//if (nb1/pow(10, nb2.e)>nb2.m){
		return true;
	}
	return false;
}

/*:)
 * It's better to enter the bigger number first I think.
 */
LSN operator+(const LSN& nb1, const LSN& nb2) {
	return {nb1.m+nb2.m/pow(10., (long double)(nb1.e-nb2.e)), nb1.e};
}

LSN operator+(const LSN& nb1, const long double& nb2) {
	LSN nnb(nb1.m+nb2/pow(10., (long double)nb1.e), nb1.e);
	nnb.recal();
	return nnb;
}

LSN operator+(const long double& nb1, const LSN& nb2) {
	LSN nnb(nb1+nb2.m*pow(10., (long double)nb2.e), 0);
	nnb.recal();
	return nnb;
}
/*:)
 * It's better to enter the bigger number first.
 */
LSN operator-(const LSN& nb1, const LSN& nb2) {
	LSN nnb(nb1.m-nb2.m/pow(10., (long double)(nb1.e-nb2.e)), nb1.e);
	nnb.recal();
	return nnb;
}

LSN operator-(const LSN& nb1, const long double& nb2) {
	LSN nnb(nb1.m-nb2/pow(10., (long double)nb1.e), nb1.e);
	nnb.recal();
	return nnb;
}

LSN operator-(const long double& nb1, const LSN& nb2) {
	LSN nnb(nb1-nb2.m*pow(10., (long double)nb2.e), 0);
	nnb.recal();
	return nnb;
}

LSN operator*(const LSN& nb1, const LSN& nb2) {
	LSN nnb(nb1.m*nb2.m, nb1.e+nb2.e);
	nnb.recal();
	return nnb;
}

LSN operator*(const LSN& nb, const long double& k) {
	LSN nnb(nb.m*k, nb.e);
	nnb.recal();
	return nnb;
}

LSN operator*(const long double& k, const LSN& nb) {
	LSN nnb(nb.m*k, nb.e);
	nnb.recal();
	return nnb;
}

LSN operator/(const LSN& nb1, const LSN& nb2) {
	LSN nnb(nb1.m/nb2.m, nb1.e-nb2.e);
	nnb.recal();
	return nnb;
}

LSN operator/(const LSN& nb, const long double& k) {
	LSN nnb(nb.m/k, nb.e);
	nnb.recal();
	return nnb;
}

LSN operator/(const long double& k, const LSN& nb) {
	LSN nnb(nb.m/k, nb.e);
	nnb.recal();
	return nnb;
}



std::string LSN::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="LSN[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" : "");
		mes+=std::to_string(m) + "x10^" + std::to_string(e);
	}else{
		mes+=std::to_string(m).erase(4, std::to_string(m).length()) + "e" + std::to_string(e);
	}

	return mes;
}

void LSN::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


/*
 * Functions
 */

LSN abs(const LSN& nb) {
	LSN resp{std::abs(nb.m), nb.e};
	//resp.recal();
	return resp;
}

LSN pow(const LSN& nb, const long int& e) {
	LSN resp{pow(nb.m, (long double)e), nb.e*e};
	resp.recal();
	return resp;
}

/*// Calculate the n root of a number
LSN nrt(LSN& nb, long int e) {
	//LSN nb2={1, 0};
	for (long int i(0) ; i<nb.e%e ; i++)
	{
		nb.m*=nb;
	}
	recal(nb2);
	return *(new LSN{pow(nb.m, e), nb.e*e});
}*/

/*
 * Calculate the square root of a number.
 */

LSN sqrt(const LSN& nb) {
	LSN resp={pow(nb.m, 0.5), nb.e/2};//Doesn't work (exponent cast to int)
	resp.recal();
	return resp;
}




