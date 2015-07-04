#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "ConsoleUtils.h"
#include "EntityNames.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"

#include <time.h>
#include <fstream>

std::ofstream os;

int main(){
	// define this to send output to a text file
#ifdef TEXTOUTPUT
	os.open("output.txt");
#endif

	// seed random number generator
	srand((unsigned) time(NULL));

	// create a miner and his wife
	Miner* Bob = new Miner(ent_Miner_Bob);
	MinersWife* Elsa = new MinersWife(ent_Elsa);

	// register them with the entity manager
	EntityMgr->RegisterEntity(Bob);
	EntityMgr->RegisterEntity(Elsa);

	//simply run through a few Update calls
	for(int i=0; i<30; i++){
		Bob->Update();
		Elsa->Update();
		Dispatch->DispatchDelayedMessages();
		Sleep(800);
	}

	delete Bob;
	delete Elsa;
	
	//wait for a keypress before exiting
	PressAnyKeyToContinue();
	return 0;
}