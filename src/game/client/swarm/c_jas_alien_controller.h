#ifndef C_JAS_ALIEN_CONTROLLER_H
#define C_JAS_ALIEN_CONTROLLER_H
#ifdef _WIN32
#pragma once
#endif

class C_ASW_Alien;
class C_ASW_Buzzer;

DECLARE_AUTO_LIST( I_JaS_Alien_Controller_List );

class C_JaS_Alien_Controller : public C_BaseEntity, public I_JaS_Alien_Controller_List
{
public:
	DECLARE_CLASS( C_JaS_Alien_Controller, CBaseEntity );
	DECLARE_CLIENTCLASS();

	IMPLEMENT_AUTO_LIST_GET();

	C_JaS_Alien_Controller();
	~C_JaS_Alien_Controller();

	virtual void ClientThink();

	CNetworkHandle( C_ASW_Alien, m_hAlien );
	CNetworkHandle( C_ASW_Buzzer, m_hBuzzerOverride );

	ClientCCHandle_t m_CCHandle;
};

#endif