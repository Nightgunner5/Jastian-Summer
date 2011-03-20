#include "cbase.h"
#include "asw_simple_grub.h"
#include "ai_network.h"

class CJaS_GeneratorSparks : public CASW_Simple_Grub
{
public:
	DECLARE_CLASS( CJaS_GeneratorSparks, CASW_Simple_Grub );

	CJaS_GeneratorSparks();
	virtual ~CJaS_GeneratorSparks();

	virtual void Spawn();
	virtual void Precache();
};

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
	SetHullType( HULL_TINY );

	m_takedamage = DAMAGE_NO;
}

void CJaS_GeneratorSparks::Precache()
{
	BaseClass::Precache();

	PrecacheModel( "models/aliens/Grubs/Grub.mdl" );
}