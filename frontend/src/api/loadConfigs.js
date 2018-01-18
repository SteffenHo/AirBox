import request from '../utils/request.js';

const loadConfigs = () => request('http://airbox/devices/configs');
export default loadConfigs;
