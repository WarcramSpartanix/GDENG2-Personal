#pragma once
#include "ObjectState.h"
#include <vector>
#include "AGameObject.h"

enum EngineMode
{
	Editor, Play, Paused
};

struct ObjStatePair
{
	AGameObject* obj;
	ObjectState state;
};

class EngineBackend
{
public:
	static EngineBackend* getInstance();

	EngineMode getMode();
	void setMode(EngineMode mode);
	void startFrameStep();
	bool insideFrameStep();
	void endFrameStep();

	void setStates();
	void resetStates();

private:
	EngineBackend();
	~EngineBackend();

	static EngineBackend* sharedInstance;

	EngineMode m_mode = EngineMode::Editor;
	bool m_framestep = false;

	std::vector<ObjStatePair> m_objStateList;
};

