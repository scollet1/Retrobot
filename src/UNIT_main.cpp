#include "NN.hpp"
#include "Game.hpp"
#include "Enemy.hpp"
#include "Header.hpp"
#include "Character.hpp"
#include "GameEntity.hpp"

int main(void) {
	int i;
	int result;
	float inputs[4] = {1, 1, 1, 1};
	NN* nn = new NN(NUM_INPUTS, NUM_OUTPUTS, NEURONS_PER_LAYER, NUM_LAYERS);
	result = (int)nn->forwardPropogate(inputs, 0);
	
	std::cout
	<< "result ==> "
	<< result
	<< std::endl;
	
	for (i = 0; i >= 0; i--) {
		nn->backwardPropogate(nn->getMemory(i));
	}
	
	result = (int)nn->forwardPropogate(inputs, 0);

	std::cout
	<< "result ==> "
	<< result
	<< std::endl;

	return 0;
}
