#include "cbase.h"
#include "jas_alien_controller.h"
#include "asw_alien.h"
#include "asw_buzzer.h"
#include "asw_ai_senses.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_SERVERCLASS_ST( CJaS_Alien_Controller, DT_JaS_Alien_Controller )
	SendPropEHandle( SENDINFO( m_hAlien ) ),
	SendPropEHandle( SENDINFO( m_hBuzzerOverride ) ),
END_SEND_TABLE()

BEGIN_DATADESC( CJaS_Alien_Controller )
	DEFINE_FIELD( m_hAlien, FIELD_EHANDLE ),
	DEFINE_FIELD( m_hBuzzerOverride, FIELD_EHANDLE ),

	DEFINE_INPUTFUNC( FIELD_STRING, "SetAlien", InputSetAlien ),
END_DATADESC()

LINK_ENTITY_TO_CLASS( jas_alien_controller, CJaS_Alien_Controller )

CJaS_Alien_Controller::CJaS_Alien_Controller()
{
	m_hAlien = NULL;
	m_hBuzzerOverride = NULL;
}

CJaS_Alien_Controller::~CJaS_Alien_Controller()
{
	if ( m_hAlien )
		m_hAlien->GetASWSenses()->SetBeingControlled( false );
	m_hAlien = NULL;
	if ( m_hBuzzerOverride )
		m_hBuzzerOverride->GetASWSenses()->SetBeingControlled( false );
	m_hBuzzerOverride = NULL;
}

void CJaS_Alien_Controller::InputSetAlien( inputdata_t &inputdata )
{
	if ( m_hAlien )
	{
		m_hAlien->GetASWSenses()->SetBeingControlled( false );
	}
	m_hAlien = NULL;
	if ( m_hBuzzerOverride )
	{
		m_hBuzzerOverride->GetASWSenses()->SetBeingControlled( false );
		m_hBuzzerOverride->SetRenderAlpha( 255 );
	}
	m_hBuzzerOverride = NULL;

	CASW_Alien *pAlien = dynamic_cast<CASW_Alien *>( gEntList.FindEntityByName( NULL, inputdata.value.String(), this, inputdata.pActivator, inputdata.pCaller ) );
	
	if ( !pAlien )
	{
		CASW_Buzzer *pBuzzer = dynamic_cast<CASW_Buzzer *>( gEntList.FindEntityByName( NULL, inputdata.value.String(), this, inputdata.pActivator, inputdata.pCaller ) );
		if ( pBuzzer )
		{
			pBuzzer->GetASWSenses()->SetBeingControlled( true );
			pBuzzer->SetRenderAlpha( 0 );
			m_hBuzzerOverride = pBuzzer;
		}

		return;
	}

	pAlien->GetASWSenses()->SetBeingControlled( true );
	m_hAlien = pAlien;
}