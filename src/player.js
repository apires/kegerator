import logger from "npmlog";
import { spawn } from "child_process";
import http from "http";
import { Buffer } from "safe-buffer";

export default function Player(options = {}) {
    const location = options.location ?? "/usr/bin/vlc";
    const host = options.httpHost ?? "0.0.0.0";
    const port = options.httpPort ?? "61136";

    const vlc = spawn(location, ["--intf", "http", "--http-port", port, "--http-host", host, '--http-password', 'LBD']);

    vlc.stdout.on('data', data => logger.info("player", data.toString()));
    vlc.stderr.on('data', data => logger.error("player", data.toString()));
    vlc.on('close', code => logger.critical("player", `Player closed with code ${code}`));

    const c = client(host, port);

    return {

        stop() {
            vlc.kill();
        },
        getPlaylist(done) {
            logger.info("player", "called getting playlist");
            c.getPlaylist(function (err, data) {
                if (err != null) {
                    logger.error("player", `error getting playlist ${error}`);
                    done(err);
                    return;
                }

                logger.info("player", data);
            });
        }


    }
}

function client(host, port) {
    const options = {
        hostname: host,
        port: port,
        method: "GET",
        auth: ":LBD"
    }

    return {
        getPlaylist(done) {
            http.request({ ...options, path: "/requests/playlist.json" }, r => {
                let b = '';
                r.on('data', (chunk) => b += chunk);
                r.on('error', e => logger.error("error!"));
                r.on('end', () => done(null, b));

            }).setTimeout(2000).end();

        }

    }

    function read(stream, done) {
        const b = "";
        stream.on('data', (chunk) => b += chunk);
        stream.on('error', e => logger.error("error!"));
        stream.on('end', () => done(null, b));
    }

}