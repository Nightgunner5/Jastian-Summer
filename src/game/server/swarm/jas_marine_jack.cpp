#include "cbase.h"
#include "asw_marine.h"
#include "asw_marine_resource.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

class CJaS_Marine_Jack : public CASW_Marine
{
public:
	DECLARE_CLASS( CJaS_Marine_Jack, CASW_Marine );

	CJaS_Marine_Jack() : CASW_Marine() {}
	~CJaS_Marine_Jack() {}

	virtual void Spawn();
};

LINK_ENTITY_TO_CLASS( jas_marine_jack, CJaS_Marine_Jack );

void CJaS_Marine_Jack::Spawn()
{
	CASW_Marine_Resource *pResource = dynamic_cast<CASW_Marine_Resource *>( CreateEntityByName( "asw_marine_resource" ) );
	pResource->SetProfileIndex( 6 );
	pResource->SetMarineEntity( this );
	SetMarineResource( pResource );
	pResource->Spawn();
	m_pProfileOverride = pResource->GetProfile();
	SelectModelFromProfile();
	SetModelFromProfile();

	CBaseCombatWeapon *pWeapon = dynamic_cast<CBaseCombatWeapon *>( CreateEntityByName( "asw_weapon_sniper_rifle" ) );
	if ( pWeapon )
	{
		pWeapon->Spawn();
		pWeapon->GiveDefaultAmmo();
		pWeapon->m_iClip1 = 9999;
		GiveAmmo(9999, pWeapon->GetPrimaryAmmoType());
		Weapon_Equip_In_Index( pWeapon, 0 );
		Weapon_Switch( pWeapon );
	}
	m_bConstantSlowHeal = true;

	m_hSquadFormation = static_cast<CASW_SquadFormation *>( CreateEntityByName( "asw_squadformation" ) );
	m_hSquadFormation->Leader( this );

	SetRenderColor( 0x99, 0x40, 0x40 );

	BaseClass::Spawn();
}