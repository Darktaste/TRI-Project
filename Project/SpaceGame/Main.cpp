/*****************************************************************************************
* Desc: Tutorial 02 IND_Surface
*****************************************************************************************/

#include "common\include\CIndieLib.h"
#include "common\include\IND_Surface.h"
#include "common\include\IND_Entity2d.h"
#include "common\include\IND_Animation.h"
#include <vector>
#include <tchar.h>

using namespace std;

/*
==================
Main
==================
*/
int IndieLib()
{
	
	// ----- IndieLib intialization -----

	CIndieLib *mI = CIndieLib::instance();
	if (!mI->init()) return 0;

	
	// ----- Surface loading -----

	// Loading Background
	IND_Surface *mSurfaceBack = IND_Surface::newSurface();
	//changing the backgrounda
	if (!mI->_surfaceManager->add(mSurfaceBack, "../SpaceGame/resources/1.jpg", IND_OPAQUE, IND_32)) return 0;

	// Loading heart
	IND_Surface *mSurfaceHeart= IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mSurfaceHeart, "../SpaceGame/resources/heart.png", IND_ALPHA, IND_32)) return 0;

	// ----- Animations loading -----

	// Characters animations, we apply a color key of (0, 48, 152)
	IND_Animation *mAnimationCharacter1 = IND_Animation::newAnimation();
	if (!mI->_animationManager->addToSurface(mAnimationCharacter1, "../SpaceGame/resources/animations/sword_master.xml", IND_ALPHA, IND_32, 0, 255, 0)) return 0;

	// Characters animations, we apply a color key of (0, 48, 152)
	IND_Animation *mAnimationCharacter2 = IND_Animation::newAnimation();
	if (!mI->_animationManager->addToSurface(mAnimationCharacter2, "../SpaceGame/resources/animations/character2.xml", IND_ALPHA, IND_32, 0, 48, 152)) return 0;

	
	// ----- Set the surface and animations into 2d entities -----

	// Creating 2d entity for the background
	IND_Entity2d *mBack = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mBack);					// Entity adding
	mBack->setSurface(mSurfaceBack);					// Set the surface into the entity

	//heart
	vector<IND_Entity2d*> health;
	IND_Entity2d *a,*b,*c;
	health.push_back(a);
	health.push_back(b);
	health.push_back(c);
	health[0] = IND_Entity2d::newEntity2d();
	health[1] = IND_Entity2d::newEntity2d();
	health[2] = IND_Entity2d::newEntity2d();
	
	mI->_entity2dManager->add(health[0]);
	mI->_entity2dManager->add(health[1]);
	mI->_entity2dManager->add(health[2]);
	health[0]->setSurface(mSurfaceHeart);
	health[1]->setSurface(mSurfaceHeart);
	health[2]->setSurface(mSurfaceHeart);

	// Character 1
	IND_Entity2d *mPlayer1 = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mPlayer1);					// Entity adding
	mPlayer1->setAnimation(mAnimationCharacter1);				// Set the animation into the entity

	// Character 2
	IND_Entity2d *mPlayer2 = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mPlayer2);					// Entity adding
	mPlayer2->setAnimation(mAnimationCharacter2);				// Set the animation into the entity


	// ----- Changing the attributes of the 2d entities -----
	health[0]->setScale(0.3F, 0.3F);
	health[1]->setScale(0.3F, 0.3F);
	health[2]->setScale(0.3F, 0.3F);

	// Player 1
	mPlayer1->setSequence(0);						// Choose sequence
	mPlayer1->setPosition(0, 120, 0);
	mPlayer1->setNumReplays(0);
	mPlayer1->getAnimation()->setIsActive(0, false);
	

	// Player 2
	mPlayer2->setSequence(0);						// Choose sequence
	mPlayer2->setPosition(480, 200, 0);
	mPlayer2->setNumReplays(-1);						// The animation will be displayed 3 times


	//heart
	float width = mSurfaceHeart->getWidth()*0.3F;
	health[0]->setPosition(mI->_window->getWidth() - width, 0, 100);
	health[1]->setPosition(mI->_window->getWidth() - 2.1F*width, 0, 100);
	health[2]->setPosition(mI->_window->getWidth() - 3.2F*width, 0, 100);

	// ----- Main Loop -----
	int counter = 2;
	while (!mI->_input->onKeyPress(IND_ESCAPE) && !mI->_input->quit())
	{

		mI->_input->update();

		//Player 1 attaks if Left CRTL is pressed
		if (mI->_input->onKeyPress(IND_LCTRL) && mPlayer1->getAnimation()->getActualFramePos(0) == 6)
		{

			mPlayer1->setNumReplays(1);

			if (counter >= 0)
			{

				health[counter]->setShow(false);
				counter -= 1;

			}
			

		}

		// Toogle full screen when pressing "space"
		if (mI->_input->onKeyPress(IND_SPACE)) mI->_render->toggleFullScreen();
		mI->_render->beginScene();
		mI->_entity2dManager->renderEntities2d();
		mI->_render->endScene();
	}

	// ----- Free -----

	mI->end();

	return 0;
}