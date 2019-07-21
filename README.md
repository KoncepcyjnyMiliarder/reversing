# My old game cheats sources

The sources have been written AGES ago (around 2010), back when I really enjoyed disassembling and reverse engineering computer games, to find out every detail of how they work under the hood.
Luckily some codes did survive till today, these definitely got their... charm :)

## Lineage2 fishbot

Designed for interlude version, works by redirecting several callbacks (ones responsible for fishing events) from the game's network dispatch table to my hooks.

## Unreal aimbot

Aimbot for the old UT99 fps, working only in singleplayer

## Minesweeper solver

Got full access to memory representing the board, but tries to play fair (makes only choices that can be deducted on what potential user sees).
In case of lack of obvious moves, it uses it's illegal knowledge of board and then attempts to make new move legally.

## ThePilotOfTheService

Lineage2 Interlude/H5 bot. Casts skills, uses items, reproduces the world based on incoming gameserver packets, and most importantly... grinds for hours :)