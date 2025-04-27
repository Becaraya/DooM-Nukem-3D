function mapDraw(al, a, b) {
    b.y = a.y + 5;
    b.x = a.x + 5;

    for (let y = a.y + 1; y < b.y; y++) {
        for (let x = a.x + 1; x < b.x; x++) {
            al.pix[x + y * WIN_SIZEX] = 0x52fc03;
        }
    }

    a.x = al.play.posx * 10 + (WIN_SIZEX + WIN_SIZEX / 2);
    a.y = -al.play.posy * 10 + (WIN_SIZEY - WIN_SIZEY / 2);
    b.x = a.x + al.sin[al.play.dir] * 10;
    b.y = a.y - al.cos[al.play.dir] * 10;

    drawLine(a, b, al.sdlSurf, 0xFFFFFF);

    al.pix[a.x + a.y * WIN_SIZEX] = 0xff00ff;
    al.pix[a.x + 1 + a.y * WIN_SIZEX] = 0xff00ff;
    al.pix[a.x + (a.y + 1) * WIN_SIZEX] = 0xff00ff;
    al.pix[a.x + 1 + (a.y + 1) * WIN_SIZEX] = 0xff00ff;
}

function drawMap(al) {
    let a = {};
    let b = {};

    for (let sec = 1; sec <= al.nbSec; sec++) {
        for (let wal = 0; wal < al.sec[sec].nbWal; wal++) {
            a.x = al.sec[sec].walls[wal].x1 * 10 + (WIN_SIZEX + WIN_SIZEX / 2);
            a.y = -al.sec[sec].walls[wal].y1 * 10 + (WIN_SIZEY - WIN_SIZEY / 2);
            b.x = al.sec[sec].walls[wal].x2 * 10 + (WIN_SIZEX + WIN_SIZEX / 2);
            b.y = -al.sec[sec].walls[wal].y2 * 10 + (WIN_SIZEY - WIN_SIZEY / 2);

            drawLine(a, b, al.sdlSurf, 0xBF55EC);
        }
    }

    mapDraw(al, a, b);
}

function drawLine(a, b, surface, color) {
    // Simulated line drawing
}