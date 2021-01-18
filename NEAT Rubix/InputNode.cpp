#include "InputNode.h"


// face is capital letter

InputNode::InputNode() {}
InputNode::InputNode(char f, int r, int c)
{
	face = f;
	row = r;
	col = c;
}


double InputNode::getValue(Cube thisCube) {
	char val;
	if (face == 'F') {
		val = thisCube.Front[InputNode::row][InputNode::col];
	}
	if (face == 'B') {
		val = thisCube.Back[InputNode::row][InputNode::col];
	}
	if (face == 'L') {
		val = thisCube.Left[InputNode::row][InputNode::col];
	}
	if (face == 'R') {
		val = thisCube.Right[InputNode::row][InputNode::col];
	}
	if (face == 'U') {
		val = thisCube.Up[InputNode::row][InputNode::col];
	}
	if (face == 'D') {
		val = thisCube.Down[InputNode::row][InputNode::col];
	}
	return double(val);
}


InputNode::~InputNode()
{
}
