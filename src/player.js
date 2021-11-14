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
        },
        toggleRandom(done) {
            logger.info("player", "toggling random");
            c.toggleRandom(function (err, data) {
                if (err != null) {
                    logger.error("player", `error toggling random ${error}`);
                    done(err);
                    return;
                }
                const { random } = JSON.parse(data);
                done(null, random);
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
            read("/requests/playlist.json", {}, done);
        },
        toggleRandom(done) {
            read("/requests/status.json", { command: "pl_random" }, done);
        }

    }

    function read(base_path, extra, done) {
        let path = base_path;
        if (extra != null) {
            const params = new URLSearchParams(extra);
            path += ("?" + params.toString());
        }

        http.request({ ...options, path }, r => {
            let b = '';
            r.on('data', (chunk) => b += chunk);
            r.on('error', e => logger.error("error!"));
            r.on('end', () => done(null, b));

        }).setTimeout(2000).end();
    }

}