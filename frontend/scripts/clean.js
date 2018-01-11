const fs = require('fs');
const path = require('path');

const jsFile = path.join(__dirname, '..', 'src', 'bundle.js');
const cssFile = path.join(__dirname, '..', 'src', 'bundle.css');

fs.unlink(jsFile, (err) => {
    if(err) {
        console.error(err);
    }
});

fs.unlink(cssFile, (err) => {
    if(err) {
        console.error(err);
    }
});
