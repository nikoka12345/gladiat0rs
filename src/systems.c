//!---INPUT---!//
static
void input_system()
{
    int player_position_id = entities[player_id].position_index;
    int player_collision_id = entities[player_id].collision_index;
    int player_animation_index = entities[player_id].animation_index;
    int player_stat_index = entities[player_id].stat_index;
    if(s.e.type == SDL_KEYDOWN && s.e.key.repeat == 0 && player_id != -1)
    {
        switch( s.e.key.keysym.sym )
        {
            case SDLK_w:
            {
                pressed_up = true;
                velocities[entities[player_id].velocity_index].dy -= stats[player_stat_index].speed;
            }break;
            case SDLK_s:
            {
                pressed_down = true;
                velocities[entities[player_id].velocity_index].dy += stats[player_stat_index].speed;
            }break;
            case SDLK_a:
            {
                pressed_left = true;
                velocities[entities[player_id].velocity_index].dx -= stats[player_stat_index].speed;
            }break;
            case SDLK_d:
            {
                pressed_right = true;
                velocities[entities[player_id].velocity_index].dx += stats[player_stat_index].speed;
                
            }break;
            case SDLK_m:
            {
                if(s.muted == false)
                {
                    s.muted = true;
                    Mix_PauseMusic();
                }
                else if(s.muted == true)
                {
                    s.muted = false;
                    Mix_ResumeMusic();
                }
            }break;
            
            case SDLK_UP:
            {
                if(player_shoot == false)
                {
                    player_shoot = true;
                    shoot_direction = UP;
                    
                    play_animation(player_animation_index,"player_attack_up",true);
                }
            }break;
            
            case SDLK_DOWN:
            {
                
                if(player_shoot == false)
                {
                    player_shoot = true;
                    shoot_direction = DOWN;
                    
                    play_animation(player_animation_index,"player_attack_down",true);
                }
            }break;
            
            case SDLK_LEFT:
            {
                
                if(player_shoot == false)
                {
                    player_shoot = true;
                    shoot_direction = LEFT;
                    
                    play_animation(player_animation_index,"player_attack_left",true);
                }
            }break;
            case SDLK_RIGHT:
            {
                
                if(player_shoot == false)
                {
                    player_shoot = true;
                    shoot_direction = RIGHT;
                    play_animation(player_animation_index,"player_attack_right",true);
                }
            }break;
            
            
            case SDLK_1:
            {enemy_to_spawn = 1;}break;
            case SDLK_2:
            {enemy_to_spawn = 2;}break;
            case SDLK_3:
            {enemy_to_spawn = 3;}break;
            case SDLK_4:
            {enemy_to_spawn = 4;}break;
            case SDLK_5:
            {enemy_to_spawn = 5;}break;
            
            case SDLK_8:
            {to_run = 1;}break;
            case SDLK_9:
            {to_run = 2;}break;
            
        }
    }
    else if(s.e.type == SDL_KEYUP && s.e.key.repeat == 0 && player_id != -1)
    {
        switch( s.e.key.keysym.sym )
        {
            case SDLK_w:
            {
                if(pressed_up == true)
                {
                    velocities[entities[player_id].velocity_index].dy += stats[player_stat_index].speed;
                    pressed_up = false;
                }
            }break;
            case SDLK_s:
            {
                
                if(pressed_down == true)
                {
                    velocities[entities[player_id].velocity_index].dy -= stats[player_stat_index].speed;
                    pressed_down = false;
                }
            }break;
            case SDLK_a:
            {
                if(pressed_left == true)
                {
                    velocities[entities[player_id].velocity_index].dx += stats[player_stat_index].speed;
                    pressed_left = false;
                }
            }break;
            case SDLK_d:
            {
                if(pressed_right == true)
                {
                    velocities[entities[player_id].velocity_index].dx -= stats[player_stat_index].speed;
                    pressed_right = false;
                }
            }break;
        }
    }
    /*else if(s.e.type == SDL_MOUSEBUTTONDOWN )
    {
        if(s.e.button.button == SDL_BUTTON_LEFT)
        {
            int x, y;
            SDL_GetMouseState( &x, &y );
            x = (x-320) /2;
            y = y/2;
            
            
            if(enemy_to_spawn == 1)
            {
                int enemy_id = create_entity("swordsman");
                add_position_component(enemy_id,x,y,35,35);
                add_velocity_component(enemy_id,0,0);
                add_collision_component(enemy_id,x,y,20,29,true,"enemy");
                add_ai_component(enemy_id,true,to_run);
                add_animation_component(enemy_id,"swordsman_idle",swordsman_texture,SDL_FLIP_NONE,false);
                add_stat_component(enemy_id,5,3,2,450,70);
                add_shake(SMALL);
            }
            else if(enemy_to_spawn == 2)
            {
                int enemy_id = create_entity("biggie");
                add_position_component(enemy_id,x,y,45,45);
                add_velocity_component(enemy_id,0,0);
                add_collision_component(enemy_id,x,y,29,39,true,"enemy");
                add_ai_component(enemy_id,false,1);
                add_animation_component(enemy_id,"biggie_idle",biggie_texture,SDL_FLIP_NONE,false);
                add_stat_component(enemy_id,10,2,4,500,60);
                add_shake(MEDIUM);
            }
            else if(enemy_to_spawn == 3)
            {
                int enemy_id = create_entity("christian");
                add_position_component(enemy_id,x,y,35,35);
                add_velocity_component(enemy_id,0,0);
                add_collision_component(enemy_id,x,y,15,31,true,"enemy");
                add_ai_component(enemy_id,true,to_run);
                add_animation_component(enemy_id,"christian_idle",christian_texture,SDL_FLIP_NONE,false);
                add_stat_component(enemy_id,3,4,1,390,80);
                add_shake(SMALL);
            }
            else if(enemy_to_spawn == 4)
            {
                int enemy_id = create_entity("axe_man");
                add_position_component(enemy_id,x,y,40,40);
                add_velocity_component(enemy_id,0,0);
                add_collision_component(enemy_id,x,y,26,30,true,"enemy");
                add_ai_component(enemy_id,false,1);
                add_animation_component(enemy_id,"axe_man_idle",axe_man_texture,SDL_FLIP_NONE,false);
                add_stat_component(enemy_id,7,3,2,450,70);
                add_shake(SMALL);
            }
            else if(enemy_to_spawn == 5)
            {
                int enemy_id = create_entity("miniboss");
                add_position_component(enemy_id,x,y,32,32);
                add_velocity_component(enemy_id,0,0);
                add_collision_component(enemy_id,x,y,22,32,true,"enemy");
                add_ai_component(enemy_id,false,3);
                add_animation_component(enemy_id,"miniboss_idle",miniboss_texture,SDL_FLIP_NONE,false);
                add_stat_component(enemy_id,15,4,5,450,80);
                add_shake(MEDIUM);
            }
        }
    }*/
}


//!---MOVEMANT---!//
static
void collision(int entity_id_,char* vel)
{
    int dx = 0,dy = 0;
    SDL_Rect rect;
    rect.x = collisions[entities[entity_id_].collision_index].x;
    rect.y = collisions[entities[entity_id_].collision_index].y;
    rect.w = collisions[entities[entity_id_].collision_index].w;
    rect.h = collisions[entities[entity_id_].collision_index].h;
    
    if(strcmp(vel,"dx") == 0)
        dx = velocities[entities[entity_id_].velocity_index].dx;
    if(strcmp(vel,"dy") == 0)
        dy = velocities[entities[entity_id_].velocity_index].dy;
    
    if(strcmp(vel,"dx") == 0 && dx == 0)
        return;
    if(strcmp(vel,"dy") == 0 && dy == 0)
        return;
    
    for(int i=0;i<MAX_COLLISION_COMPONENTS;i++)
    {
        if(collisions[i].entity_id == -1)
            break;
        
        if(collisions[i].destroyed == false && collisions[i].entity_id != entity_id_ && collisions[entities[entity_id_].collision_index].destroyed == false && entities[entity_id_].collision_index != -1)
        {
            SDL_Rect rect_a = {collisions[i].x,collisions[i].y,collisions[i].w,collisions[i].h};
            
            if(checkCollision(rect_a,rect) == true)
            {
                ///!---CASES---!///
                /*player collisions*/
                if(strcmp(collisions[entities[entity_id_].collision_index].type,"player") == 0 && strcmp(collisions[i].type,"wall") == 0)
                {
                    //Move player out of wall
                    collide_with_wall(entity_id_,i,vel);
                }
                /* bullets collisions */
                else if(strcmp(collisions[entities[entity_id_].collision_index].type,"bullet") == 0 && strcmp(collisions[i].type,"wall") == 0)
                {
                    destroy_component(entity_id_);
                    play_sound(hit);
                }
                else if(strcmp(collisions[entities[entity_id_].collision_index].type,"bullet") == 0 && strcmp(collisions[i].type,"enemy") == 0)
                {
                    
                    int enemy_ai_index = entities[collisions[i].entity_id].ai_index;
                    int enemy_stat_index = entities[collisions[i].entity_id].stat_index;
                    int enemy_position_index = entities[collisions[i].entity_id].position_index;
                    int arrow_stat_index = entities[entity_id_].stat_index;
                    int bullet_velocity_index = entities[entity_id_].velocity_index ;
                    
                    
                    stats[enemy_stat_index].hp -= stats[arrow_stat_index].dmg;
                    
                    //Draw text
                    SDL_Color color = {139,0,0};
                    int neg_dmg = -stats[arrow_stat_index].dmg;
                    char dmg[5];
                    
                    // convert 123 to string [buf]
                    sprintf(dmg,"%d",neg_dmg);
                    
                    add_text_entity(dmg,11,color,positions[enemy_position_index].x,positions[enemy_position_index].y + 5,true,6);
                    
                    if(stats[enemy_stat_index].hp > 0 && ai[enemy_ai_index].knock_back == true)
                    {
                        ai[enemy_ai_index].hit_time = SDL_GetTicks();
                        velocities[entities[ai[enemy_ai_index].entity_id].velocity_index].dx =  velocities[bullet_velocity_index].dx;
                        
                        velocities[entities[ai[enemy_ai_index].entity_id].velocity_index].dy =  velocities[bullet_velocity_index].dy;
                    }
                    else if(stats[enemy_stat_index].hp <= 0)
                    {
                        
                        if(strcmp(entities[collisions[i].entity_id].type,"swordsman") == 0)
                        {
                            swordsman_killed ++;
                            xp+= 34;
                        }
                        if(strcmp(entities[collisions[i].entity_id].type,"biggie") == 0)
                        {
                            biggie_killed++;
                            xp+= 70;
                        }
                        if(strcmp(entities[collisions[i].entity_id].type,"christian") == 0)
                        {
                            christian_killed++;
                            xp+= 15;
                        }
                        if(strcmp(entities[collisions[i].entity_id].type,"axe_man") == 0)
                        {
                            axe_man_killed ++;
                            xp+= 57;
                        }
                        if(strcmp(entities[collisions[i].entity_id].type,"miniboss") == 0)
                        {
                            miniboss_killed ++;
                            xp+= 130;
                        }
                        
                        
                        destroy_component(collisions[i].entity_id);
                        add_shake(SMALL);
                        
                        killed++;
                        enemies_alive--;
                        if(max_lvl == false && killed >= current_goal)
                        {
                            powerup();
                        }
                        else if(max_lvl == false)
                        {
                            SDL_Color color = {255,255,255};
                            char new_text[100] = "Powerup: ";
                            char killed_char[5];
                            char goal_char[5];
                            sprintf(killed_char,"%d",killed);
                            sprintf(goal_char,"%d",current_goal);
                            strcat(new_text,killed_char);
                            strcat(new_text,"/");
                            strcat(new_text,goal_char);
                            
                            change_text(goal_text,new_text,9,color);
                        }
                        //Healing chance
                        int heal = rand() % 100 + 1;
                        if(heal >= 96)
                        {
                            int healing = rand() % 2 + 1;
                            if(player_id != -1)
                            {
                                stats[entities[player_id].stat_index].hp += healing;
                                if(stats[entities[player_id].stat_index].hp > stats[entities[player_id].stat_index].max_hp)
                                    stats[entities[player_id].stat_index].hp = stats[entities[player_id].stat_index].max_hp;
                                
                                change_hp_text();
                            }
                        }
                        
                    }
                    
                    play_sound(hit);
                    destroy_component(entity_id_);
                    
                }
                /*enemy collisions*/
                else if(strcmp(collisions[entities[entity_id_].collision_index].type,"enemy") == 0 && strcmp(collisions[i].type,"wall") == 0)
                {
                    collide_with_wall(entity_id_,i,vel);
                    
                    if(ai[entities[entity_id_].ai_index].ai_type == 2 || ai[entities[entity_id_].ai_index].ai_type == 3)
                    {
                        if(strcmp(vel,"dx") == 0)
                        {
                            velocities[entities[entity_id_].velocity_index].dx = -velocities[entities[entity_id_].velocity_index].dx;
                        }
                        else if(strcmp(vel,"dy") == 0)
                        {
                            velocities[entities[entity_id_].velocity_index].dy = -velocities[entities[entity_id_].velocity_index].dy;
                        }
                    }
                    
                    
                }
                else if(strcmp(collisions[entities[entity_id_].collision_index].type,"enemy") == 0 && strcmp(collisions[i].type,"player") == 0)
                {
                    
                    
                    int enemy_stat_index = entities[entity_id_].stat_index;
                    int player_stat_index= entities[collisions[i].entity_id].stat_index;
                    int player_position_index =  entities[collisions[i].entity_id].position_index;
                    
                    if(stats[enemy_stat_index].can_dmg == true)
                    {
                        
                        
                        stats[player_stat_index].hp -= stats[enemy_stat_index].dmg;
                        
                        int neg_dmg = -stats[enemy_stat_index].dmg;
                        char dmg[5];
                        
                        // convert 123 to string [buf]
                        sprintf(dmg,"%d",neg_dmg);
                        
                        //Draw text
                        SDL_Color color = {139,0,0};
                        add_text_entity(dmg,11,color,positions[player_position_index].x,positions[player_position_index].y + 7,true,6);
                        stats[enemy_stat_index].can_dmg = false;
                        add_shake(SMALL);
                        
                        //Change hp text
                        change_hp_text();
                        
                        //Destroy player if no hp
                        if(player_id != -1 && stats[player_stat_index].hp <=0)
                        {
                            destroy_component(collisions[i].entity_id);
                            player_id = -1;
                            dead_timer = SDL_GetTicks();
                        }
                    }
                }
                
                /*else if(strcmp(collisions[entities[entity_id_].collision_index].type,"enemy") == 0 && strcmp(collisions[i].type,"enemy") == 0)
                {
                    collide_with_wall(entity_id_,i,vel);
                }*/
            }
        }
    }
}

static
void movemant_system()
{
    for(int i=0;i<MAX_VELOCITY_COMPONENTS;i++)
    {
        if(velocities[i].entity_id == -1)
            break;
        
        int entity_id = velocities[i].entity_id;
        if(velocities[i].destroyed == false)
        {
            float dx = velocities[i].dx;
            float dy = velocities[i].dy;
            
            //Normalize movemant
            if(velocities[i].entity_id == player_id)
            {
                float sq = sqrt(dx*dx + dy*dy);
                if(sq != 0)
                {
                    dx = dx/sq*5;
                    dy = dy/sq*5;
                }
            }
            
            //if player is shooting slow down
            if(velocities[i].entity_id == player_id && player_shoot == true)
                dx /=2;
            
            positions[entities[entity_id].position_index].x += dx;
            
            //Move x
            if(entities[entity_id].collision_index != -1 && collisions[entities[entity_id].collision_index].destroyed == false)
            {
                collisions[entities[entity_id].collision_index].x = positions[entities[entity_id].position_index].x;
                collision(entity_id,"dx");
            }
            
            if(velocities[i].destroyed == false)
            {
                //Move y
                //if player is shooting slow down
                if(velocities[i].entity_id == player_id && player_shoot == true)
                    dy /=2;
                
                
                positions[entities[entity_id].position_index].y += dy;
                if(entities[entity_id].collision_index != -1 &&   collisions[entities[entity_id].collision_index].destroyed == false)
                {
                    collisions[entities[entity_id].collision_index].y =positions[entities[entity_id].position_index].y;
                    
                    collision(entity_id,"dy");
                }
            }
            
        }
        
        
        //Check for animation change
        if(entities[entity_id].animation_index != -1 && animations[entities[entity_id].animation_index].destroyed == false)
        {
            int animation_index = entities[entity_id].animation_index;
            int velocity_index = entities[entity_id].velocity_index;
            //Player animations
            if(strcmp(entities[entity_id].type , "player") == 0 && player_id !=-1)
            {
                if((animations[animation_index].play_once == false || (animations[animation_index].play_once == true && animations[animation_index].done == true)) && player_shoot == false )
                {
                    if (velocities[velocity_index].dx > 0)
                        play_animation(entities[player_id].animation_index,"player_right",false);
                    else if (velocities[velocity_index].dx < 0)
                        play_animation(entities[player_id].animation_index,"player_left",false);
                    else if (velocities[velocity_index].dy > 0)
                        play_animation(entities[player_id].animation_index,"player_down",false);
                    else if (velocities[velocity_index].dy < 0)
                        play_animation(entities[player_id].animation_index,"player_up",false);
                    else
                        play_animation(entities[player_id].animation_index,"player_idle",false);
                }
                
            }
            
            //Enemy animations
            if(strcmp(entities[entity_id].type , "swordsman") == 0 || strcmp(entities[entity_id].type , "biggie") == 0 || strcmp(entities[entity_id].type , "christian") == 0 ||
               strcmp(entities[entity_id].type , "axe_man") == 0)
            {
                if(animations[animation_index].play_once == false || (animations[animation_index].play_once == true && animations[animation_index].done == true))
                {
                    char animation_name[255];
                    
                    strcpy(animation_name,entities[entity_id].type);
                    
                    if (velocities[velocity_index].dx > 0)
                        strcat(animation_name,"_right");
                    else if (velocities[velocity_index].dx < 0)
                        strcat(animation_name,"_left");
                    else if (velocities[velocity_index].dy > 0)
                        strcat(animation_name,"_down");
                    else if (velocities[velocity_index].dy < 0)
                        strcat(animation_name,"_up");
                    else
                        strcat(animation_name,"_idle");
                    
                    
                    play_animation(entities[entity_id].animation_index,animation_name,false);
                }
            }
            
            if(strcmp(entities[entity_id].type , "miniboss") == 0 && ai[entities[entity_id].ai_index].spin_time == -1 && ai[entities[entity_id].ai_index].daze_time == -1)
            {
                
                if(animations[animation_index].play_once == false || (animations[animation_index].play_once == true && animations[animation_index].done == true))
                {
                    char animation_name[255];
                    
                    strcpy(animation_name,entities[entity_id].type);
                    
                    if (velocities[velocity_index].dx > 0)
                        strcat(animation_name,"_right");
                    else if (velocities[velocity_index].dx < 0)
                        strcat(animation_name,"_left");
                    else if (velocities[velocity_index].dy > 0)
                        strcat(animation_name,"_down");
                    else if (velocities[velocity_index].dy < 0)
                        strcat(animation_name,"_up");
                    else
                        strcat(animation_name,"_idle");
                    
                    
                    play_animation(entities[entity_id].animation_index,animation_name,false);
                }
            }
        }
    }
}

//!---AI--!//
void ai_system()
{
    for(int i=0; i<MAX_AI_COMPONENTS;i++)
    {
        if(ai[i].entity_id == -1)
            break;
        
        if(ai[i].ai_type == 1)
        {
            if(ai[i].destroyed == false && ai[i].hit_time == -1 && player_id != -1)
            {
                int ai_collision_index = entities[ai[i].entity_id].collision_index;
                int ai_velocity_index = entities[ai[i].entity_id].velocity_index;
                
                float x1 = collisions[ai_collision_index].x;
                float y1 = collisions[ai_collision_index].y;
                
                float x2 = collisions[entities[player_id].collision_index].x + collisions[entities[player_id].collision_index].w / 2;
                float y2 = collisions[entities[player_id].collision_index].y + collisions[entities[player_id].collision_index].h / 2;
                
                float delta_x = x2 - x1;
                float delta_y = y2 - y1;
                
                float length = sqrt((delta_x * delta_x) + (delta_y*delta_y));
                
                //Stat info
                int ai_stat_index = entities[ai[i].entity_id].stat_index;
                int range_follow = stats[ai_stat_index].range_follow;
                int range_attack = stats[ai_stat_index].range_attack;
                int speed = stats[ai_stat_index].speed;
                
                if(length <= range_follow && length >= range_attack && ai[i].wait_time == -1 && ai[i].attack_time == -1)
                {
                    float vect_x = (x2-x1)/length;
                    float vect_y = (y2-y1)/length;
                    
                    velocities[ai_velocity_index].dx = vect_x * speed;
                    velocities[ai_velocity_index].dy = vect_y * speed;
                }
                else if(length < range_attack && ai[i].wait_time == -1 && ai[i].attack_time == -1)
                {
                    ai[i].wait_time = SDL_GetTicks();
                    velocities[ai_velocity_index].dx = 0;
                    velocities[ai_velocity_index].dy = 0;
                }
                else if(ai[i].wait_time != -1 && (SDL_GetTicks()- ai[i].wait_time) > 500)
                {
                    ai[i].attack_time = SDL_GetTicks();
                    ai[i].wait_time = -1;
                    
                    stats[ai_stat_index].can_dmg = true;
                    float vect_x = (x2-x1)/length;
                    float vect_y = (y2-y1)/length;
                    
                    velocities[ai_velocity_index].dx = vect_x * 10;
                    velocities[ai_velocity_index].dy = vect_y * 10;
                    
                    //Play enemy animation
                    if( abs(x2-x1) > abs(y2-y1))
                    {
                        char animation_name[255];
                        strcpy(animation_name,entities[ai[i].entity_id].type);
                        if(x2 > x1)
                            strcat(animation_name,"_attack_right");
                        if(x2 < x1)
                            strcat(animation_name,"_attack_left");
                        
                        play_animation(entities[ai[i].entity_id].animation_index,animation_name,true);
                    }
                    else
                    {
                        char animation_name[255];
                        strcpy(animation_name,entities[ai[i].entity_id].type);
                        if(y2 > y1)
                            strcat(animation_name,"_attack_down");
                        if(y2 < y1)
                            strcat(animation_name,"_attack_up");
                        
                        play_animation(entities[ai[i].entity_id].animation_index,animation_name,true);
                    }
                }
                else if(ai[i].attack_time != -1 && (SDL_GetTicks()- ai[i].attack_time) > 300)
                {
                    ai[i].attack_time = -1;
                    stats[ai_stat_index].can_dmg = false;
                }
                else if(length > range_follow)
                {
                    ai[i].wait_time = -1;
                    ai[i].attack_time = -1;
                    velocities[ai_velocity_index].dx = 0;
                    velocities[ai_velocity_index].dy = 0;
                }
            }
            else if(ai[i].destroyed == false && ai[i].hit_time != -1 && (SDL_GetTicks()- ai[i].hit_time) > 100 && player_id != -1)
            {
                ai[i].hit_time = -1;
                ai[i].attack_time = -1;
                ai[i].wait_time = -1;
            }
            else if(ai[i].destroyed == false && player_id == -1)
            {
                int ai_velocity_index = entities[ai[i].entity_id].velocity_index;
                ai[i].hit_time = -1;
                ai[i].attack_time = -1;
                ai[i].wait_time = -1;
                velocities[ai_velocity_index].dx = 0;
                velocities[ai_velocity_index].dy = 0;
            }
            
        }
        else if(ai[i].ai_type == 2 && ai[i].destroyed == false)
        {
            //Random running enemy
            int ai_velocity_index = entities[ai[i].entity_id].velocity_index;
            if(ai[i].wait_time == -1 || (SDL_GetTicks() - ai[i].wait_time > 2000))
            {
                
                int ai_stat_index = entities[ai[i].entity_id].stat_index;
                ai[i].wait_time = SDL_GetTicks();
                stats[ai_stat_index].can_dmg = true;
                
                float dx = rand() % 3 + 1;
                int dx_sign = rand() % 2 + 1;
                
                if(dx_sign == 1)
                    dx = -dx;
                
                
                float dy = rand() % 3 + 1;
                int dy_sign = rand() % 2 + 1;
                
                if(dy_sign == 1)
                    dy = -dy;
                
                
                velocities[ai_velocity_index].dx = dx;
                velocities[ai_velocity_index].dy = dy;
            }
        }
        else if(ai[i].ai_type == 3 && ai[i].destroyed == false)
        {
            miniboss_ai(i);
        }
    }
    
}


//!---RENDERING---!//
static
void rendering_system()
{
    //Render animations
    for(int i=0; i< MAX_ANIMATION_COMPONENTS;i++)
    {
        if(animations[i].entity_id == -1)
            break;
        
        //Draw hp for enemies
        int entity_id = animations[i].entity_id;
        if(strcmp(entities[entity_id].type , "swordsman") == 0 || strcmp(entities[entity_id].type , "biggie") == 0 || strcmp(entities[entity_id].type , "christian") == 0 ||
           strcmp(entities[entity_id].type , "axe_man") == 0 ||
           strcmp(entities[entity_id].type , "miniboss") == 0)
        {
            draw_enemy_hp(entity_id);
        }
        
        if(animations[i].destroyed == false)
        {
            if(animations[i].play_once == true && animations[i].done == true)
            {
                if(player_shoot == true && animations[i].entity_id == player_id)
                    player_shoot = false;
                
                //Draw last frame of animation that is done
                int frame_to_draw = animations[i].number_of_frames - 1;
                int position_index = entities[animations[i].entity_id].animation_index;
                SDL_Rect texture_part = animations[i].starting_position;
                texture_part.x = texture_part.x + texture_part.w * frame_to_draw;
                
                SDL_Rect position = {positions[position_index].x + animations[i].x_off, positions[position_index].y + animations[i].y_off,
                    positions[position_index].w,positions[position_index].h};
                
                //SDL_RenderDrawRect(s.renderer,&position);
                SDL_RenderCopyEx(s.renderer,animations[i].texture,&texture_part,&position,0,NULL,animations[i].flip_flags);
            }
            else
            {
                int frame_to_draw = ((SDL_GetTicks() - animations[i].start_time) * animations[i].frame_rate / 1000) % animations[i].number_of_frames;
                
                //If player shot an arrow
                if(player_shoot == true && frame_to_draw >=3 && animations[i].entity_id == player_id)
                    shoot_arrow();
                
                
                //If animtaion is done
                if(animations[i].play_once == true && (frame_to_draw < animations[i].last_frame || frame_to_draw == animations[i].number_of_frames - 1))
                {
                    animations[i].done = true;
                    animations[i].last_frame = frame_to_draw;
                    
                    if(animations[i].entity_id == player_id && player_shoot == true)
                        player_shoot = false;
                    
                    if(strcmp(entities[animations[i].entity_id].type,"miniboss") == 0)
                    {
                        int ai_index = entities[animations[i].entity_id].ai_index;
                        if(ai[ai_index].spin == 2)
                        {
                            ai[ai_index].spin_time = SDL_GetTicks();
                        }
                    }
                }
                
                //Render frame
                int position_index = entities[animations[i].entity_id].position_index;
                animations[i].last_frame = frame_to_draw;
                SDL_Rect texture_part = animations[i].starting_position;
                texture_part.x = texture_part.x + texture_part.w * frame_to_draw;
                
                SDL_Rect position = {positions[position_index].x + animations[i].x_off - g.camera.x, positions[position_index].y + animations[i].y_off - g.camera.y,
                    positions[position_index].w,positions[position_index].h};
                
                /*int collision_index = entities[animations[i].entity_id].collision_index;
                SDL_Rect collision_ = {collisions[collision_index].x, collisions[collision_index].y,
                    collisions[collision_index].w,collisions[collision_index].h};
                SDL_RenderDrawRect(s.renderer,&collision_);*/
                
                SDL_RenderCopyEx(s.renderer,animations[i].texture,&texture_part,&position,0,NULL,animations[i].flip_flags);
            }
            
        }
        
        
    }
    
    
    //!--Render static ui elements--!//
    //Main rect
    SDL_SetRenderDrawColor(s.renderer,100,54,18,255);
    SDL_Rect ui_rect = { 0, 0,150,64};
    SDL_RenderFillRect(s.renderer,&ui_rect);
    SDL_Rect ui_rect_1 = { 5,5,140,54};
    SDL_SetRenderDrawColor(s.renderer,118,67,26,255);
    SDL_RenderFillRect(s.renderer,&ui_rect_1);
    //Face rect
    SDL_Rect face_1 = {  8, 14,36,36};
    SDL_Rect face = {  10,  16, 32,32};
    SDL_SetRenderDrawColor(s.renderer,100,54,18,255);
    SDL_RenderFillRect(s.renderer,&face_1);
    SDL_SetRenderDrawColor(s.renderer,118,67,26,255);
    SDL_RenderFillRect(s.renderer,&face);
    //Face texture
    SDL_RenderCopy(s.renderer,ui_face,NULL,&face);
    
    
    //HP bar
    
    SDL_Rect hp_rect = {44,26,98,16};
    SDL_Rect hp_rect_2 = {46,28,0,12};
    if(player_id != -1)
    {
        float hp_bar = 94 * stats[player_id].hp / stats[player_id].max_hp;
        hp_rect_2.w = (int)hp_bar;
    }
    SDL_SetRenderDrawColor(s.renderer,0,0,0,255);
    SDL_RenderFillRect(s.renderer,&hp_rect);
    SDL_SetRenderDrawColor(s.renderer,139,0,0,255);
    SDL_RenderFillRect(s.renderer,&hp_rect_2);
    
    
    //Render sprites
    for(int i=0;i<MAX_SPRITE_COMPONENTS;i++)
    {
        if(sprites[i].entity_id == -1)
            break;
        
        if(sprites[i].destroyed == false)
        {
            int position_index = entities[sprites[i].entity_id].position_index;
            SDL_Rect position = {positions[position_index].x - g.camera.x,positions[position_index].y - g.camera.y,
                positions[position_index].w,positions[position_index].h};;
            
            //Camera stuff
            if(sprites[i].ui_text == true)
            {
                position.x = positions[position_index].x;
                position.y = positions[position_index].y;
            }
            
            if(sprites[i].texture_part.w == -1)
                SDL_RenderCopyEx(s.renderer,sprites[i].texture,NULL,&position,0,NULL,sprites[i].flip_flags);
            else
                SDL_RenderCopyEx(s.renderer,sprites[i].texture,&sprites[i].texture_part,&position,0,NULL,sprites[i].flip_flags);
            
            
            //Fade out if needed
            if(sprites[i].fade == true)
            {
                sprites[i].opacity-=sprites[i].fade_speed;
                SDL_SetTextureAlphaMod(sprites[i].texture,sprites[i].opacity);
                
                if(sprites[i].opacity <= 0)
                {
                    SDL_DestroyTexture(sprites[i].texture);
                    destroy_component(sprites[i].entity_id);
                }
            }
        }
    }
    
}
