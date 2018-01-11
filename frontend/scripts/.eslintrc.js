module.exports = {
    "env": {
        "node": true,
        "es6": true
    },
    "parser": "babel-eslint",
    "extends": ["eslint:recommended", "plugin:react/recommended"],
    "parserOptions": {
        "sourceType": "module",
        "ecmaVersion": 8,
        "ecmaFeatures": {
            "jsx": true
        },
        "plugins": [
            "react",
            "babel"
        ]
    },
    "rules": {
        "indent": [
            "error",
            4,
            {
                "SwitchCase": 1
            }
        ],
        "quotes": [
            "error",
            "single"
        ],
        "semi": [
            "error",
            "always"
        ],
        "no-console": 0,
        "max-lines": ["error", 250],
        "max-len": ["error", {
            "code": 100
        }],
        "spaced-comment": ["error", "always"],
        "object-curly-spacing": ["error", "always"],
        "key-spacing": ["error", {
            "beforeColon": false
        }],
        "curly": ["error", "all"],
        "no-nested-ternary": ["error"],
        "space-infix-ops": ["error"],
        "prefer-template": ["error"],
        "consistent-return": ["error", {
            "treatUndefinedAsUnspecified": true
        }],
        "no-else-return": ["error"],
        "no-await-in-loop": ["error"],
        "no-prototype-builtins": ["error"],
        "no-template-curly-in-string": ["error"],
        "valid-jsdoc": ["error"],
        "class-methods-use-this": ["error"],
        "no-alert": ["error"],
        "no-empty-function": ["error"],
        "dot-notation": ["error"],
        "eqeqeq": ["error", "always"],
        "no-eval": ["error"],
        "no-extra-bind": ["error"],
        "no-floating-decimal": ["error"],
        "no-implicit-coercion": ["error"],
        "no-implied-eval": ["error"],
        "no-invalid-this": ["error"],
        "no-iterator": ["error"],
        "no-lone-blocks": ["error"],
        "no-magic-numbers": ["error"],
        "no-multi-spaces": ["error"],
        "no-multi-str": ["error"],
        "no-new": ["error"],
        "no-new-wrappers": ["error"],
        "no-octal": ["error"],
        "no-param-reassign": ["error"],
        "no-proto": ["error"],
        "no-restricted-properties": ["error"],
        "no-return-assign": ["error"],
        "no-return-await": ["error"],
        "no-script-url": ["error"],
        "no-self-assign": ["error", {
            "props": true
        }],
        "no-self-compare": ["error"],
        "no-sequences": ["error"]
    }
};
