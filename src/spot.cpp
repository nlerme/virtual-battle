#include "ground.h"
#include "config.h"
#include "spot.h"


CSpot::CSpot( const uint team_id, 
	      const float speed, 
	      const point2f & pos, 
	      const vec2f & dir, 
	      const color4f & color, 
	      const float max_life_level, 
	      const float max_weapons_level, 
	      const float strength ) : m_TeamId(team_id), 
				       m_Speed(speed), 
				       m_Position(pos), 
				       m_Direction(dir), 
				       m_Color(color), 
				       m_LifeLevel(max_life_level), 
				       m_MaxLifeLevel(max_life_level), 
				       m_WeaponsLevel(max_weapons_level), 
				       m_MaxWeaponsLevel(max_weapons_level), 
				       m_State(ST_LOOKING_FOR_ENNEMY), 
				       m_Ennemy(NULL), 
				       m_IsBestKiller(false), 
				       m_NbKills(0), 
				       m_Strength(strength){}

CSpot::~CSpot(){}

void CSpot::move()
{
	CGround *g(CGround::instance());

	point2i p1(std::min<int>(m_Position.x+1, CConfig::WindowWidth-1), m_Position.y);
	point2i p2(std::max<int>(m_Position.x-1, 0), m_Position.y);
	point2i p3(m_Position.x, std::min<int>(m_Position.y+1, CConfig::WindowHeight-1));
	point2i p4(m_Position.x, std::max<int>(m_Position.y-1, 0));

	double gx = ((*g)(p1.x, p1.y) - (*g)(p2.x, p2.y)) / 2.0f;
	double gy = ((*g)(p3.x, p3.y) - (*g)(p4.x, p4.y)) / 2.0f;

	vec2d gd(gx, gy);
	double rugosity_factor(exp(-gd.norm() / sq(0.1)));

	m_Position.x = m_Position.x+m_Direction.x*m_Speed*rugosity_factor;
	m_Position.y = m_Position.y+m_Direction.y*m_Speed*rugosity_factor;
}

void CSpot::move_to( const point2f & target )
{
	m_Direction = vec2f(m_Position, target);
	m_Direction.normalize();
}

void CSpot::rotate( const float angle )
{
	m_Direction.rotate(angle);
}

const uint & CSpot::team_id() const
{
	return m_TeamId;
}

void CSpot::team_id( const uint team_id )
{
	m_TeamId = team_id;
}

const point2f & CSpot::position() const
{
	return m_Position;
}

void CSpot::position( const point2f & p )
{
	m_Position = p;
}

const vec2f & CSpot::direction() const
{
	return m_Direction;
}

void CSpot::direction( const vec2f & d )
{
	m_Direction = d;
}

const color4f & CSpot::color() const
{
	return m_Color;
}

void CSpot::color( const color4f & c )
{
	m_Color = c;
}

const float & CSpot::max_life_level() const
{
	return m_MaxLifeLevel;
}

void CSpot::max_life_level( const float mlf )
{
	m_MaxLifeLevel = mlf;
}

const float & CSpot::life_level() const
{
	return m_LifeLevel;
}

void CSpot::life_level( const float lf )
{
	m_LifeLevel = lf;
}

const float & CSpot::max_weapons_level() const
{
	return m_MaxWeaponsLevel;
}

void CSpot::max_weapons_level( const float mwp )
{
	m_MaxWeaponsLevel = mwp;
}

const float & CSpot::weapons_level() const
{
	return m_WeaponsLevel;
}

void CSpot::weapons_level( const float wp )
{
	m_WeaponsLevel = wp;
}

const ESpotState & CSpot::state() const
{
	return m_State;
}

void CSpot::state( const ESpotState state )
{
	m_State = state;
}

CSpot* CSpot::ennemy() const
{
	return m_Ennemy;
}

void CSpot::ennemy( CSpot *ennemy )
{
	m_Ennemy = ennemy;
}

const bool & CSpot::is_best_killer() const
{
	return m_IsBestKiller;
}

void CSpot::best_killer( const bool bk )
{
	m_IsBestKiller = bk;
}

const uint & CSpot::nb_kills() const
{
	return m_NbKills;
}

void CSpot::increase_nb_kills()
{
	m_NbKills++;
}

void CSpot::render( IWindow *window ) const
{
	window->set_pixel(int(m_Position.x), int(m_Position.y), m_Color);
	window->draw_line(m_Position.x, m_Position.y, (m_Position.x+m_Direction.x*15.0f), (m_Position.y+m_Direction.y*15.0f), m_Color);

	if( m_IsBestKiller )
	{
		window->draw_circle(m_Position.x, m_Position.y, 20, m_Color);
		window->draw_circle(m_Position.x, m_Position.y, 23, m_Color);
	}
}

const float CSpot::strength() const
{
	return expf(-float(m_NbKills) / sq(m_Strength));
}

const float & CSpot::speed() const
{
	return m_Speed;
}

void CSpot::speed( const float s )
{
	m_Speed = s;
}
