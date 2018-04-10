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
	int _connections;

public:
	Layer(int numNeurons, int connections) {
		this->_connections = connections; // connections per neuron to next layer
		this->_numNeurons = numNeurons;
		this->_neurons = new Neuron[numNeurons];
		for (int i = numNeurons - 1; i >= 0; i--) {
			this->_neurons[i] = (*new Neuron(connections));
		
		}
	};~Layer(){};Layer(){};Layer(Layer const & r){*this = r;}

	Layer & operator=(Layer const & r) {
		this->_numNeurons = r._numNeurons;
		this->_neurons = new Neuron[r._numNeurons];
		for (int i = 0; i < r._numNeurons; i++) {
			this->_neurons[i] = Neuron(r._connections);
		} return *this;
	}

	float sumAllOut(int index) {
		int i;
		float result = 0.0;
		/* loop through each neuron
		and sum the result of the neurons' activation
		multiplied by the weight connected to a specific neuron
		in the next layer */
		for (i = 0; i < this->_numNeurons; i++) {
			result += this->_neurons[i].activate() *
			this->_neurons[i].getWeight(index);
		}
//		std::cout << "PRINTING SUMALLOUT RESULT" << std::endl;
//		std::cout << result << std::endl;
		return result;
	}

	float sumAllWeight() {
		float result = 0;
		for (int i = 0; i < this->_numNeurons; i++) {
			result += this->_neurons[i].sumAllWeight();
		} return result;
	}

	Neuron &/* Who would win???
		A terrible programmer with a year of experience
		-----------------------------------------------
		or one little andy boi??? */
		getNeuron(int index) { // fucking got it lol
		return this->_neurons[index];
	}

	int & getNeurons() {
		return this->_numNeurons;
	}
};

#endif
