#ifndef NEURON_HPP
# define NEURON_HPP

# include "Header.hpp"
# include <iostream>
# include <cstdlib>
# include <stdio.h>
# include <string.h>
# include <math.h>

class Neuron {
private:
	float _input;
	float _output;
	float * _weights;
	int _numWeights;
	float _bias;
	float _delta;

public:
	Neuron(int connections) {
		/* Neurons are created with # of connections to other neurons */
		this->_delta = 0.0f;
		this->_numWeights = connections;
		this->_bias = RNG(-1.0, 1.0);
		this->_weights = new float[connections];
		for (int i = 0; i < connections; i++) {
			this->_weights[i] = RNG(-1.0, 1.0);
		}
	};~Neuron(){};Neuron(){};Neuron(Neuron const &r){*this=r;}

	Neuron & operator=(const Neuron & r) {
		memcpy(&this->_input, &r._input, 1 * sizeof(float));
		this->_output = r._output;
		this->_numWeights = r._numWeights;
		this->_bias = r._bias;
		this->_weights = new float[this->_numWeights];
		for (int i = 0; i < r._numWeights; i++) {
			this->_weights[i] = r._weights[i];
		}
		return *this;
	}

	float RNG(float Min, float Max) {
		/* random # betweeen -1.0 to 1.0 */
		float random = 	static_cast <float> (rand() /
				static_cast <float> (RAND_MAX *
				((Max - Min) + Min)));
		return random;
	}

	float activate() {
		/* copy input to output and apply an activation to the (output)
		before returning. In this case the output is sigmoid */
		this->_output = this->_input;
		return 1.0 / (1 + pow(2.718281, -this->_input));
	}
	
	float transferDeriv(float input) {
		/* calculate the derivative of the activation function.
		In this case the activation function is sigmoid */
		return 1 / (1 + pow(2.718281, -input));
	}

	float getWeight(int index) {
		/* returns a weight from an array of connections */
		return this->_weights[index];
	}

	float & getInput() {
		/* gets input to neuron */
		return this->_input;
	}

	float & getOutput() {
		return this->_output;
	}

	void setDelta(float value) {
		this->_delta = value;
	}

	float & getDelta() {
		return this->_delta;
	}

	int getWeights() {
		return this->_numWeights;
	}

	float sumAllWeight() {
		float result = 0;

		for (int i = 0; i < this->_numWeights; i++) {
			result += this->_weights[i];
		} return result;
	}

	void setWeight(int w, float value) {
//		std::cout
//		<< "weights before == "
//		<< this->_weights[w]
//		<< std::endl;
		this->_weights[w] = value;
//		std::cout
//		<< "weights after == "
//		<< this->_weights[w]
//		<< std::endl;
	}

	void setInput(float const & value) {
		this->_input = value;
	}
};

#endif
