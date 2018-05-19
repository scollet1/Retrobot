#include <iostream>
#include <fstream>

NN * readFromFile(char * file, NN * nn) {
	ifstream fileo;

	fileo.open(file, ios::in);
	float obj;

	for (int i = 0; i < nn->getLayers(); i++) {
		for (int j = 0; j < nn->getLayer(i)->getNeurons(); j++) {
			for (int k = 0; k < nn->getLayer(i).getNeuron(j).getWeights(); k++) {
				nn->getLayer(i)->getNeuron(j).setWeight(k, fileo.read(float*)&obj, sizeof(obj));
			}
		}	
	}
}
