#include"EntityManager.h"
#include"BaseGameEntity.h"

EntityManager* EntityManager::Instance(){
	static EntityManager instance;
	return &instance;
}

void EntityManager::RegisterEntity(BaseGameEntity* entity){
	m_EntityMap.insert(std::make_pair(entity->ID(), entity));
}

BaseGameEntity* EntityManager::GetEntityByID(int id)const{
	EntityMap::const_iterator ent = m_EntityMap.find(id);
	assert((ent != m_EntityMap.end()) && "<EntityManager::GetEntityByID>:invalid ID");
	return ent->second;
}

void EntityManager::RemoveEntity(BaseGameEntity* pEntity){
	m_EntityMap.erase(m_EntityMap.find(pEntity->ID()));
}