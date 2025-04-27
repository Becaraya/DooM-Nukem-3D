function bzerooo(obj) {
    for (const key in obj) {
        if (typeof obj[key] === "object" && obj[key] !== null) {
            bzerooo(obj[key]);
        } else {
            obj[key] = 0;
        }
    }
}

function main(args) {
    const al = {};

    bzerooo(al);

    if (args.length === 0) {
        init(al, null, 1);
    } else if (args.length === 1) {
        init(al, args[0], 0);
    } else if (args.length > 1) {
        init(al, null, 1);
        al.map_write_name = args[1];
    }

    mainLoop(al);
}