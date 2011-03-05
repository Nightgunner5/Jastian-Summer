#ifndef _INCLUDED_C_ASW_FIRSTPERSON_H
#define _INCLUDED_C_ASW_FIRSTPERSON_H
#ifdef _WIN32
#pragma once
#endif

class C_ASW_FirstPerson
{
public:
	C_ASW_FirstPerson();
	virtual ~C_ASW_FirstPerson();

	static void RecreateAll();
	static void DestroyAll();

	bool m_bPlayerIsColonist;

protected:
	static const char * ParseEntity( const char *pEntData );
	static void ParseAllEntities(const char *pMapData);
	void ParseMapData( CEntityMapData *mapData );
	bool KeyValue( const char *szKeyName, const char *szValue );
};

extern C_ASW_FirstPerson* g_pFirstPerson;

#endif // _INCLUDED_C_ASW_FIRSTPERSON_H