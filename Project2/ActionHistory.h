#pragma once
#include <stack>
#include "EditorAction.h"


class ActionHistory
{
public:
	static ActionHistory* getInstance();

	void recordUndo(AGameObject* gameObject);
	void recordRedo(AGameObject* gameObject);
	bool hasRemainingUndoActions();
	bool hasRemainingRedoActions();
	EditorAction* undoAction();
	EditorAction* redoAction();
	void clear();

private:
	ActionHistory();
	~ActionHistory();

	static ActionHistory* sharedInstance;

	std::stack<EditorAction*> m_redoStack;
	std::stack<EditorAction*> m_undoStack;
};

