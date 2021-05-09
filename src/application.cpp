#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "window.h"
#include "team_manager.h"
#include "application.h"
#include "ground.h"

using std::cout;
using std::cerr;
using std::endl;


CApplication::CApplication() : CScopeLogger(__FUNCTION__)
{
	// Help on keys
	std::cout << "[ Keys / mouse gestures ]\n";
	std::cout << "-------------------------\n";
	std::cout << "key s              -> start / stop simulation\n";
	std::cout << "key f              -> windowed / fullscreen mode\n";
	std::cout << "key g              -> randomly generate new teams\n";
	std::cout << "key esc            -> quit\n";
	std::cout << "left mouse button  -> add spot for a specific team\n";
	std::cout << "right mouse button -> remove random spot for a specific team\n\n";

	// We create the teams and pause the simulation on start
	CTeamManager::instance()->generate();

	pause();
	CGlobalTimer::instance()->init();
	CGlobalTimer::instance()->pause();

	// We generate the ground
	CGround::instance()->generate(CConfig::WindowWidth, CConfig::WindowHeight);
}

CApplication::~CApplication(){}

void CApplication::begin()
{
	window()->clear(color4f(color3f::white, 1.0f));

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CApplication::mouse_motion( const int x, const int y ){}

void CApplication::mouse_button_up( const int x, const int y, const EMouseButton & button ){}

void CApplication::mouse_button_down( const int x, const int y, const EMouseButton & button )
{
	int team_id;


	// We get the team number corresponding to the supplying point and add a new spot
	if( (team_id = CTeamManager::instance()->teamid_supplying_point(x, y)) >= 0 )
	{
		if( button == MOUSE_BUTTON_LEFT )
			CTeamManager::instance()->add_spot(team_id);
		else if( button == MOUSE_BUTTON_RIGHT )
			CTeamManager::instance()->remove_random_spot(team_id);
	}
}

void CApplication::key_down( const int key )
{
	switch( key )
	{
		case SDLK_ESCAPE :
			quit();
			break;

		case 'f' :
			window()->toggle_fullscreen();
			break;

		case 's' :
			pause();
			CGlobalTimer::instance()->pause();
			break;

		case 'c' :
			CTeamManager::instance()->generate();
			CGlobalTimer::instance()->init();

			if( is_paused() )
				CGlobalTimer::instance()->pause();
			break;
	}
}

void CApplication::key_up( const int key ){}

void CApplication::render() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(5.0f);

	glPushMatrix();
	  glTranslatef(0.0f, 0.0f, -0.1f);
	  CGround::instance()->render(window());
	glPopMatrix();

	CTeamManager::instance()->render(window());
}

void CApplication::update()
{
	CTeamManager::instance()->update();
}

void CApplication::end(){}
