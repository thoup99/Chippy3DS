#include "3ds.h"

class KeypadRenderer {
private:
    C3D_RenderTarget* screen;
public:
    KeypadRenderer() {};
    KeypadRenderer(C3D_RenderTarget* s) {
		screen = s;
	};
};