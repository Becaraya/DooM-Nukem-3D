function inWin(x, y) {
    return x >= 0 && x < WIN_SIZEX && y >= 0 && y < WIN_SIZEY;
}

function prontUwon(al, scale, alpha) {
    const yd = al.youWin;
    let win = {
        x: WIN_SIZEX / 2 - (yd.sizeX * scale) / 2,
        y: WIN_SIZEY / 2 - (yd.sizeY * scale) / 2,
    };

    for (let y = 0; y < yd.sizeY * scale; y++) {
        for (let x = 0; x < yd.sizeX * scale; x++) {
            const tmp = yd.pix[Math.floor(y / scale) * yd.sizeX + Math.floor(x / scale)];
            if (inWin(x + win.x, y + win.y) && tmp !== 0xffff) {
                al.pix[(y + win.y) * WIN_SIZEX + x + win.x] = alphaPix(tmp, alpha);
            }
        }
    }
}

function won(al) {
    let stat = 0;
    stat += al.dtime;
    if (stat === 1000000) stat = 1000001;

    const scale = 20 - 18 * (stat / 3000000.0);
    pixToPix(al.pixDead, al.pix, (10000000 - stat) / 10000000.0);

    if (stat < 3000000) {
        prontUwon(al, scale, stat / 3000000.0);
    } else {
        prontUwon(al, 2, 1);
    }

    refresh(al);
}

function alphaPix(color, alpha) {
    // Simulated alpha blending
    return color;
}

function pixToPix(src, dest, alpha) {
    // Simulated pixel blending
}