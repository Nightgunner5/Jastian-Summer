#include "cbase.h"
#include "c_jas_alien_controller.h"
#include "c_asw_alien.h"
#include "c_asw_buzzer.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_CLIENTCLASS_DT( C_JaS_Alien_Controller, DT_JaS_Alien_Controller, CJaS_Alien_Controller )
	RecvPropEHandle( RECVINFO( m_hAlien ) ),
	RecvPropEHandle( RECVINFO( m_hBuzzerOverride ) ),
END_RECV_TABLE()

IMPLEMENT_AUTO_LIST( I_JaS_Alien_Controller_List );

C_JaS_Alien_Controller::C_JaS_Alien_Controller()
{
	SetNextClientThink( gpGlobals->curtime + 0.1f );
	m_CCHandle = g_pColorCorrectionMgr->AddColorCorrection( "scripts/colorcorrection/infested_green.raw" );
}

C_JaS_Alien_Controller::~C_JaS_Alien_Controller()
{
}

extern bool g_bRenderingGlows;
void C_JaS_Alien_Controller::ClientThink()
{
	g_bRenderingGlows = m_hAlien.Get() || m_hBuzzerOverride.Get();

	if ( m_CCHandle != INVALID_CLIENT_CCHANDLE )
	{
		g_pColorCorrectionMgr->SetColorCorrectionWeight( m_CCHandle, m_hAlien.Get() || m_hBuzzerOverride.Get() ? 1.0f : 0.0f );
	}

	SetNextClientThink( gpGlobals->curtime + 0.1f );
}
