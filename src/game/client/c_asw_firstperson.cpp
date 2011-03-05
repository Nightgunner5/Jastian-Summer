#include "cbase.h"
#include "c_asw_firstperson.h"
#include "asw_input.h"
#include "mapentities_shared.h"
#include "datacache/imdlcache.h"
#include "gamestringpool.h"
#include "tier1/fmtstr.h"

C_ASW_FirstPerson* g_pFirstPerson = NULL;
extern ConVar asw_controls;
extern ConVar asw_draw_hud;

C_ASW_FirstPerson::C_ASW_FirstPerson()
{
	if (g_pFirstPerson != NULL)
	{
		delete g_pFirstPerson;
		g_pFirstPerson = NULL;
	}
	
	m_bPlayerIsColonist = false;
	g_pFirstPerson = this;
	ASWInput()->CAM_ToFirstPerson();
	asw_controls.SetValue(0);
}

C_ASW_FirstPerson::~C_ASW_FirstPerson()
{
	if (g_pFirstPerson == this)
	{
		g_pFirstPerson = NULL;
		ASWInput()->CAM_ToThirdPerson();
		asw_controls.SetValue(1);
	}
}


void C_ASW_FirstPerson::RecreateAll()
{
	DestroyAll();
	ParseAllEntities( engine->GetMapEntitiesString() );
}

void C_ASW_FirstPerson::DestroyAll()
{
	if (g_pFirstPerson)
	{
		delete g_pFirstPerson;
		g_pFirstPerson = NULL;

		ASWInput()->CAM_ToThirdPerson();
		asw_controls.SetValue(1);
	}
}

const char *C_ASW_FirstPerson::ParseEntity( const char *pEntData )
{
	CEntityMapData entData( (char*)pEntData );
	char className[MAPKEY_MAXLENGTH];
	
	MDLCACHE_CRITICAL_SECTION();

	if (!entData.ExtractValue("classname", className))
	{
		Error( "classname missing from entity!\n" );
	}

	if ( !Q_strcmp( className, "asw_firstperson" ) )
	{
		if (!g_pFirstPerson)
		{
			g_pFirstPerson = new C_ASW_FirstPerson();
		}

		// Set up keyvalues.
		g_pFirstPerson->ParseMapData(&entData);

		engine->ClientCmd( "cl_selectm 0 -1" );
		engine->ClientCmd( "cl_start" );
		asw_draw_hud.SetValue( 0 );

		return entData.CurrentBufferPosition();
	}
	
	// Just skip past all the keys.
	char keyName[MAPKEY_MAXLENGTH];
	char value[MAPKEY_MAXLENGTH];
	if ( entData.GetFirstKey(keyName, value) )
	{
		do 
		{
		} 
		while ( entData.GetNextKey(keyName, value) );
	}

	//
	// Return the current parser position in the data block
	//
	return entData.CurrentBufferPosition();
}

bool C_ASW_FirstPerson::KeyValue( const char *szKeyName, const char *szValue ) 
{
	if ( !Q_strcmp( szKeyName, "player_is_colonist" ) )
	{
		if ( atoi( szValue ) )
		{
			m_bPlayerIsColonist = true;
		}
		else
		{
			m_bPlayerIsColonist = false;
		}
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// Purpose: Only called on BSP load. Parses and spawns all the entities in the BSP.
// Input  : pMapData - Pointer to the entity data block to parse.
//-----------------------------------------------------------------------------
void C_ASW_FirstPerson::ParseAllEntities(const char *pMapData)
{
	int nEntities = 0;

	char szTokenBuffer[MAPKEY_MAXLENGTH];
	//  Loop through all entities in the map data, creating each.
	for ( ; true; pMapData = MapEntity_SkipToNextEntity(pMapData, szTokenBuffer) )
	{
		// Parse the opening brace.
		char token[MAPKEY_MAXLENGTH];
		pMapData = MapEntity_ParseToken( pMapData, token );
		// Check to see if we've finished or not.
		if (!pMapData)
			break;

		if (token[0] != '{')
		{
			Error( "C_ASW_FirstPerson::ParseAllEntities: found %s when expecting {", token);
			continue;
		}
		// Parse the entity and add it to the spawn list.
		pMapData = ParseEntity( pMapData );

		nEntities++;
	}
}

void C_ASW_FirstPerson::ParseMapData( CEntityMapData *mapData )
{
	char keyName[MAPKEY_MAXLENGTH];
	char value[MAPKEY_MAXLENGTH];

	// loop through all keys in the data block and pass the info back into the object
	if ( mapData->GetFirstKey(keyName, value) )
	{
		do
		{
			KeyValue( keyName, value );
		}
		while ( mapData->GetNextKey(keyName, value) );
	}
}