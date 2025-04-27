function initTextEdit(al) {
    setText(al.text.sectIndex, "WHO", getRect(25, 20), addColor(TEXT_EDITOR));
    setText(al.text.wallIndex, "WHO WALL", getRect(25, 58), addColor(TEXT_EDITOR));
    setText(al.text.difEz, "Difficulty : Easy", getRect(70, 135), addColor(TEXT_EDITOR));
    setText(al.text.difHa, "Difficulty : Hard", getRect(70, 135), addColor(TEXT_EDITOR));
    setText(al.text.cancel, "CANCEL", getRect(600, 20), addColor(TEXT_EDITOR));
    setText(al.text.settings, "Settings", getRect(25, 200), addColor(TEXT_EDITOR));
    setText(al.text.sector, "Sector", getRect(70, 250), addColor(TEXT_EDITOR));
    setText(al.text.flTex, "Floor Texture", getRect(70, 330), addColor(TEXT_EDITOR));
    setText(al.text.flHei, "Floor Height", getRect(70, 410), addColor(TEXT_EDITOR));
    setText(al.text.ceTex, "Ceiling Texture", getRect(300, 330), addColor(TEXT_EDITOR));
    initTextEditNext(al);
}

function initTextEditNext(al) {
    setText(al.text.ceHei, "Ceiling Height", getRect(300, 410), addColor(TEXT_EDITOR));
    setText(al.text.ceHeiNum, "Ceiling Hei Num", getRect(570, 410), addColor(TEXT_EDITOR));
    setText(al.text.flHeiNum, "Floor Hei Num", getRect(570, 410), addColor(TEXT_EDITOR));
    setText(al.text.wall, "Wall", getRect(300, 250), addColor(TEXT_EDITOR));
    setText(al.text.wallTex, "Wall Texture", getRect(70, 330), addColor(TEXT_EDITOR));
    setText(al.text.tools, "Tools", getRect(25, 500), addColor(TEXT_EDITOR));
    setText(al.text.setSpawn, "Set Spawn", getRect(70, 550), addColor(TEXT_EDITOR));
    setText(al.text.setEnd, "Set End", getRect(70, 550), addColor(TEXT_EDITOR));
    setText(al.text.setBadPig, "Set Goret", getRect(300, 550), addColor(TEXT_EDITOR));
    setText(al.text.draw, "Draw", getRect(520, 550), addColor(TEXT_EDITOR));
    setText(al.text.link, "Sector Link", getRect(70, 615), addColor(TEXT_EDITOR));
    setText(al.text.genMap, "GENERATION MAP", getRect(295, 665), addColor(TEXT_EDITOR));
    initTextEditNextNext(al);
}

function initTextEditNextNext(al) {
    setText(al.text.setPlayer, "Player", getRect(520, 250), addColor(TEXT_EDITOR));
    setText(al.text.life, "Life", getRect(70, 330), addColor(TEXT_EDITOR));
    setText(al.text.power, "Power", getRect(300, 330), addColor(TEXT_EDITOR));
    setText(al.text.weapon, "Weapon", getRect(520, 330), addColor(TEXT_EDITOR));
    setText(al.text.size, "Size", getRect(70, 410), addColor(TEXT_EDITOR));
    setText(al.text.mass, "Mass", getRect(300, 410), addColor(TEXT_EDITOR));
    setText(al.text.playerValue, "Player num", getRect(570, 410), addColor(TEXT_EDITOR));
    setText(al.text.resetMap, "Reset Map", getRect(300, 135), addColor(TEXT_EDITOR));
    setText(al.text.resetPlayer, "Reset Player", getRect(515, 135), addColor(TEXT_EDITOR));
    setText(al.text.gravity, "Gravity", getRect(300, 615), addColor(TEXT_EDITOR));
    setText(al.text.gNum, "9.81", getRect(570, 625), addColor(TEXT_EDITOR));
    setText(al.text.isDoor, "Is Door", getRect(520, 330), addColor(TEXT_EDITOR));
}

function setText(textObj, text, rect, color) {
    textObj.str = text;
    textObj.rect = rect;
    textObj.color = color;
}

function getRect(x, y) {
    return { x, y, w: 0, h: 0 };
}

function addColor(color) {
    return { r: (color >> 16) & 0xFF, g: (color >> 8) & 0xFF, b: color & 0xFF, a: (color >> 24) & 0xFF };
}