#include "EngineBackend.h"
#include "GameObjectManager.h"

EngineBackend* EngineBackend::sharedInstance = nullptr;

EngineBackend* EngineBackend::getInstance()
{
    if (sharedInstance == nullptr)
        sharedInstance = new EngineBackend();
    return sharedInstance;
}

EngineMode EngineBackend::getMode()
{
    return m_mode;
}

void EngineBackend::setMode(EngineMode mode)
{
    if (mode == EngineMode::Editor)
    {
        resetStates();
    }
    else if (mode == EngineMode::Play)
    {
        setStates();
    }
    m_mode = mode;
}

void EngineBackend::startFrameStep()
{
    m_framestep = true;
}

bool EngineBackend::insideFrameStep()
{
    return m_framestep;
}

void EngineBackend::endFrameStep()
{
    m_framestep = false;
}

void EngineBackend::setStates()
{
    std::vector<AGameObject*> objList = GameObjectManager::getInstance()->getAllObjects();

    m_objStateList.clear();
    for (int i = 0; i < objList.size(); i++)
    {
        ObjStatePair temp; temp.obj = objList[i];
        temp.state = ObjectState(temp.obj->getLocalPosition(), temp.obj->getLocalRotation(), temp.obj->getLocalScale());
        
        m_objStateList.push_back(temp);
    }
}

void EngineBackend::resetStates()
{
    std::vector<AGameObject*> objList = GameObjectManager::getInstance()->getAllObjects();
    for (int i = 0; i < m_objStateList.size(); i++)
    {
        AGameObject* obj = m_objStateList[i].obj;

        obj->setPosition(m_objStateList[i].state.position);
        obj->setRotation(m_objStateList[i].state.rotation);
        obj->setScale(m_objStateList[i].state.scale);

        //if gameobject was deleted during play
        if (GameObjectManager::getInstance()->findObjectByName(obj->getName()) != obj)
        {
            GameObjectManager::getInstance()->addObject(obj);
        }
    }
    GameObjectManager::getInstance()->resetAllComponents();
}

EngineBackend::EngineBackend()
{
}

EngineBackend::~EngineBackend()
{
}
