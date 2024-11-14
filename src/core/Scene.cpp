////:)
//#ifndef SCENE2D_CPP
//
//#define SCENE2D_CPP
//
//
#include "Scene.h"



Scene::Scene(){//:)
	;
}

Scene::Scene(const Scene& scene){//:/
	;
}

Scene::~Scene(){//:)
	;
}

std::set<Displayable*> Scene::getPDisplayables(){//:)
	return m_pdisplayables;
}

void Scene::addPDisplayable(Displayable* pdisplayable){//:)
	m_pdisplayables.insert(pdisplayable);
}

//
//void Scene2D::setPoints(std::vector<Point2D*> ppoints)//:)
//{
//	for (int i(0) ; i<(int)ppoints.size() ; i++)
//	{
//		this->setPoint(*ppoints[i]);
//	}
//}
//
//void Scene2D::setPoint(Point2D point)//:)
//{
//	//printf("ppoint: (%Lg, %Lg)\n", ppoint->x, ppoint->y);
//	Point2D* newppoint=new Point2D{point};
//	//printf("new_ppoint: (%Lg, %Lg)\n", new_ppoint->x, new_ppoint->y);
//	m_ppoints.push_back(newppoint);
//}*/
//
///*std::vector<Shape2D*>& Scene2D::getPShapes()//:)
//{
//	return m_pshapes;
//}*/
//
///*void Scene2D::setShapes(std::vector<Line2D*> plines)//:)
//{
//	for (int i(0) ; i<(int)plines.size() ; i++)
//	{
//		this->setLine(*plines[i]);
//	}
//}*/
//
///*void Scene2D::setShape(Shape2D& shape)//:)
//{
//	Shape2D* newpshape=new Shape2D(&shape);
//	m_pshapes.push_back(newpshape);
//}
//
//void Scene2D::setCircle(Circle2D& circle)//:)
//{
//	Circle2D* newpcircle=new Circle2D(&circle);
//	m_pshapes.push_back(newpcircle);
//}
//
//void Scene2D::setPolygon(Polygon2D& polygon)//:)
//{
//	Polygon2D* newppolygon=new Polygon2D(&polygon);
//	m_pshapes.push_back(newppolygon);
//}*/
//
///*std::vector<Vector2D*>& Scene2D::getPVectors()//:)
//{
//	return m_pvectors;
//}
//
//void Scene2D::setVectors(std::vector<Vector2D*> pvectors)//:)
//{
//	for (int i(0) ; i<(int)pvectors.size() ; i++)
//	{
//		this->setVector(*pvectors[i]);
//	}
//}
//
//void Scene2D::setVector(Vector2D& vector)//:)
//{
//	Vector2D* newpvector=new Vector2D(vector);
//	newpvector->setPColor(m_pcolors[1]);
//
//	m_pvectors.push_back(newpvector);
//}*/
//
///*std::vector<Point2D*>& Scene2D::getPointsObject(Object2D* pobject)//:)
//{
//	//printf("m_ppoints.size(): %i\n", (int)m_ppoints.size());
//	return pobject->getPoints();
//}*/
//
///*void Scene2D::setPointObject(Point2D* ppoint, Object2D* pobject)//:)
//{
//	printf("m_ppoints.size(): %i\n", (int)m_ppoints.size());
//	pobject->setPoint(this->setPoint(ppoint));
//	printf("m_ppoints.size(): %i\n", (int)m_ppoints.size());
//}*/
//
//std::vector<Object2D*>& Scene2D::getPObjects()//:)
//{
//	return m_pobjects;
//}
//
///*void Scene2D::setObject(Object2D& object)//:)
//{
//	printf("SCENE: SET OBJECT1\n");
//	print(&object);
//	//Point2D newpoint={m_pcursor->x, m_pcursor->y, m_pcolors[1]};
//	printf("AAAAAAAAAAARG!2\n");
//	Object2D* newpobject=new Object2D(&object);
//	printf("AAAAAAAAAAARG!3\n");
//	//newpobject->setPColor(m_pcolors[1]);
//	printf("AAAAAAAAAAARG!4\n");
//	//Object2D newobject("object", m_cursor);
//
//	m_pobjects.push_back(newpobject);
//	printf("SCENE: SET OBJECT2\n");
//}*/
//
///*void Scene2D::setRObject(RObject2D& robject)//:) Coince à partir de là
//{
//	printf("SCENE: SET ROBJECT1\n");
//	print(&robject);
//	//Point2D newpoint={m_pcursor->x, m_pcursor->y, m_pcolors[1]};
//	RObject2D* newprobject=new RObject2D(&robject);
//
//	printf("SCENE: SET ROBJECT2\n");
//	m_pobjects.push_back(newprobject);
//	printf("SCENE: SET ROBJECT3\n");
//}
//
//std::vector<SDL_Color*>& Scene2D::getPColors()//:)
//{
//	return m_pcolors;
//}
//
//void Scene2D::setPColors(std::vector<SDL_Color*> pcolors)//:)
//{
//	int szpcolors(pcolors.size());
//	for (int i(0) ; i<szpcolors ; i++)
//	{
//		this->setPColor(pcolors[i]);
//	}
//}
//
//void Scene2D::setPColor(SDL_Color* pcolor)//:)
//{
//	m_pcolors.push_back(pcolor);
//}*/
//
//
//
//
//
//
///*std::vector<Object2D*> Scene2D::getCollidingObjects()//:)
//{
//	std::vector<Object2D*> pobjects_colliding;
//	std::vector<Object2D*> pobjects2(m_pobjects);
//
//	for (auto it_pobjects(m_pobjects.begin()) ; it_pobjects!=m_pobjects.end() ; it_pobjects++)
//	{
//		int szpobjects2(pobjects2.size());
//		for (int i(0) ; i<szpobjects2 ; i++)
//		{
//			if (*it_pobjects!=*pobjects2.begin() && testCollide(**it_pobjects, *pobjects2[i]))
//			{
//				pobjects_colliding.push_back(*it_pobjects);
//				pobjects_colliding.push_back(pobjects2[i]);
//			}
//		}
//	}
//	return pobjects_colliding;
//}*/
//
//
//
//
//
//
//// void Scene2D::aleaGeneration(unsigned int nbObjects, Object2D& object, unsigned int radius, LSN avMass, LSN avCharge, float noise)//:)
//// {
//// 	unsigned int i(0);
//// 	while (i<nbObjects)
//// 	{
//// 		//Object2D newobject(object);
//// 		//newobject.setMass(avMass);
//// 		//newobject.setCharge(avCharge);
//// 		//newobject.setCentroid({{(long double)(int)(rand()%(2*radius+1) -radius), 0}, {(long double)(int)(rand()%(2*radius+1) -radius), 0}});
//// 		this->setObject(/*newobject*/object);
//// 		//(long int)(long double)(avMass*(1+noise)-avMass*(1-noise)+1);
//// 		//m_pobjects[m_pobjects.size()-1]->setMass({(long double)(rand()%(long int)(long double)(avMass*(1+noise)-avMass*(1-noise)+1) +(long int)(long double)(avMass*(1-noise))), 0});
//// 		m_pobjects[m_pobjects.size()-1]->setMass(avMass);
//// 		m_pobjects[m_pobjects.size()-1]->setCharge(avCharge);
//// 		m_pobjects[m_pobjects.size()-1]->setCentroid({{(long double)(int)(rand()%(2*radius+1) -radius), 0}, {(long double)(int)(rand()%(2*radius+1) -radius), 0}});
//// 		//LSN mass{(long double)(rand()%(long int)(long double)(avMass*(1+noise)-avMass*(1-noise)+1) +(long int)(long double)(avMass*(1-noise))), 0};
//// 		/*LSN charge({(long double)(rand()%(long int)(long double)(avCharge*(1+noise)-avCharge*(1-noise)+1) +(long int)(long double)(avCharge*(1-noise))), 0});
//// 		//printf("Max: %ld  Min: %ld  Lenght:%Lg    Mass: %i\n", (long int)(avMass*(1+noise)), (long int)(avMass*(1-noise)), (avMass*(1+noise)-avMass*(1-noise)+1), mass);
//// 		Object2D* newpobject=this->setObject("object",
//// 			new Point2D{(long double)(int)(rand()%(2*radius+1) -radius), (long double)(int)(rand()%(2*radius+1) -radius)},
//// 			(long double)(int)(rand()%(long int)(avMass*(1+noise)-avMass*(1-noise)+1) +(long int)(avMass*(1-noise))),
//// 			(long double)(int)(rand()%(long int)(avCharge*(1+noise)-avCharge*(1-noise)+1) +(long int)(avCharge*(1-noise))));
//// 		ppoints.insert(ppoints.begin(), new Point2D{{(long double)(int)(rand()%(2*radius+1) -radius), 0}, {(long double)(int)(rand()%(2*radius+1) -radius), 0}});
//// 		ppoints.erase(ppoints.begin());*/
//// 		i++;
//// 	}
//// }
//
///*void Scene2D::physicsLoop(unsigned int frames)//:)
//{
//	printf("99999999999999999999 B1\n");
//	std::chrono::system_clock::time_point time1=std::chrono::system_clock::now();
//	std::chrono::system_clock::time_point time2=std::chrono::system_clock::now();
//	std::chrono::system_clock::time_point time3=std::chrono::system_clock::now();
//	std::chrono::duration<double> delta_t(0);
//	//double delta_t1(0);
//	double delta_t2(0);
//	//double delta_t3(0);
//
//	printf("99999999999999999999 B2\n");
//	unsigned int i(0);
//	while (i<frames)
//	{
//		//printf("A\n");
//		delta_t=std::chrono::system_clock::now()-time1;
//		//printf("delta_t: %f\n", delta_t.count());
//		//delta_t1=delta_t.count();
//		//printf("Delta_t1: %f\n", delta_t1);
//		delta_t=std::chrono::system_clock::now()-time2;
//		//printf("delta_t: %f\n", delta_t.count());
//		delta_t2=delta_t.count();
//		//printf("Delta_t2: %f\n", delta_t2);
//		delta_t=std::chrono::system_clock::now()-time3;
//		//printf("delta_t: %f\n", delta_t.count());
//		//delta_t3=delta_t.count();
//		//printf("Delta_t3: %f\n", delta_t3);
//
//		//printf("C\n");
//		if (delta_t2 >= (double)1/m_PPS)// Stays here
//		{
//			//printf("1\n");
//			time2=std::chrono::system_clock::now();
//			//this->applyMotions(delta_t2*m_speed);
//
//			//printf("2\n");
//			//this->applyGEInteractions(delta_t2*m_speed);//Must be moved to a bubble
//			//printf("3\n");
//			//this->applyCollisions(delta_t.count());
//			this->moveObjects(delta_t2*m_speed);
//			//printf("4\n");
//		}
//		//printf("99999999999999999999 B8\n");
//		//printf("D\n");
//	}
//}*/
//
///*void Scene2D::renderScene()//Must be moved to Game2D
//{
//	if (!m_fpaths)
//	{
//		SDL_SetRenderDrawColor(m_prenderer, m_pcolors[0]->r, m_pcolors[0]->g, m_pcolors[0]->b, m_pcolors[0]->a);
//		SDL_RenderClear(m_prenderer);
//	}
//
//	int szpcameras(m_pcameras.size());
//	for (int i(0) ; i<szpcameras ; i++)
//	{
//		m_pcameras[i]->renderPoints(m_ppoints);
//		//m_pcameras[i]->renderLines(m_plines);
//		m_pcameras[i]->renderVectors(m_pvectors);
//		//m_pcameras[i]->renderPolygons(m_ppolygons);
//		m_pcameras[i]->renderObjects(m_pobjects);
//	}
//
//	SDL_RenderPresent(m_prenderer);
//}*/
//
///*void Scene2D::callLogicBricks(double delta_t)//:)
//{
//	//printf("99999999999999999999 B3_1\n");
//	int szplogic_bricks(m_plogic_bricks.size());
//	for (int i(0) ; i<szplogic_bricks ; i++)
//	{
//		//printf("99999999999999999999 B3_2\n");
//		m_plogic_bricks[i]->call();
//		m_plogic_bricks[i]->transmit();				//##"""""""""""""""""""" HUGE ERROR ! """"""""""""""""""""""""""""##
//		//printf("99999999999999999999 B3_3\n");
//	}
//}*/
//
///*void Scene2D::applyMotions(double delta_t)//:)
//{
//	//printf("99999999999999999999 B3_1\n");
//	int szpmotions(m_pmotions.size());
//	for (int i(0) ; i<szpmotions ; i++)
//	{
//		//printf("99999999999999999999 B3_2\n");
//		//m_pmotions[i]->call(delta_t);				//##"""""""""""""""""""" HUGE ERROR ! """"""""""""""""""""""""""""##
//		//printf("99999999999999999999 B3_3\n");
//	}
//}*/
//
//// void Scene2D::applyGEInteractions(double delta_t)//:)
//// {
//// 	//printf("m_pobjects.size(): %i\n", (int)m_pobjects.size());
//// 	std::vector<Object2D*> pobjects2(m_pobjects);
//
//// 	for (auto it_pobjects(m_pobjects.begin()) ; it_pobjects!=m_pobjects.end() ; it_pobjects++)
//// 	{
//// 		//printf("///////////////////////////////*it_pobjects: %p\n", *it_pobjects);
//// 		//printf("pobjects2.size(): %i\n", (int)pobjects2.size());
//
//// 		int szpobjects2(pobjects2.size());
//// 		for (int i(0) ; i<szpobjects2 ; i++)
//// 		{
//// 			//printf("///////////////////////////////*1");
//// 			//printf("/i: %i/", i);
//// 			if (*it_pobjects!=pobjects2[i])
//// 			{
//// 				// Collisions
//// 				/*if (m_fcollision)
//// 				{
//// 					if (m_fcollision)
//// 					{
//// 						;
//// 					}
//// 				}*/
//// 				// Gravity
//// 				if (m_fgravity)
//// 				{
//// 					printf("delta_t1: %lf\n", delta_t);
//// 					Vector2D gravitForce(NULL, *pobjects2[i]->getPCentroid() - *(*it_pobjects)->getPCentroid());
//// 					//Vector2D* pgravitForce=new Vector2D(new Point2D{{0, 0}, {0, 0}}, new Point2D{{0, 0}, {1, 0}});
//// 					//printf("*********pgravitForce->getEnd() BEFORE: (%Lg, %Lg)\n", pgravitForce->getEnd()->x, pgravitForce->getEnd()->y);
//// 					//printf("*********(*it_pobjects)->getMass(): %Lg\n", (*it_pobjects)->getMass());
//// 					//printf("*********(*pobjects2.begin())->getMass(): %Lg\n", (*pobjects2.begin())->getMass());
//// 					//printf("*********(*it_pobjects)->getMass()*(*pobjects2.begin())->getMass(): %Lg\n", (*it_pobjects)->getMass()*(*pobjects2.begin())->getMass());
//// 					//pgravitForce->setNorm(100000000000);
//// 					printf("delta_t2: %lf\n", delta_t);
//// 					(*it_pobjects)->getMass()*pobjects2[i]->getMass();
//// 					LSN nb(/*(*it_pobjects)->getMass()*pobjects2[i]->getMass()*/pow(getDistance(*(*it_pobjects)->getPCentroid(), *pobjects2[i]->getPCentroid()), 2));
//// 					print(&nb);
//// 					printf("delta_t2_2: %lf\n", delta_t);
//// 					gravitForce.setNorm((G*(*it_pobjects)->getMass()*pobjects2[i]->getMass())/pow(getDistance(*(*it_pobjects)->getPCentroid(), *pobjects2[i]->getPCentroid()), 2));
//// 					printf("delta_t: %lf\n", delta_t);
//// 					//pgravitForce->setNorm({1, 9});
//// 					print(&gravitForce.getNorm());
//// 					printf("delta_t3: %lf\n", delta_t);
//// 					(*it_pobjects)->setForce(gravitForce, true, delta_t);
//// 					printf("delta_t4: %lf\n", delta_t);
//// 					gravitForce*=-1;
//// 					//printf("**Second OBJ setForce: %Lg\n", pgravitForce->getNorm());
//// 					pobjects2[i]->setForce(gravitForce, true, delta_t);
//// 				}
//// 				// Electromagnetism
//// 				if (m_felectromagnetism)
//// 				{
//// 					//printf("delta_t: %lf\n", delta_t);
//// 					Vector2D electForce(NULL, *((*it_pobjects)->getPCentroid()) - *(pobjects2[i]->getPCentroid()));
//// 					//printf("*********pelectForce->getNorm() BEFORE: %Lg\n", pelectForce->getNorm());
//// 					//printf("*********(*it_pobjects)->getMass(): %Lg\n", (*it_pobjects)->getMass());
//// 					//printf("*********(*pobjects2.begin())->getMass(): %Lg\n", (*pobjects2.begin())->getMass());
//// 					//printf("*********(*it_pobjects)->getMass()*(*pobjects2.begin())->getMass(): %Lg\n", (*it_pobjects)->getMass()*(*pobjects2.begin())->getMass());
//// 					electForce.setNorm((K*(*it_pobjects)->getCharge()*pobjects2[i]->getCharge())/pow(getDistance(*(*it_pobjects)->getPCentroid(), *pobjects2[i]->getPCentroid()), 2));
//// 					//printf("*********pelectForce->getNorm() AFTER: %Lg\n", pelectForce->getNorm());
//// 					//printf("**First OBJ setForce: %Lg\n", pelectForce->getNorm());
//// 					(*it_pobjects)->setForce(electForce, true, delta_t);
//// 					electForce*=-1;
//// 					//printf("**Second OBJ setForce: %Lg\n", pelectForce->getNorm());
//// 					pobjects2[i]->setForce(electForce, true, delta_t);
//// 				}
//// 			}
//// 		}
//// 		pobjects2.erase(pobjects2.begin());
//// 	}
//// }
//
///*void Scene2D::applyCollisions(double delta_t)//:)
//{
//	//printf("m_pobjects: %i\n", (int)m_pobjects.size());
//
//	for (int i(0) ; i<(int)m_pobjects.size() ; i++)
//	{
//		m_pobjects[i]->apply(delta_t);
//	}
//}*/
//
///*void Scene2D::moveObjects(double delta_t)//:)
//{
//	//printf("a\n");
//	int szpobjects(m_pobjects.size());
//	for (int i(0) ; i<szpobjects ; i++)
//	{
//		printf("b\n");
//		//long double oldX((long double)m_pobjects[i]->getCentroid()->x), oldY((long double)m_pobjects[i]->getCentroid()->y);
//
//		printf("c\n");
//		m_pobjects[i]->move(delta_t);
//		printf("cc\n");
//		m_pobjects[i]->spin(delta_t);
//
//		printf("d\n");
//		m_pobjects[i]->getPLinAcceleration()->setNorm({0, 0});
//		printf("e\n");
//		m_pobjects[i]->setRotAcceleration({0, 0});
//
//		printf("f\n");
//		//test(oldX, oldY, (long double)m_pobjects[i]->getCentroid()->x, (long double)m_pobjects[i]->getCentroid()->y);
//	}
//}*/
//
//
//
//
//
///*void Scene2D::delShapes()//:)
//{
//	int szpshapes(m_pshapes.size());
//	for (int i(0) ; i<szpshapes ; i++)
//	{
//		//m_ppoints[i]->pcolor=NULL;
//		delete *m_pshapes.begin();
//		m_pshapes.erase(m_pshapes.begin());
//	}
//}*/
//
///*void Scene2D::delObjects()//:)
//{
//	printf("SCENE: DEL OBJECTS START\n");
//	int szpobjects(m_pobjects.size());
//	for (int i(0) ; i<szpobjects ; i++)
//	{
//		if (*m_pobjects.begin()==NULL)
//		{
//			printf("NULL\n");
//		}
//		delete *m_pobjects.begin();
//		m_pobjects.erase(m_pobjects.begin());
//	printf("SCENE: DEL OBJECTS END\n");
//	}
//}*/
//
///*void Scene2D::delRObjects()//:)
//{
//	int szprobjects(m_probjects.size());
//	for (int i(0) ; i<szprobjects ; i++)
//	{
//		if (*m_probjects.begin()==NULL)
//		{
//			printf("NULL\n");
//		}
//		delete *m_probjects.begin();
//		m_probjects.erase(m_probjects.begin());
//	}
//}*/
//
///*void Scene2D::delCameras()//:)
//{
//	int szpcameras(m_pcameras.size());
//	for (int i(0) ; i<szpcameras ; i++)
//	{
//		if (*m_pcameras.begin()==NULL)
//		{
//			printf("NULL\n");
//		}
//		delete *m_pcameras.begin();
//		m_pcameras.erase(m_pcameras.begin());
//	}
//}*/
//
///*void Scene2D::delBricks()//:)
//{
//	printf("F__K1\n");
//	int szpbricks(m_pbricks.size());
//	for (int i(0) ; i<szpbricks ; i++)
//	{
//		delete *m_pbricks.begin();
//		m_pbricks.erase(m_pbricks.begin());
//	}
//	printf("F__K2\n");
//}*/
//
///*void Scene2D::delMotions()//:)
//{
//	int szpmotions(m_pmotions.size());
//	for (int i(0) ; i<szpmotions ; i++)
//	{
//		delete *m_pmotions.begin();
//		m_pmotions.erase(m_pmotions.begin());
//	}
//}*/
//
///*void Scene2D::delPoints()//:)
//{
//	int szppoints(m_ppoints.size());
//	for (int i(0) ; i<szppoints ; i++)
//	{
//		//m_ppoints[i]->pcolor=NULL;
//		delete *m_ppoints.begin();
//		m_ppoints.erase(m_ppoints.begin());
//	}
//}
//
//void Scene2D::delVectors()//:)
//{
//	int szpvectors(m_pvectors.size());
//	for (int i(0) ; i<szpvectors ; i++)
//	{
//		//m_ppoints[i]->pcolor=NULL;
//		delete *m_pvectors.begin();
//		m_pvectors.erase(m_pvectors.begin());
//	}
//}*/
//
///*void Scene2D::delColors()//:)
//{
//	int szpcolors(m_pcolors.size());
//	for (int i(0) ; i<szpcolors ; i++)
//	{
//
//		m_pcolors.erase(m_pcolors.begin());
//	}
//}*/
//
//
//
//
//
//
///*bool Scene2D::testPresencePoint(Point2D* ppoint)
//{
//	bool test(false);
//
//	if (ppoint!=NULL)
//	{
//		int szppoints(m_ppoints.size());
//		for (int i(0) ; i<szppoints; i++)
//		{
//			if (m_ppoints[i]==ppoint)
//			{
//				test=true;
//				// To stop the loop.
//				i=szppoints;
//			}
//		}
//	}
//	return test;
//}*/
//
///*bool Scene2D::testPresenceObject(Object2D* pobject)
//{
//	bool test(false);
//
//	if (pobject!=NULL)
//	{
//		int szpobjects(m_pobjects.size());
//		for (int i(0) ; i<szpobjects; i++)
//		{
//			if (m_pobjects[i]==pobject)
//			{
//				test=true;
//				// To stop the loop.
//				i=szpobjects;
//			}
//		}
//	}
//	return test;
//}*/
//
///*bool Scene2D::testPresenceCamera(Camera2D* pcamera)
//{
//	bool test(false);
//
//	if (pcamera!=NULL)
//	{
//		int szpcameras(m_pcameras.size());
//		for (int i(0) ; i<szpcameras; i++)
//		{
//			if (m_pcameras[i]==pcamera)
//			{
//				test=true;
//				// To stop the loop.
//				i=szpcameras;
//			}
//		}
//	}
//	return test;
//}*/
//
///*bool Scene2D::testPresenceLogicBrick(LogicBrick* plogic_brick)
//{
//	bool test(false);
//
//	if (plogic_brick!=NULL)
//	{
//		int szplogic_bricks(m_plogic_bricks.size());
//		for (int i(0) ; i<szplogic_bricks; i++)
//		{
//			if (m_plogic_bricks[i]==plogic_brick)
//			{
//				test=true;
//				// To stop the loop.
//				i=szplogic_bricks;
//			}
//		}
//	}
//	return test;
//}*/
//
//
//
//
//
///*void print(Scene2D* pscene, unsigned int indent)
//{
//	if (pscene!=NULL)
//	{
//		if (indent==0)
//		{
//			//printf("\nScene2D (%s, %p):\n", name, pscene);
//			printf("\nScene2D (%p):\n", pscene);
//		}
//
//		//printTabs(indent+1);
//		//printf("-Speed: %f\n", pscene->getSpeed());
//
//		//printTabs(indent+1);
//		//printf("-FPS: %ui\n", pScene->getFPS());
//
//		//printTabs(indent+1);
//		//printf("-PPS: %ui\n", pScene->getPPS());
//
//		//printTabs(indent+1);
//		//printf("-LPS: %ui\n", pScene->getBPS());
//
//		printTabs(indent+1);
//		printf("Cursor: \n");
//		//print(pScene->getPCursor(), indent+1);
//		printf("\n");
//
//		int szpobjects(pscene->getPObjects().size());
//		for (int i(0) ; i<szpobjects ; i++)
//		{
//			printTabs(indent+1);
//			print(pscene->getPObjects()[i], indent+1);
//			printf("\n");
//		}
//
//	}
//}*/
//
//
//
//
//
//
///*int main()
//{
//	printf("1\n");
//	//Scene2D* pscene1=new Scene2D("scene");
//	Scene2D scene1("scene");
//	printf("2\n");
//	printf("3\n");
//
//	//RigidObject2D obj2("rigid_object2");
//	//pscene1->setObject(obj2);
//	printf("7\n");
//	//delete pscene1;
//	printf("8\n");
//	return 0;
//}*/
//
//#endif
