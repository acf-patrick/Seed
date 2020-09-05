#include "header/map.h"
#include "header/app.h"

Tilemap::Tilemap(const std::string& file_name)
{
	/* setting up callback functions */
	tmx_img_load_func = _load;
	tmx_img_free_func = _free;

	m_map = tmx_load(file_name.c_str());
	if (!m_map)
	{
		std::cerr << tmx_strerr() << std::endl;
		exit (1);
	}
}

Tilemap::~Tilemap()
{
	tmx_map_free(m_map);
	m_map = nullptr;
}

void Tilemap::draw(SDL_Renderer * renderer, Camera * camera)
{
	
}

void Tilemap::drawLayers(tmx_layer * layer)
{
    while (layer != NULL)
    {
        switch (layer->type)
        {
        case L_GROUP:
            drawLayers(layer->content.group_head);
            break;
        case L_LAYER:
            drawTiles(layer->content.gids);
            break;
        case L_IMAGE:
			drawImage(layer);
            break;
		case L_OBJGR:
			drawObjects(layer->content.objgr);
        default:
            break;
        }
        layer = layer->next;
    }
}

void Tilemap::drawImage(tmx_layer * layer)
{
	SDL_Renderer* renderer = App::instance->getRenderer();
    SDL_Rect src = { 0 }, dest = { layer->offsetx, layer->offsety };
	SDL_Texture* texture = (SDL_Texture*)layer->content.image->resource_image;
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
	dest.w = src.w;
	dest.h = src.h;
	SDL_RenderCopy(renderer, texture, &src, &dest);
}

void Tilemap::drawTiles(uint32_t * gids)
{
	
}

void Tilemap::drawObjects(tmx_object_group * obj_group)
{
	
}