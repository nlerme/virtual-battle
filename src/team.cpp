#include "font_manager.h"
#include "team.h"


CTeam::CTeam( const uint team_id, 
	      const point2f & supplying_pos, 
	      const uint supplying_radius, 
	      const uint nb_spots, 
	      const color4f & color ) : m_TeamId(team_id), 
					m_SupplyingPos(supplying_pos), 
					m_SupplyingRadius(supplying_radius), 
					m_DeadSpots(0), 
					m_Color(color)
{
	for( uint k=0; k<nb_spots; k++ )
		m_Spots.push_back(CSpot::random(team_id, m_SupplyingPos, m_Color));

	m_BestKiller = m_Spots[m_Spots.size()-1];
	m_BestKiller->best_killer(true);
}

CTeam::~CTeam()
{
	for( uint k=0; k<m_Spots.size(); k++ )
		delete m_Spots[k], m_Spots[k]=NULL;
}

void CTeam::add_spot()
{
	m_Spots.push_back(CSpot::random(m_TeamId, m_SupplyingPos, m_Color));
}

void CTeam::remove_random_spot()
{
	if( m_Spots.size() > 1 )
	{
		uint spot_id;

		do
		{
			spot_id = uniform<int>(0, m_Spots.size());
		}
		while( m_Spots[spot_id]->is_best_killer() );

		delete m_Spots[spot_id], m_Spots[spot_id]=NULL;
		m_Spots.erase(m_Spots.begin()+spot_id);
	}
}

const uint & CTeam::supplying_radius() const
{
	return m_SupplyingRadius;
}

const point2f & CTeam::supplying_pos() const
{
	return m_SupplyingPos;
}

const uint CTeam::nb_dead_spots() const
{
	return m_DeadSpots;
}

const uint CTeam::nb_alive_spots() const
{
	return (m_Spots.size()-m_DeadSpots);
}

void CTeam::increase_dead_spots()
{
	m_DeadSpots++;
}

void CTeam::render( IWindow *window ) const
{
	for( uint k=0; k<m_Spots.size(); k++ )
		m_Spots[k]->render(window);

	window->draw_rectangle(m_SupplyingPos.x-m_SupplyingRadius, 
			       m_SupplyingPos.y-m_SupplyingRadius, 
			       2*m_SupplyingRadius, 
			       2*m_SupplyingRadius, 
			       color4f(color3f::white, 1.0f));

	CFontManager::instance()->font("default")->put_text("Team " + to_string(m_TeamId), m_SupplyingPos.x-25.0f, m_SupplyingPos.y-m_SupplyingRadius-15.0f);
}

bool CTeam::is_winner( const std::vector<CTeam*> & teams ) const
{
	if( nb_alive_spots() == 0 )
		return false;

	for( uint t=0; t<teams.size(); t++ )
		if( t != m_TeamId && teams[t]->nb_alive_spots() != 0 )
			return false;

	return true;
}

std::vector<CSpot*> & CTeam::spots()
{
	return m_Spots;
}

CSpot* CTeam::best_killer() const
{
	return m_BestKiller;
}

void CTeam::best_killer( CSpot *bk )
{
	m_BestKiller = bk;
}

CSpot* CTeam::get_nearest_ennemy( const std::vector<CTeam*> & teams, const uint sindex )
{
	std::vector<uint> indexes(teams.size());
	CSpot *ennemy(NULL);
	float min_dist(std::numeric_limits<float>::max()), dist;


	for( uint t=0; t<indexes.size(); t++ )
		indexes[t] = t;

	std::random_shuffle(indexes.begin(), indexes.end());

	for( uint t=0; t<indexes.size(); t++ )
	{
		if( indexes[t] == m_TeamId )
			continue;

		std::vector<CSpot*> & spots = teams[indexes[t]]->spots();

		for( uint s=0; s<spots.size(); s++ )
		{
			if( spots[s]->state() == ST_LOOKING_FOR_ENNEMY || spots[s]->state() == ST_IDLE || spots[s]->state() == ST_GO_HOME )
			{
				dist = distance(spots[s]->position(), m_Spots[sindex]->position());

				if( dist < min_dist )
				{
					min_dist = std::min(dist, min_dist);
					ennemy = spots[s];
				}
			}
		}
	}

	return ennemy;
}

float CTeam::fight_probability( CSpot *s1, CSpot *s2 )
{
	// This function returns the probability that s1 wins against s2. It is equal to 0.5 if both 
	// have the same life ratio. Larger life ratio wrt to the other results in higher chance to win.
	float l1(s1->life_level()/s1->max_life_level());
	float l2(s2->life_level()/s2->max_life_level());
	float st1(s1->strength());
	float st2(s2->strength());
	return (l1*st1-l2*st2+1.0f)/2.0f;
}

void CTeam::update_spot( std::vector<CTeam*> & teams, const uint sindex )
{
	CSpot *spot(m_Spots[sindex]), *ennemy(NULL), *best_killer(NULL);


	if( spot->state() == ST_LOOKING_FOR_ENNEMY )
	{
		ennemy = get_nearest_ennemy(teams, sindex);

		if( !ennemy )
		{
			spot->state(ST_IDLE);
		}
		else
		{
			ennemy->ennemy(spot);
			spot->ennemy(ennemy);

			ennemy->move_to(spot->position());
			spot->move_to(ennemy->position());

			spot->state(ST_HUNTING);
			spot->ennemy()->state(ST_HUNTING);
		}
	}
	else if( spot->state() == ST_HUNTING )
	{
		if( distance(spot->position(), spot->ennemy()->position()) > 15.0f )
		{
			spot->move();
		}
		else
		{
			spot->ennemy()->state(ST_FIGHTING);
			spot->state(ST_FIGHTING);
		}
	}
	else if( spot->state() == ST_FIGHTING )
	{
		float weapons_level1(spot->weapons_level());
		float weapons_level2(spot->ennemy()->weapons_level());

		if( weapons_level1 <= 0.0f || weapons_level2 <= 0.0f )
		{
			if( weapons_level1 <= 0.0f )
			{
				spot->ennemy()->state(ST_LOOKING_FOR_ENNEMY);
				spot->state(ST_SUPPLYING);
				spot->move_to(m_SupplyingPos);
			}

			if( weapons_level2 <= 0.0f )
			{
				spot->ennemy()->state(ST_SUPPLYING);
				spot->ennemy()->move_to(teams[spot->ennemy()->team_id()]->supplying_pos());
				spot->state(ST_LOOKING_FOR_ENNEMY);
			}

			spot->ennemy()->ennemy(NULL);
			spot->ennemy(NULL);
		}
		else
		{
			spot->weapons_level(weapons_level1-1.0f);
			spot->ennemy()->weapons_level(weapons_level2-1.0f);

			float life_level1(spot->life_level());
			float life_level2(spot->ennemy()->life_level());

			if( uniform<float>() < fight_probability(spot, spot->ennemy()) )
				spot->ennemy()->life_level(life_level2-1.0f);
			else
				spot->life_level(life_level1-1.0f);

			if( life_level1 <= 0.0f )
			{
				//-----------
				spot->ennemy()->increase_nb_kills();
				best_killer = teams[spot->ennemy()->team_id()]->best_killer();

				if( best_killer != spot->ennemy() && spot->ennemy()->nb_kills() > best_killer->nb_kills() )
				{
					best_killer->best_killer(false);
					spot->ennemy()->best_killer(true);
					teams[spot->ennemy()->team_id()]->best_killer(spot->ennemy());
				}
				//-----------

				spot->ennemy()->state(ST_LOOKING_FOR_ENNEMY);
				spot->state(ST_DEAD);
				increase_dead_spots();
				spot->color(color4f(color3f::black, 0.4f));
			}

			if( life_level2 <= 0.0f )
			{
				spot->ennemy()->color(color4f(color3f::black, 0.4f));
				spot->ennemy()->state(ST_DEAD);
				teams[spot->ennemy()->team_id()]->increase_dead_spots();
				spot->state(ST_LOOKING_FOR_ENNEMY);

				//-----------
				spot->increase_nb_kills();

				if( m_BestKiller != spot && spot->nb_kills() > m_BestKiller->nb_kills() )
				{
					m_BestKiller->best_killer(false);
					spot->best_killer(true);
					m_BestKiller = spot;
				}
				//-----------
			}

			if( life_level1 <= 0.0f || life_level2 <= 0.0f )
			{
				spot->ennemy()->ennemy(NULL);
				spot->ennemy(NULL);
			}
		}
	}
	else if( spot->state() == ST_IDLE )
	{
		if( is_winner(teams) )
		{
			spot->move_to(m_SupplyingPos);
			spot->state(ST_GO_HOME);
		}
	}
	else if( spot->state() == ST_GO_HOME )
	{
		if( distance(spot->position(), m_SupplyingPos) > spot->speed() )
			spot->move();
	}
	else if( spot->state() == ST_SUPPLYING )
	{
		if( distance(spot->position(), m_SupplyingPos) > spot->speed() )
			spot->move();
		else
		{
			if( spot->weapons_level() < spot->max_weapons_level() )
				spot->weapons_level(spot->weapons_level()+spot->max_weapons_level()*0.1f);
			else
				spot->state(ST_LOOKING_FOR_ENNEMY);
		}
	}
}

void CTeam::update( std::vector<CTeam*> & teams )
{
	for( uint sindex=0; sindex<m_Spots.size(); sindex++ )
		update_spot(teams, sindex);
}
