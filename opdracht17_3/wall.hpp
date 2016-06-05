#ifndef WALL_HPP
#define WALL_HPP

#include "window.hpp"
#include "rectangle.hpp"

class wall : public rectangle{
private:
	bool filled;
	int update_count;
	vector start;
	vector end;

public:
	wall(window & w, const vector & location, const vector & end, vector bounce);
	void draw() override;
	void update();
};

#endif