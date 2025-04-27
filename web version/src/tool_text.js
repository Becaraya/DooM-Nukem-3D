function initTtf(al) {
    if (!ttfInit()) {
        al.ttfSt = 1;
    } else {
        yeet(al);
    }

    al.font = openFont("/Library/Fonts/Arial.ttf", 20);
    if (!al.font) {
        yeet(al);
    }
}

function setText(text, str, coo, clr) {
    text.str = str;
    text.where = { x: coo.x, y: coo.y };
    text.clr = { ...clr };
    return 0;
}

function titleCmp(al, text) {
    if (
        (text.str === al.text.settings.str && coCmp(text.where, al.text.settings.where)) ||
        (text.str === al.text.cancel.str && coCmp(text.where, al.text.cancel.where)) ||
        (text.str === al.text.tools.str && coCmp(text.where, al.text.tools.where))
    ) {
        return 1;
    }
    return 0;
}

function ttfInit() {
    // Simulated TTF initialization
    return true;
}

function openFont(path, size) {
    // Simulated font opening
    return { path, size };
}

function coCmp(rect1, rect2) {
    return rect1.x === rect2.x && rect1.y === rect2.y;
}