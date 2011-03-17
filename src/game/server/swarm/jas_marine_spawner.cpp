#include "cbase.h"

#include "asw_shareddefs.h"
#include "asw_marine.h"
#include "jas_marine_spawner.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

LINK_ENTITY_TO_CLASS( jas_marine_spawner, CJaS_Marine_Spawner );

BEGIN_DATADESC( CJaS_Marine_Spawner )
	DEFINE_KEYFIELD( m_iWeaponPrimary, FIELD_STRING, "starting_primary" ),
	DEFINE_KEYFIELD( m_iWeaponSecondary, FIELD_STRING, "starting_secondary" ),
	DEFINE_KEYFIELD( m_nProfileId, FIELD_INTEGER, "profile_id" ),
	DEFINE_FIELD( m_nSquadId, FIELD_INTEGER ),
	DEFINE_FIELD( m_hMarine, FIELD_EHANDLE ),

	DEFINE_THINKFUNC( Think ),

	DEFINE_OUTPUT( m_OutputMarineDied, "MarineDied" ),
	
	DEFINE_INPUTFUNC( FIELD_VOID, "SpawnMarine", InputSpawnMarine ),
	DEFINE_INPUTFUNC( FIELD_VOID, "ForgetMarine", InputForgetMarine ),
	DEFINE_INPUTFUNC( FIELD_VOID, "IncrementSquadId", InputIncrementSquadId )
END_DATADESC()

CJaS_Marine_Spawner::CJaS_Marine_Spawner()
{
	m_nSquadId = 0;
	m_hMarine = NULL;
	m_bHaveSpawnedMarine = false;
}
CJaS_Marine_Spawner::~CJaS_Marine_Spawner() {}

void CJaS_Marine_Spawner::Spawn()
{
	BaseClass::Spawn();

	SetNextThink( gpGlobals->curtime + 0.1f );
}

void CJaS_Marine_Spawner::Think()
{
	if ( m_bHaveSpawnedMarine && !m_hMarine.Get() )
	{
		m_bHaveSpawnedMarine = false;
		m_OutputMarineDied.FireOutput( this, this );
	}

	SetNextThink( gpGlobals->curtime + 0.1f );
}

void CJaS_Marine_Spawner::InputSpawnMarine( inputdata_t &inputdata )
{
	if ( m_bHaveSpawnedMarine )
		return;

	CASW_Marine *pMarine = static_cast<CASW_Marine *>( CreateEntityByName( "asw_marine" ) );
	
	pMarine->SetAbsOrigin( GetAbsOrigin() );
	pMarine->SetAbsAngles( GetAbsAngles() );
	pMarine->KeyValueFromInt( "profile_id", m_nProfileId );
	pMarine->KeyValueFromString( "starting_primary", STRING( m_iWeaponPrimary ) );
	pMarine->KeyValueFromString( "starting_secondary", STRING( m_iWeaponSecondary ) );

	char squadid[256];
	V_snprintf( squadid, 256, "%s_%d", GetEntityNameAsCStr(), m_nSquadId );
	pMarine->KeyValueFromString( "squad_id", squadid );

	pMarine->Spawn();

	m_hMarine = pMarine;

	m_bHaveSpawnedMarine = true;
}

void CJaS_Marine_Spawner::InputForgetMarine( inputdata_t &inputdata )
{
	m_bHaveSpawnedMarine = false;
	m_hMarine = NULL;
}

void CJaS_Marine_Spawner::InputIncrementSquadId( inputdata_t &inputdata )
{
	m_nSquadId++;
}
