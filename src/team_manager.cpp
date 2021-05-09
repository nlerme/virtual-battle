#include <iomanip>
#include <sstream>
#include "global_timer.h"
#include "team_manager.h"


CTeamManager::CTeamManager() : CScopeLogger(__FUNCTION__){}

CTeamManager::~CTeamManager()
{
	purge();
}

void CTeamManager::add_spot( const uint team_id )
{
	m_Teams[team_id]->add_spot();
}

void CTeamManager::remove_random_spot( const uint team_id )
{
	m_Teams[team_id]->remove_random_spot();
}

int CTeamManager::teamid_supplying_point( const int x, const int y ) const
{
	for( uint k=0; k<m_Teams.size(); k++ )
	{
		point2f sp(m_Teams[k]->supplying_pos());
		uint spr(m_Teams[k]->supplying_radius());

		if( is_between<int>(x, sp.x-spr, sp.x+spr) && is_between<int>(y, sp.y-spr, sp.y+spr) )
			return k;
	}

	return -1;
}

void CTeamManager::purge()
{
	for( uint k=0; k<m_Teams.size(); k++ )
		delete m_Teams[k], m_Teams[k]=NULL;

	m_Teams.clear();
}

void CTeamManager::generate()
{
	uint team_id(0);
	uint supplying_radius(10);


	// We first purge teams and generate new ones
	purge();

	// blue team
	m_Teams.push_back(new CTeam(
					team_id++, 
					point2f(CConfig::WindowWidth*0.2f, CConfig::WindowHeight*0.8f), 
					supplying_radius, 
					uniform<int>(1990, 2000), 
					color4f(color3f::blue, 0.7f)
				   ));

	// red team
	m_Teams.push_back(new CTeam(
					team_id++, 
					point2f(CConfig::WindowWidth*0.8f, CConfig::WindowHeight*0.8f), 
					supplying_radius, 
					uniform<int>(1990, 2000), 
					color4f(color3f::red, 0.7f)
				   ));

	// purple team
	m_Teams.push_back(new CTeam(
					team_id++, 
					point2f(CConfig::WindowWidth*0.2f, CConfig::WindowHeight*0.2f), 
					supplying_radius, 
					uniform<int>(1990, 2000), 
					color4f(color3f::purple, 0.7f)
				   ));

	// green team
	m_Teams.push_back(new CTeam(
					team_id++, 
					point2f(CConfig::WindowWidth*0.8f, CConfig::WindowHeight*0.2f), 
					supplying_radius, 
					uniform<int>(1990, 2000), 
					color4f(color3f::green, 0.7f)
				   ));
}

void CTeamManager::render( IWindow *window ) const
{
	for( uint k=0; k<m_Teams.size(); k++ )
		m_Teams[k]->render(window);

	window->draw_line(CConfig::WindowWidth*0.5f, 0, CConfig::WindowWidth*0.5f, CConfig::WindowHeight, color4f(color3f::white, 1.0f));
	window->draw_line(0, CConfig::WindowHeight*0.5f, CConfig::WindowWidth, CConfig::WindowHeight*0.5f, color4f(color3f::white, 1.0f));

	// Time elapsed
	std::ostringstream oss;
	oss.setf(std::ios::fixed, std::ios::floatfield);
	oss << "Total time elapsed: " << std::setprecision(2) << CGlobalTimer::instance()->time() << " secs\n";

	// Some stats per team
	for( uint k=0; k<m_Teams.size(); k++ )
		oss << "Team " << k << ": " << std::setprecision(2) << float(m_Teams[k]->nb_alive_spots())/m_Teams[k]->spots().size()*100.0f << "% alive spots (" << m_Teams[k]->nb_alive_spots() << ") | best kills=" << m_Teams[k]->best_killer()->nb_kills() << '\n';

	CFontManager::instance()->font("default")->put_text(oss.str(), 10.0f, CConfig::WindowHeight-20.0f);
}

void CTeamManager::update()
{
	for( uint tindex=0; tindex<m_Teams.size(); tindex++ )
		m_Teams[tindex]->update(m_Teams);
}
