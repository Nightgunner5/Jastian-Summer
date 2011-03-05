#ifndef JAS_ALIEN_CONTROLLER_H
#define JAS_ALIEN_CONTROLLER_H
#ifdef _WIN32
#pragma once
#endif

class CASW_Alien;
class CASW_Buzzer;

class CJaS_Alien_Controller : public CBaseEntity
{
public:
	DECLARE_CLASS( CJaS_Alien_Controller, CBaseEntity );
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

	CJaS_Alien_Controller();
	~CJaS_Alien_Controller();

	virtual void InputSetAlien( inputdata_t &inputdata );
	int ShouldTransmit( const CCheckTransmitInfo *pInfo ) { return FL_EDICT_ALWAYS; }
	
	CNetworkHandle( CASW_Alien, m_hAlien );
	CNetworkHandle( CASW_Buzzer, m_hBuzzerOverride );
};

#endif