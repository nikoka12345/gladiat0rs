void play_animation(int animation_index,char * animation_name,int play_once)
{
    if(strcmp(animations[animation_index].animation_name,animation_name) != 0)
    {
        animation_info * temp = head;
        
        while(strcmp(animation_name,temp->name) != 0 && temp!= NULL)
            temp = temp->next;
        
        if(temp!= NULL)
        {
            strcpy(animations[animation_index].animation_name,animation_name);
            animations[animation_index].start_time = SDL_GetTicks();
            animations[animation_index].last_frame = 0;
            animations[animation_index].done = false;
            animations[animation_index].number_of_frames = temp->number_of_frames;
            animations[animation_index].frame_rate = temp->frame_rate;
            animations[animation_index].starting_position = temp->starting_;
            animations[animation_index].x_off = temp->x_offset;
            animations[animation_index].y_off = temp->y_offset;
            
            //Change position with and height
            int position_index = entities[animations[animation_index].entity_id].position_index;
            positions[position_index].w = temp->starting_.w;
            positions[position_index].h = temp->starting_.h;
            
            animations[animation_index].play_once = play_once;
        }
    }
}

void play_sound(Mix_Chunk *sound)
{
    if(s.muted == false)
        Mix_PlayChannel( -1, sound, 0 );
}

void play_music(Mix_Music *music)
{
    if(s.muted == false)
        Mix_PlayMusic( music, -1 );
}

int add_text_entity(const char * text,int font_size,SDL_Color color,int x,int y,int fade,int fade_speed)
{
    TTF_Font* font = TTF_OpenFont("assets/BULKYPIX.TTF", font_size);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    SDL_Surface* text_surface = TTF_RenderText_Solid(font,text, color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    SDL_FreeSurface(text_surface);
    int w = 0, h=0;
    
    TTF_SizeText(font, text,&w, &h);
    
    
    int id = create_entity("text");
    add_position_component(id,x,y,w,h);
    add_sprite_component(id,text_texture,fade,fade_speed,SDL_FLIP_NONE);
    if(fade == true)
    {
        add_velocity_component(id,0,-1);
    }
    TTF_CloseFont( font );
    return id;
}

void change_text(int text_id,const char* new_text,int font_size,SDL_Color color)
{
    
    TTF_Font* font = TTF_OpenFont("assets/BULKYPIX.TTF", font_size);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    int w = 0, h=0;
    TTF_SizeText(font, new_text,&w, &h);
    
    int position_index = entities[text_id].position_index;
    int sprite_index = entities[text_id].sprite_index;
    
    positions[position_index].w = w;
    positions[position_index].h = h;
    
    SDL_Surface* text_surface = TTF_RenderText_Solid(font,new_text, color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    SDL_FreeSurface(text_surface);
    
    SDL_DestroyTexture(sprites[sprite_index].texture);
    sprites[sprite_index].texture = text_texture;
    TTF_CloseFont( font );
}
