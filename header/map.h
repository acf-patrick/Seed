#ifndef MAP_H
#define MAP_H

#include <tmx/tmx.h>
#include "drawable.h"

class TileMap : public Drawable
{
public:
	TileMap();
	~TileMap();

protected:
	
	
private:
	tmx_map * m_map;
};

#endif // MAP_H

