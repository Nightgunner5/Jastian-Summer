#include "cbase.h"
#include "asw_simple_alien.h"
#include "ai_network.h"

class CJaS_Fireflies : public CASW_Simple_Alien
{
public:
	DECLARE_CLASS( CJaS_Fireflies, CASW_Simple_Alien );
	DECLARE_DATADESC();

	CJaS_Fireflies();
	virtual ~CJaS_Fireflies();

	virtual void Spawn();
	virtual void Precache();
	virtual void WhatToDoNext(float delta);

	virtual Vector PickRandomDestination( float dist, Vector bias );
	virtual bool ApplyGravity( Vector &vecTarget, float deltatime );
	virtual bool PerformMovement( float deltatime );
	virtual float GetIdealSpeed() const;
	virtual bool FailedMove();

private:
	Vector m_vecStartPos;
};

BEGIN_DATADESC( CJaS_Fireflies )
	DEFINE_FIELD( m_vecStartPos, FIELD_VECTOR ),
END_DATADESC();

PRECACHE_REGISTER( jas_fireflies );
LINK_ENTITY_TO_CLASS( jas_fireflies, CJaS_Fireflies );

CJaS_Fireflies::CJaS_Fireflies()
{
}

CJaS_Fireflies::~CJaS_Fireflies()
{
}

void CJaS_Fireflies::Spawn()
{
	BaseClass::Spawn();

	// We need all this to prevent us from getting stuck in walls.
	SetModel( "models/aliens/buzzer/buzzer.mdl" );
	SetRenderMode( kRenderNone );
	AddEffects( EF_NODRAW | EF_NOSHADOW );
	SetSolid( SOLID_NONE );

	m_bAllowEnemies = false;
	m_vecStartPos = GetAbsOrigin();
	SetHullType( HULL_TINY_CENTERED );

	m_takedamage = DAMAGE_NO;
}

void CJaS_Fireflies::Precache()
{
	BaseClass::Precache();

	PrecacheModel( "models/aliens/buzzer/buzzer.mdl" );
}

Vector CJaS_Fireflies::PickRandomDestination( float dist, Vector bias )
{
	Vector vecRandom = GetAbsOrigin() + RandomVector(-1, 1) * dist + bias;
	
	// Constrain movement to a 256-radius sphere from the spawn point.
	if ( vecRandom.DistToSqr( m_vecStartPos ) > 65536.0f )
		return VectorLerp( vecRandom, m_vecStartPos, 65536.0f / vecRandom.DistToSqr( m_vecStartPos ) );

	return vecRandom;
}


void CJaS_Fireflies::WhatToDoNext( float delta )
{
	// Unstick from walls (this code helps because normal unsticking would allow going behind displacement walls)
	int nNode = g_pBigAINet->NearestNodeToPoint( GetAbsOrigin(), false );
	if ( nNode > -1 )
	{
		Vector vecNode = g_pBigAINet->GetNodePosition( GetHullType(), nNode );
		if ( vecNode != vec3_origin )
		{
			Ray_t ray;
			trace_t trace;
			// Trace backwards because we're specifically looking for displacements.
			ray.Init( vecNode, GetAbsOrigin(), GetHullMins(), GetHullMaxs() );
			CTraceFilterSimple traceFilter( this, GetCollisionGroup() );
			enginetrace->TraceRay( ray, MASK_NPCSOLID, &traceFilter, &trace );
			if ( trace.DidHit() )
				SetAbsOrigin( vecNode );
		}
	}

	Vector vecMoveDestination = PickRandomDestination( 64, vec3_origin );
	if ( !enginetrace->PointOutsideWorld( vecMoveDestination ) )
	{
		SetMoveTarget( vecMoveDestination );
	}
	SetNextThink( gpGlobals->curtime + 0.1f );
}

bool CJaS_Fireflies::FailedMove()
{
	m_bMoving = false;
	m_vecMoveTarget = GetAbsOrigin();

	int nNode = g_pBigAINet->NearestNodeToPoint( GetAbsOrigin(), false );
	if ( nNode > -1 )
	{
		Vector vecNode = g_pBigAINet->GetNodePosition( GetHullType(), nNode );
		if ( vecNode != vec3_origin )
		{
			SetAbsOrigin( vecNode );
			m_vecMoveTarget = vecNode;
			return true;
		}
	}

	if ( UTIL_FindClosestPassableSpace( this, m_MoveFailure.trace.plane.normal, MASK_NPCSOLID, &m_vecMoveTarget, FL_AXIS_DIRECTION_NONE ) )
	{
		m_vecMoveTarget = GetAbsOrigin();
		return true;
	}
	return false;
}

bool CJaS_Fireflies::ApplyGravity( Vector &vecTarget, float deltatime )
{
	return false;
}

bool CJaS_Fireflies::PerformMovement( float deltatime )
{
	if (!m_bMoving)
		return false;

	if (m_hMoveTarget.Get())	// if we're moving to a specific object, update our target vector with its current location
	{
		m_vecMoveTarget = m_hMoveTarget->GetAbsOrigin();
	}
	Vector vecStartDiff = m_vecMoveTarget - GetAbsOrigin();

	// check we're not there already
	if (vecStartDiff.Length() <= m_fArrivedTolerance)
	{
		FinishedMovement();
		return true;
	}
	
	// work out the new position we want to be in
	Vector vecDir = vecStartDiff;
	vecDir.NormalizeInPlace();
	//Msg("moving with delta %f\n", delta);
	Vector vecNewPos = GetAbsOrigin() + vecDir * GetIdealSpeed() * deltatime;
	if (TryMove(GetAbsOrigin(), vecNewPos, deltatime))
	{
		// apply gravity to our new position
		ApplyGravity(vecNewPos, deltatime);

		// we moved (at least some portion, maybe all)
		UTIL_SetOrigin(this, vecNewPos);

		// check if we're close enough, or have gone past, the move target
		Vector vecEndDiff = m_vecMoveTarget - GetAbsOrigin();
		if (vecStartDiff.Dot(vecEndDiff) < 0 || vecEndDiff.Length() <= m_fArrivedTolerance)
		{
			// we've arrived
			FinishedMovement();
		}
		return true;
	}
	else
	{
		vecNewPos = GetAbsOrigin();
		if (ApplyGravity(vecNewPos, deltatime))	// if we failed to move forward, make sure gravity is still applied
		{
			// we moved (at least some portion, maybe all)
			UTIL_SetOrigin(this, vecNewPos);
		}
	}
	
	FailedMove();
	return false;
}

float CJaS_Fireflies::GetIdealSpeed() const
{
	return 100.0f;
}
