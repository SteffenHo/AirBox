import loadConfigs from './api/loadConfigs.js';
import loadDevices from './api/loadDevices.js';

function bootstrap() {
    const test = 'test';
    console.log(test);
    console.log(test);
    console.log(test);



    Promise.all([
        loadDevices(),
        loadConfigs(),
    ]).then((t) => {
        console.log(t);
    });
}

bootstrap();
