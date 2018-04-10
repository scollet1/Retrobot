# include <iostream>
# include <fstream>

void writer(const char * filename, NN * obj) {
	ofstream fileobj;

	fileobj.open(filename, ios::app);
	fileobj.write((char*)& obj, sizeof(obj));
}
