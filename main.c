#include <stdio.h>
#include <tmx.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "index.h"
#include "string.h"

const int WIDTH = 600;
const int HEIGHT = 600;

const int TANK_WIDTH = 40;
const int TANK_HEIGHT = 40;

const int UP = 270;
const int RIGHT = 0;
const int DOWN = 90;
const int LEFT = 180;


typedef struct{
    int x,y;
    int width,height;
    int direction;
    int angle;
    int speed;
    SDL_Texture *texture;
}Player;

void createPlayer(Player player, SDL_Rect s_rect, SDL_Rect d_rect, SDL_Renderer *render, SDL_Surface *image)
{
    SDL_RenderClear(render);
    player.texture = SDL_CreateTextureFromSurface(render, image);

    SDL_RenderCopyEx(render, player.texture, &s_rect, &d_rect, player.angle, NULL, player.direction);

    SDL_DestroyTexture(player.texture);
}

//todo: check player near box is in map box
int checkCollision(Player player, tmx_map* map, int dicrection)
{
    //遍历map图形

    tmx_layer *layer = map->ly_head;

    unsigned long i, j;
    unsigned int gid, x, y, w, h, react_height, react_width, flags;
    SDL_Rect player_rect;

    

    tmx_tileset *ts;
  
    void *image;

    while (layer)
    {
        if (layer->visible)
        {
            if (strcmp(layer->name, "brick") == 0)
            {

                tmx_object_group *objgr = layer->content.objgr;


                SDL_Rect rect;
                set_color(objgr->color);
                tmx_object *head = objgr->head;
                while (head)
                {
                    if (head->visible)
                    {
                        if (head->obj_type == OT_SQUARE)
                        {
                            rect.x = head->x;
                            rect.y = head->y;
                            rect.w = head->width;
                            rect.h = head->height;

                            
                            printf("当前的tank位置x:%d,y:%d\n", player.x,player.y);
                            printf("rect值x:%d,y:%d,w:%d,h:%d\n",rect.x,rect.y,rect.w,rect.h);

                            // if(player.x+player.speed+player.width > rect.x && rect.x + rect.w > player.x && player.y + player.height > rect.y && rect.y + rect.h > player.y)
                            // {
                            //     return 1;
                            // }

                            
                            //todo 朝向右的时候，右上，右下，都在矩形中
                            if (dicrection == SDLK_RIGHT)
                            {
                                if ((rect.x < player.x + player.width + player.speed && rect.y <= player.y && rect.x + rect.w > player.x + player.width + player.speed && rect.y + rect.h > player.y) || (rect.x < player.x + player.width + player.speed && rect.y < player.y + player.height && rect.x + rect.w > player.x + player.width + player.speed && rect.y + rect.h > player.y + player.height))
                                {
                                    return 1;
                                }
                            }
                            else if (dicrection == SDLK_LEFT)
                            {
                                if ((rect.x < player.x - player.speed && rect.y <= player.y && rect.x + rect.w > player.x - player.speed && rect.y + rect.h > player.y) || (rect.x < player.x - player.speed && rect.y < player.y + player.height && rect.x + rect.w > player.x - player.speed && rect.y + rect.h > player.y + player.height))
                                {
                                    return 1;
                                }
                            }
                            else if (dicrection == SDLK_UP)
                            {
                                if ((rect.x <= player.x && rect.y < player.y - player.speed && rect.x + rect.w > player.x && rect.y + rect.h > player.y - player.speed) || (rect.x < player.x + player.width && rect.y < player.y - player.speed && rect.x + rect.w > player.x + player.width && rect.y + rect.h > player.y - player.speed))
                                {
                                    return 1;
                                }
                            }
                            else if(dicrection == SDLK_DOWN)
                            {
                                if ((rect.x < player.x + player.width && rect.y < player.y + player.height + player.speed && rect.x + rect.w > player.x + player.width && rect.y + rect.h > player.y + player.height + player.speed) || (rect.x <= player.x && rect.y < player.y + player.height + player.speed && rect.x + rect.w > player.x && rect.y + rect.h > player.y + player.height + player.speed))
                                {
                                    return 1;
                                }
                            }
                            
                        }
                    }
                    head = head->next;
                }
            }
        }
        layer = layer->next;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *render;

    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        printf("初始化错误");
        return 1;
    }

    if(!(window = SDL_CreateWindow("tank game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL))){
       printf("创建窗口失败");
       return 1;
    }

    if (!(ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)))
    {
        printf("渲染器创建失败");
        return 1;
    }

    // SDL_SetRenderDrawColor(render, 0, 255, 0 ,255);
    // SDL_RenderClear(render);
    // SDL_RenderPresent(render);

    

    //TODO:渲染图片
    SDL_Surface *image;
    image = IMG_Load("tanks.png");
    if(!image){
        printf("Load error:%s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture *texture;
    Player player1,player2;

    SDL_Rect s_rect, d_rect;

    player1.x = 0;
    player1.y = 0;
    player1.width = TANK_WIDTH;
    player1.height = TANK_HEIGHT;
    player1.direction = SDL_FLIP_NONE;
    player1.angle = 0;
    player1.speed = 10;

    //原矩形
    s_rect.x = 0;
    s_rect.y = 0;
    s_rect.w = TANK_WIDTH;
    s_rect.h = TANK_WIDTH;

    //目标矩形
    d_rect.x = player1.x;
    d_rect.y = player1.y;
    d_rect.w = player1.width;
    d_rect.h = player1.height;

    tmx_img_load_func = SDL_tex_loader;
    tmx_img_free_func = (void (*)(void *))SDL_DestroyTexture;

    tmx_map *map = tmx_load("tank.tmx");
    if (map == NULL)
    {
        tmx_perror("Cannot load map");
        return 1;
    }

    SDL_TimerID timer_id;
    unsigned int lastTime = 0, currentTime;
    while(1){
        SDL_Event event;
        int key;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                printf("事件执行了，我要退出了");
                SDL_Quit();
                break;
            case SDL_KEYDOWN:
                key = event.key.keysym.sym;

                if (key == SDLK_RIGHT)
                {
                    player1.angle = 90;
                    int result = checkCollision(player1, map, key);

                    if(result){
                        break;
                    }

                    if (d_rect.x < WIDTH - player1.width)
                    {

                        player1.x += player1.speed;
                        d_rect.x = player1.x;
                        
                    }
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    player1.angle = 270;
                    int result = checkCollision(player1, map, key);

                    if (result)
                    {
                        break;
                    }
                    if (d_rect.x > 0)
                    {
                        player1.x -= player1.speed;
                        d_rect.x = player1.x;
                        
                        
                    }
                }

                if (event.key.keysym.sym == SDLK_UP)
                {

                    player1.angle = 0;
                    int result = checkCollision(player1, map, key);

                    if (result)
                    {
                        break;
                    }
                    if (d_rect.y > 0)
                    {
                        player1.y -= player1.speed;
                        d_rect.y = player1.y;
                        
                    }
                }

                if (event.key.keysym.sym == SDLK_DOWN)
                {

                    player1.angle = 180;
                    int result = checkCollision(player1, map, key);

                    if (result)
                    {
                        break;
                    }
                    if (d_rect.y < HEIGHT - player1.height)
                    {
                        player1.y += player1.speed;
                        d_rect.y = player1.y;
                        
                    }
                }

                //SDL_Quit();
                break;
            default:
                break;
            }
        }
        currentTime = SDL_GetTicks();

        //printf("sdl time %i\r\n", currentTime / 1000);

       

        

        createPlayer(player1, s_rect, d_rect, ren, image);
        //SDL_RenderPresent(ren);


        //map添加精灵
        //map->ly_head->content->

        render_map(map);

        //s_rect.x = 256 * (currentTime * 10 / 1000 % 6);



        
        
        

        SDL_RenderPresent(ren);
    }



    SDL_Quit();

    return 0;

}
