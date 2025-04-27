function freeRect(rect) {
    rect = null;
}

function freeTextHeiNum(al) {
    al.text.ceHeiNum.str = null;
    al.text.ceHeiNum.where = null;
    al.text.flHeiNum.str = null;
    al.text.flHeiNum.where = null;
}

function freeTextNextNext(al) {
    al.text.setPlayer.str = null;
    al.text.setPlayer.where = null;
    al.text.life.str = null;
    al.text.life.where = null;
    al.text.power.str = null;
    al.text.power.where = null;
    al.text.weapon.str = null;
    al.text.weapon.where = null;
    al.text.size.str = null;
    al.text.size.where = null;
    al.text.mass.str = null;
    al.text.mass.where = null;
    al.text.gravity.str = null;
    al.text.gravity.where = null;
    al.text.isDoor.str = null;
    al.text.isDoor.where = null;
}

function freeTextNext(al) {
    al.text.sector.str = null;
    al.text.sector.where = null;
    al.text.tools.str = null;
    al.text.tools.where = null;
    al.text.setSpawn.str = null;
    al.text.setSpawn.where = null;
    al.text.setEnd.str = null;
    al.text.setEnd.where = null;
    al.text.setBadPig.str = null;
    al.text.setBadPig.where = null;
    al.text.wallTex.str = null;
    al.text.wallTex.where = null;
    al.text.flTex.str = null;
    al.text.flTex.where = null;
    al.text.ceTex.str = null;
    al.text.ceTex.where = null;
    al.text.flHei.str = null;
    al.text.flHei.where = null;
    al.text.ceHei.str = null;
    al.text.ceHei.where = null;
    al.text.draw.str = null;
    al.text.draw.where = null;
    al.text.link.str = null;
    al.text.link.where = null;
}

function freeText(al) {
    al.text.genMap.str = null;
    al.text.genMap.where = null;
    al.text.sectIndex.str = null;
    al.text.sectIndex.where = null;
    al.text.wallIndex.str = null;
    al.text.wallIndex.where = null;
    al.text.settings.str = null;
    al.text.settings.where = null;
    al.text.wall.str = null;
    al.text.wall.where = null;
    al.text.resetMap.str = null;
    al.text.resetMap.where = null;
    al.text.resetPlayer.str = null;
    al.text.resetPlayer.where = null;

    freeTextHeiNum(al);
    freeTextNext(al);
    freeTextNextNext(al);
}