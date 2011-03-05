#include "cbase.h"
#include "jas_weapon_flashlight_shared.h"
#include "in_buttons.h"

#ifdef CLIENT_DLL
#include "c_asw_player.h"
#include "c_asw_weapon.h"
#include "c_asw_marine.h"
#else
#include "asw_marine.h"
#include "asw_player.h"
#include "asw_weapon.h"
#include "npcevent.h"
#include "asw_gamerules.h"
#include "globalstate.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_NETWORKCLASS_ALIASED( JaS_Weapon_Flashlight, DT_JaS_Weapon_Flashlight )

BEGIN_NETWORK_TABLE( CJaS_Weapon_Flashlight, DT_JaS_Weapon_Flashlight )
#ifdef CLIENT_DLL
	// recvprops
#else
	// sendprops
#endif
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CJaS_Weapon_Flashlight )
	
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( jas_weapon_flashlight, CJaS_Weapon_Flashlight );
PRECACHE_WEAPON_REGISTER(jas_weapon_flashlight);

#ifndef CLIENT_DLL

//---------------------------------------------------------
// Save/Restore
//---------------------------------------------------------
BEGIN_DATADESC( CJaS_Weapon_Flashlight )
	
END_DATADESC()

#endif /* not client */

CJaS_Weapon_Flashlight::CJaS_Weapon_Flashlight()
{
#ifdef GAME_DLL
	m_pFlashlight = NULL;
#endif
}


CJaS_Weapon_Flashlight::~CJaS_Weapon_Flashlight()
{
#ifdef GAME_DLL
	if ( m_pFlashlight )
		UTIL_Remove( m_pFlashlight );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: 
// Output : Activity
//-----------------------------------------------------------------------------
Activity CJaS_Weapon_Flashlight::GetPrimaryAttackActivity( void )
{
	return ACT_VM_PRIMARYATTACK;
}

#ifndef CLIENT_DLL

void CJaS_Weapon_Flashlight::MarineDropped(CASW_Marine* pMarine)
{
	if ( m_pFlashlight )
		UTIL_Remove( m_pFlashlight );
	
	if ( GlobalEntity_GetState( "jas_playercontrolledmarineview" ) == GLOBAL_ON )
		GlobalEntity_SetState( MAKE_STRING( "jas_playercontrolledmarineview" ), GLOBAL_DEAD );

	gameeventmanager->FireEvent( gameeventmanager->CreateEvent( "jas_flashlightpickup" ) );

	BaseClass::MarineDropped(pMarine);
}

void CJaS_Weapon_Flashlight::Equip( CBaseCombatCharacter *pOwner )
{
	BaseClass::Equip(pOwner);

	if ( m_pFlashlight )
		UTIL_Remove( m_pFlashlight );

	m_pFlashlight = dynamic_cast<CEnvProjectedTexture *>( CreateEntityByName( "env_projectedtexture" ) );
	m_pFlashlight->AddSpawnFlags( ENV_PROJECTEDTEXTURE_STARTON | ENV_PROJECTEDTEXTURE_ALWAYSUPDATE );
	m_pFlashlight->KeyValueFromInt( "enableshadows", 1 );
	m_pFlashlight->KeyValueFromInt( "shadowquality", 1 );
	m_pFlashlight->KeyValueFromInt( "lightfov", 80 );
	m_pFlashlight->Spawn();
	m_pFlashlight->AcceptInput( "AlwaysUpdateOn", this, this, variant_t(), 0 );
	m_pFlashlight->SetParent( this );
	
	SetThink( &CJaS_Weapon_Flashlight::EquipThink );
	SetNextThink( gpGlobals->curtime + 0.1f );

	if ( GlobalEntity_GetState( "jas_playercontrolledmarineview" ) == GLOBAL_DEAD )
		GlobalEntity_SetState( MAKE_STRING( "jas_playercontrolledmarineview" ), GLOBAL_ON );
}

void CJaS_Weapon_Flashlight::EquipThink()
{
	Vector offset;
	VectorRotate( Vector( ASW_MARINE_GUN_OFFSET_X, ASW_MARINE_GUN_OFFSET_Y + 2.0f, ASW_MARINE_GUN_OFFSET_Z ), GetAbsAngles(), offset );
	m_pFlashlight->SetAbsOrigin( GetAbsOrigin() + offset );
	m_pFlashlight->SetAbsAngles( GetAbsAngles() );
}

void CJaS_Weapon_Flashlight::OrientFlashlight( const QAngle &eyes )
{
	if ( m_pFlashlight )
		m_pFlashlight->SetAbsAngles( eyes );
}

#endif // not client

void CJaS_Weapon_Flashlight::PrimaryAttack( void )
{
	// do nothing
}

void CJaS_Weapon_Flashlight::Precache()
{
	BaseClass::Precache();
}