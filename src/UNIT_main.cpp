#include "NN.hpp"
#include "Game.hpp"
#include "Enemy.hpp"
#include "Header.hpp"
#include "Character.hpp"
#include "GameEntity.hpp"

#define MEMORY 256

int main(void) {
	int i;
	int result;
	int gameTime = -1;
	float * NoneCheck;
	float inputs[NUM_INPUTS] = {1, 2, 3, 4};
	NN* nn = new NN(NUM_INPUTS, NUM_OUTPUTS, NUM_LAYERS, NEURONS_PER_LAYER);

	while (++gameTime < 300) {
		result = (int)nn->forwardPropogate(inputs, gameTime);
		for (i = 0; i < nn->getMemoryIndex(); i++) {
			nn->backwardPropagate(nn->getMemory(i), 1, 1, 1);
		}
		std::cout << "result == " << result << " && gamteime ==  " << gameTime << std::endl;
	}

	std::cout << "print" << std::endl;
//	exit(1);
	/*for (int i = 0; i < nn->getLayers(); i++) {
		for (int j = nn->getLayer(i).getNeurons() - 1; j >= 0; j--) {
			for (int k = nn->getLayer(i).getNeuron(j).getWeights() - 1; k >= 0; k--) {
				std::cout << "weight == " << nn->getLayer(i).getNeuron(j).getWeight(k) << std::endl;
			}
		}
	}*/
	return 0;
}
