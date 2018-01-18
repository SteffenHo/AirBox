import request from '../utils/request.js';

const sendConfig = (id) => request(`http://airbox/devices/configs/${id}/send`, 'POST');
export default sendConfig;
