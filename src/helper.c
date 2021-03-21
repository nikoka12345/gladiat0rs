static
int checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

void collide_with_wall(int entity_id_,int wall_id_,char* vel)
{
    int entity_collision_index = entities[entity_id_].collision_index;
    int entity_position_index = entities[entity_id_].position_index;
    
    int wall_collision_index =  entities[wall_id_].collision_index;
    int wall_position_index =  entities[wall_id_].position_index;
    
    float hspeed = velocities[entities[entity_id_].velocity_index].dx;
    float vspeed = velocities[entities[entity_id_].velocity_index].dy;
    
    if(strcmp(vel,"dx") == 0)
    {
        if(hspeed > 0)
        {
            collisions[entity_collision_index].x = collisions[wall_collision_index].x - collisions[entity_collision_index].w;
            
            positions[entity_position_index].x = collisions[entity_collision_index].x;
        }
        else if(hspeed < 0)
        {
            collisions[entity_collision_index].x = collisions[wall_collision_index].x + collisions[wall_collision_index].w;
            
            
            positions[entity_position_index].x = collisions[entity_collision_index].x;
        }
    }
    else if(strcmp(vel,"dy") == 0)
    {
        if(vspeed > 0)
        {
            collisions[entity_collision_index].y = collisions[wall_collision_index].y - collisions[entity_collision_index].h;
            
            positions[entity_position_index].y = collisions[entity_collision_index].y;
        }
        else if(vspeed < 0)
        {
            
            collisions[entity_collision_index].y = collisions[wall_collision_index].y + collisions[wall_collision_index].h;
            
            positions[entity_position_index].y = collisions[entity_collision_index].y;
        }
        
    }
}


void shoot_arrow()
{
    
    int player_position_id = entities[player_id].position_index;
    int player_collision_id = entities[player_id].collision_index;
    int player_animation_index = entities[player_id].animation_index;
    int dmg = 1;
    if(player_id != -1)
        dmg = stats[entities[player_id].stat_index].dmg;
    
    if(shoot_direction == UP)
    {
        int bullet_id = create_entity("arrow");
        add_position_component(bullet_id,collisions[player_collision_id].x + 7,collisions[player_collision_id].y - 11,3,11);
        add_velocity_component(bullet_id,0,-6);
        add_collision_component(bullet_id,collisions[player_collision_id].x + 7,collisions[player_collision_id].y -11 ,3,11,true,"bullet");
        add_sprite_component(bullet_id,arrow_v,false,0,SDL_FLIP_NONE);
        add_stat_component(bullet_id,1,6,dmg,0,0);
        
        if(max_lvl == true)
        {
            //Left
            int bullet_id_1 = create_entity("arrow");
            add_position_component(bullet_id_1,collisions[player_collision_id].x + 7,collisions[player_collision_id].y - 11,3,11);
            add_velocity_component(bullet_id_1,-1,-6);
            add_collision_component(bullet_id_1,collisions[player_collision_id].x + 7,collisions[player_collision_id].y -11 ,3,11,true,"bullet");
            add_sprite_component(bullet_id_1,arrow_v,false,0,SDL_FLIP_NONE);
            add_stat_component(bullet_id_1,1,6,dmg,0,0);
            
            //Right
            int bullet_id_2 = create_entity("arrow");
            add_position_component(bullet_id_2,collisions[player_collision_id].x + 7,collisions[player_collision_id].y - 11,3,11);
            add_velocity_component(bullet_id_2,1,-6);
            add_collision_component(bullet_id_2,collisions[player_collision_id].x + 7,collisions[player_collision_id].y -11 ,3,11,true,"bullet");
            add_sprite_component(bullet_id_2,arrow_v,false,0,SDL_FLIP_NONE);
            add_stat_component(bullet_id_2,1,6,dmg,0,0);
        }
        
        shoot_direction = NONE;
        play_sound(shoot);
    }
    else if(shoot_direction == DOWN)
    {
        int bullet_id = create_entity("arrow");
        add_position_component(bullet_id,collisions[player_collision_id].x + 7,collisions[player_collision_id].y + collisions[player_collision_id].h ,3,11);
        add_velocity_component(bullet_id,0,6);
        add_collision_component(bullet_id,collisions[player_collision_id].x + 7,collisions[player_collision_id].y + collisions[player_collision_id].h ,3,11,true,"bullet");
        add_sprite_component(bullet_id,arrow_v,false,0,SDL_FLIP_VERTICAL);
        add_stat_component(bullet_id,1,6,dmg,0,0);
        
        
        if(max_lvl == true)
        {
            //Left
            int bullet_id_1 = create_entity("arrow");
            add_position_component(bullet_id_1,collisions[player_collision_id].x + 7,collisions[player_collision_id].y + collisions[player_collision_id].h ,3,11);
            add_velocity_component(bullet_id_1,-1,6);
            add_collision_component(bullet_id_1,collisions[player_collision_id].x + 7,collisions[player_collision_id].y + collisions[player_collision_id].h ,3,11,true,"bullet");
            add_sprite_component(bullet_id_1,arrow_v,false,0,SDL_FLIP_VERTICAL);
            add_stat_component(bullet_id_1,1,6,dmg,0,0);
            
            //Right
            int bullet_id_2 = create_entity("arrow");
            add_position_component(bullet_id_2,collisions[player_collision_id].x + 7,collisions[player_collision_id].y + collisions[player_collision_id].h ,3,11);
            add_velocity_component(bullet_id_2,1,6);
            add_collision_component(bullet_id_2,collisions[player_collision_id].x + 7,collisions[player_collision_id].y + collisions[player_collision_id].h ,3,11,true,"bullet");
            add_sprite_component(bullet_id_2,arrow_v,false,0,SDL_FLIP_VERTICAL);
            add_stat_component(bullet_id_2,1,6,dmg,0,0);
        }
        
        shoot_direction = NONE;
        play_sound(shoot);
    }
    else if(shoot_direction == RIGHT)
    {
        
        int bullet_id = create_entity("arrow");
        add_position_component(bullet_id,collisions[player_collision_id].x + collisions[player_collision_id].w ,collisions[player_collision_id].y + 14,11,3);
        add_velocity_component(bullet_id,6,0);
        add_collision_component(bullet_id,collisions[player_collision_id].x + collisions[player_collision_id].w ,collisions[player_collision_id].y + 6,11,3,true,"bullet");
        add_sprite_component(bullet_id,arrow_h,false,0,SDL_FLIP_NONE);
        add_stat_component(bullet_id,1,6,dmg,0,0);
        
        
        if(max_lvl == true)
        {
            //Up
            int bullet_id_1 = create_entity("arrow");
            add_position_component(bullet_id_1,collisions[player_collision_id].x + collisions[player_collision_id].w ,collisions[player_collision_id].y + 14,11,3);
            add_velocity_component(bullet_id_1,6,-1);
            add_collision_component(bullet_id_1,collisions[player_collision_id].x + collisions[player_collision_id].w ,collisions[player_collision_id].y + 6,11,3,true,"bullet");
            add_sprite_component(bullet_id_1,arrow_h,false,0,SDL_FLIP_NONE);
            add_stat_component(bullet_id_1,1,6,dmg,0,0);
            
            //Down
            int bullet_id_2 = create_entity("arrow");
            add_position_component(bullet_id_2,collisions[player_collision_id].x + collisions[player_collision_id].w ,collisions[player_collision_id].y + 14,11,3);
            add_velocity_component(bullet_id_2,6,1);
            add_collision_component(bullet_id_2,collisions[player_collision_id].x + collisions[player_collision_id].w ,collisions[player_collision_id].y + 6,11,3,true,"bullet");
            add_sprite_component(bullet_id_2,arrow_h,false,0,SDL_FLIP_NONE);
            add_stat_component(bullet_id_2,1,6,dmg,0,0);
        }
        
        shoot_direction = NONE;
        play_sound(shoot);
    }
    else if(shoot_direction == LEFT)
    {
        
        int bullet_id = create_entity("arrow");
        add_position_component(bullet_id,collisions[player_collision_id].x - 11 ,collisions[player_collision_id].y + 14,11,3);
        add_velocity_component(bullet_id,-6,0);
        add_collision_component(bullet_id,positions[player_position_id].x - 30 ,positions[player_position_id].y + 20 ,11,3,true,"bullet");
        add_sprite_component(bullet_id,arrow_h,false,0,SDL_FLIP_HORIZONTAL);
        add_stat_component(bullet_id,1,6,dmg,0,0);
        
        if(max_lvl == true)
        {
            //Up
            int bullet_id_1 = create_entity("arrow");
            add_position_component(bullet_id_1,collisions[player_collision_id].x - 11 ,collisions[player_collision_id].y + 14,11,3);
            add_velocity_component(bullet_id_1,-6,-1);
            add_collision_component(bullet_id_1,positions[player_position_id].x - 30 ,positions[player_position_id].y + 20 ,11,3,true,"bullet");
            add_sprite_component(bullet_id_1,arrow_h,false,0,SDL_FLIP_HORIZONTAL);
            add_stat_component(bullet_id_1,1,6,dmg,0,0);
            
            //Dow
            int bullet_id_2 = create_entity("arrow");
            add_position_component(bullet_id_2,collisions[player_collision_id].x - 11 ,collisions[player_collision_id].y + 14,11,3);
            add_velocity_component(bullet_id_2,-6,1);
            add_collision_component(bullet_id_2,positions[player_position_id].x - 30 ,positions[player_position_id].y + 20 ,11,3,true,"bullet");
            add_sprite_component(bullet_id_2,arrow_h,false,0,SDL_FLIP_HORIZONTAL);
            add_stat_component(bullet_id_2,1,6,dmg,0,0);
            
        }
        
        
        
        shoot_direction = NONE;
        play_sound(shoot);
    }
}

void add_shake(enum ss_amount amount_)
{
    amount = amount_;
    shake_timer = SDL_GetTicks();
}

void shake()
{
    if (amount == SMALL && SDL_GetTicks() - shake_timer <= 100)
	{
		s.m_rect.x = rand() % 4 - 2;
		s.m_rect.y = rand() % 4 - 2;
	}
    else if (amount== MEDIUM && SDL_GetTicks() - shake_timer <= 400)
	{
		s.m_rect.x = rand() % 8 - 4;
		s.m_rect.y = rand() % 8 - 4;
	}
	
	else if (amount == BIG && SDL_GetTicks() - shake_timer <= 500)
	{
		s.m_rect.x = rand() % 8 - 4;
		s.m_rect.y = rand() % 8 - 4;
	}
	else
	{
		s.m_rect.x = 0;
		s.m_rect.y = 0;
		amount = NO;
	}
}

void change_hp_text()
{
    //Change hp text
    SDL_Color white_color = {255,255,255};
    char hp_info[50] = "";
    char hp[10],max_hp[10];
    sprintf(hp,"%d",stats[player_id].hp);
    sprintf(max_hp,"%d",stats[player_id].max_hp);
    strcat(hp_info,hp);
    strcat(hp_info,"/");
    strcat(hp_info,max_hp);
    change_text(hp_text,hp_info,10,white_color);
}

void change_level_text()
{
    //Change hp text
    SDL_Color white_color = {255,255,255};
    char lvl_info[50] = "Level";
    char lvl[10];
    sprintf(lvl,"%d",level);
    strcat(lvl_info,lvl);
    change_text(lvl_text,lvl_info,14,white_color);
}

void powerup()
{
    current_index++;
    if(current_index > 6 && max_lvl == false)
    {
        max_lvl = true;
        
        SDL_Color color = {255,255,255};
        int player_position_index = entities[player_id].position_index;
        int x = positions[player_position_index].x;
        int y = positions[player_position_index].y;
        add_text_entity("TRIPLE ARROW",11,color,x,y,true,3);
        
        
        change_text(goal_text,"",9,color);
        change_text(power_text,"ITS OVER 9000",9,color);
    }
    else
    {
        //Reset
        killed = 0;
        current_goal = goals[current_index];
        
        //Change text
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
        
        //Add powerup
        if(player_id != -1)
        {
            if(current_index == 1)
            {
                SDL_Color color = {255,255,255};
                int player_position_index = entities[player_id].position_index;
                int x = positions[player_position_index].x;
                int y = positions[player_position_index].y;
                add_text_entity("+ MAX HP",11,color,x,y,true,3);
                
                stats[entities[player_id].stat_index].max_hp +=4;
                stats[entities[player_id].stat_index].hp +=4;
                change_text(power_text,"Power: 150",10,color);
                change_hp_text();
            }
            else if(current_index == 2)
            {
                SDL_Color color = {255,255,255};
                int player_position_index = entities[player_id].position_index;
                int x = positions[player_position_index].x;
                int y = positions[player_position_index].y;
                add_text_entity("SPEED UP",11,color,x,y,true,3);
                
                change_text(power_text,"Power: 280",10,color);
                
                stats[entities[player_id].stat_index].speed +=1;
                if(velocities[entities[player_id].velocity_index].dx != 0)
                {
                    if(velocities[entities[player_id].velocity_index].dx > 0)
                        velocities[entities[player_id].velocity_index].dx = stats[entities[player_id].stat_index].speed;
                    else velocities[entities[player_id].velocity_index].dx =- stats[entities[player_id].stat_index].speed;
                }
                if(velocities[entities[player_id].velocity_index].dy != 0)
                {
                    if(velocities[entities[player_id].velocity_index].dy > 0)
                        velocities[entities[player_id].velocity_index].dy = stats[entities[player_id].stat_index].speed;
                    else velocities[entities[player_id].velocity_index].dy =- stats[entities[player_id].stat_index].speed;
                }
            }
            else if(current_index == 3)
            {
                SDL_Color color = {255,255,255};
                int player_position_index = entities[player_id].position_index;
                int x = positions[player_position_index].x;
                int y = positions[player_position_index].y;
                add_text_entity("DAMAGE UP",11,color,x,y,true,3);
                
                change_text(power_text,"Power: 399",10,color);
                
                stats[entities[player_id].stat_index].dmg +=1;
            }
            else if(current_index == 4)
            {
                SDL_Color color = {255,255,255};
                int player_position_index = entities[player_id].position_index;
                int x = positions[player_position_index].x;
                int y = positions[player_position_index].y;
                add_text_entity("+ MAX HP",11,color,x,y,true,3);
                
                stats[entities[player_id].stat_index].max_hp +=5;
                stats[entities[player_id].stat_index].hp +=5;
                change_text(power_text,"Power: 415",10,color);
                change_hp_text();
            }
            else if(current_index == 5)
            {
                SDL_Color color = {255,255,255};
                int player_position_index = entities[player_id].position_index;
                int x = positions[player_position_index].x;
                int y = positions[player_position_index].y;
                add_text_entity("SPEED UP",11,color,x,y,true,3);
                
                stats[entities[player_id].stat_index].speed +=1;
                if(velocities[entities[player_id].velocity_index].dx != 0)
                {
                    if(velocities[entities[player_id].velocity_index].dx > 0)
                        velocities[entities[player_id].velocity_index].dx = stats[entities[player_id].stat_index].speed;
                    else velocities[entities[player_id].velocity_index].dx =- stats[entities[player_id].stat_index].speed;
                }
                if(velocities[entities[player_id].velocity_index].dy != 0)
                {
                    if(velocities[entities[player_id].velocity_index].dy > 0)
                        velocities[entities[player_id].velocity_index].dy = stats[entities[player_id].stat_index].speed;
                    else velocities[entities[player_id].velocity_index].dy =- stats[entities[player_id].stat_index].speed;
                }
                
                change_text(power_text,"Power: 500",10,color);
            }
            else if(current_index == 6)
            {
                SDL_Color color = {255,255,255};
                int player_position_index = entities[player_id].position_index;
                int x = positions[player_position_index].x;
                int y = positions[player_position_index].y;
                add_text_entity("+ MAX HP",11,color,x,y,true,3);
                
                stats[entities[player_id].stat_index].max_hp +=7;
                stats[entities[player_id].stat_index].hp +=7;
                change_text(power_text,"Power: 1590",10,color);
                change_hp_text();
            }
            
        }
        
    }
    
}

void draw_enemy_hp(int entity_id)
{
    if(entities[entity_id].stat_index != -1 && stats[entities[entity_id].stat_index].destroyed == false &&  stats[entities[entity_id].stat_index].hp != stats[entities[entity_id].stat_index].max_hp)
    {
        int position_index = entities[entity_id].position_index;
        SDL_Rect hp_outer = {positions[position_index].x - g.camera.x, positions[position_index].y - 10 - g.camera.y,20,6};
        float width = 18 * stats[entities[entity_id].stat_index].hp / stats[entities[entity_id].stat_index].max_hp;
        SDL_Rect hp_inner = {positions[position_index].x + 1 - g.camera.x,positions[position_index].y - 9 - g.camera.y,width,4};
        
        SDL_SetRenderDrawColor(s.renderer,0,0,0,255);
        SDL_RenderFillRect(s.renderer,&hp_outer);
        SDL_SetRenderDrawColor(s.renderer,139,0,0,255);
        SDL_RenderFillRect(s.renderer,&hp_inner);
    }
}

void miniboss_ai(int i)
{
    if(ai[i].spin == -1)
    {
        ai[i].spin = rand() % 2 + 1;
    }
    
    //Follow
    if(ai[i].spin == 1)
    {
        if(player_id != -1)
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
                ai[i].spin = rand() % 2 + 1;
                velocities[ai_velocity_index].dx = 0;
                velocities[ai_velocity_index].dy = 0;
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
    //Spin
    else
    {
        if(ai[i].daze_time == -1 && ai[i].spin_time == -1)
        {
            play_animation(entities[ai[i].entity_id].animation_index,"miniboss_prepare",true);
        }
        else if(ai[i].spin_time != -1)
        {
            int velocity_index = entities[ai[i].entity_id].velocity_index;
            if(velocities[velocity_index].dx == 0 && velocities[velocity_index].dy == 0)
            {
                play_animation(entities[ai[i].entity_id].animation_index,"miniboss_spin",false);
                int stats_index = entities[ai[i].entity_id].stat_index;
                if(stats_index != -1 && stats[stats_index].destroyed == false)
                    stats[stats_index].can_dmg = true;
                
                
                float dx = rand() % 5 + 3;
                int dx_sign = rand() % 2 + 1;
                
                if(dx_sign == 1)
                    dx = -dx;
                
                
                float dy = rand() % 5 + 3;
                int dy_sign = rand() % 2 + 1;
                
                if(dy_sign == 1)
                    dy = -dy;
                
                velocities[velocity_index].dx = dx;
                velocities[velocity_index].dy = dy;
            }
        }
        else if(ai[i].daze_time != -1)
        {
            play_animation(entities[ai[i].entity_id].animation_index,"miniboss_daze",false);
        }
        
        //End of states
        if(ai[i].spin_time != -1 && (SDL_GetTicks() - ai[i].spin_time > 5000))
        {
            ai[i].spin_time = -1;
            ai[i].daze_time = SDL_GetTicks();
            
            int stats_index = entities[ai[i].entity_id].stat_index;
            if(stats_index != -1 && stats[stats_index].destroyed == false)
                stats[stats_index].can_dmg = false;
            
            int velocity_index = entities[ai[i].entity_id].velocity_index;
            
            velocities[velocity_index].dx = 0;
            velocities[velocity_index].dy = 0;
        }
        if(ai[i].daze_time != -1 && (SDL_GetTicks() - ai[i].daze_time > 3000))
        {
            ai[i].daze_time = -1;
            ai[i].spin = rand() % 2 + 1;
        }
        
    }
    
}

void reset_entities()
{
    
    swordsman_killed = 0;
    biggie_killed = 0;
    christian_killed = 0;
    axe_man_killed = 0;
    miniboss_killed = 0;
    
    player_id = -1;
    player_shoot = false;
    shoot_direction = NONE;
    dead_timer = -1;
    
    current_goal = 8;
    max_lvl = false;
    killed = 0;
    current_index = 0;
    
    enemies_alive = 0;
    
    level = 0;
    xp = 0;
    xp_required = 100;
    
    init_entities();
    init_components();
}

void add_scores()
{
    if(swordsman_score != NULL)
    {
        SDL_DestroyTexture(swordsman_score);
        swordsman_score = NULL;
        
        SDL_DestroyTexture(christian_score);
        christian_score = NULL;
        
        SDL_DestroyTexture(axe_man_score);
        axe_man_score = NULL;
        
        SDL_DestroyTexture(biggie_score);
        biggie_score = NULL;
        
        SDL_DestroyTexture(miniboss_score);
        miniboss_score = NULL;
    }
    
    
    char s_score_char[50] = "";
    char c_score_char[50] = "";
    char a_score_char[50] = "";
    char b_score_char[50] = "";
    char m_score_char[50] = "";
    
    sprintf(s_score_char,"%d",swordsman_killed);
    sprintf(c_score_char,"%d",christian_killed);
    sprintf(a_score_char,"%d",axe_man_killed);
    sprintf(b_score_char,"%d",biggie_killed);
    sprintf(m_score_char,"%d",miniboss_killed);
    
    //Level
    char lvl_info[50] = "Level";
    char lvl[10];
    sprintf(lvl,"%d",level);
    strcat(lvl_info,lvl);
    
    
    
    SDL_Color color = {255,255,255};
    TTF_Font* font = TTF_OpenFont("assets/BULKYPIX.TTF", 12);
    TTF_Font* font_level = TTF_OpenFont("assets/BULKYPIX.TTF", 24);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    SDL_Surface* text_surface = TTF_RenderText_Solid(font,s_score_char, color);
    swordsman_score = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    
    int w = 0, h=0;
    TTF_SizeText(font, s_score_char ,&w, &h);
    s_score.x = 220;
    s_score.y = 190;
    s_score.w = w;
    s_score.h = h;
    
    text_surface = TTF_RenderText_Solid(font,c_score_char, color);
    christian_score = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, c_score_char ,&w, &h);
    c_score.x = s_score.x + 55;
    c_score.y = 190;
    c_score.w = w;
    c_score.h = h;
    
    text_surface = TTF_RenderText_Solid(font,a_score_char, color);
    axe_man_score = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, a_score_char ,&w, &h);
    a_score.x = c_score.x + 55;
    a_score.y = 190;
    a_score.w = w;
    a_score.h = h;
    
    text_surface = TTF_RenderText_Solid(font,b_score_char, color);
    biggie_score = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, b_score_char ,&w, &h);
    b_score.x = a_score.x + 55;
    b_score.y = 190;
    b_score.w = w;
    b_score.h = h;
    
    text_surface = TTF_RenderText_Solid(font,m_score_char, color);
    miniboss_score = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, m_score_char ,&w, &h);
    m_score.x = b_score.x + 55;
    m_score.y = 190;
    m_score.w = w;
    m_score.h = h;
    
    text_surface = TTF_RenderText_Solid(font_level, lvl_info, color);
    level_score = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font_level, lvl_info ,&w, &h);
    level_rect.w = w;
    level_rect.h = h;
    
    
    SDL_FreeSurface(text_surface);
    TTF_CloseFont( font );
    TTF_CloseFont( font_level );
}


void spawn()
{
    //Choose number of enemies
    int min = 1;
    int max = 3;
    if(current_index == 2)
    {
        min = 2;
        max = 3;
    }
    else if(current_index == 3)
    {
        min = 2;
        max = 4;
    }
    else if(current_index == 4 || current_index == 5)
    {
        min = 3;
        max = 5;
    }
    else if(current_index == 6)
    {
        min = 4;
        max = 6;
    }
    else if(current_index > 6 && level < 20)
    {
        min = 5;
        max = 7;
    }
    else if(current_index > 6 && level >= 20 && level < 30)
    {
        min = 6;
        max = 11;
    }
    else if(current_index > 6 && level >= 30)
    {
        min = 7;
        max = 14;
    }
    
    int number_to_spawn = rand()%(max-min + 1) + min;
    
    for(int i=0;i<number_to_spawn;i++)
    {
        //Choose position
        int player_x = 0;
        int player_y = 0;
        if(player_id != -1)
        {
            player_x = positions[entities[player_id].position_index].x;
            player_y = positions[entities[player_id].position_index].y;
        }
        
        int x = rand()%(870 - 80 + 1) + 80;
        while(x >= player_x - 50 && x <= player_x + 50)
            x = rand()%(870 - 80 + 1) + 80;
        
        int y = rand()%(640-70 + 1) + 70;
        
        while(y >= player_y - 50 && y <= player_y + 50)
            y = rand()%(640-70 + 1) + 70;
        
        SDL_Rect position = {x,y,10,10};
        
        //Choose enemy
        int enemy = 1;
        if(current_index < 3)
            enemy = rand()%(2 - 1 + 1) + 1;
        else if(current_index == 3)
            enemy = rand()%(3 - 1 + 1) + 1;
        else if(current_index > 3 && current_index <= 6)
            enemy = rand()%(4 - 1 + 1) + 1;
        else if(current_index > 6)
            enemy = rand()%(5 - 1 + 1) + 1;
        
        
        //Spawn
        switch(enemy)
        {
            //Christian
            case 1:
            {
                int enemy_id = create_entity("christian");
                add_position_component(enemy_id,x,y,35,35);
                add_velocity_component(enemy_id,0,0);
                add_collision_component(enemy_id,x,y,15,31,true,"enemy");
                add_ai_component(enemy_id,true,1);
                add_animation_component(enemy_id,"christian_idle",christian_texture,SDL_FLIP_NONE,false);
                add_stat_component(enemy_id,3,4,1,390,80);
                add_shake(SMALL);
            }break;
            
            //Swordsman
            case 2:
            {
                int enemy_id = create_entity("swordsman");
                add_position_component(enemy_id,x,y,35,35);
                add_velocity_component(enemy_id,0,0);
                add_collision_component(enemy_id,x,y,20,29,true,"enemy");
                add_ai_component(enemy_id,true,1);
                add_animation_component(enemy_id,"swordsman_idle",swordsman_texture,SDL_FLIP_NONE,false);
                add_stat_component(enemy_id,5,3,2,450,70);
                add_shake(SMALL);
            }break;
            
            //Axeman
            case 3:
            {
                int enemy_id = create_entity("axe_man");
                add_position_component(enemy_id,x,y,40,40);
                add_velocity_component(enemy_id,0,0);
                add_collision_component(enemy_id,x,y,26,30,true,"enemy");
                add_ai_component(enemy_id,false,1);
                add_animation_component(enemy_id,"axe_man_idle",axe_man_texture,SDL_FLIP_NONE,false);
                add_stat_component(enemy_id,7,3,2,450,70);
                add_shake(SMALL);
            }break;
            
            //Biggie
            case 4:
            {
                int enemy_id = create_entity("biggie");
                add_position_component(enemy_id,x,y,45,45);
                add_velocity_component(enemy_id,0,0);
                add_collision_component(enemy_id,x,y,29,39,true,"enemy");
                add_ai_component(enemy_id,false,1);
                add_animation_component(enemy_id,"biggie_idle",biggie_texture,SDL_FLIP_NONE,false);
                add_stat_component(enemy_id,10,2,4,500,60);
                add_shake(MEDIUM);
            }break;
            
            //miniboss
            case 5:
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
    }
    enemies_alive = number_to_spawn;
}