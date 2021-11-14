import readline from "readline";
import logger from "npmlog";

export function KeyboardController(player) {
    if (!process.stdin.isTTY) {
        logger.error("keyboard", "Not in a TTY");
        process.exit("-1");
    }

    readline.emitKeypressEvents(process.stdin);
    process.stdin
        .setRawMode(true)
        .on("keypress", (_, key) => handleKeypress(player, key));
}

function handleKeypress(player, key) {
    if (key.name == "c" && key.ctrl) {
        logger.info("keyboard", "Caught CTRL+C");
        player.stop();
        process.exit(0);
    }

    switch (key.name) {
        case 'q':
            player.stop();
            process.exit(0);
            break;
        case 'l':
            logger.info("keyboard", "getting playlist");
            player.getPlaylist();
            break;
        default:
            logger.info("keyboard", `"Unhandled event - ${key.name}" CTRL(${key.ctrl}) SHIFT(${key.shift}) META(${key.meta})`);
    }

}