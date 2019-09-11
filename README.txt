Documentation file for Doom-nukem project by becaraya and pitriche

The binary takes a file witch content follows this pattern:
(fields are indicated as 'size in byte - field name')
(name:{} indicates a repeating field)

4 - total size
2 - number of sectors
sectors:
{
	2 - floor height
	1 - floor texture index (0 for invisible floor)
	2 - ceiling height
	1 - ceiling texture index (0 for invisible roof)
	2 - number of walls
	walls:
	{
		2 - x1
		2 - y1
		2 - x2
		2 - y2
		2 - sector index (0 if wall, index of linked sector if portal)
		1 - wall texture (0 if invisible)
		1 - bottom texture (0 if invisible)
		1 - top texture (0 if invisible)
	}
}
1 - number of textures
textures:
{
	2 - texture size x
	2 - texture size y
	pixels:
	{
		1 - transparency (0 for opaque and !=0 for transparent)
		1 - red
		1 - green
		1 - blue
	}
}

notes:
Both textures and sectors tab must start at 1, for utility purposes (sorry).
Pixels are in y lines of x pixels.
The first step of rendering will be to fill screen with the skybox, witch will
be in the texture tab at index 0.