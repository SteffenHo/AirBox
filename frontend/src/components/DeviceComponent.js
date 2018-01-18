import ConfigComponent from './ConfigComponent.js';
import createConfig from '../api/createConfig.js';

export default class DeviceComponent {
    constructor(root, device) {
        this.root = root;

        this.onCreate = this.onCreate.bind(this);
        this.update(device);
    }

    onCreate(event) {
        const { id } = this.device;
        const name = window.prompt('Name: ');

        createConfig(id, name).then(() => {
            window.alert('created');
        });
    }

    update(device) {
        this.device = device;

        if(!this.elements) {
            const root = document.createElement('div');
            root.className = 'device';

            const remoteControl = document.createElement('div');
            remoteControl.className = 'remote-control';

            root.appendChild(remoteControl);

            const information = document.createElement('div');
            information.className = 'information';
            remoteControl.appendChild(information);

            const settings = document.createElement('div');
            settings.className = 'information__settings';
            information.appendChild(settings);

            const addButton = document.createElement('div');
            addButton.className = 'information__settings__add';
            addButton.onclick = this.onCreate;
            addButton.innerText = '+';
            settings.appendChild(addButton);

            const nameElement = document.createElement('div');
            nameElement.className = 'information__name';
            information.appendChild(nameElement);

            const controls = document.createElement('div');
            controls.className = 'controls';
            remoteControl.appendChild(controls);

            this.root.appendChild(root);

            this.elements = {
                root,
                remoteControl,
                controls,
                information,
                nameElement,
                settings,
            };
        }

        const { nameElement, controls } = this.elements;

        nameElement.innerText = device.name || '';

        device.configs.forEach((config) => {
            if(!config.handler) {
                config.handler = new ConfigComponent(controls, config);
            }

            config.handler.update(config);
        });
    }
}
