#ifndef NEURON_HPP
# define NEURON_HPP

# include "Header.hpp"
# include <iostream>
# include <cstdlib>

class Neuron {
protected:
	float _input;
	float _output;
	float * _weights;
	int _numWeights;
	float _bias;

public:
	Neuron(int connections) {
		//std::cout << "neuron constructor called" << std::endl;
		this->_numWeights = connections;
		this->_bias = RNG(-1, 1);
		this->_weights = new float[connections];
		for (int i = 0; i < connections; i++) {
			this->_weights[i] = RNG(-1, 1);
		}
		//std::cout << "neuron constructor completed" << std::endl;
	};~Neuron(){};Neuron(){};

	Neuron & operator=(const Neuron & r) {
		this->_input = r._input;
		this->_output = r._output;
		this->_numWeights = r._numWeights;
		this->_bias = r._bias;
		this->_weights = new float[this->_numWeights];
		for (int i = 0; i < r._numWeights; i++) {
			this->_weights[i] = r._weights[i];
		}
	}

	float RNG(float Min, float Max)
	{
		return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
	}

	float activate(float input) {
		this->_output = input;
	}
	
	float derive(float input) {
		return input * (1 - input);
	}

	float getWeight(int index) {
		//std::cout << "getting weight" << index << std::endl;
		//std::cout << this->_weights[index] << std::endl;
		return this->_weights[index];
	}

	float get(std::string opt) {
		if (opt == "INPUT") {
			return this->_input;
		} else if (opt == "OUPUT") {
			return this->_output;
		} else if (opt == "WEIGHTS") {
			return this->_numWeights;
		} else if (opt == "BIAS") {
			return this->_bias;
		}
	}

	float sumAllWeight() {
		float result = 0;

		for (int i = 0; i < this->_numWeights; i++) {
			result += this->_weights[i];
		} return result;
	}

	void setWeight(int w, int value) {
		this->_weights[w] = value;
	}

	void set(std::string opt, float value) {
		if (opt == "INPUT") {
			this->_input = value;
		} else if (opt == "OUTPUT") {
			this->_output = value;
		} else;
	}
};

#endif
