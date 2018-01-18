import ConfigComponent from './ConfigComponent.js';

export default class DeviceComponent {
    constructor(root, device) {
        this.root = root;

        this.update(device);
    }

    update(device) {
        const { createElement } = document;

        if(!this.elements) {
            const root = createElement('div');
            root.className = 'device';

            const remoteControl = createElement('div');
            remoteControl.className = 'remote-control';

            root.appendChild(remoteControl);

            const information = createElement('div');
            information.className = 'information';
            remoteControl.appendChild(information);

            const controls = createElement('div');
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
