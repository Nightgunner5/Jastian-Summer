#ifndef _INCLUDED_JAS_MARINE_SPAWNER_H
#define _INCLUDED_JAS_MARINE_SPAWNER_H
#ifdef _WIN32
#pragma once
#endif

class CJaS_Marine_Spawner : public CServerOnlyEntity
{
	DECLARE_CLASS( CJaS_Marine_Spawner, CServerOnlyEntity );
	DECLARE_DATADESC();
	
public:
	CJaS_Marine_Spawner();
	~CJaS_Marine_Spawner();

	virtual void Spawn();
	virtual void Think();
	
	void InputSpawnMarine( inputdata_t &inputdata );
	void InputIncrementSquadId( inputdata_t &inputdata );

protected:
	string_t m_iWeaponPrimary;
	string_t m_iWeaponSecondary;
	int m_nProfileId;
	int m_nSquadId;
	EHANDLE m_hMarine;
	bool m_bHaveSpawnedMarine;

	COutputEvent m_OutputMarineDied;
};

#endif /* _INCLUDED_JAS_MARINE_SPAWNER_H */