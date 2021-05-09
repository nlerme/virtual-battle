#ifndef __TEAM_H__
#define __TEAM_H__

#include <vector>
#include "utils.h"
#include "exceptions.h"
#include "spot.h"


// aliases
typedef std::vector<CSpot*>        TSpotsList;
typedef TSpotsList::iterator       TSpotsListIt;
typedef TSpotsList::const_iterator TSpotsListCIt;

class CTeam
{
     private :
	uint m_TeamId;
	std::vector<CSpot*> m_Spots;
	point2f m_SupplyingPos;
	uint m_SupplyingRadius;
	uint m_DeadSpots;
	CSpot *m_BestKiller;
	color4f m_Color;

	bool is_winner( const std::vector<CTeam*> & teams ) const;
	CSpot* get_nearest_ennemy( const std::vector<CTeam*> & teams, const uint sindex );
	float fight_probability( CSpot *s1, CSpot *s2 );
	void update_spot( std::vector<CTeam*> & teams, const uint sindex );
	void increase_dead_spots();

     public :
	CTeam( const uint team_id, const point2f & supplying_pos, const uint supplying_radius, const uint nb_spots, const color4f & color );
	virtual ~CTeam();

	std::vector<CSpot*> & spots();
	void add_spot();
	void remove_random_spot();
	CSpot* best_killer() const;
	void best_killer( CSpot *bk );
	const point2f & supplying_pos() const;
	const uint nb_dead_spots() const;
	const uint nb_alive_spots() const;
	void render( IWindow *window ) const;
	void update( std::vector<CTeam*> & teams );
	const uint & supplying_radius() const;
	
};

#endif //__TEAM_H__
