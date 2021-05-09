#ifndef __TEAM_MANAGER_H__
#define __TEAM_MANAGER_H__

#include <vector>
#include "types.h"
#include "geometry.h"
#include "team.h"
#include "utils.h"
#include "logger.h"
#include "config.h"
#include "exceptions.h"
#include "spot.h"
#include "singleton.h"
#include "color.h"
#include "font_manager.h"


// aliases
typedef std::vector<CTeam*>        TTeamsList;
typedef TTeamsList::iterator       TTeamsListIt;
typedef TTeamsList::const_iterator TTeamsListCIt;

class CTeamManager : public CSingleton<CTeamManager>, public CScopeLogger
{
     friend class CSingleton<CTeamManager>;

     private :
	std::vector<CTeam*> m_Teams;

	void purge();

	CTeamManager();
	virtual ~CTeamManager();

     public :
	void generate();
	void add_spot( const uint team_id );
	void remove_random_spot( const uint team_id );
	void render( IWindow *window ) const;
	void update();
	int teamid_supplying_point( const int x, const int y ) const;
};

#endif //__TEAM_MANAGER_H__
