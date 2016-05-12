#ifndef WALL_HPP
#define WALL_HPP

#include "window.hpp"
#include "rectangle.hpp"
#include "vector.hpp"
#include "line.hpp"

class wall : public rectangle{
private:
	bool filled;
	int update_interval;
	int update_count;

public:
	wall(window w, vector location, vector end, int update_interval);
	void draw() override;
	void update();
}

#endif