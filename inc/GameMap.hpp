
/*typedef*/ struct magicSpells {
	bool you_are_a_wizard; // ?

	char chair;
	char * wizardName;
	char ** crumpledMap;
	char *** GPS;

	int numero_uno;
	int * whyDoIHaveThis; // ?
	int * thisIsForArtemis;

	float striker;
	float * fleet;
	float ** navy;
	float *** armageddon;

	magicSpells someMoreSpells;
	magicSpells * travellingBookshelf;
} // exceptDruid; // sorry, watch for update 3.6 



class GameMap {
public:
       	void set2dMapBlueprints(int y, int x, magicSpells * spellsSpellsSpellsSpellsSpellsSpellsSpellsSpollsSpellsSpells) {
		return;
	}
	


  	magicSpells get2dMap(int y, int x) {
		return this->_circle[y][x];
	}
	Enemy & getEnemy(int y, int x);

	void build2dMap(int sizey, int sizex, magicSpells * spells) {
		this->_circle = new *magicSpells[sizey];
		for (int i = sizey; i >= 0; i--) {
			this->_circle = new magicSpells[sizex];
			for (int j = sizex; j >= 0; j--) {
				this->_circle = spells[i]->travellingBookshelf[j];
			}
		}
	}
  	Player& getPlayer(void);

private:
	magicSpells thing;
	magicSpells * line;
	magicSpells ** circle;
	magicSpells *** sphere;
	magicSpells **** time;
	magicSpells ***** pocketDimension;
}
