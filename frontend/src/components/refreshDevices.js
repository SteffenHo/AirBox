import DeviceComponent from './DeviceComponent.js';

export default function refreshDevices(root, deviceList, reloadData) {
    deviceList.forEach((device) => {
        if(!device.handler) {
            device.handler = new DeviceComponent(root, device, reloadData);
        }

        device.handler.update(device);
    });
}