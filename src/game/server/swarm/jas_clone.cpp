#include "cbase.h"
#include "jas_clone.h"
#include "asw_gamerules.h"

#define JAS_CLONE_MODEL "models/jas_colonist/colonist.mdl"

LINK_ENTITY_TO_CLASS( jas_clone, CJaS_Clone );

IMPLEMENT_SERVERCLASS_ST( CJaS_Clone, DT_JaS_Clone )
END_SEND_TABLE();

BEGIN_DATADESC( CJaS_Clone )
END_DATADESC();

CJaS_Clone::CJaS_Clone()
{
}
CJaS_Clone::~CJaS_Clone()
{
}

void CJaS_Clone::Spawn()
{
	BaseClass::Spawn();
	Precache();

	SetModel( JAS_CLONE_MODEL );
	SetHullType(HULL_HUMAN);
	SetHullSizeNormal();
	SetSolid( SOLID_BBOX );
	AddSolidFlags( FSOLID_NOT_STANDABLE );
	ChangeFaction( FACTION_MARINES );
	SetBloodColor( BLOOD_COLOR_RED );
	m_flFieldOfView		= 0.02;
	m_NPCState		= NPC_STATE_NONE;
	SetMaxHealth( 100 );
	SetHealth( 100 );
	SetNextThink( gpGlobals->curtime + 0.1f );

	if ( !HasSpawnFlags( SF_NPC_START_EFFICIENT ) )
	{
		CapabilitiesAdd( bits_CAP_ANIMATEDFACE | bits_CAP_TURN_HEAD );
		CapabilitiesAdd( bits_CAP_USE_WEAPONS | bits_CAP_AIM_GUN | bits_CAP_MOVE_SHOOT );
		CapabilitiesAdd( bits_CAP_DUCK | bits_CAP_DOORS_GROUP );
		CapabilitiesAdd( bits_CAP_USE_SHOT_REGULATOR );
	}
	CapabilitiesAdd( bits_CAP_NO_HIT_PLAYER | bits_CAP_NO_HIT_SQUADMATES );
	CapabilitiesAdd( bits_CAP_MOVE_GROUND );
	SetMoveType( MOVETYPE_STEP );
	
	AddEFlags( EFL_NO_DISSOLVE | EFL_NO_MEGAPHYSCANNON_RAGDOLL | EFL_NO_PHYSCANNON_INTERACTION );
	NPCInit();
}
void CJaS_Clone::Precache()
{
	BaseClass::Precache();

	PrecacheModel( JAS_CLONE_MODEL );
}

bool CJaS_Clone::CreateBehaviors()
{
	AddBehavior( &m_ActBusyBehavior );
//	AddBehavior( &m_FearBehavior );
//	AddBehavior( &m_FollowBehavior );
//	AddBehavior( &m_LeadBehavior );

	return BaseClass::CreateBehaviors();
}

int CJaS_Clone::SelectSchedule()
{
	//if ( m_ActBusyBehavior.IsRunning() && m_ActBusyBehavior.NeedsToPlayExitAnim() )
	//{
	//	trace_t tr;
	//	Vector	vUp = GetAbsOrigin();
	//	vUp.z += .25;
	//
	//	AI_TraceHull( GetAbsOrigin(), vUp, GetHullMins(),
	//		GetHullMaxs(), MASK_SOLID, this, COLLISION_GROUP_NONE, &tr );
	//
	//	if ( tr.startsolid )
	//	{
	//		if ( HasCondition( COND_HEAR_DANGER ) )
	//		{
	//			m_ActBusyBehavior.StopBusying();
	//		}
	//		DeferSchedulingToBehavior( &m_ActBusyBehavior );
	//		return BaseClass::SelectSchedule();
	//	}
	//}
	//int nSched = SelectFlinchSchedule();
	//if ( nSched != SCHED_NONE )
	//	return nSched;

	BehaviorSelectSchedule();
	
	return BaseClass::SelectSchedule();
}

void CJaS_Clone::Think() {
	BaseClass::Think();
}