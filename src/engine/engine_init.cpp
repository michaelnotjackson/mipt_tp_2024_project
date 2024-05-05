#include <engine/assets_storage.h>
#include <engine/engine_init.h>

bool EngineInitTextures() {
  if (!assets_manager.LoadTexture(
          "assets/Tiny "
          "Swords/Factions/Knights/Troops/Warrior/Blue/Warrior_Blue.png",
          "textures/warriors/warrior_blue")) {
    return false;
  }

  if (!assets_manager.LoadTexture(
          "assets/Tiny "
          "Swords/Factions/Knights/Troops/Warrior/Red/Warrior_Red.png",
          "textures/warriors/warrior_red")) {
    return false;
  }

  if (!assets_manager.LoadTexture(
          "assets/Tiny Swords/Terrain/Ground/Tilemap_Flat.png",
          "textures/terrain/grass")) {
    return false;
  }

  if (!assets_manager.LoadTexture(
          "assets/Tiny Swords/Terrain/Ground/Tilemap_Flat_Hovered.png",
          "textures/terrain/grass_hovered")) {
    return false;
  }

  if (!assets_manager.LoadTexture(
          "assets/Tiny Swords/Terrain/Ground/Tilemap_Elevation.png",
          "textures/terrain/wall")) {
    return false;
  }

  if (!assets_manager.LoadTexture(
          "assets/Tiny Swords/Terrain/Ground/Tilemap_Elevation_Hovered.png",
          "textures/terrain/wall_hovered")) {
    return false;
  }
  if (!assets_manager.LoadTexture(
    "assets/Tiny Swords/Factions/Knights/Troops/Dead/Dead.png",
    "textures/warriors/death"
  ))

  return true;
}

bool EngineInitAnimations() {
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(assets_manager.GetTexture("textures/terrain/grass"),
                         SDL_Rect{64, 64, 64, 64}, 1, SDL_GetTicks64(), 1, 1),
          "animations/terrain/grass")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/terrain/grass_hovered"),
              SDL_Rect{64, 64, 64, 64}, 1, SDL_GetTicks64(), 1, 1),
          "animations/terrain/grass_hovered")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(assets_manager.GetTexture("textures/terrain/wall"),
                         SDL_Rect{64, 64, 64, 64}, 1, SDL_GetTicks64(), 1, 1),
          "animations/terrain/wall")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/terrain/wall_hovered"),
              SDL_Rect{64, 64, 64, 64}, 1, SDL_GetTicks64(), 1, 1),
          "animations/terrain/wall_hovered")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(assets_manager.GetTexture("textures/terrain/grass"),
                         SDL_Rect{384, 64, 64, 64}, 1, SDL_GetTicks64(), 1, 1),
          "animations/terrain/sand")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/terrain/grass_hovered"),
              SDL_Rect{384, 64, 64, 64}, 1, SDL_GetTicks64(), 1, 1),
          "animations/terrain/sand_hovered")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 0, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/idle")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/move")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 2, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/attack1_right")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 3, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/attack2_right")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 4, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/attack1_down")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 5, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/attack2_down")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 6, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/attack1_up")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 0, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/attack2_up")) {
    return false;
  }

  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_red"),
              SDL_Rect{0, 0, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_red/idle")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_red"),
              SDL_Rect{0, 192, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_red/move")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_red"),
              SDL_Rect{0, 192 * 2, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_red/attack1_right")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_red"),
              SDL_Rect{0, 192 * 3, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_red/attack2_right")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_red"),
              SDL_Rect{0, 192 * 4, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_red/attack1_down")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_red"),
              SDL_Rect{0, 192 * 5, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_red/attack2_down")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_red"),
              SDL_Rect{0, 192 * 6, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_red/attack1_up")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_red"),
              SDL_Rect{0, 0, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_red/attack2_up")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
    CBaseAnimation(
      assets_manager.GetTexture("textures/warriors/death"),
      SDL_Rect{0, 0, 128, 128}, 7, SDL_GetTicks64(), 125, 0.6),
      "animations/warriors/death"
  )) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
    CBaseAnimation(
      assets_manager.GetTexture("textures/warriors/death"),
      SDL_Rect{0, 128, 128, 128}, 7, SDL_GetTicks64(), 120, 0.6),
      "animations/warriors/skull_disappear"
  )) {
    return false;
  }

  return true;
}