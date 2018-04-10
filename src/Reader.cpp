NN * reader(filename) {
	ifstream fileobj;
	NN * retNN;

	fileobj.open(filename, ios::in);
	fileobj.read((char*)&retNN, sizeof(retNN));
	return retNN;
}
