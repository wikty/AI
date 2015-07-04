#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
//#pragma(disable:4786)

#include<map>
#include<cassert>
#include<string>

class BaseGameEntity;

// provide easy access
#define EntityMgr EntityManager::Instance()

class EntityManager{
private:
	typedef std::map<int, BaseGameEntity*> EntityMap;
private:
	// ID => pointer(to entity)
	EntityMap m_EntityMap;
	EntityManager(){}
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);
public:
	static EntityManager* Instance();

	// this method stores a pointer to the entity in the std::vector
	// m_Entities at the index position indicated by the entity's ID
	void RegisterEntity(BaseGameEntity* entity);

	// returns a pointer to the entity with the ID given as a argument
	BaseGameEntity* GetEntityByID(int id)const;

	// this method removes the entity from the map
	void RemoveEntity(BaseGameEntity* pEntity);
};

#endif
