#ifndef VICTIM_HPP
#define VICTIM_HPP

#include "window.hpp"
#include "rectangle.hpp"

class victim : public rectangle{
private:
	vector start;
	vector end;
public:
	victim(window & w, const vector & start, const vector & end, vector bounce);
	void draw() override;
	void interact(drawable & other) override;
};
#endif