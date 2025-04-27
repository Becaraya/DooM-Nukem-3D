function shoot(al) {
    const tmp = 60000;

    if (al.fireAnim < 100000) al.f = al.weapon[1];
    else if (al.fireAnim < 100000 + 1 * tmp) al.f = al.weapon[2];
    else if (al.fireAnim < 100000 + 2 * tmp) al.f = al.weapon[3];
    else if (al.fireAnim < 100000 + 3 * tmp) al.f = al.weapon[4];
    else if (al.fireAnim < 100000 + 5 * tmp) al.f = al.weapon[5];
    else if (al.fireAnim < 100000 + 7 * tmp) al.f = al.weapon[6];
    else if (al.fireAnim < 100000 + 9 * tmp) al.f = al.weapon[5];
    else if (al.fireAnim < 100000 + 11 * tmp) al.f = al.weapon[4];
    else if (al.fireAnim < 100000 + 13 * tmp) al.f = al.weapon[3];
    else al.f = al.weapon[0];
}

function drawWeapon(al) {
    const scale = 2.5;
    const tex = al.f;
    const win = {
        x: WIN_SIZEX / 2 + (tex.sizeX * scale) / 2 - 100,
        y: WIN_SIZEY - tex.sizeY * scale,
    };

    for (let y = 0; y < tex.sizeY * scale; y++) {
        for (let x = 0; x < tex.sizeX * scale; x++) {
            const tmp = tex.pix[Math.floor(y / scale) * tex.sizeX + Math.floor(x / scale)];
            if (tmp !== 41704) {
                al.pix[(y + win.y) * WIN_SIZEX + x + win.x] = tmp;
            }
        }
    }
}

function drawHud(al) {
    let a = al.play.alive;

    while (a > 0) {
        for (let y = 0; y < al.h.sizeY; y++) {
            for (let x = 0; x < al.h.sizeX; x++) {
                const pix = al.h.pix[x + (al.h.sizeY - y - 1) * al.h.sizeX];
                if (pix) {
                    al.pix[x + 45 * a + (y + 20) * WIN_SIZEX] = pix;
                }
            }
        }
        a--;
    }
}

function renderTwo(al) {
    pimpCross(al);
    drawHud(al);
    shoot(al);
    drawWeapon(al);
    console.log("fps:", Math.floor(1000000 / al.dtime));
    refresh(al);
}

function render(al) {
    const ray = { nbHits: 0 };
    al.wallScale = 0.1624 * D_2PI / al.fov;

    al.pix.fill(0);

    for (let x = 0; x < WIN_SIZEX; x++) {
        ray.nbHits = 0;
        ray.x = x;
        const angle = (Math.atan(al.fov * (x - WIN_SIZEX / 2) / WIN_SIZEX) / M_2PI) * D_2PI + al.play.dir;
        castRay(al, angle & D_2PIM, ray);
        column(al, ray);
    }

    if (al.k.m) drawMap(al);
    renderTwo(al);
}