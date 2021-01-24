#include <stdio.h>
#include <tmx.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "index.h"

const int WIDTH = 600;
const int HEIGHT = 600;

const int TANK_WIDTH = 40;
const int TANK_HEIGHT = 40;

const int UP = 270;
const int RIGHT = 0;
const int DOWN = 90;
const int LEFT = 180;


typedef struct{
    float x,y;
    int width,height;
    int direction;
    int angle;
    SDL_Texture *texture;
}Player;

void createPlayer(Player player, SDL_Rect s_rect, SDL_Rect d_rect, SDL_Renderer *render, SDL_Surface *image)
{
    SDL_RenderClear(render);
    player.texture = SDL_CreateTextureFromSurface(render, image);

    SDL_RenderCopyEx(render, player.texture, &s_rect, &d_rect, player.angle, NULL, player.direction);

    SDL_DestroyTexture(player.texture);
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
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                printf("事件执行了，我要退出了");
                SDL_Quit();
                break;
            case SDL_KEYDOWN:
                
                if (event.key.keysym.sym == SDLK_RIGHT){
                    if (d_rect.x < WIDTH - player1.width){
                        d_rect.x += 10;
                        player1.angle = 90;
                    }
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    if (d_rect.x > 0)
                    {
                        d_rect.x -= 10;
                        player1.angle = 270;
                        
                    }
                }

                if (event.key.keysym.sym == SDLK_UP)
                {
                    if (d_rect.y > 0)
                    {
                        d_rect.y -= 10;
                        player1.angle = 0;
                    }
                }

                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    if (d_rect.y < HEIGHT - player1.height)
                    {
                        d_rect.y += 10;
                        player1.angle = 180;
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