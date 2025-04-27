class TextureGroup {
    constructor(sizeX, sizeY, nbTex, orientations) {
        this.sizeX = sizeX; // Largeur du groupe de textures
        this.sizeY = sizeY; // Hauteur du groupe de textures
        this.nbTex = nbTex; // Nombre de textures
        this.orientations = orientations; // Tableau des orientations, chaque orientation contient des textures
    }

    writeToBuffer() {
        // Crée un tableau de bytes pour représenter le groupe de textures
        const bufferSize = 12 + this.orientations.length * this.nbTex * this.sizeX * this.sizeY * 4;
        const buffer = new ArrayBuffer(bufferSize);
        const view = new DataView(buffer);

        // Écrit la largeur, la hauteur et le nombre de textures dans les 12 premiers octets
        view.setUint32(0, this.sizeX, true);
        view.setUint32(4, this.sizeY, true);
        view.setUint32(8, this.nbTex, true);

        let offset = 12;
        this.orientations.forEach(orientation => {
            orientation.forEach(texture => {
                texture.forEach((pixel, index) => {
                    view.setUint32(offset + index * 4, pixel, true);
                });
                offset += this.sizeX * this.sizeY * 4;
            });
        });

        return buffer;
    }
}

class TextureGroupManager {
    constructor() {
        this.textureGroups = []; // Liste des groupes de textures
    }

    addTextureGroup(textureGroup) {
        this.textureGroups.push(textureGroup);
    }

    writeAllToBuffer() {
        // Crée un tableau de bytes pour représenter tous les groupes de textures
        const headerSize = 2;
        const totalSize = this.textureGroups.reduce(
            (sum, group) => sum + (12 + group.orientations.length * group.nbTex * group.sizeX * group.sizeY * 4),
            headerSize
        );
        const buffer = new ArrayBuffer(totalSize);
        const view = new DataView(buffer);

        // Écrit le nombre de groupes de textures dans les 2 premiers octets
        view.setUint16(0, this.textureGroups.length, true);

        let offset = headerSize;
        this.textureGroups.forEach(group => {
            const groupBuffer = group.writeToBuffer();
            new Uint8Array(buffer).set(new Uint8Array(groupBuffer), offset);
            offset += groupBuffer.byteLength;
        });

        return buffer;
    }
}

// Exemple d'utilisation
const orientation1 = [
    new Array(64 * 64).fill(0xFF0000), // Texture rouge
    new Array(64 * 64).fill(0x00FF00), // Texture verte
];
const orientation2 = [
    new Array(64 * 64).fill(0x0000FF), // Texture bleue
    new Array(64 * 64).fill(0xFFFF00), // Texture jaune
];

const textureGroup = new TextureGroup(64, 64, 2, [orientation1, orientation2]);
//manager viens de hms_encoder_tex.js
manager.addTextureGroup(textureGroup);

const buffer = manager.writeAllToBuffer();
console.log(buffer); // Vous pouvez utiliser ce buffer pour des opérations supplémentaires