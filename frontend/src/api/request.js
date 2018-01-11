export default function request(url, method = 'GET', pHeaders = null, data = null) {
    const headers = Object.assign({
        'Cache-Control': 'no-cache',
    }, pHeaders);

    return fetch(url, {
        method,
            headers,
        }).then(res => {
        if(res.statusCode === 200) {
            return res.json();
        }

        return res.text();
    });
}