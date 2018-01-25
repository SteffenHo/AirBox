import loadConfigs from './api/loadConfigs.js';
import loadDevices from './api/loadDevices.js';
import refreshDevices from './components/refreshDevices.js';

let devices = null;

function reloadData() {
    const root = document.querySelector('main.content');
    root.innerHTML = '';

    loadDevices()
        .then((data) => {
            devices = data.body.map((device) => {
                device.configs = [];
                return device;
            });

            refreshDevices(root, devices, reloadData);
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

            refreshDevices(root, devices);
        });
}


reloadData();