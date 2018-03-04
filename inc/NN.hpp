#ifndef NN_HPP
# define NN_HPP

# include "Header.hpp"
# include "Layer.hpp"
# include "Neuron.hpp"

# define MEMORY 256

class NN {
private:
	Layer * _layers;
//	float * _errors;
	int _numLayers;
	int _numInputs;
	float **_memory;

public:
	NN(int numInputs, int numOutputs, int numLayers, int numNeurons) {
		int i;
		
		this->_layers = new Layer[numLayers];
		this->_numLayers = numLayers;
		this->_numInputs = numInputs;
		for (i = 0; i < numLayers; i++) {
			if (i == 0) {
				this->_layers[i] = Layer(numInputs);
			} else if (i == numLayers - 1) {
				this->_layers[i] = Layer(numOutputs);
			} else {
				this->_layers[i] = Layer(numNeurons);
			}
		}
		int io = numInputs + numOutputs;
		this->_memory = new float*[MEMORY];
		for (i = 0; i < MEMORY; i++) {
			this->_memory[i] = new float[io];
		}
//		this->_errors = Layer(numOutputs);
	};~NN(){}

	void save() {

	}

	void load() {
		float* loadedWeights;

		for (int i = 0; i < this->_numLayers; i++) {
			for (int j = 0; j < this->_layers->get("NEURONS"); j++) {
				this->_layers->
					getNeuron(j).
					setWeight(j, loadedWeights[i + j]);
			}
		}
	}

	float* getMemory(int snapshot) {
		return this->_memory[snapshot];
	}

	int getMemories() {
		return MEMORY;
	}

	void remember(float * data, int snapshot) {
		if (snapshot < MEMORY) {
			for (int i = 0; i < NUM_INPUTS + NUM_OUTPUTS; i++) {
				this->_memory[snapshot][i] = data[i];
			}
		} return;
	}


	float forwardPropogate(float *data, int snapshot) {
		for (int h = 0; h < this->_layers[0].get("NEURONS"); h++) {
			this->_memory[snapshot][h] = data[h];
			this->_layers[0].getNeuron(h).set("INPUT", data[h]);
		}

		for (int i = 0; i < this->_numLayers - 1; i++) {
			for (int j = 0; j < this->_layers[i + 1].get("NEURONS"); j++) {
				this->_layers[i + 1].
				getNeuron(j).
				set("INPUT", this->_layers[i].
				sumAllOut(j));
			}
		}

		float highest = 0;
		for (int o = 0;
			o < this->_layers[this->_numLayers - 1].get("NEURONS"); 
			o++)  {
			if (this->_layers[this->_numLayers - 1].
			getNeuron(o).get("OUTPUT") > highest) {
				this->_memory[snapshot][o + this->_numInputs] =
				this->_layers[this->_numLayers - 1].getNeuron(o).get("OUTPUT");
				highest = this->_layers[this->_numLayers - 1].
				getNeuron(o).get("OUTPUT");
			}
		}
		remember(data, snapshot);
		return highest;
	}
	
	float calculateReward(float health, float lives, float attackDamage) {
		float result = ((health * 10.0)
			+ (lives * 5.0)
			+ (attackDamage * 50.0))
			/ MAX_REWARD;
		return result > THRESHOLD ? 1.0 : result;
	}

	void backwardPropogate(float* memory) {
		/* calculate EXPECTED OUTPUTS from REWARD */

		int i;
		
		float reward = calculateReward(
				memory[0],
				memory[1],
				memory[2]
		);

		float errors[NUM_OUTPUTS];

		/* calculate
		OUTPUT ERRORS */

		for (i = NUM_INPUTS; i < NUM_OUTPUTS; i++) {
			errors[i - NUM_INPUTS] = (memory[i] * reward) - memory[i];
		}

		float hiddenErrors[NEURONS_PER_LAYER];

		/* start with the FIRST HIDDEN LAYER and OUTPUT LAYER ERRORS */ 
		for (i = this->_numLayers - 2; i >= 0; i--) {
			adjustErrors(this->_layers[i], errors, i);
			/*if (i == this->_numLayers - 2) {*/
				/* resize ERROR VECTOR to fit HIDDEN NEURON ERRORS */
/*				delete errors;
				errors = new float[NUM_NEURONS];
			}
			for (i = 0; i < NUM_NEURONS; i++) {
				errors[i] = hiddenErrors[i];
			}*/			
		}
		return;
	}

	float deriv(float in) {
		return in + (1 - in);
	}

	void adjustErrors(Layer layer, float* errors, int index) {
		int ns = layer.get("NEURONS");
		float hiddenErrors[ns];
		float expected[ns];
		int i;
		float reward = 0.0;

		hiddenErrors[i] = errors[i]
				* (layer.getNeuron(j).getWeight(k)
				/ layer.getNeuron(j).sumAllWeight());
		
		for (i = 0; i < ns; i++) {
			int weights = layer.getNeuron(i).get("WEIGHTS");
			float hiddenErrors[weights];
			float denom = layer.sumAllWeight();
			hiddenErrors[j] =  (layer.getNeuron(i).getWeight(j) / denom) * errors[j];
		}


		if (index == NUM_LAYERS - 1) {
			for (int h = 0; h < NUM_OUTPUTS; h++) {
				expected[h] = reward *
						layer.
						getNeuron(h).
						get("OUTPUT");
			}
		}

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
	
	}
};

#endif
