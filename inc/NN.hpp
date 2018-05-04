#ifndef NN_HPP
# define NN_HPP

# include "Header.hpp"
# include "Layer.hpp"
# include "Neuron.hpp"
# include <math.h>
# include <vector>

# define MEMORY 256

// NOTE : NEED TO KEEP TRACK OF SCORE

class NN {

protected:
	int * _map;
	int _maxScore;
	int _numLayers;
	int _numInputs;
	Layer * _layers;
	int _memoryIndex;
	float _learningRate;
	float *_memory[MEMORY];

public:
	NN(int numInputs, int numOutputs, int numLayers, int numNeurons) {
		int i;
		this->_maxScore = 0;
		this->_memoryIndex = 0;
		this->_layers = new Layer[numLayers];
		this->_numLayers = numLayers;
		this->_numInputs = numInputs;
		this->_map = new int[numOutputs];
		this->_learningRate = 0.99f;
		/* harcoded mappings for intended outputs 
		due to change */
//		this->_map[0]=1;
//		this->_map[1]=2;
		this->_map[2]=3;
		this->_map[3]=4;
		this->_map[4]=5;
		this->_map[1]=6;
		this->_map[0]=8;
		for (i = 0; i < numLayers; i++) {
			if (i == 0) {
				this->_layers[i] = *new Layer(numInputs, numNeurons);
			} else if (i == numLayers - 1) {
				this->_layers[i] = *new Layer(numOutputs, 0);
			} else if (i == numLayers - 2) {
				this->_layers[i] = *new Layer(numNeurons, numOutputs);
			} else {
				this->_layers[i] = *new Layer(numNeurons, numNeurons);
			}
		}
		int io = numInputs + numOutputs;
		for (i = 0; i < MEMORY; i++) {
			this->_memory[i] = new float[io];
		}
	};~NN(){};NN(){};NN(NN const & r){*this=r;}

	NN & operator=(NN const & r) {
		this->_learningRate = r._learningRate;
		this->_numLayers = r._numLayers;
		this->_numInputs = r._numInputs;
		for (int i = 0; i < this->_numLayers; i++) {
			this->_layers[i] = r._layers[i];
		}
		for (int j = 0; j < MEMORY; j++) {
			this->_memory[j] = new float[NUM_INPUTS + NUM_OUTPUTS];
		}
		return *this;
	}

	float getLR() {
		return this->_learningRate;
	}

	void save() {
		/* save trained weights */
	}

	void load() {
		/* load trained weights */
		float* loadedWeights;

		for (int i = 0; i < this->_numLayers; i++) {
			for (int j = 0; j < this->_layers->getNeurons(); j++) {
				this->_layers->
					getNeuron(j).
					setWeight(j, loadedWeights[i + j]);
			}
		}
	}

	Layer & getLayer(int i) {
		return this->_layers[i];
	}

	int getLayers() {
		return this->_numLayers;
	}

	int getMemories() {
		return MEMORY;
	}

	int getMemoryIndex() {
		return this->_memoryIndex;
	}

	float * getMemory(int snapshot) {
		////std::cout << "RETURNING MEMORY SNAPSHOT == " << snapshot << std::endl;

//		for (int i = 0; i < NUM_INPUTS + NUM_OUTPUTS; i++) {
//			////std::cout << this->_memory[snapshot][i] << std::endl;
//		}

		if (snapshot <= this->_memoryIndex && snapshot < MEMORY) {
			//std::cout << "snapshot === " << snapshot << std::endl;
			return this->_memory[snapshot];
		} else {
			//std::cout << "snapshot % MEMORY === " << snapshot % MEMORY  << std::endl;
			return this->_memory[snapshot % MEMORY];
		}
	}

	void remember(float * data, int snapshot) {
		//std::cout << "MEMBERING" << std::endl;
		int i;
		/* remember function takes a float array of data to be
		indexed and stored by snapshot number,
		this keeps the data sequential for use later by the
		backpropagation algorithm */

		if (snapshot >= MEMORY) {
			//std::cout << "snap > MEMORY == " << snapshot % MEMORY << std::endl;
			this->_memoryIndex = snapshot % MEMORY;
		} else if (snapshot > this->_memoryIndex) {
			//std::cout << "snap > MEMINDEX == " << snapshot << std::endl;
			this->_memoryIndex = snapshot;
		}

		for (i = 0; i < NUM_INPUTS + NUM_OUTPUTS; i++) {
			this->_memory[this->_memoryIndex][i] = data[i];
		}
		//std::cout << "I MEMBER" << std::endl;
	}

	float * squash(float * array, int len) {
		/* Squashes an array to 1-hot vector */
		int i;
		float sum = 0.0f;

		for (i = 0; i < len; i++) {sum+=array[i];} // loooool
		for (i = 0; i < len; i++) {array[i]/=sum;} // k
		return array;
	}

	int & forwardPropogate(float * data, int snapshot) {
		//std::cout << "FORWARD PROPPIN IT UP" << std::endl;
		int o; // o, hi
		int h;
		int i;
		int j;
		int index;
		float out;
		float highest = 0.0f;
		float array[NUM_INPUTS + NUM_OUTPUTS];
//		////std::cout << "REMEMBERING SNAPSHOT == " << snapshot << std::endl;
//		remember(data, snapshot);
		/* loop through the first layer and set the inputs equal to
		relevant observations of the game state */
		for (h = 0; h < this->_layers[0].getNeurons(); h++) {
			array[h] = data[h];
			this->_layers[0].getNeuron(h).setInput(data[h]);
		}

		/* loop through every other layer after the first,
		looking at the next layer,
		forward propagating the signals through activations */
		for (i = 0; i < this->_numLayers - 1; i++) {
			for (j = 0; j < this->_layers[i + 1].getNeurons(); j++) {
				out = this->_layers[i].sumAllOut(j);
				this->_layers[i + 1].
				getNeuron(j).
				setInput(out);
			}
		}

		/* loop through the neurons on the last layer
		and look at the highest produced result at each index
		if the result at index i is higher than the current highest result
		then we set the highest equal to the result at index i
		and save the index */
		for (o = 0; o < this->_layers[this->_numLayers - 1].getNeurons(); o++)  {
			array[o + NUM_INPUTS] =
			this->_layers[this->_numLayers - 1].getNeuron(o).activate() / NUM_OUTPUTS;

			if (this->_layers[this->_numLayers - 1].getNeuron(o).activate() / NUM_OUTPUTS > highest) {
				highest = this->_layers[this->_numLayers - 1].
				getNeuron(o).activate() / NUM_OUTPUTS;
				index = o;
			}
		}
		/* remember the snapshot for later use in training */
		remember(array, snapshot);
		////std::cout << "LEAVING FORWARD PROP WITH SNAPSHOT == " << snapshot << std::endl;
		////std::cout << "address of snapshot == " << getMemory(snapshot) << std::endl;
		/* return the index mapped to an actual output */
		//std::cout << "FORWARD PROP DONEZO" << std::endl;
		if (RNGf(0.0f, 1.0f) >= this->_learningRate) {
			return this->_map[index];
		} else {
//			std::cout << RNG(0, 7) << std::endl;
			return this->_map[(RNG(0, NUM_OUTPUTS))];
		}
	}
	
	float RNGf(float min, float max) {
		float random = static_cast <float> (rand() /
				static_cast <float> (RAND_MAX *
				((max - min) + min)));
		return random;
	}

	int RNG(int min, int max) {
		int random  = rand() % max + min;
		return random;
	}

	float calculateReward(float health, float lives, float attackDamage, int score) {
		/* simply returns the current player state in comparison to
		the maximum reward in order to evaluate performance */
		/* BIG OL' NOTE :: MIGHT NEED ADJUSTMENT DEPENDING ON LEARNING RATE */
		/*////std::cout << "PRINTING REWARD STATS" << std::endl;
		////std::cout <<
		health <<
		std::endl <<
		lives <<
		std::endl <<
		attackDamage <<
		std::endl;*/
		if (score > this->_maxScore) this->_maxScore = score;
		float result = ((health)
			+ (lives)
			+ (attackDamage)) + score;
		return result;
	}

	void backwardPropagate(float * memory, float health, float lives, float atkDmg, int score) {
		////std::cout << "BACK PROPPING IT UP" << std::endl;
		/* for every layer in the network,
		starting from the end and working to the front
			errors[]
			if not the last layer
				for every neuron[i] in that layer
					error = 0.0
					for every neuron[j] in the layer after current layer
						error += neuron.getWeight(j) * delta;
					errors[i] = error;
			else
				for every neuron[j] in the last layer
					errors[j] = expected[j] - neuron.getOutput();
			for every neuron[i] in layer
				neuron.setDelta(errors[i] * neuron.transferDeriv(neuron.getOutput()));*/
		int i;
		int j;
		int k;
		/* calculate the reward from remembered player status */
		float reward = calculateReward(
			health, lives, atkDmg, score
		);
		float error;
		float expected[NUM_OUTPUTS];
		std::vector<float> errors(NUM_OUTPUTS);

		/* calculate the expected output for the final output */
//		////std::cout << "PRINTING EXPECTED VALUES" << std::endl;
		////std::cout << "before getting expected" << std::endl;
//		for (i = NUM_INPUTS; i < NUM_OUTPUTS; i++) { // cheeky math, looks bad man sorry future samurai
//			expected[i - NUM_INPUTS] = memory[i] * MAX_REWARD; // update: cheeky math might be fucking me
//			std::cout << expected[i] << std::endl;
//		}
//		exit(1);

		/* loop through each layer before the last
		and adjust weights dependent on the errors
		of the "previous" layer */
		////std::cout << "before loopin" << std::endl;
		for (i = this->_numLayers - 1; i >= 0; i--) {
			errors.resize(this->_layers[i].getNeurons());
			if (i != this->_numLayers - 1) { // not last layer
				for (j = 0; j < this->_layers[i].getNeurons(); j++) {
					error = 0.0f;
					for (k = 0; k < this->_layers[i + 1].getNeurons(); k++) {
						error += this->_layers[i].getNeuron(j).getWeight(k) *	// gotta
							 this->_layers[i].getNeuron(k).getDelta();	// clean
//						std::cout << "error == " <<  error << std::endl;
						errors.push_back(error);
					}
				}
			} else {
//				std::cout << "let's start this shit" << std::endl;
				float discount = 0.99;
				for (j = 0; j < this->_layers[i].getNeurons(); j++) {
					/*////std::cout <<
					"reward == " <<
					reward <<
					std::endl <<
					1 - (reward / MAX_REWARD) <<
					std::endl;*/
					errors.push_back(
						(((MAX_REWARD + this->_maxScore) -
						(reward * discount)) /
						(MAX_REWARD + (this->_maxScore * discount)) *
						(this->_layers[i].getNeuron(j).activate() / NUM_OUTPUTS))
						//(memory[i + NUM_INPUTS] * (1 - (reward / MAX_REWARD))) - memory[i + NUM_INPUTS]
					);
					discount *= discount;
				}
//				for (std::vector<float>::const_iterator q = errors.begin(); q != errors.end(); q++) {
//					std::cout << "output error " << (*q) << std::endl;
//				}
//				exit(1);
			}
			j = 0;
			for (std::vector<float>::const_iterator q = errors.begin(); q != errors.end(); q++) {
				this->_layers[i].getNeuron(j).setDelta(*q *				// this
				this->_layers[i].getNeuron(j).transferDeriv(				// shit
				this->_layers[i].getNeuron(j).activate()));				// ip man kung fu ???
//				std::cout << "delta == " << this->_layers[i].getNeuron(j).getDelta() << std::endl;
				j++;
			}
		}

		if (RNGf(0.0f, 1.0f) >= this->_learningRate)
		if (RNGf(0.0f, 1.0f) >= this->_learningRate)
			this->_learningRate *= 0.99f;
		updateWeights(expected, memory);
//		////std::cout << "crisis averted" << std::endl;
	}

	void updateWeights(float * expected, float * memory) {
		std::vector<float> inputs;
		int i;
		int j;
		int k;

		inputs.resize(NUM_INPUTS);
		for (i = 0; i < NUM_INPUTS; i++) {
//			std::cout << memory[i] << std::endl;
			inputs[i] = memory[i];
//			std::cout << inputs[i] << std::endl;
		}
//		exit(1);
		for (i = 0; i < this->_numLayers; i++) {
			inputs.resize(this->_layers[i].getNeurons());
			if (i != 0) {
				for (j = 0; j < this->_layers[i].getNeurons(); j++) {
					inputs[j] = this->_layers[i].getNeuron(j).getInput();
				}
				for (j = 0; j < this->_layers[i].getNeurons(); j++) {
					for (k = 0; k < this->_layers[i].getNeuron(j).getWeights(); k++) {
//						std::cout << "printing wait == " << this->_layers[i].getNeuron(j).getWeight(k) << std::endl;
//						std::cout << "learning rate == " << 0.87 << std::endl;
//						std::cout << "this input == " << inputs[j] << std::endl;
//						std::cout << "should be == " << this->_layers[i].getNeuron(j).getWeight(k) + 0.87 * this->_layers[i].getNeuron(j).getDelta() * inputs[j] << std::endl;
						this->_layers[i].getNeuron(j).setWeight(k
						, this->_layers[i].getNeuron(j).getWeight(k)
						+ this->_learningRate
						* this->_layers[i].getNeuron(j).getDelta()
						* inputs[j]);
//						std::cout << "printing wait == " << this->_layers[i].getNeuron(j).getWeight(k) << std::endl;
					}
				}
			}
		}
	}
		

	/*float * adjustErrors(Layer & layer, float * errors, int index) {
		int h;
		int i;
		int j;
		int weights;
		float reward = 0.0;
		int numNeurons = layer.getNeurons(); // NUMBER OF NEURONS
		float expected[numNeurons];
		float hiddenErrors[numNeurons]; //
		float denom = layer.sumAllWeight();

		 ITERATE through each NEURON on LAYER
		get number of WEIGHTS connected to each NEURON 
		for (i = 0; i < numNeurons; i++) {
			weights = layer.getNeuron(i).getWeights();
			float hiddenErrors[weights];
			 if we're on the last layer
			loop through the outputs and find the expected value 
			if (index != NUM_LAYERS - 1) {
				for (j = 0; j < weights; j++) {
					hiddenErrors[j] = (layer.getNeuron(i).getWeight(j) / denom) * errors[j];
				}
			} else {
				for (h = 0; h < NUM_OUTPUTS; h++) {
					expected[h] = MAX_REWARD *
						layer.
						getNeuron(h).
						getOutput();
				}
		
				for (h = 0; h < NUM_OUTPUTS; h++) {
					weights = expected[h] - 
						(reward * layer.
						getNeuron(h).
						getOutput());
				}
			}
		} return hiddenErrors;*/

// NO ### !!!
/*		for (int i = 0; i < ns; i++) {
			ns = layer.getNeuron(i).get("WEIGHTS");
			float deltas[ns];
			for (int j = 0; j < ns; j++) {
				deltas[j] = LEARNING_RATE * errors[] * deriv(predicted[i]);
			}
			deltas = 
			layer.getNeuron(i).get("WEIGHT") / denom;
		 return;
*/
// BAD ### !!!
	
	//}
};

#endif
