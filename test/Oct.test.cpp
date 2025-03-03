/*
 * Oct.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef OCT_TEST_CPP_

#define OCT_TEST_CPP_

#include <boost/test/unit_test.hpp>
#include <string.h>

#include "../src/core/utils_Oct.hpp"
#include "../src/core/utils_Particle3D.hpp"

/*
 * TODO:
 * insert doesn't work
 */


struct FOct {
	Oct<Particle3D<SN<float, char>>, SN<float, char>>* poct;
	Oct<Particle3D<float>, float>* poctf;
	
	FOct() {
		BOOST_TEST_MESSAGE("setup fixture");
		poct=new Oct<Particle3D<SN<float, char>>, SN<float, char>>();
		poct->setPtrGetW(getMass);
		
		poctf=new Oct<Particle3D<float>, float>();
		poctf->setPtrGetW(getMass);
	}
	~FOct() {
		BOOST_TEST_MESSAGE("teardown fixture");
		delete poct;
		delete poctf;
	}
};



BOOST_FIXTURE_TEST_SUITE (Oct_test, FOct) // The name of this serie is Oct_test

	BOOST_AUTO_TEST_CASE (test_constructor_default) { //
		Point3D<SN<float, char>> p(SN<float, char>{0,0}, SN<float, char>{0,0}, SN<float, char>{0,0});
		SN<float, char> a(1,2);
		SN<float, char> b(0,0);
		BOOST_CHECK(poct->getBarycenter() == p);
		BOOST_CHECK(poct->getPoint() == p);

		BOOST_CHECK(poct->getA() == a);
		//BOOST_CHECK(poct->getPoint() == p);
		
		BOOST_CHECK(poct->getPtrGetW() != NULL);
		BOOST_CHECK(poct->tot_weight == b);
	
		BOOST_CHECK(poct->pU == NULL);
		
		BOOST_CHECK(poct->isLeaf() == true);
		BOOST_CHECK(poct->isEmpty() == true);
		
		BOOST_CHECK(poct->alpha == 0.5);
		BOOST_CHECK(poct->ffuse == false);
		
		BOOST_CHECK(poct->getNB_OCTS() == 1);
		
		// Float
		/*Point3D<float> pf(0., 0., 0.);
		BOOST_CHECK(poctf->getBarycenter() == pf);
		BOOST_CHECK(poctf->getPoint() == pf);

		BOOST_CHECK(poctf->isLeaf() == true);
		BOOST_CHECK(poctf->isEmpty() == true);*/
	}
	
	BOOST_AUTO_TEST_CASE (test_constructor) { //
		Point3D<SN<float, char>> p(SN<float, char>{1,0}, SN<float, char>{-1,0}, SN<float, char>{3,0});
		SN<float, char> a(5,1);
		SN<float, char> b(0,0);
		std::shared_ptr<Oct<Particle3D<SN<float, char>>, SN<float, char>>> poct2=std::make_shared<Oct<Particle3D<SN<float, char>>, SN<float, char>>>(a, p);
		
		BOOST_CHECK(poct2->getBarycenter() == p);
		BOOST_CHECK(poct2->getPoint() == p);

		BOOST_CHECK(poct2->getA() == a);
		//BOOST_CHECK(poct->getPoint() == p);
		
		BOOST_CHECK(poct2->getPtrGetW() == NULL);
		BOOST_CHECK(poct2->tot_weight == b);
	
		BOOST_CHECK(poct2->pU == NULL);
		
		BOOST_CHECK(poct2->isLeaf() == true);
		BOOST_CHECK(poct2->isEmpty() == true);
		
		BOOST_CHECK(poct2->alpha == 0.5);
		BOOST_CHECK(poct2->ffuse == false);
		
		BOOST_CHECK(poct2->getNB_OCTS() == 2);
		
		// Float
		/*Point3D<float> pf(0., 0., 0.);
		BOOST_CHECK(poctf->getBarycenter() == pf);
		BOOST_CHECK(poctf->getPoint() == pf);

		BOOST_CHECK(poctf->isLeaf() == true);
		BOOST_CHECK(poctf->isEmpty() == true);*/
	}
	
	BOOST_AUTO_TEST_CASE (test_getPChilds) { //
		std::unordered_set<Oct<Particle3D<SN<float, char>>, SN<float, char>>*> pchilds=poct->getPChilds();
		BOOST_CHECK(pchilds.size() == 0);//Should be at 0 by default.
		
		std::shared_ptr<Particle3D<SN<float, char>>> pp=std::make_shared<Particle3D<SN<float, char>>>(SN<float, char>{1,0}, SN<float, char>{-1,0}, SN<float, char>{3,0});
		poct->insert(pp);
		BOOST_CHECK(pchilds.size() == 0);//Shouldn't have created sub octs.
		
		std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>(SN<float, char>{-1,0}, SN<float, char>{1,0}, SN<float, char>{3,0});
		poct->insert(pp);
		printf("\n#########Nb childs %lu\n", pchilds.size());
		BOOST_CHECK(pchilds.size() == 2);//Should have created 2 sub octs.
	}
	
	BOOST_AUTO_TEST_CASE (test_getPBrothers) { //
		std::unordered_set<Oct<Particle3D<SN<float, char>>, SN<float, char>>*> pbrothers=poct->getPBrothers();
		BOOST_CHECK(pbrothers.size() == 0);//Should be at 0 by default.
		
		std::shared_ptr<Particle3D<SN<float, char>>> pp=std::make_shared<Particle3D<SN<float, char>>>(SN<float, char>{1,0}, SN<float, char>{-1,0}, SN<float, char>{3,0});
		poct->insert(pp);
		BOOST_CHECK(pbrothers.size() == 0);//Shouldn't have created brothers.
		
		std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>(SN<float, char>{-1,0}, SN<float, char>{1,0}, SN<float, char>{3,0});
		poct->insert(pp);
		BOOST_CHECK(pbrothers.size() == 0);//Shouldn't have created brothers.
	}
	
	BOOST_AUTO_TEST_CASE (test_insert) { //
		std::shared_ptr<Particle3D<SN<float, char>>> pp=std::make_shared<Particle3D<SN<float, char>>>();
		poct->insert(pp);

		std::unordered_set<std::shared_ptr<Particle3D<SN<float, char>>>> pparts_sn=poct->getPUnderElements();
		for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts_sn){
			print(*ppart);
			printf("\n");
		}
		BOOST_CHECK(pparts_sn.size() == 1);
		BOOST_CHECK(poctf->getNB_OCTS() == 1);
		BOOST_CHECK(poctf->isEmpty() == false);

		// Float
		std::shared_ptr<Particle3D<float>> ppf=std::make_shared<Particle3D<float>>();
		poctf->insert(ppf);

		std::unordered_set<std::shared_ptr<Particle3D<float>>> pparts_f=poctf->getPUnderElements();
		BOOST_CHECK(pparts_f.size() == 1);
		BOOST_CHECK(poctf->getNB_OCTS() == 1);
		BOOST_CHECK(poctf->isEmpty() == false);
	}

	BOOST_AUTO_TEST_CASE (test_isEmpty) { //

		BOOST_CHECK(true == poct->isEmpty());

		std::shared_ptr<Particle3D<SN<float, char>>> pp1=std::make_shared<Particle3D<SN<float, char>>>();
		//std::shared_ptr<Particle3D<SN<float, char>>> pp1=std::make_shared<Particle3D<SN<float, char>>>(SN<float, char>{1,0}, SN<float, char>{1,0}, SN<float, char>{1,0});
		poct->insert(pp1);

		BOOST_CHECK(1 == poct->getNB_OCTS());//True
		BOOST_CHECK(!poct->isEmpty());//Should pass

		std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>();
		poct->insert(pp2);

		BOOST_CHECK(!poct->isEmpty());

		poct->empty();

		BOOST_CHECK(true == poct->isEmpty());

		// Float
		BOOST_CHECK(true == poctf->isEmpty());

		std::shared_ptr<Particle3D<float>> pp1f=std::make_shared<Particle3D<float>>();
		poctf->insert(pp1f);

		BOOST_CHECK(false == poctf->isEmpty());

		std::shared_ptr<Particle3D<float>> pp2f=std::make_shared<Particle3D<float>>();
		poctf->insert(pp2f);

		BOOST_CHECK(false == poctf->isEmpty());

		poctf->empty();

		BOOST_CHECK(true == poctf->isEmpty());
	}

	BOOST_AUTO_TEST_CASE (test_empty) { //
		std::shared_ptr<Particle3D<SN<float, char>>> pp1=std::make_shared<Particle3D<SN<float, char>>>();
		std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>(SN<float, char>{1,0}, SN<float, char>{-1,0}, SN<float, char>{1,0}, SN<float, char>{1,6});

		poct->insert(pp1);
		BOOST_CHECK(1 == poct->getPUnderElements().size());
		BOOST_CHECK(1 == poct->getNB_OCTS());

		poct->insert(pp2);
		BOOST_CHECK(2 == poct->getPElements().size());
		BOOST_CHECK(3 == poct->getNB_OCTS());

		poct->empty();

		BOOST_CHECK(0 == poct->getPElements().size());
		BOOST_CHECK(1 == poct->getNB_OCTS());

		// Float
		std::shared_ptr<Particle3D<float>> pp1f=std::make_shared<Particle3D<float>>();
		std::shared_ptr<Particle3D<float>> pp2f=std::make_shared<Particle3D<float>>(1., -1., 1., 1000000.);

		poctf->insert(pp1f);
		BOOST_CHECK(1 == poctf->getPElements().size());
		BOOST_CHECK(1 == poctf->getNB_OCTS());

		poctf->insert(pp2f);
		BOOST_CHECK(2 == poctf->getPElements().size());
		BOOST_CHECK(3 == poctf->getNB_OCTS());

		poctf->empty();

		BOOST_CHECK(0 == poctf->getPElements().size());
		BOOST_CHECK(1 == poctf->getNB_OCTS());
	}

	BOOST_AUTO_TEST_CASE (test_getPElements) { //
		std::shared_ptr<Particle3D<SN<float, char>>> pp1=std::make_shared<Particle3D<SN<float, char>>>();
		poct->insert(pp1);

		BOOST_CHECK(1 == poct->getPElements().size());
		BOOST_CHECK(1 == poct->getPUnderElements().size());
		BOOST_CHECK(poct->isFull());
		BOOST_CHECK(poct->isLeaf());

		poct->empty();
		
		BOOST_CHECK(0 == poct->getPElements().size());
		BOOST_CHECK(poct->isEmpty());
		BOOST_CHECK(!poct->isLeaf());

		std::shared_ptr<Particle3D<SN<float, char>>> pp3=std::make_shared<Particle3D<SN<float, char>>>(SN<float, char>{1,0}, SN<float, char>{-1,0}, SN<float, char>{1,0}, SN<float, char>{1,6});
		poct->insert(pp1);
		poct->insert(pp3);
		
		//BOOST_CHECK(0 == poct->getPElements().size());//PROBLEM should't work (cannot insert 2 p at origin(exact same coords)
		//BOOST_CHECK(1 == poct->getPElements().size());
		BOOST_CHECK(2 == poct->getPElements().size());//  Should work

		// Float
		std::shared_ptr<Particle3D<float>> pp1f=std::make_shared<Particle3D<float>>();
		poctf->insert(pp1f);

		//BOOST_CHECK(0 == poct->getPElements().size());
		BOOST_CHECK(1 == poctf->getPElements().size());
		//BOOST_CHECK(2 == poct->getPElements().size());

		poctf->empty();

		std::shared_ptr<Particle3D<float>> pp2f=std::make_shared<Particle3D<float>>(1., -1., 1., 1000000.);
		poctf->insert(pp1f);
		poctf->insert(pp2f);

		BOOST_CHECK(2 == poctf->getPElements().size());

		poctf->empty();

		std::shared_ptr<Particle3D<float>> pp3f=std::make_shared<Particle3D<float>>();
		poctf->insert(pp1f);
		poctf->insert(pp3f);
		
		BOOST_CHECK(0 == poctf->getPElements().size());//PROBLEM should't work (cannot insert 2 p at origin(exact same coords)
		//BOOST_CHECK(1 == poct->getPElements().size());
		BOOST_CHECK(2 == poctf->getPElements().size());//  Should work
	}

	BOOST_AUTO_TEST_CASE (test_fuse) { //
		std::shared_ptr<Particle3D<SN<float, char>>> pp1=std::make_shared<Particle3D<SN<float, char>>>();

		//poct->ffuse is by default false
		std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>();
		poct->insert(pp1);
		poct->insert(pp2);

		BOOST_CHECK(1 == poct->getPElements().size());

		poct->empty();
		
		poct->ffuse=true;	// Fuse on
		poct->insert(pp1);
		poct->insert(pp2);
		
		BOOST_CHECK(1 == poct->getPElements().size());
		
		poct->empty();
	}
	
	BOOST_AUTO_TEST_CASE (test_remove) { //
		std::shared_ptr<Particle3D<SN<float, char>>> pp=std::make_shared<Particle3D<SN<float, char>>>();

		BOOST_CHECK(poct->remove(pp) == false);
		poct->insert(pp);
		BOOST_CHECK(poct->remove(pp) == true);

		// Float
		std::shared_ptr<Particle3D<float>> ppf=std::make_shared<Particle3D<float>>();

		BOOST_CHECK(poctf->remove(ppf) == false);
		poctf->insert(ppf);
		BOOST_CHECK(poctf->remove(ppf) == true);
	}


BOOST_AUTO_TEST_SUITE_END()




#endif /* OCT_TEST_CPP_ */
