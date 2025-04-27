class TextureGroup {
    constructor(sizeX, sizeY, nbTex, orientations) {
        this.sizeX = sizeX;
        this.sizeY = sizeY;
        this.nbTex = nbTex;
        this.orientations = orientations; // Array of orientations, each containing pixel data
    }

    static parse(buffer) {
        const view = new DataView(buffer);
        const sizeX = view.getUint32(0, true);
        const sizeY = view.getUint32(4, true);
        const nbTex = view.getUint32(8, true);

        const orientations = [];
        let offset = 12;
        for (let or = 0; or < 8; or++) {
            const orientation = [];
            for (let tex = 0; tex < nbTex; tex++) {
                const pixelData = new Uint8Array(buffer.slice(offset, offset + sizeX * sizeY * 4));
                orientation.push(pixelData);
                offset += sizeX * sizeY * 4;
            }
            orientations.push(orientation);
        }

        return new TextureGroup(sizeX, sizeY, nbTex, orientations);
    }
}

class TextureGroupParser {
    constructor() {
        this.textureGroups = [];
    }

    parseTextureGroups(buffer) {
        const view = new DataView(buffer);
        const nbTexGp = view.getUint16(0, true);

        let offset = 2;
        for (let i = 0; i < nbTexGp; i++) {
            const groupSize = 12 + 8 * view.getUint32(offset + 8, true) * view.getUint32(offset, true) * view.getUint32(offset + 4, true) * 4;
            const groupBuffer = buffer.slice(offset, offset + groupSize);
            this.textureGroups.push(TextureGroup.parse(groupBuffer));
            offset += groupSize;
        }
    }
}

// Exemple d'utilisation
const parser = new TextureGroupParser();
const buffer = new ArrayBuffer(2048); // Simule un buffer contenant des groupes de textures
parser.parseTextureGroups(buffer);
console.log(parser.textureGroups);