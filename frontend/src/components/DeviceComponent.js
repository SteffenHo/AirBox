import ConfigComponent from './ConfigComponent.js';

export default class DeviceComponent {
    constructor(root, device) {
        this.root = root;

        this.update(device);
    }

    update(device) {
        if(!this.elements) {
            const root = document.createElement('div');
            root.className = 'device';

            const remoteControl = document.createElement('div');
            remoteControl.className = 'remoteControl';

            root.appendChild(remoteControl);

            const information = document.createElement('div');
            information.className = 'information';
            remoteControl.appendChild(information);

            const controls = document.createElement('div');
            controls.className = 'controls';
            remoteControl.appendChild(controls);

            this.root.appendChild(root);

            this.elements = {
                root,
                remoteControl,
                controls,
                information,
            };
        }

        const { information, controls } = this.elements;

        information.innerText = device.name || '';

        device.configs.forEach((config) => {
            if(!config.handler) {
                config.handler = new ConfigComponent(controls, config);
            }

            config.handler.update(config);
        });
    }
}
