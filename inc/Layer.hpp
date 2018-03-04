#ifndef LAYER_HPP
# define LAYER_HPP

# include "Header.hpp"
# include "Neuron.hpp"
# include <cstdlib>
# include <stdlib.h>

class Layer {
private:
	Neuron * _neurons;
	int _numNeurons;

public:
	Layer(int numNeurons) {
		this->_numNeurons = numNeurons;
		this->_neurons = new Neuron[numNeurons];
		for (int i = 0; i < numNeurons; i++) {
			this->_neurons[i] = Neuron(numNeurons);
		} 
	};~Layer(){};Layer(){};

	Layer & operator=(const Layer & r) {
		this->_numNeurons = r._numNeurons;
		for (int i = 0; i < r._numNeurons; i++) {
			this->_neurons[i] = r._neurons[i];
		}
	}

	float sumAllOut(int index) {
		float result = 0;
		for (int i = 0; i < this->_numNeurons; i++) {
			result += this->_neurons[i].get("OUTPUT") *
			this->_neurons[i].getWeight(index);
		} return result;
	}

	float sumAllWeight() {
		float result = 0;
		for (int i = 0; i < this->_numNeurons; i++) {
			result += this->_neurons[i].get("WEIGHT");
		} return result;
	}

	Neuron getNeuron(int index) {
		return this->_neurons[index];
	}

	int get(std::string opt) {
		if (opt == "NEURONS") {
			return this->_numNeurons;
		}
	}
};

#endif
