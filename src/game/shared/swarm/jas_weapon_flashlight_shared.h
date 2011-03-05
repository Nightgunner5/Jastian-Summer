#ifndef _INCLUDED_JAS_WEAPON_FLASHLIGHT_H
#define _INCLUDED_JAS_WEAPON_FLASHLIGHT_H
#pragma once

#ifdef CLIENT_DLL
#include "c_asw_weapon.h"
#define CASW_Weapon C_ASW_Weapon
#define CJaS_Weapon_Flashlight C_JaS_Weapon_Flashlight
#define CASW_Marine C_ASW_Marine
#else
#include "asw_weapon.h"
#include "npc_combine.h"
#include "env_projectedtexture.h"
#endif

#include "basegrenade_shared.h"
#include "asw_shareddefs.h"

class CJaS_Weapon_Flashlight : public CASW_Weapon
{
public:
	DECLARE_CLASS( CJaS_Weapon_Flashlight, CASW_Weapon );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	CJaS_Weapon_Flashlight();
	virtual ~CJaS_Weapon_Flashlight();
	void Precache();
	
	Activity	GetPrimaryAttackActivity( void );

	void	PrimaryAttack();

	#ifndef CLIENT_DLL
		DECLARE_DATADESC();

		// todo: stop AI attacking with this?
		int		CapabilitiesGet( void ) { return bits_CAP_WEAPON_RANGE_ATTACK1; }

		virtual const char* GetPickupClass() { return "jas_pickup_flashlight"; }

		// for toggling the flashlight effect when we take/drop this weapon
		virtual void MarineDropped(CASW_Marine* pMarine);
		virtual void Equip( CBaseCombatCharacter *pOwner );
		virtual void EquipThink();
		virtual void OrientFlashlight( const QAngle &eyes );
		CHandle<CEnvProjectedTexture> m_pFlashlight;
	#endif

	virtual bool IsOffensiveWeapon() { return false; }

	virtual bool ASWCanBeSelected() { return true; }	// no selecting this

	// Classification
	virtual Class_T		Classify( void ) { return (Class_T) CLASS_ASW_FLASHLIGHT; }
};


#endif /* _INCLUDED_JAS_WEAPON_FLASHLIGHT_H */
