#ifndef __SPOT_H__
#define __SPOT_H__

#include "geometry.h"
#include "color.h"
#include "utils.h"
#include "config.h"
#include "window.h"


enum ESpotState
{
	ST_IDLE,
	ST_HUNTING,
	ST_FIGHTING,
	ST_DEAD,
	ST_LOOKING_FOR_ENNEMY,
	ST_SUPPLYING,
	ST_GO_HOME
};

class CSpot
{
     private :
	uint m_TeamId;
	float m_Speed;
	point2f m_Position;
	vec2f m_Direction;
	color4f m_Color;
	float m_LifeLevel;
	float m_MaxLifeLevel;
	float m_WeaponsLevel;
	float m_MaxWeaponsLevel;
	ESpotState m_State;
	CSpot *m_Ennemy;
	bool m_IsBestKiller;
	uint m_NbKills;
	float m_Strength;

     public :
	CSpot( const uint team_id, 
	       const float speed, 
	       const point2f & pos, 
	       const vec2f & dir, 
	       const color4f & color, 
	       const float max_life_level, 
	       const float max_weapons_level, 
	       const float strength );
	virtual ~CSpot();

	static CSpot* random( const uint team_id, const point2f & supplying_pos, const color4f & color )
	{
		float max_life_level, max_weapons_level, speed, strength;
		point2f pos;
		vec2f dir;


		speed             = uniform(2.0f, 6.0f);
		max_life_level    = uniform(400.0f, 500.0f);
		max_weapons_level = uniform(800.0f, 1500.0f);
		strength          = uniform(1.0f, 10.0f);
		dir               = vec2f::urandom(-1.0f, +1.0f);
		dir.normalize();

		do
		{
			pos = point2f::grandom(supplying_pos, point2f(40.0f, 40.0f));
		}
		while( pos.x < 0 || pos.x >= CConfig::WindowWidth || pos.y < 0 || pos.y >= CConfig::WindowHeight );

		return new CSpot(team_id, speed, pos, dir, color, max_life_level, max_weapons_level, strength);
	}

	// actions
	void move();
	void move_to( const point2f & target );
	void rotate( const float angle );

	// getters and setters
	const uint & nb_kills() const;
	void increase_nb_kills();
	const bool & is_best_killer() const;
	void best_killer( const bool bk );
	const uint & team_id() const;
	void team_id( const uint team_id );
	const point2f & position() const;
	void position( const point2f & p );
	const vec2f & direction() const;
	void direction( const vec2f & d );
	const color4f & color() const;
	void color( const color4f & c );
	const float & max_life_level() const;
	void max_life_level( const float mlf );
	const float & life_level() const;
	void life_level( const float lf );
	const float & max_weapons_level() const;
	void max_weapons_level( const float mwp );
	const float & weapons_level() const;
	void weapons_level( const float wp );
	const ESpotState & state() const;
	void state( const ESpotState state );
	CSpot* ennemy() const;
	void ennemy( CSpot *ennemy );
	const float strength() const;
	const float & speed() const;
	void speed( const float s );

	// other
	void render( IWindow *window ) const;
};

#endif //__SPOT_H__
