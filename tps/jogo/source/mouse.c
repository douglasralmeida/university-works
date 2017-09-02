#include "funcoes.h"
#include "mouse.h"

void ConfigMouseCursor(ALLEGRO_MOUSE_CURSOR* Cursor)
{
	al_set_mouse_cursor(Application.Screen, Cursor);
}