import loadConfigs from './api/loadConfigs.js';
import loadDevices from './api/loadDevices.js';
import refreshDevices from './components/refreshDevices.js';

function bootstrap() {
    let devices = null;

    loadDevices()
        .then((data) => {
            devices = data.body.map((device) => {
                device.configs = [];
                return device;
            });

            refreshDevices(devices);
        })
        .then(() => {
            return loadConfigs();
        })
        .then((data) => {
            const deviceConfigs = data.body;

            deviceConfigs.forEach((config) => {
                const device = devices.find(d => d.id === config.deviceId);
                device.configs.push(config);
            });

            refreshDevices(devices);
        });
}

bootstrap();
