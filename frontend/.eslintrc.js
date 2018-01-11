module.exports = {
  "env": {
    "browser": true,
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
    "max-lines": [ "error", 250 ],
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
    "no-sequences": ["error"],
    "no-throw-literal": ["error"],
    "no-unmodified-loop-condition": ["error"],
    "no-unused-expressions": ["error"],
    "no-useless-concat": ["error"],
    "no-useless-return": ["error"],
    "no-with": ["error"],
    "prefer-promise-reject-errors": ["error"],
    "radix": ["error", "always"],
    "require-await": ["error"],
    "yoda": ["error", "never"],
    "no-undefined": ["error"],
    "no-use-before-define": ["error"],
    "array-bracket-newline": ["error", {
      "multiline": true,
      "minItems": 2
    }],
    "array-element-newline": ["error", {
      "multiline": true,
      "minItems": 2
    }],
    "object-curly-newline": ["error", {
      "ObjectExpression": "always",
      "ObjectPattern": {
        "multiline": true
      }
    }],
    "block-spacing": ["error", "always"],
    "brace-style": ["error", "1tbs"],
    "camelcase": ["error", {
      "properties": "always"
    }],
    "comma-dangle": ["error", {
      "arrays": "always-multiline",
      "objects": "always-multiline",
      "imports": "always-multiline",
      "exports": "always-multiline",
    }],
    "comma-spacing": ["error", {
      "before": false,
      "after": true
    }],
    "comma-style": ["error", "last"],
    "computed-property-spacing": ["error", "never"],
    "eol-last": ["error", "always"],
    "func-call-spacing": ["error", "never"],
    "max-depth": ["error", 4],
    "max-statements-per-line": ["error", {
      "max": 1
    }],
    "newline-per-chained-call": ["error", {
      "ignoreChainWithDepth": 2
    }],
    "no-array-constructor": ["error"],
    "no-lonely-if": ["error"],
    "no-mixed-operators": ["error"],
    "no-multi-assign": ["error"],
    "no-trailing-spaces": ["error", {
      "skipBlankLines": true
    }],
    "no-unneeded-ternary": ["error"],
    "no-whitespace-before-property": ["error"],
    "padded-blocks": ["error", "never"],
    "quote-props": ["error", "consistent-as-needed"],
    "require-jsdoc": ["error"],
    "semi-spacing": ["error", {
      "before": false,
      "after": true
    }],
    "semi-style": ["error", "last"],
    "space-before-blocks": ["error"],
    "space-before-function-paren": ["error", "never"],
    "switch-colon-spacing": ["error", {
      "after": true,
      "before": false
    }],
    "wrap-regex": ["error"],
    "constructor-super": ["error"],
    "no-confusing-arrow": ["error", {
      "allowParens": false
    }],
    "no-duplicate-imports": ["error", {
      "includeExports": true
    }],
    "no-useless-computed-key": ["error"],
    "no-useless-constructor": ["error"],
    "no-var": ["error"],
    "prefer-const": ["error"],
    "prefer-rest-params": ["error"],
    "react/jsx-uses-vars": ["error"],
    "react/react-in-jsx-scope": "off",
  }
};
