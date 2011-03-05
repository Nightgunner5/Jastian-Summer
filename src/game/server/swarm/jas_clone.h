#include "ai_playerally.h"
#include "ai_behavior_actbusy.h"
#include "ai_behavior_fear.h"
#include "ai_behavior_follow.h"
#include "ai_behavior_lead.h"

class CJaS_Clone : public CAI_BaseActor
{
public:
	DECLARE_CLASS( CJaS_Clone, CAI_BaseActor );
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

	CJaS_Clone();
	~CJaS_Clone();
	
	virtual void Spawn();
	virtual void Precache();

	virtual bool CreateBehaviors();
	virtual int SelectSchedule();
	virtual void Think();

private:
	CAI_ActBusyBehavior m_ActBusyBehavior;
	CAI_FearBehavior m_FearBehavior;
	CAI_FollowBehavior m_FollowBehavior;
	CAI_LeadBehavior m_LeadBehavior;
	
	virtual CAI_FollowBehavior &GetFollowBehavior( void ) { return m_FollowBehavior; }
};