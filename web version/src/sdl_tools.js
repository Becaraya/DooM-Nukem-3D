function addColor(color) {
    return {
        a: (color >> 24) & 0xFF,
        r: (color >> 16) & 0xFF,
        g: (color >> 8) & 0xFF,
        b: color & 0xFF,
    };
}

function getRect(x, y) {
    return { x, y, w: 0, h: 0 };
}