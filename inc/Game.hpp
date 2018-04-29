/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 10:47:39 by scollet           #+#    #+#             */
/*   Updated: 2018/01/13 10:47:40 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

#include <ncurses.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include "Enemy.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "NN.hpp"


class Game {

public:
  Game(int y, int x);
  ~Game(void);
  Game(Game const& rhs);
  Game& operator=(Game const& rhs);

  bool isRunning(void);
  void keyCommand(int num);
  void terminate(int err);
  int getMaxY(void);
  int getMaxX(void);
  void setMap(int y, int x, char ch);
  char getMap(int y, int x);
  Enemy & getEnemy(int y, int x);
  void buildMaps(int sizey, int sizex);
  Player& getPlayer(void);

	NN *getNN() {return this->_nn;}

	int getNearestEnemy(int x, int y, int axis, int dir) {
		int i;
		int end;

		if (dir < 0) {
			end = 5;
		} else if (dir > 0) {
			if (axis == 'y') {
				end = getMaxY() - 5;
			} else if (axis == 'x') {
				end = getMaxX() - 5;
			}
		}

//		std::cout << "borken" << std::endl;
		if (axis == 'y') {
			for (i = y; i != end; i += dir) {
//				std::cout << y << " " << i << " " << end << std::endl;
				if (getMap(i, x) != ' ' || getMap(i, x) != '!' || getMap(i, x) != 'A' || getMap(i, x) != '\\' || getMap(i, x) != '/') {
//					std::cout << "not borken" << std::endl;
					return (i);
				}
			}
		} else if (axis == 'x') {
			for (i = x; i != end; i += dir) {
//				std::cout << x << " " << i << " " << end << std::endl;
				if (getMap(y, i) != ' ' || getMap(y, i) != '!' || getMap(y, i) != 'A' || getMap(y, i) != '\\' || getMap(y, i) != '/') {
//					std::cout << "not borken" << std::endl;
					return (i);
				}
			}
		}
	}

private:
  int     _maxX;
  int     _maxY;
  bool    _running;
  Player  *_player;
  char    **_map;
  Enemy   **_enemies;
	NN *_nn;
};

#endif
