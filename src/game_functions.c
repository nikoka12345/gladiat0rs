void add_(animation_info * info)
{
    if(head == NULL)
    {
        head = info;
    }
    else
    {
        animation_info *temp = head;
        while(temp->next != NULL)
                        temp = temp->next;
        
        temp->next = info;
    }
}

void load_animations_info()
{
    FILE* file = fopen("assets/animations.txt", "r");
    char buffer[255];
    char c = 'a';
    int i = 0;
    while( c != EOF)
    {
        c = fgetc(file);
                    
        if(c == '{' || c == '}' || c == '\n')
        {
            i = 0;
            fgetc(file);
        }
        else
        {
            buffer[i] = c;
            i++;
            
            if(c == ':')
            {
                //animation name
                buffer[--i] = '\0';
                i = 0;
                
                int x,y,w,h,num,fps,x_off,y_off;
                //x
                fscanf(file, "%d", &x);
                fgetc(file);
                //y
                fscanf(file, "%d", &y);
                fgetc(file);
                //w
                fscanf(file, "%d", &w);
                fgetc(file);
                //h
                fscanf(file, "%d", &h);
                fgetc(file);
                //number of frames
                fscanf(file, "%d", &num);
                fgetc(file);
                //frame rate
                fscanf(file, "%d", &fps);
                fgetc(file);
                //x_off
                fscanf(file, "%d", &x_off);
                fgetc(file);
                //y_off
                fscanf(file, "%d", &y_off);
                fgetc(file);
                
                SDL_Rect starting_ = {x,y,w,h};
                animation_info* info = malloc(sizeof(animation_info));
                
                strncpy(info->name,buffer,sizeof(info->name));
                info->starting_ = starting_;
                info->number_of_frames = num;
                info->frame_rate = fps;
                info->x_offset = x_off;
                info->y_offset = y_off;
                info->next = NULL;
                add_(info);
            }
        }
    }
    
    
    fclose(file);
}

void init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Could not init SDL %s\n", SDL_GetError());
    }
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        printf("Could not init SDL_image %s\n", SDL_GetError());
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0  )
    {
        printf("SDL Mixer init failed %s \n",SDL_GetError());
    }
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto screen_width = DM.w;
    auto screen_height = DM.h;
    
    int window_width = 640;
    int window_height = 480;
    
    if(window_width*2 <= screen_width && window_height*2 <= screen_height)
    {
        window_width *=2;
        window_height *=2;
    }
    
    s.window = SDL_CreateWindow("Gladiat0rs",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                window_width,
                                window_height,
                                SDL_WINDOW_FULLSCREEN_DESKTOP);
    //SDL_WINDOW_FULLSCREEN_DESKTOP || SDL_WINDOW_SHOWN
    if (s.window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());;
    }
    
    s.renderer = SDL_CreateRenderer(s.window,
                                    -1,
                                    SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(s.renderer, 640, 480);
    if (s.renderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());;
    }
    
    s.m_texture =  SDL_CreateTexture(s.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640, 480);
    SDL_Rect rect = {0,0,640,480};
    s.m_rect = rect;
    s.muted = false;
    
    //Load textures
    SDL_Surface *temp;
    if((temp = IMG_Load("assets/arrow_h.png")) == NULL){
                    printf("Image didn't load %s\n",SDL_GetError());
    }
    arrow_h =  SDL_CreateTextureFromSurface(s.renderer,temp);
    SDL_FreeSurface(temp);
    
    if((temp = IMG_Load("assets/arrow_v.png")) == NULL){
                    printf("Image didn't load %s \n",SDL_GetError());
    }
    arrow_v =  SDL_CreateTextureFromSurface(s.renderer,temp);
    SDL_FreeSurface(temp);
    
    if((temp = IMG_Load("assets/arena.png")) == NULL){
                    printf("Image didn't load %s \n",SDL_GetError());
    }
    arena_texture =  SDL_CreateTextureFromSurface(s.renderer,temp);
    SDL_FreeSurface(temp);
    
    if((temp = IMG_Load("assets/bigger_arena.png")) == NULL){
                    printf("Image didn't load %s \n",SDL_GetError());
    }
    bigger_arena_texture =  SDL_CreateTextureFromSurface(s.renderer,temp);
    SDL_FreeSurface(temp);
    
    if((temp = IMG_Load("assets/player.png")) == NULL){
                    printf("Image didn't load %s \n",SDL_GetError());
    }
    player_texture =  SDL_CreateTextureFromSurface(s.renderer,temp);
    SDL_FreeSurface(temp);
    
    
    if((temp = IMG_Load("assets/swordsman.png")) == NULL){
                    printf("Image didn't load %s \n",SDL_GetError());
    }
    swordsman_texture =  SDL_CreateTextureFromSurface(s.renderer,temp);
    SDL_FreeSurface(temp);
    
    if((temp = IMG_Load("assets/biggie.png")) == NULL){
                    printf("Image didn't load %s \n",SDL_GetError());
    }
    biggie_texture =  SDL_CreateTextureFromSurface(s.renderer,temp);
    SDL_FreeSurface(temp);
    
    if((temp = IMG_Load("assets/christian.png")) == NULL){
                    printf("Image didn't load %s \n",SDL_GetError());
    }
    christian_texture =  SDL_CreateTextureFromSurface(s.renderer,temp);
    SDL_FreeSurface(temp);
    
    if((temp = IMG_Load("assets/axe_man.png")) == NULL){
                    printf("Image didn't load %s \n",SDL_GetError());
    }
    axe_man_texture =  SDL_CreateTextureFromSurface(s.renderer,temp);
    SDL_FreeSurface(temp);
    
    if((temp = IMG_Load("assets/miniboss.png")) == NULL){
                    printf("Image didn't load %s \n",SDL_GetError());
    }
    miniboss_texture =  SDL_CreateTextureFromSurface(s.renderer,temp);
    SDL_FreeSurface(temp);
    
    if((temp = IMG_Load("assets/ui_face.png")) == NULL){
                    printf("Image didn't load %s \n",SDL_GetError());
    }
    ui_face =  SDL_CreateTextureFromSurface(s.renderer,temp);
    SDL_FreeSurface(temp);
    
    load_animations_info();
    /*animation_info * temp_ = head;
    while(temp_!=NULL)
    {
        printf("%s\n",temp_->name);
        temp_ =temp_->next;
    }*/
    
    //Loading sounds
    main_menu_music = Mix_LoadMUS( "assets/sound/main_menu_music.mp3");
    if(main_menu_music == NULL)
    {
        printf("Music didn't load %s \n",SDL_GetError());
    }
    main_theme = Mix_LoadMUS( "assets/sound/main_theme.mp3");
    if(main_theme == NULL)
    {
        printf("Music didn't load %s \n",SDL_GetError());
    }
    death_theme = Mix_LoadMUS( "assets/sound/death_theme.mp3");
    if(death_theme == NULL)
    {
        printf("Music didn't load %s \n",SDL_GetError());
    }
    
    
    
    play_music(main_menu_music);
    
    
    shoot = Mix_LoadWAV( "assets/sound/shoot.wav" );
    if(shoot == NULL)
    {
        printf("Music didn't load %s \n",SDL_GetError());
    }
    hit= Mix_LoadWAV( "assets/sound/hit.wav" );
    if(hit == NULL)
    {
        printf("Music didn't load %s \n",SDL_GetError());
    }
    
    
    init_entities();
    init_components();
    
    //Init text for menus
    SDL_Color color = {255,255,255};
    TTF_Font* font = TTF_OpenFont("assets/BULKYPIX.TTF", 25);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    
    SDL_Surface* text_surface = TTF_RenderText_Solid(font,"Play", color);
    play_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    int w = 0, h=0;
    TTF_SizeText(font, "Play",&w, &h);
    play_rect.x=  320 - w/2;
    play_rect.y= 240 - h/2;
    play_rect.w= w;
    play_rect.h= h;
    
    text_surface = TTF_RenderText_Solid(font,"Options", color);
    options_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, "Options",&w, &h);
    options_rect.x=  play_rect.x;
    options_rect.y=  play_rect.y + play_rect.h + 5;
    options_rect.w= w;
    options_rect.h= h;
    
    text_surface = TTF_RenderText_Solid(font,"Exit", color);
    exit_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, "Exit",&w, &h);
    exit_rect.x=  options_rect.x;
    exit_rect.y=  options_rect.y + options_rect.h + 5;
    exit_rect.w= w;
    exit_rect.h= h;
    
    text_surface = TTF_RenderText_Solid(font,">", color);
    cursor_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, ">",&w, &h);
    cursor_rect.x=  play_rect.x - 25;
    cursor_rect.y=  play_rect.y;
    cursor_rect.w= w;
    cursor_rect.h= h;
    
    text_surface = TTF_RenderText_Solid(font,"Volume", color);
    volume_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, "Volume:",&w, &h);
    volume_rect.x= 320 - w/2 - 100;
    volume_rect.y= 240 - h/2;
    volume_rect.w= w;
    volume_rect.h= h;
    
    text_surface = TTF_RenderText_Solid(font,"Fullscreen:", color);
    fullscreen_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, "Fullscreen:",&w, &h);
    fullscreen_rect.x= volume_rect.x;
    fullscreen_rect.y= volume_rect.y + volume_rect.h + 5;
    fullscreen_rect.w= w;
    fullscreen_rect.h= h;
    
    text_surface = TTF_RenderText_Solid(font,"ON", color);
    on_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, "ON",&w, &h);
    on_rect.x= fullscreen_rect.x + fullscreen_rect.w + 10;
    on_rect.y= fullscreen_rect.y;
    on_rect.w= w;
    on_rect.h= h;
    
    text_surface = TTF_RenderText_Solid(font,"OFF", color);
    off_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, "OFF",&w, &h);
    off_rect.x= fullscreen_rect.x + fullscreen_rect.w + 10;
    off_rect.y= fullscreen_rect.y;
    off_rect.w= w;
    off_rect.h= h;
    
    text_surface = TTF_RenderText_Solid(font,"Back", color);
    back_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, "Back",&w, &h);
    back_rect.x= fullscreen_rect.x;
    back_rect.y= fullscreen_rect.y + fullscreen_rect.h + 5;
    back_rect.w= w;
    back_rect.h= h;
    
    //For pause
    text_surface = TTF_RenderText_Solid(font,"Resume", color);
    resume_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, "Resume",&w, &h);
    resume_rect.x= 320 - w/2;
    resume_rect.y= 240 - h/2;
    resume_rect.w= w;
    resume_rect.h= h;
    
    pause_options_rect.x = resume_rect.x;
    pause_options_rect.y = resume_rect.y + resume_rect.h + 5;
    pause_options_rect.w = options_rect.w;
    pause_options_rect.h = options_rect.h;
    
    text_surface = TTF_RenderText_Solid(font,"Main Menu", color);
    main_menu_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, "Main Menu",&w, &h);
    main_menu_rect.x= pause_options_rect.x;
    main_menu_rect.y= pause_options_rect.y + pause_options_rect.h + 5;
    main_menu_rect.w= w;
    main_menu_rect.h= h;
    
    //For dead screen
    text_surface = TTF_RenderText_Solid(font,"Retry", color);
    retry_texture = SDL_CreateTextureFromSurface(s.renderer, text_surface);
    TTF_SizeText(font, "Retry",&w, &h);
    retry_rect.x= 320 - w/2;
    retry_rect.y= 240 - h/2 + 60;
    retry_rect.w= w;
    retry_rect.h= h;
    
    dead_main_menu_rect.x = retry_rect.x;
    dead_main_menu_rect.y = retry_rect.y + retry_rect.h + 5;
    dead_main_menu_rect.w = main_menu_rect.w;
    dead_main_menu_rect.h = main_menu_rect.h;
    
    dead_exit_rect.x = dead_main_menu_rect.x;
    dead_exit_rect.y = dead_main_menu_rect.y + dead_main_menu_rect.h + 5;
    dead_exit_rect.w = exit_rect.w;
    dead_exit_rect.h = exit_rect.h;
    
    SDL_FreeSurface(text_surface);
    TTF_CloseFont( font );
}

void seed_entities()
{
    //Add player
    int player = create_entity("player");
    add_position_component(player,100,100,35,35);
    add_velocity_component(player,0,0);
    add_collision_component(player,100,100,14,29,true,"player");
    add_animation_component(player,"player_right",player_texture,SDL_FLIP_NONE,false);
    add_stat_component(player,10,4,1,0,0);
    player_id = player;
    
    //Add walls
    int wall_id_0 = create_entity("wall");
    add_collision_component(wall_id_0,0,0,960,64,false,"wall");
    int wall_id_1 = create_entity("wall");
    add_collision_component(wall_id_1,32,0,32,736,false,"wall");
    int wall_id_2 = create_entity("wall");
    add_collision_component(wall_id_2,0,672,960,32,false,"wall");
    int wall_id_3 = create_entity("wall");
    add_collision_component(wall_id_3,896,0,32,736,false,"wall");
    
    /* For smaller arena
int wall_id_0 = create_entity("wall");
        add_collision_component(wall_id_0,0,32,640,32,false,"wall");
        int wall_id_1 = create_entity("wall");
        add_collision_component(wall_id_1,32,0,32,480,false,"wall");
        int wall_id_2 = create_entity("wall");
        add_collision_component(wall_id_2,0,416,640,32,false,"wall");
        int wall_id_3 = create_entity("wall");
        add_collision_component(wall_id_3,576,0,32,480,false,"wall");
*/
    
    
    //Text
    SDL_Color color = {255,255,255};
    power_text = add_text_entity("Power: 10",10,color,46,14,false,0);
    goal_text = add_text_entity("Powerup: 0/8",9,color,46,44,false,0);
    
    sprites[entities[power_text].sprite_index].ui_text = true;
    sprites[entities[goal_text].sprite_index].ui_text = true;
    
    //HP text
    char hp_info[50] = "";
    char hp[10],max_hp[10];
    sprintf(hp,"%d",stats[player_id].hp);
    sprintf(max_hp,"%d",stats[player_id].max_hp);
    strcat(hp_info,hp);
    strcat(hp_info,"/");
    strcat(hp_info,max_hp);
    
    hp_text = add_text_entity(hp_info,10,color,73,30,false,0);
    sprites[entities[hp_text].sprite_index].ui_text = true;
    
    //Lvl text
    char lvl_info[50] = "Level";
    char lvl[10];
    sprintf(lvl,"%d",level);
    strcat(lvl_info,lvl);
    lvl_text = add_text_entity(lvl_info,14,color,560,10,false,0);
    sprites[entities[lvl_text].sprite_index].ui_text = true;
}


static
void cleanup()
{
    SDL_DestroyRenderer(s.renderer);
    SDL_DestroyWindow(s.window);
    SDL_Quit();
}

static
void show_framerate(int start_time,int counted_frames)
{
    float frame_rate  = counted_frames  / ( (SDL_GetTicks() - start_time) / 1000.f );
    if( frame_rate > 2000000 )
    {
        frame_rate = 01;
    }
    char title[64]  = "Gladiat0rs FPS: ";
    char integer_string[32];
    sprintf(integer_string, "%f", frame_rate);
    strcat(title, integer_string);
    
    SDL_SetWindowTitle(s.window,title);
}

static
void cap_framerate(int frame_start_time)
{
    int frame_time = SDL_GetTicks() - frame_start_time;
    if (FRAME_DELAY > frame_time)
    {
        SDL_Delay(FRAME_DELAY - frame_time);
    }
}