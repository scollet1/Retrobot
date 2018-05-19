#include <iostream>
#include <fstream>

void saveToFile(NN * nn) {
	ofstream fileo;

	fileo.open("savenn.txt", ios::app);
	for (int i = 0; i < nn->getLayers(); i++) {
		for (int j = 0; j < nn->getLayer(i).getNeurons(); j++) {
			for (int k = 0; k < nn->getLayer(i).getNeuron(j).getWeights(); k++) {
				fileo.write((float*)&nn->getLayer(i)->getNeuron(j).getWeight(k), sizeof(float));
			}
		}
	}
}
