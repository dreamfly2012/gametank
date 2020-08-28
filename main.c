#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int WIDTH = 960;
const int HEIGHT = 640;

const int UP = 270;
const int RIGHT = 0;
const int DOWN = 90;
const int LEFT = 180;


typedef struct{
    float x,y;
    int width,height;
    int direction;
    SDL_Texture *texture;
}Player;

void createPlayer(Player player, SDL_Rect s_rect, SDL_Rect d_rect, SDL_Renderer *render, SDL_Surface *image)
{
    player.texture = SDL_CreateTextureFromSurface(render, image);

    SDL_RenderCopyEx(render, player.texture, &s_rect, &d_rect, player.direction, NULL, SDL_FLIP_NONE);

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

    if(!(render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE))){
        printf("渲染器创建失败");
        return 1;
    }

    

    SDL_SetRenderDrawColor(render, 0, 255, 0 ,255);
    SDL_RenderClear(render);
    SDL_RenderPresent(render);

    

    //TODO:渲染图片
    SDL_Surface *image;
    image = IMG_Load("sprite.webp");
    if(!image){
        printf("Load error:%s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture *texture;
    Player player1,player2;

    SDL_Rect s_rect, d_rect;

    player1.x = 0;
    player1.y = 0;
    player1.width = 256;
    player1.height = 256;
    player1.direction = RIGHT;

    s_rect.x = 256;
    s_rect.y = 0;
    s_rect.w = 256;
    s_rect.h = 256;

    d_rect.x = player1.x;
    d_rect.y = player1.y;
    d_rect.w = player1.width;
    d_rect.h = player1.height;

 
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
             printf("key is pressed");
             SDL_Quit();
             break;
            default:
                break;
            }
        }
        currentTime = SDL_GetTicks();

        printf("sdl time %i\r\n", currentTime / 1000);

       
        s_rect.x = 256 * (currentTime*10 / 1000 % 6);
        

           
        SDL_RenderClear(render);
        createPlayer(player1, s_rect, d_rect, render, image);

        SDL_RenderPresent(render);
    }



    SDL_Quit();

    return 0;

}