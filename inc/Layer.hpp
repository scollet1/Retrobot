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
		//std::cout << "layer constructor called" << std::endl;
		this->_numNeurons = numNeurons;
		this->_neurons = new Neuron[numNeurons];
/*		for (int i = 0; i < numNeurons; i++) {
			this->_neurons[i] = Neuron(numNeurons);
		}*/
		//std::cout << "layer constructor completed" << std::endl;
	};~Layer(){};Layer(){};

	Layer & operator=(const Layer & r) {
		this->_numNeurons = r._numNeurons;
		this->_neurons = new Neuron[this->_numNeurons];
		for (int i = 0; i < r._numNeurons; i++) {
			//std::cout << "seg" << std::endl;
			this->_neurons[i] = r._neurons[i];
			//std::cout << "end" << std::endl;
		}
	}

	float sumAllOut(int index) {
		float result = 0.0;
		//std::cout << "summing output for neuron" << std::endl;
		for (int i = 0; i < this->_numNeurons; i++) {
			result += this->_neurons[i].get("OUTPUT") *
			this->_neurons[i].getWeight(index);
		}
		//std::cout << "output returned" << std::endl;
		return result;
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
