function loadHud(al) {
    al.h = loadBmpToTexture("ressources/HUD/heart.bmp", 46, 41);
    al.weapon = [
        loadBmpToTexture("ressources/weapon/shotgun1.bmp", 102, 85),
        loadBmpToTexture("ressources/weapon/shotgun_fire.bmp", 102, 105),
        loadBmpToTexture("ressources/weapon/shotgun_fire2.bmp", 118, 150),
        loadBmpToTexture("ressources/weapon/shotgun2.bmp", 118, 131),
        loadBmpToTexture("ressources/weapon/shotgun3.bmp", 160, 140),
        loadBmpToTexture("ressources/weapon/shotgun4.bmp", 160, 176),
        loadBmpToTexture("ressources/weapon/shotgun5.bmp", 133, 172),
    ];
    al.f = al.weapon[0];
}

function imNotGoingToHellForThis(al, ipix) {
    for (let i = 0; i < 8; i++) {
        if (al.mobDeath[i].pixels[ipix] !== 0xffff) {
            al.mobDeath[i].pixels[ipix] |= 0xff000000;
        }
    }
}

function loadDeath(al) {
    al.youDied = loadBmpToTexture("ressources/you_died.bmp", 518, 93);
    al.youWin = loadBmpToTexture("ressources/you_win.bmp", 518, 93);
    al.mobDeath = [];
    for (let i = 0; i < 8; i++) {
        al.mobDeath.push(loadBmpToTexture(`ressources/mob_death/${i}.bmp`, 512, 512));
    }
    if (al.mobDeath.every(tex => tex.width === 512)) {
        for (let i = 0; i < 262144; i++) {
            imNotGoingToHellForThis(al, i);
        }
    }
}

function loadGoret(tgp) {
    tgp.nbTex = 4;
    tgp.sizeX = 512;
    tgp.sizeY = 512;
    tgp.orientations = [];
    for (let or = 0; or < 8; or++) {
        const orientation = [];
        for (let i = 0; i < tgp.nbTex; i++) {
            const path = `ressources/sprite/or${or + 1}/${i + 1}.bmp`;
            orientation.push(loadBmpToPixels(path, 512, 512));
        }
        tgp.orientations.push(orientation);
    }
}

function initTextures(al) {
    loadHud(al);
    loadDeath(al);

    if (!al.textures) {
        al.nbTex = 3;
        al.textures = [
            loadBmpToTexture("ressources/skybox.bmp", 32, 32),
            loadBmpToTexture("ressources/wall_tex.bmp", 800, 800),
            loadBmpToTexture("ressources/floor_tex.bmp", 950, 950),
            loadBmpToTexture("ressources/ceiling_tex.bmp", 512, 512),
        ];
        if (al.textures[0].pixels[0] !== 0xffff00ff) {
            for (let i = 0; i < 32 * 32; i++) {
                al.textures[0].pixels[i] |= 0xff000000;
            }
        }
    }

    if (!al.textureGroups) {
        al.nbTexGp = 1;
        al.textureGroups = [{}];
        loadGoret(al.textureGroups[0]);
    }
}

function loadBmpToTexture(path, width, height) {
    return { path, width, height, pixels: new Uint32Array(width * height) };
}

function loadBmpToPixels(path, width, height) {
    return new Uint32Array(width * height); // Simulated pixel data
}