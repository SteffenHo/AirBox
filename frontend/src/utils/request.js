import HttpStatusCodes from '../constants/HttpStatusCodes.js';

/**
 * Requests data from the server
 * @param {String} url - The url of the resource
 * @param {String} [method = GET] - The request method
 * @param {{}|null} [pHeaders = null] - The headers that should be set on the request (object)
 * @param {{}|null} [data = null] - The data that should be send in the body of the request
 * @returns {Promise<Response>} - The response wrapped inside an object
 */
export default function request(url, method = 'GET', pHeaders = null, data = null) {
    const headers = Object.assign({
        'Cache-Control': 'no-cache',
    }, pHeaders);

    const options = {
        method,
        headers,
    };

    if(data) {
        options.body = JSON.stringify(data);
    }

    return fetch(url, options)
        .then(res => {
            if(res.status === HttpStatusCodes.OK) {
                return {
                    body: res.json(),
                };
            }

            return {
                body: res.text(),
            };
        });
}
