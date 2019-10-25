Documentation file for Doom-nukem project by becaraya and pitriche

The binary takes a file witch content follows this pattern:
(fields are indicated as 'size in byte - field name')
(name:{} indicates a repeating field and () is a commentary)


(16 header)
4  0- number of sectors
4  4- player starting sector
4  8- player starting x
4 12- player starting y
sectors (16 header + nb_wall * 32 walls):
{
	4  0- floor height
	4  4- ceiling height
	2  8- floor texture index (0 for invisible floor)
	2 10- ceiling texture index (0 for invisible roof)
	4 12- number of walls
	walls (32):
	{
		4  0- x1
		4  4- y1
		4  8- x2
		4 12- y2
		2 16- wall texture (0 if invisible)
		2 18- bottom texture (0 if invisible)
		2 20- top texture (0 if invisible)
		2 22- is crossable (0 if solid, !0 if crossable)
		4 24- sector index (0 if wall, index of linked sector if portal)
		4 26- pad
	}
}
(16 header)
2  0- number of textures
14 2- pad
textures(16 header + x * y * 4 pixels):
{
	4 0- texture size x
	4 4- texture size y
	8 8- pad
	pixels:
	{
		1 0- blue
		1 1- green
		1 2- red
		1 4- transparency (0 for opaque and !=0 for transparent)
	}
}

notes:
Both textures and sectors tab must start at 1, for utility purposes (sorry).
Pixels are in y lines of x pixels.
The first step of rendering will be to fill screen with the skybox, witch will
be in the texture tab at index 0. nb_tex doesn't count skybox in
Coordonates and floor heights are in centimeters
