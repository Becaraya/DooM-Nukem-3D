function pimpCross(al) {
    let i = Math.floor(WIN_SIZEY / 2) - 12;

    while (i <= Math.floor(WIN_SIZEY / 2) + 12) {
        if (i >= Math.floor(WIN_SIZEY / 2) - 2 && i <= Math.floor(WIN_SIZEY / 2) + 2) {
            i++;
            continue;
        }
        al.pix[i * WIN_SIZEX + Math.floor(WIN_SIZEX / 2) - 1] = 0x000000;
        al.pix[i * WIN_SIZEX + Math.floor(WIN_SIZEX / 2)] = 0x52fc03;
        al.pix[i * WIN_SIZEX + Math.floor(WIN_SIZEX / 2) + 1] = 0x000000;
        i++;
    }

    i = Math.floor(WIN_SIZEX / 2) - 12;

    while (i <= Math.floor(WIN_SIZEX / 2) + 12) {
        if (i >= Math.floor(WIN_SIZEX / 2) - 2 && i <= Math.floor(WIN_SIZEX / 2) + 2) {
            i++;
            continue;
        }
        al.pix[WIN_SIZEX * (Math.floor(WIN_SIZEY / 2) - 1) + i] = 0x000000;
        al.pix[WIN_SIZEX * Math.floor(WIN_SIZEY / 2) + i] = 0x52fc03;
        al.pix[WIN_SIZEX * (Math.floor(WIN_SIZEY / 2) + 1) + i] = 0x000000;
        i++;
    }
}