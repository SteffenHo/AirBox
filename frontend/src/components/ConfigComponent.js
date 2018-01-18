export default class ConfigComponent {
    constructor(root, config) {
        this.root = root;

        this.update(config);
    }

    update(config) {
        if(!this.elements) {
            const root = document.createElement('button');
            root.className = 'control-button';

            this.root.appendChild(root);

            this.elements = {
                root,
            };
        }

        const { root } = this.elements;

        root.innerText = config.name;
    }
}
