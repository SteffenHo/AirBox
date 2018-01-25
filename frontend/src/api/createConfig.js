import request from '../utils/request.js';

const createConfig = (deviceId, name) => request('http://airbox/devices/configs', 'POST', null, {
    deviceId,
    name,
}).catch(() => Promise.resolve());
export default createConfig;
