#include "ActionHistory.h"

ActionHistory* ActionHistory::sharedInstance = nullptr;

ActionHistory* ActionHistory::getInstance()
{
    if (sharedInstance == nullptr)
        sharedInstance = new ActionHistory();
    return sharedInstance;
}

void ActionHistory::recordUndo(AGameObject* gameObject)
{
    m_undoStack.push(new EditorAction(gameObject));
}

void ActionHistory::recordRedo(AGameObject* gameObject)
{
    m_redoStack.push(new EditorAction(gameObject));
}


bool ActionHistory::hasRemainingUndoActions()
{
    return !m_undoStack.empty();
}

bool ActionHistory::hasRemainingRedoActions()
{
    return !m_redoStack.empty();
}

EditorAction* ActionHistory::undoAction()
{
    if (!hasRemainingUndoActions())
    {
        return NULL;
    }
    EditorAction* temp = m_undoStack.top();
    m_undoStack.pop();
    return temp;
}

EditorAction* ActionHistory::redoAction()
{
    if (!hasRemainingRedoActions())
    {
        return NULL;
    }
    EditorAction* temp = m_redoStack.top();
    m_redoStack.pop();
    return temp;
}

void ActionHistory::clear()
{
    for (int i = 0; i < m_undoStack.size(); i++)
    {
        m_undoStack.pop();
    }
    for (int i = 0; i < m_redoStack.size(); i++)
    {
        m_redoStack.pop();
    }
}

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
}
