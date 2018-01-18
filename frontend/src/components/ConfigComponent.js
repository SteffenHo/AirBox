import ConfigComponentBase from './ConfigComponentBase.js';

export default class ConfigComponent {
    constructor(root, config) {
        this.root = root;

        this.update(config);
        this.onClick = this.onClick.bind(this);
    }

    onClick(event) {
        console.log(event);
    }

    update(config) {
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
