import DeviceComponent from './DeviceComponent.js';

const root = document.querySelector('main.content');

export default function refreshDevices(deviceList) {
    deviceList.forEach((device) => {
        if(!device.handler) {
            device.handler = new DeviceComponent(root, device);
        }

        device.handler.update(device);
    });
}