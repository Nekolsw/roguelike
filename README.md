# 2D Roguelike с собственным движком на C++

Курсовой игровой проект в жанре Roguelike с собственным движком на C++ с использованием SFML. в игре
предстоит перемещаться по сгенерированным лабиринтам и сражаться с различными противниками.

## Roguelike
- Генерация процедурных уровней (MazeGenerator)
- Враги и ИИ (AIMovementComponent)
- Характеристики персонажа (CharacterStatsComponent)
- Перманентная смерть

## Engine
2D движок, реализующий:
- Обработку ввода (InputComponent)
- Систему игровых объектов (GameObject) 
- Систему сущностей (Component)
- Отрисовку спрайтов (RenderSystem)
- Отслеживание коллизии (Collision)
- Физику (PhysicsSystem)
- Воспроизведение звуков (SoundComponent)

## Установка и запуск
1. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/Nekolsw/roguelike

2. Откройте Game.sln в Visual Studio

3. Соберите и запустите проект (F5)

## Используемые технологии

- C++17

- SFML 2.5.1

- Visual Studio 2022

## Лицензия

- MIT.