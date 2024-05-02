// [HACKATHON 3-9]
// TODO: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_settings.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.

static ALLEGRO_BITMAP* gameTitle = NULL;
static ALLEGRO_SAMPLE_ID menuBGM;
extern float music_volume;
extern float effect_volume;



static Button btnv1add;
static Button btnv1minus;
static Button btnv2add;
static Button btnv2minus;
static Button btnexit;
float volume0518_1;
float volume0518_2;
char v1[50];
char v2[50];

static void init() {
	btnv1add = button_create(500, 285, 50, 50, "Assets/add.png", "Assets/add2.png");
	btnv1minus = button_create(250, 285, 50, 50, "Assets/minus.png", "Assets/minus2.png");
	btnv2add = button_create(500, 385, 50, 50, "Assets/add.png", "Assets/add2.png");
	btnv2minus = button_create(250, 385, 50, 50, "Assets/minus.png", "Assets/minus2.png");
	btnexit = button_create(730, 20, 50, 50, "Assets/exit.png", "Assets/exit2.png");
	//gameTitle = load_bitmap("Assets/title.png");
	//gameTitleW = al_get_bitmap_width(gameTitle);
	//gameTitleH = al_get_bitmap_height(gameTitle);
	stop_bgm(menuBGM);
	menuBGM = play_bgm(themeMusic, music_volume);
	//game_log("ooo");

}


static void draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2,
		SCREEN_H -500,
		ALLEGRO_ALIGN_CENTER,
		v1
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2,
		SCREEN_H - 400,
		ALLEGRO_ALIGN_CENTER,
		v2
	);
	drawButton(btnv1add);
	drawButton(btnv1minus);
	drawButton(btnv2add);
	drawButton(btnv2minus);
	drawButton(btnexit);
	volume0518_1 = music_volume * 20;
	if ((music_volume * 20) > 100)
	{
		music_volume = 5;
		volume0518_1 = 1;
	}
	volume0518_2 = effect_volume * 20;
	if ((effect_volume * 20) > 100)
	{
		effect_volume = 5;
		volume0518_2 = 1;
	}
	sprintf(&v1, "MUSIC: %2.0f", volume0518_1);
	sprintf(&v2, "EFFECT: %2.0f", volume0518_2);
	/*const float scale = 0.7;
	const float offset_w = (SCREEN_W >> 1) - 0.5 * scale * gameTitleW;
	const float offset_h = (SCREEN_H >> 1) - 0.5 * scale * gameTitleH;
	al_draw_scaled_bitmap(
		gameTitle,
		0, 0,
		gameTitleW, gameTitleH,
		offset_w, offset_h,
		gameTitleW * scale, gameTitleH * scale,
		0
	);*/
}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	//	[HACKATHON 3-7]
	//	TODO: Update button's status(hovered), and utilize the function `pnt_in_rect`, which you just implemented
	//	Uncomment and fill the code below
	btnv1add.hovered = buttonHover(btnv1add, mouse_x, mouse_y);
	btnv2minus.hovered = buttonHover(btnv2minus, mouse_x, mouse_y);
	btnv2add.hovered = buttonHover(btnv2add, mouse_x, mouse_y);
	btnv1minus.hovered = buttonHover(btnv1minus, mouse_x, mouse_y);
	btnexit.hovered = buttonHover(btnexit, mouse_x, mouse_y);
}


//	[HACKATHON 3-8]
//	TODO: When btnSettings clicked, switch to settings scene
//	Uncomment and fill the code below

static void on_mouse_down() {
	game_log("mouse");
	if (btnv1add.hovered) {
		music_volume = music_volume + 0.2;
		game_log("%f\n%f\n", music_volume, effect_volume);
		stop_bgm(menuBGM);
		menuBGM = play_bgm(themeMusic, music_volume);
		play_audio(PACMAN_SOUND, effect_volume);
	}
	else if (btnv2add.hovered) {
		effect_volume = effect_volume + 0.2;
		game_log("%f\n%f\n", music_volume, effect_volume);
		play_audio(PACMAN_SOUND, effect_volume);
	}
	else if (btnv1minus.hovered) {
		music_volume = music_volume - 0.2;
		if (music_volume < 0)
		{
			music_volume = 0;
		}
		game_log("%f\n%f\n", music_volume, effect_volume);
		stop_bgm(menuBGM);
		menuBGM = play_bgm(themeMusic, music_volume);
		play_audio(PACMAN_SOUND, effect_volume);
	}
	else if (btnv2minus.hovered) {
		effect_volume = effect_volume - 0.2;
		if (effect_volume < 0)
		{
			effect_volume = 0;
		}
		game_log("%f\n%f\n", music_volume,effect_volume);
		play_audio(PACMAN_SOUND, effect_volume);
	}
	else if (btnexit.hovered) {
		game_change_scene(scene_menu_create());
	}
		//game_change_scene(scene_settings_create());
}


static void destroy() {
	stop_bgm(menuBGM);
	al_destroy_bitmap(gameTitle);
	//	[HACKATHON 3-10]
	//	TODO: Destroy button images
	//	Uncomment and fill the code below
	//al_destroy_bitmap(gameTitle);
	//al_destroy_bitmap(gameTitle);
}

static void on_key_down(int keycode) {

	switch (keycode) {
	case ALLEGRO_KEY_ENTER:
		game_change_scene(scene_menu_create());
		game_log("hi");
		break;
	default:
		break;
	}
}




// The only function that is shared across files.
Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.draw = &draw;
	scene.initialize = &init;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}