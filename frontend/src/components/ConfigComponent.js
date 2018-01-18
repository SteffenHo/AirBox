import ConfigComponentBase from './ConfigComponentBase.js';
import sendConfig from '../api/sendConfig.js';

export default class ConfigComponent {
    constructor(root, config) {
        this.root = root;

        this.update(config);
        this.onClick = this.onClick.bind(this);
    }

    onClick() {
        const { id } = this.config;

        sendConfig(id);
    }

    update(config) {
        this.config = config;

        const componentConfig = {
            title: config.name,
            onClick: this.onClick,
        };

        if(!this.baseComponent) {
            this.baseComponent = new ConfigComponentBase(this.root, componentConfig);
        }

        this.baseComponent.update(componentConfig);
    }
}
