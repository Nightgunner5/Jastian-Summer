#include "cbase.h"
#include "asw_simple_grub.h"
#include "ai_network.h"

class CJaS_GeneratorSparks : public CASW_Simple_Grub
{
public:
	DECLARE_CLASS( CJaS_GeneratorSparks, CASW_Simple_Grub );
	DECLARE_DATADESC();

	CJaS_GeneratorSparks();
	virtual ~CJaS_GeneratorSparks();

	virtual void Spawn();
	virtual void Precache();
	virtual void Think();

private:
	Vector m_vecStartPos;
};

BEGIN_DATADESC( CJaS_GeneratorSparks )
	DEFINE_FIELD( m_vecStartPos, FIELD_VECTOR ),
END_DATADESC();

PRECACHE_REGISTER( jas_generatorsparks );
LINK_ENTITY_TO_CLASS( jas_generatorsparks, CJaS_GeneratorSparks );

CJaS_GeneratorSparks::CJaS_GeneratorSparks() {}

CJaS_GeneratorSparks::~CJaS_GeneratorSparks() {}

void CJaS_GeneratorSparks::Spawn()
{
	BaseClass::Spawn();

	// We need all this to prevent us from getting stuck in walls.
	SetModel( "models/aliens/Grubs/Grub.mdl" );
	SetRenderMode( kRenderNone );
	AddEffects( EF_NODRAW | EF_NOSHADOW );
	SetSolid( SOLID_NONE );

	m_bAllowEnemies = true;
	m_vecStartPos = GetAbsOrigin();
	SetHullType( HULL_TINY );

	m_takedamage = DAMAGE_NO;
}

void CJaS_GeneratorSparks::Precache()
{
	BaseClass::Precache();

	PrecacheModel( "models/aliens/Grubs/Grub.mdl" );
}

void CJaS_GeneratorSparks::Think()
{
	BaseClass::Think();

	if ( !RandomInt( 0, 10 ) )
	{
		CBaseEntity *pNearestMarine = gEntList.FindEntityByClassnameNearest( "asw_marine", m_vecStartPos, 384 );
		CBaseEntity *pNearestDrone = gEntList.FindEntityByClassnameNearest( "asw_drone", m_vecStartPos, 384 );
		CBaseEntity *pNearestBuzzer = gEntList.FindEntityByClassnameNearest( "asw_buzzer", m_vecStartPos, 384 );

		CBaseEntity *pNearest = pNearestMarine ? pNearestMarine : ( pNearestDrone ? pNearestDrone : pNearestBuzzer );
		if ( !pNearest )
		{
			SetEnemy( NULL );
			return;
		}

		if ( pNearestDrone && pNearest->GetDistanceToEntity( this ) > pNearestDrone->GetDistanceToEntity( this ) )
		{
			pNearest = pNearestDrone;
		}
		if ( pNearestBuzzer && pNearest->GetDistanceToEntity( this ) > pNearestBuzzer->GetDistanceToEntity( this ) )
		{
			pNearest = pNearestBuzzer;
		}

		SetEnemy( pNearest );
	}
}