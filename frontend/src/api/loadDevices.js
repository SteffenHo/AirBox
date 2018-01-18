import request from '../utils/request.js';

const loadDevices = () => request('http://airbox/devices');
export default loadDevices;
