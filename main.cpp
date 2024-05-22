#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "definition.h"
#include "in.h"
#include "graphics.h"
#include "game.h"
#include <ctime>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(0));
    Graphics graphics;
    graphics.init();
    Input input;
    input.init();
    Game game;
    game.init(graphics);

    bool unmute = true;
    bool guide = false;
    bool mouseHover1 = false;
    bool mouseHover2 = false;
    bool mouseHover3 = false;
    SDL_Rect muteButton = {20, 20, 50, 49};
    SDL_Rect playButton = {450 , 350, 120, 123};
    SDL_Rect guideButton = {970, 350, 120, 115};
    SDL_Rect quitButton = {700, 350, 120, 120};
    SDL_Event e;
    while(isGameRunning)
	{
	    if(!playgame){
            game.drawplay(graphics);
            if(unmute){
                game.drawunmute(graphics); game.playgmusic();
            }
            else{
                game.drawmute(graphics);
                Mix_HaltMusic();
            }
            if(mouseHover1){game.drawplaybutton2(graphics);} else game.drawplaybutton1(graphics);
            if(mouseHover2){game.drawquitbutton2(graphics);} else game.drawquitbutton1(graphics);
            if(mouseHover3){game.drawguide1button(graphics);} else game.drawguidebutton(graphics);
            if(guide){game.drawhuongdan(graphics);}
            graphics.presentScene();
            while(SDL_PollEvent(&e)){
                if(e.type == SDL_QUIT) {SDL_Quit(); return 0;}
                if(e.type == SDL_MOUSEMOTION){
                    int mouseX = e.motion.x; int mouseY = e.motion.y;
                    if (mouseX >= playButton.x && mouseX <= (playButton.x + playButton.w) &&
                        mouseY >= playButton.y && mouseY <= (playButton.y + playButton.h)){
                        mouseHover1 = true;
                    }
                    else
                    {
                        mouseHover1 = false;
                    }
                    if (mouseX >= quitButton.x && mouseX <= (quitButton.x + quitButton.w) &&
                        mouseY >= quitButton.y && mouseY <= (quitButton.y + quitButton.h))
                    {
                        mouseHover2 = true;
                    }
                    else
                    {
                        mouseHover2 = false;
                    }
                    if (mouseX >= guideButton.x && mouseX <= (guideButton.x + guideButton.w) &&
                        mouseY >= guideButton.y && mouseY <= (guideButton.y + guideButton.h))
                    {
                        mouseHover3 = true;
                    }
                    else
                    {
                        mouseHover3 = false;
                    }
                }

                if(e.type == SDL_MOUSEBUTTONDOWN){
                    int mouseX = e.button.x; int mouseY = e.button.y;
                    if (mouseX >= muteButton.x && mouseX <= (muteButton.x + muteButton.w) &&
                        mouseY >= muteButton.y && mouseY <= (muteButton.y + muteButton.h))
                    {
                        unmute = !unmute;
                    }
                    if (mouseX >= playButton.x && mouseX <= (playButton.x + playButton.w) &&
                        mouseY >= playButton.y && mouseY <= (playButton.y + playButton.h))
                    {
                        playgame = true;
                    }
                    if (mouseX >= quitButton.x && mouseX <= (quitButton.x + quitButton.w) &&
                        mouseY >= quitButton.y && mouseY <= (quitButton.y + quitButton.h))
                    {
                        SDL_Quit();
                        return 0;
                    }

                    if (mouseX >= guideButton.x && mouseX <= (guideButton.x + guideButton.w) &&
                        mouseY >= guideButton.y && mouseY <= (guideButton.y + guideButton.h))
                    {
                        guide = true;
                    }

                }

                if(e.type == SDL_KEYDOWN){
                    if(e.key.keysym.sym == SDLK_ESCAPE){
                        guide = false;
                    }
                }
            }
	    }

	    if(playgame)
        {
            game.cleanmenu();
            graphics.prepareScene();
            input.get();
            game.doLogic(input.keyboard);
            game.draw(graphics);
            graphics.presentScene();
            SDL_Delay(10);
        }
	}
	waitForKeyPress();
	graphics.quit();
    return 0;
}





