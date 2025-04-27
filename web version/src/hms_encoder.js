class Entity {
    constructor(posX, posY) {
        this.posX = posX;
        this.posY = posY;
    }

    writeToBuffer() {
        const buffer = new ArrayBuffer(8);
        const view = new DataView(buffer);
        view.setInt32(0, this.posX * 100, true);
        view.setInt32(4, this.posY * 100, true);
        return buffer;
    }
}

class HMS_Encoder {
    constructor() {
        this.entities = [];
    }

    addEntity(entity) {
        this.entities.push(entity);
    }

    writeEntitiesToBuffer() {
        const headerSize = 4;
        const entitySize = 8;
        const buffer = new ArrayBuffer(headerSize + this.entities.length * entitySize);
        const view = new DataView(buffer);

        view.setInt32(0, this.entities.length, true);

        let offset = headerSize;
        this.entities.forEach(entity => {
            const entityBuffer = entity.writeToBuffer();
            new Uint8Array(buffer).set(new Uint8Array(entityBuffer), offset);
            offset += entitySize;
        });

        return buffer;
    }

    encodeToFile(fileName) {
        if (!fileName.endsWith(".hms")) {
            console.error("Invalid extension, provide a .hms file");
            return;
        }

        const entitiesBuffer = this.writeEntitiesToBuffer();
        console.log(`Writing to file: ${fileName}`);
        console.log(entitiesBuffer); // Simule l'écriture dans un fichier
        console.log("Writing success!");
    }
}

// Exemple d'utilisation
const encoder = new HMS_Encoder();
encoder.addEntity(new Entity(10, 20));
encoder.addEntity(new Entity(30, 40));
encoder.encodeToFile("output.hms");