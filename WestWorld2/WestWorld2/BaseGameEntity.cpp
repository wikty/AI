#include "BaseGameEntity.h"
#include <cassert>

// initialize the next valid ID
int BaseGameEntity::m_iNextValidID = 0;

//---------------------SetID(int val)---------------------
// this must be called within the constructor to make sure
// the ID is set correctly, it verifies that the value passed to 
// the method is greater or equal to the next valid ID, before 
// setting the ID and incrementing the next valid ID
void BaseGameEntity::SetID(int val){
	//make sure the val is equal to or greater that the next available ID
	assert((val >= m_iNextValidID) && "<BaseGameEntity::SetID>:invalid ID");
	m_ID = val;
	m_iNextValidID = m_ID + 1;
}
