export default function loadConfigs() {
    return fetch('http://airbox/devices/configs', {
        headers: {
            'Cache-Control': 'no-cache',
        }
    }).then(res => {
        if(res.statusCode === 200) {
            return res.json();
        }

        return res.text();
    });
}
