#ifndef BASE_GAME_ENTITY_H
#define BASE_GAME_ENTITY_H

class BaseGameEntity{
	private:
		// every entity must have a unique indentifying number
		int m_ID;

		// this is the next valid ID,
		// each time a BaseGameEntity is instantiated, this value is updated
		static int m_iNextValidID;

		// this must be called within the constructor to make sure
		// the ID is set correctly, it verifies that the value passed to 
		// the method is greater or equal to the next valid ID, before 
		// setting the ID and incrementing the next valid ID
		void SetID(int val);
	
	public:
		BaseGameEntity(int id){
			SetID(id);
		}

		virtual ~BaseGameEntity(){}

		// all entities must implement an update method
		virtual void Update()=0;

		int ID()const{ return m_ID; }
};

#endif




