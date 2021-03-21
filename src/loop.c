void input()
{
    if(g.state == MAIN_MENU)
    {
        while( SDL_PollEvent( &s.e ) != 0 )
        {
            if(s.e.type == SDL_QUIT )
            {
                g.running = false;
            }
            if(s.e.type == SDL_KEYDOWN )
            {
                if(options == false)
                {
                    switch(s.e.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                        {
                            if(menu_cursor_position == 0)
                            {
                                seed_entities();
                                play_music(main_theme);
                                g.state = PLAY;
                            }
                            else if(menu_cursor_position == 1)
                            {
                                menu_cursor_position = 0;
                                options = true;
                            }
                            else if(menu_cursor_position == 2)
                            {
                                g.running = false;
                            }
                        }break;
                        
                        case SDLK_w:
                        case SDLK_UP:
                        {
                            menu_cursor_position--;
                            if(menu_cursor_position <0)
                                menu_cursor_position = 2;
                        }break;
                        
                        case SDLK_s:
                        case SDLK_DOWN:
                        {
                            menu_cursor_position++;
                            if(menu_cursor_position > 2)
                                menu_cursor_position = 0;
                        }break;
                    }
                }
                else
                {
                    switch(s.e.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                        {
                            if(options_cursor_position == 2)
                            {
                                options_cursor_position = 0;
                                options = false;
                            }
                        }break;
                        
                        case SDLK_a:
                        case SDLK_LEFT:
                        {
                            if(options_cursor_position == 0)
                            {
                                volume-=16;
                                if(volume <=0)
                                    volume = 0;
                                
                                Mix_VolumeMusic(volume);
                                Mix_VolumeChunk(shoot,volume);
                                Mix_VolumeChunk(hit,volume);
                            }
                            else if(options_cursor_position == 1)
                            {
                                if(fullscreen == true)
                                {
                                    fullscreen = false;
                                    SDL_SetWindowFullscreen(s.window,0);
                                    
                                }
                                else
                                {
                                    fullscreen = true;
                                    SDL_SetWindowFullscreen(s.window,SDL_WINDOW_FULLSCREEN_DESKTOP);
                                }
                            }
                        }break;
                        case SDLK_d:
                        case SDLK_RIGHT:
                        {
                            if(options_cursor_position == 0)
                            {
                                volume +=16;
                                if(volume >=max_volume)
                                    volume = max_volume;
                                
                                Mix_VolumeMusic(volume);
                                Mix_VolumeChunk(shoot,volume);
                                Mix_VolumeChunk(hit,volume);
                            }
                            else if(options_cursor_position == 1)
                            {
                                if(fullscreen == true)
                                {
                                    fullscreen = false;
                                    SDL_SetWindowFullscreen(s.window,0);
                                }
                                else
                                {
                                    fullscreen = true;
                                    SDL_SetWindowFullscreen(s.window,SDL_WINDOW_FULLSCREEN_DESKTOP);
                                }
                            }
                        }break;
                        
                        
                        case SDLK_w:
                        case SDLK_UP:
                        {
                            options_cursor_position--;
                            if(options_cursor_position <0)
                                options_cursor_position = 2;
                        }break;
                        
                        case SDLK_s:
                        case SDLK_DOWN:
                        {
                            options_cursor_position++;
                            if(options_cursor_position > 2)
                                options_cursor_position = 0;
                        }break;
                    }
                }
            }
        }
    }
    else if(g.state == PLAY)
    {
        while( SDL_PollEvent( &s.e ) != 0 )
        {
            if(s.e.type == SDL_QUIT )
            {
                g.running = false;
            }
            if(s.e.type == SDL_KEYDOWN && s.e.key.keysym.sym == SDLK_ESCAPE )
            {
                pressed_up = pressed_down = pressed_left = pressed_right = false;
                g.state = PAUSE_MENU;
                
                if(player_id != -1)
                {
                    int velocity_index = entities[player_id].velocity_index;
                    
                    velocities[velocity_index].dx = 0;
                    velocities[velocity_index].dy = 0;
                }
            }
            input_system();
        }
    }
    else if(g.state == PAUSE_MENU)
    {
        while( SDL_PollEvent( &s.e ) != 0 )
        {
            if(s.e.type == SDL_QUIT )
            {
                g.running = false;
            }
            if(s.e.type == SDL_KEYDOWN )
            {
                if(pause_options == false)
                {
                    switch(s.e.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                        {
                            if(pause_cursor_position == 0)
                            {
                                pause_cursor_position = 0;
                                pause_options_cursor_position = 0;
                                pause_options = false;
                                g.state = PLAY;
                            }
                            else if(pause_cursor_position == 1)
                            {
                                pause_cursor_position = 0;
                                pause_options = true;
                            }
                            else if(pause_cursor_position == 2)
                            {
                                pause_cursor_position = 0;
                                pause_options_cursor_position = 0;
                                pause_options = false;
                                g.state = MAIN_MENU;
                                play_music(main_menu_music);
                                reset_entities();
                            }
                        }break;
                        
                        case SDLK_w:
                        case SDLK_UP:
                        {
                            pause_cursor_position--;
                            if(pause_cursor_position <0)
                                pause_cursor_position = 2;
                        }break;
                        
                        case SDLK_s:
                        case SDLK_DOWN:
                        {
                            pause_cursor_position++;
                            if(pause_cursor_position > 2)
                                pause_cursor_position = 0;
                        }break;
                    }
                }
                else
                {
                    switch(s.e.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                        {
                            if(pause_options_cursor_position == 2)
                            {
                                options_cursor_position = 0;
                                pause_options = false;
                            }
                        }break;
                        
                        case SDLK_a:
                        case SDLK_LEFT:
                        {
                            if(pause_options_cursor_position == 0)
                            {
                                volume-=16;
                                if(volume <=0)
                                    volume = 0;
                                
                                Mix_VolumeMusic(volume);
                                Mix_VolumeChunk(shoot,volume);
                                Mix_VolumeChunk(hit,volume);
                            }
                            else if(pause_options_cursor_position == 1)
                            {
                                if(fullscreen == true)
                                {
                                    fullscreen = false;
                                    SDL_SetWindowFullscreen(s.window,0);
                                    
                                }
                                else
                                {
                                    fullscreen = true;
                                    SDL_SetWindowFullscreen(s.window,SDL_WINDOW_FULLSCREEN_DESKTOP);
                                }
                            }
                        }break;
                        case SDLK_d:
                        case SDLK_RIGHT:
                        {
                            if(pause_options_cursor_position == 0)
                            {
                                volume +=16;
                                if(volume >=max_volume)
                                    volume = max_volume;
                                
                                Mix_VolumeMusic(volume);
                                Mix_VolumeChunk(shoot,volume);
                                Mix_VolumeChunk(hit,volume);
                            }
                            else if(pause_options_cursor_position == 1)
                            {
                                if(fullscreen == true)
                                {
                                    fullscreen = false;
                                    SDL_SetWindowFullscreen(s.window,0);
                                }
                                else
                                {
                                    fullscreen = true;
                                    SDL_SetWindowFullscreen(s.window,SDL_WINDOW_FULLSCREEN_DESKTOP);
                                }
                            }
                        }break;
                        
                        
                        case SDLK_w:
                        case SDLK_UP:
                        {
                            pause_options_cursor_position--;
                            if(pause_options_cursor_position <0)
                                pause_options_cursor_position = 2;
                        }break;
                        
                        case SDLK_s:
                        case SDLK_DOWN:
                        {
                            pause_options_cursor_position++;
                            if(pause_options_cursor_position > 2)
                                pause_options_cursor_position = 0;
                        }break;
                    }
                }
                
                if(s.e.key.keysym.sym == SDLK_ESCAPE)
                {
                    pause_cursor_position = 0;
                    pause_options_cursor_position = 0;
                    pause_options = false;
                    g.state = PLAY;
                }
            }
        }
    }
    else if(g.state == DEAD)
    {
        
        while( SDL_PollEvent( &s.e ) != 0 )
        {
            if(s.e.type == SDL_QUIT )
            {
                g.running = false;
            }
            if(s.e.type == SDL_KEYDOWN)
            {
                switch(s.e.key.keysym.sym)
                {
                    case SDLK_RETURN:
                    {
                        if(dead_cursor_position == 0)
                        {
                            dead_cursor_position = 0;
                            reset_entities();
                            seed_entities();
                            g.state = PLAY;
                            play_music(main_theme);
                        }
                        else if(dead_cursor_position == 1)
                        {
                            dead_cursor_position = 0;
                            reset_entities();
                            g.state = MAIN_MENU;
                            play_music(main_menu_music);
                        }
                        else if(dead_cursor_position == 2)
                        {
                            g.running = false;
                        }
                    }break;
                    
                    case SDLK_w:
                    case SDLK_UP:
                    {
                        dead_cursor_position--;
                        if(dead_cursor_position <0)
                            dead_cursor_position = 2;
                    }break;
                    
                    case SDLK_s:
                    case SDLK_DOWN:
                    {
                        dead_cursor_position++;
                        if(dead_cursor_position > 2)
                            dead_cursor_position = 0;
                    }break;
                }
            }
        }
    }
}

void update()
{
    
    if(g.state == MAIN_MENU)
    {
        if(options == false)
        {
            if(menu_cursor_position == 0)
            {
                cursor_rect.x = play_rect.x - 25;
                cursor_rect.y = play_rect.y;
            }
            else if(menu_cursor_position == 1)
            {
                cursor_rect.x = options_rect.x - 25;
                cursor_rect.y = options_rect.y;
            }
            else if(menu_cursor_position == 2)
            {
                cursor_rect.x = exit_rect.x - 25;
                cursor_rect.y = exit_rect.y;
            }
        }
        else if(options == true)
        {
            if(options_cursor_position == 0)
            {
                cursor_rect.x = volume_rect.x - 25;
                cursor_rect.y = volume_rect.y;
            }
            else if(options_cursor_position == 1)
            {
                cursor_rect.x = fullscreen_rect.x - 25;
                cursor_rect.y = fullscreen_rect.y;
            }
            else if(options_cursor_position == 2)
            {
                cursor_rect.x = back_rect.x - 25;
                cursor_rect.y = back_rect.y;
            }
        }
    }
    else if(g.state == PLAY)
    {
        
        ai_system();
        movemant_system();
        shake();
        
        if(dead_timer !=-1 && (SDL_GetTicks() - dead_timer > 1000))
        {
            add_scores();
            g.state = DEAD;
            play_music(death_theme);
        }
        //update camera
        if(player_id != -1)
        {
            
            int position_index = entities[player_id].position_index;
            g.camera.x = positions[position_index].x - 320;
            g.camera.y = positions[position_index].y - 240;
            
            if (g.camera.x <= 0) g.camera.x = 0;
            if (g.camera.x + g.camera.w >= 960) g.camera.x = 960 - g.camera.w;
            if (g.camera.y <= 0) g.camera.y = 0;
            if (g.camera.y + g.camera.h >= 736) g.camera.y = 736 - g.camera.h;
            
        }
        //Spawn enemies
        if(enemies_alive == 0)
        {
            spawn(); //In helper.c
        }
    }
    else if(g.state == PAUSE_MENU)
    {
        if(pause_options == false)
        {
            if(pause_cursor_position == 0)
            {
                cursor_rect.x = resume_rect.x - 25;
                cursor_rect.y = resume_rect.y;
            }
            else if(pause_cursor_position == 1)
            {
                cursor_rect.x = pause_options_rect.x - 25;
                cursor_rect.y = pause_options_rect.y;
            }
            else if(pause_cursor_position == 2)
            {
                cursor_rect.x = main_menu_rect.x - 25;
                cursor_rect.y = main_menu_rect.y;
            }
        }
        else if(pause_options == true)
        {
            if(pause_options_cursor_position == 0)
            {
                cursor_rect.x = volume_rect.x - 25;
                cursor_rect.y = volume_rect.y;
            }
            else if(pause_options_cursor_position == 1)
            {
                cursor_rect.x = fullscreen_rect.x - 25;
                cursor_rect.y = fullscreen_rect.y;
            }
            else if(pause_options_cursor_position == 2)
            {
                cursor_rect.x = back_rect.x - 25;
                cursor_rect.y = back_rect.y;
            }
        }
    }
    else if(g.state == DEAD)
    {
        if(dead_cursor_position == 0)
        {
            cursor_rect.x = retry_rect.x - 25;
            cursor_rect.y = retry_rect.y;
        }
        else if(dead_cursor_position == 1)
        {
            cursor_rect.x = dead_main_menu_rect.x - 25;
            cursor_rect.y = dead_main_menu_rect.y;
        }
        else if(dead_cursor_position == 2)
        {
            cursor_rect.x = dead_exit_rect.x - 25;
            cursor_rect.y = dead_exit_rect.y;
        }
    }
    
}

void render()
{
    
    if(g.state == MAIN_MENU)
    {
        //Change target to texture and clear renderer
        SDL_SetRenderTarget(s.renderer, s.m_texture);
        SDL_SetRenderDrawColor(s.renderer,0,0,0, 255);
        SDL_RenderClear(s.renderer);
        
        
        if(options == false)
        {
            SDL_RenderCopy(s.renderer,play_texture,NULL,&play_rect);
            SDL_RenderCopy(s.renderer,options_texture,NULL,&options_rect);
            SDL_RenderCopy(s.renderer,exit_texture,NULL,&exit_rect);
            SDL_RenderCopy(s.renderer,cursor_texture,NULL,&cursor_rect);
        }
        else
        {
            SDL_RenderCopy(s.renderer,volume_texture,NULL,&volume_rect);
            SDL_RenderCopy(s.renderer,fullscreen_texture,NULL,&fullscreen_rect);
            if(fullscreen == true)
                SDL_RenderCopy(s.renderer,on_texture,NULL,&on_rect);
            else if(fullscreen == false)
                SDL_RenderCopy(s.renderer,off_texture,NULL,&off_rect);
            
            SDL_RenderCopy(s.renderer,back_texture,NULL,&back_rect);
            SDL_RenderCopy(s.renderer,cursor_texture,NULL,&cursor_rect);
            
            float width = 100 * volume / max_volume;
            SDL_Rect _rect = {volume_rect.x + volume_rect.w + 10, volume_rect.y, (int)width, volume_rect.h};
            
            SDL_SetRenderDrawColor(s.renderer,255,255,255, 255);
            SDL_RenderFillRect(s.renderer,&_rect);
        }
        
        
        //Return target to window and clear screen
        SDL_SetRenderTarget(s.renderer, NULL);
        SDL_SetRenderDrawColor(s.renderer,0,0,0, 255);
        SDL_RenderClear(s.renderer);
        //Render m_texture
        SDL_RenderCopy(s.renderer, s.m_texture, NULL, &s.m_rect);
        
        //Present rendered content
        SDL_RenderPresent(s.renderer);
    }
    else if(g.state == PLAY)
    {
        //Change target to texture and clear renderer
        SDL_SetRenderTarget(s.renderer, s.m_texture);
        SDL_SetRenderDrawColor(s.renderer,0,0,0, 255);
        SDL_RenderClear(s.renderer);
        
        //!--Render arena--!//
        SDL_Rect arena_ = {0-g.camera.x,0-g.camera.y,960,736};
        
        SDL_RenderCopy(s.renderer,bigger_arena_texture,NULL,&arena_);
        
        rendering_system();
        
        //Render level info
        //Next lvl
        if(xp >= xp_required)
        {
            while(xp >= xp_required)
            {
                level++;
                xp = xp - xp_required;
                xp_required = xp_required + xp_required * 0.1;
            }
            change_level_text();
        }
        
        SDL_Rect level_rect = {570,26,50,16};
        SDL_Rect level_rect_1 = {572,28,0,12};
        if(player_id != -1)
        {
            float lvl_ln = 48 * xp / xp_required;
            if(lvl_ln == 0){ lvl_ln = 1; }
            
            level_rect_1.w = (int)lvl_ln;
        }
        SDL_SetRenderDrawColor(s.renderer,0,0,0,255);
        SDL_RenderFillRect(s.renderer,&level_rect);
        SDL_SetRenderDrawColor(s.renderer,255,255,255,255);
        SDL_RenderFillRect(s.renderer,&level_rect_1);
        
        
        
        //Return target to window and clear screen
        SDL_SetRenderTarget(s.renderer, NULL);
        SDL_SetRenderDrawColor(s.renderer,0,0,0, 255);
        SDL_RenderClear(s.renderer);
        //Render m_texture
        SDL_RenderCopy(s.renderer, s.m_texture, NULL, &s.m_rect);
        
        //Present rendered content
        SDL_RenderPresent(s.renderer);
    }
    else if(g.state == PAUSE_MENU)
    {
        //Change target to texture and clear renderer
        SDL_SetRenderTarget(s.renderer, s.m_texture);
        SDL_SetRenderDrawColor(s.renderer,0,0,0, 255);
        SDL_RenderClear(s.renderer);
        
        
        if(pause_options == false)
        {
            SDL_RenderCopy(s.renderer,resume_texture,NULL,&resume_rect);
            SDL_RenderCopy(s.renderer,options_texture,NULL,&pause_options_rect);
            SDL_RenderCopy(s.renderer,main_menu_texture,NULL,&main_menu_rect);
            SDL_RenderCopy(s.renderer,cursor_texture,NULL,&cursor_rect);
        }
        else
        {
            SDL_RenderCopy(s.renderer,volume_texture,NULL,&volume_rect);
            SDL_RenderCopy(s.renderer,fullscreen_texture,NULL,&fullscreen_rect);
            if(fullscreen == true)
                SDL_RenderCopy(s.renderer,on_texture,NULL,&on_rect);
            else if(fullscreen == false)
                SDL_RenderCopy(s.renderer,off_texture,NULL,&off_rect);
            
            SDL_RenderCopy(s.renderer,back_texture,NULL,&back_rect);
            SDL_RenderCopy(s.renderer,cursor_texture,NULL,&cursor_rect);
            
            float width = 100 * volume / max_volume;
            SDL_Rect _rect = {volume_rect.x + volume_rect.w + 10, volume_rect.y, (int)width, volume_rect.h};
            
            SDL_SetRenderDrawColor(s.renderer,255,255,255, 255);
            SDL_RenderFillRect(s.renderer,&_rect);
        }
        
        //Return target to window and clear screen
        SDL_SetRenderTarget(s.renderer, NULL);
        SDL_SetRenderDrawColor(s.renderer,0,0,0, 255);
        SDL_RenderClear(s.renderer);
        //Render m_texture
        SDL_RenderCopy(s.renderer, s.m_texture, NULL, &s.m_rect);
        
        //Present rendered content
        SDL_RenderPresent(s.renderer);
    }
    else if(g.state == DEAD)
    {
        //Change target to texture and clear renderer
        SDL_SetRenderTarget(s.renderer, s.m_texture);
        SDL_SetRenderDrawColor(s.renderer,0,0,0, 255);
        SDL_RenderClear(s.renderer);
        
        //!--Render arena--!//
        SDL_Rect arena_ = {0,0,640,480};
        SDL_RenderCopy(s.renderer,arena_texture,NULL,&arena_);
        
        //!-- RENDER CONTENT OF DEAD SCREEN --!//
        SDL_RenderCopy(s.renderer,retry_texture,NULL,&retry_rect);
        SDL_RenderCopy(s.renderer,main_menu_texture,NULL,&dead_main_menu_rect);
        SDL_RenderCopy(s.renderer,exit_texture,NULL,&dead_exit_rect);
        SDL_RenderCopy(s.renderer,cursor_texture,NULL,&cursor_rect);
        
        
        //Swordsman
        SDL_Rect rect = {200,140,32,32};
        rect.w = swordsman_figure.w;
        rect.h = swordsman_figure.h;
        SDL_RenderCopy(s.renderer,swordsman_texture,&swordsman_figure,&rect);
        
        //Christian
        rect.x += 55;
        rect.w = christian_figure.w;
        rect.h = christian_figure.h;
        SDL_RenderCopy(s.renderer,christian_texture,&christian_figure,&rect);
        
        //Axe man
        rect.x += 55;
        rect.w = axe_man_figure.w;
        rect.h = axe_man_figure.h;
        SDL_RenderCopy(s.renderer,axe_man_texture,&axe_man_figure,&rect);
        
        //Biggie
        rect.x += 55;
        rect.w = biggie_figure.w;
        rect.h = biggie_figure.h;
        SDL_RenderCopy(s.renderer,biggie_texture,&biggie_figure,&rect);
        
        //Miniboss
        rect.x += 55;
        rect.w = miniboss_figure.w;
        rect.h = miniboss_figure.h;
        SDL_RenderCopy(s.renderer,miniboss_texture,&miniboss_figure,&rect);
        
        
        //Scores
        SDL_RenderCopy(s.renderer,swordsman_score,NULL,&s_score);
        SDL_RenderCopy(s.renderer,christian_score,NULL,&c_score);
        SDL_RenderCopy(s.renderer,axe_man_score,NULL,&a_score);
        SDL_RenderCopy(s.renderer,biggie_score,NULL,&b_score);
        SDL_RenderCopy(s.renderer,miniboss_score,NULL,&m_score);
        SDL_RenderCopy(s.renderer,level_score,NULL,&level_rect);
        
        
        //Return target to window and clear screen
        SDL_SetRenderTarget(s.renderer, NULL);
        SDL_SetRenderDrawColor(s.renderer,0,0,0, 255);
        SDL_RenderClear(s.renderer);
        //Render m_texture
        SDL_RenderCopy(s.renderer, s.m_texture, NULL, &s.m_rect);
        
        //Present rendered content
        SDL_RenderPresent(s.renderer);
    }
    
}